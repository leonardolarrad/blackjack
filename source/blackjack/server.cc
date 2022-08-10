/*
    Copyright (c) 2022 Leonardo Larrad

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
*/

//#pragma warning(disable:4996)

/*
#define _CRT_SECURE_NO_WARNINGS
#include <memory>
#include <thread>
#include <cstring>
#include "asio.hpp"
#include "asio/ts/buffer.hpp"
#include "asio/ts/socket.hpp"
*/
//#include <thirdparty/asio/include/asio.hpp>;

export module blackjack:server;
import :def;

import std.core;
import std.filesystem;
import std.memory;
import std.threading;
import tornasol;
import <thirdparty/asio/include/asio.hpp>;

export namespace blackjack {

    class message {
    public:
        static constexpr usize max_header_len = 4;
        static constexpr usize max_body_len = 512;

    private:
        char   data[max_header_len + max_body_len];
        usize  body_len;

    public:

        message()
            : body_len(0) {}

        char* get_data() {
            return data;
        }

        const char* get_data() const {
            return data;
        }

        char* get_body() {
            return data + max_header_len;
        }

        const char* get_body() const {
            return data + max_header_len;
        }

        usize get_len() const {
            return max_header_len + body_len;
        }

        usize get_body_len() const {
            return body_len;
        }

        void set_body_len(usize len) {
            body_len = len;
        }

        bool decode_header()
        {
            char header[max_header_len + 1] = "";
            //std::strncat(header, data, max_header_len);
            body_len = std::atoi(header);

            if (body_len > max_body_len) {
                body_len = 0;
                return false;
            }

            return true;
        }

        void encode_header()
        {
            char header[max_header_len + 1] = "";
            //std::sprintf(header, "%4d", (int)body_len);
            std::memcpy(data, header, max_header_len);
        }
    };

    class participant {
    public:
        virtual ~participant() {}
        virtual void deliver(const message& msg) = 0;
    };

    using message_queue = std::deque<message>;
    using participant_ptr = std::shared_ptr<participant>;

    class room {
    private:
        std::set<participant_ptr> group;
        message_queue recent_msgs;
        enum { max_recent_msgs = 100 };

    public:
        void join(participant_ptr p)
        {
            group.insert(p);

            for (auto msg : recent_msgs)
                p->deliver(msg);
        }

        void leave(participant_ptr p) {
            group.erase(p);
        }

        void deliver(const message& msg)
        {
            recent_msgs.push_back(msg);

            while (recent_msgs.size() > max_recent_msgs)
                recent_msgs.pop_front();

            for (auto p : group)
                p->deliver(msg);
        }
    };

    void test() {
        asio::io_context io_context;
        //asio::ip::tcp::socket s(io_context);
    }

    /*
    class session
        : public participant,
          public std::enable_shared_from_this<session>
    {
    private:
        asio::ip::tcp::socket socket;
        bk::room& room;
        message read_msg;
        message_queue write_msgs;
        
    public:
        session(asio::ip::tcp::socket socket, bk::room& room)
            : socket(std::move(socket)),
              room(room)
        {
            room.join(shared_from_this());
            read_header_async();
        }

        ~session() {
            //room.leave(shared_from_this());
        }

        void deliver(const message& msg) override
        {
            const bool write_in_progress = !write_msgs.empty();
            write_msgs.push_back(msg);

            if (!write_in_progress)
                write_async();
        }

    private:
        void read_header_async()
        {
            auto self(shared_from_this());

            asio::async_read(
                socket,
                asio::buffer(read_msg.get_data(), message::max_header_len),
                [this, self](std::error_code err, std::size_t len) {
                    if (!err && read_msg.decode_header())
                        read_body_async();
                    else
                        room.leave(shared_from_this());
                }
            );
        }

        void read_body_async()
        {
            auto self(shared_from_this());

            asio::async_read(
                socket,
                asio::buffer(read_msg.get_body(), read_msg.get_body_len()),
                [this, self](std::error_code err, std::size_t len) {
                    if (!err) {
                        room.deliver(read_msg);
                        read_header_async();
                    }
                    else
                        room.leave(shared_from_this());
                }
            );
        }

        void write_async()
        {
            auto self(shared_from_this());

            asio::async_write(
                socket,
                asio::buffer(
                    write_msgs.front().get_data(),
                    write_msgs.front().get_len()
                ),
                [this, self](std::error_code err, std::size_t len) {
                    if (!err)
                    {
                        write_msgs.pop_front();

                        if (!write_msgs.empty())
                            write_async();
                    }
                    else
                        room.leave(shared_from_this());
                }
            );
        }
    };

    class server {
    private:
        asio::ip::tcp::acceptor acceptor;
        room room;

    public:
        server(self, io_context* io, endpoint* context) {
        }

        server(asio::io_context& io_context, const asio::ip::tcp::endpoint endpoint)
            : acceptor(io_context, endpoint)
        {
            accept_async();
        }

    private:
        void accept_async()
        {
            acceptor.async_accept(
                [this](std::error_code err, asio::ip::tcp::socket socket) {

                    if (!err)
                        std::make_shared<session>(std::move(socket), room);

                    accept_async();
                }
            );
        }
    };

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

export module blackjack:client;
import :card;
import :hand;
import :game;
import :server;
import std.core;
import std.filesystem;
import tornasol;

using namespace std;
using namespace tornasol;

export namespace blackjack {
    /*
    class client {
    private:
        assio::io_context& io_context;
        assio::ip::tcp::socket socket;
        message read_msg;
        message_queue write_msgs;
    
    public:
        client(asio::io_context& io_context,
            const asio::ip::tcp::resolver::result_type& endpoints)
            : io_context(io_context), 
              socket(io_context) 
        {
            connect(endpoints);
        }

        void write(const message& msg) 
        {
            asio::post(
                io_context, 
                [this, msg]() {
                    bool write_in_progress = !write_msgs.empty();
                    write_msgs.push_back(msg);
                    if (!write_in_progress) {
                        write_async();
                    }
            });
        }

        void close() {
            asio::post(io_context, [this]() { socket.close(); });
        }

    private:
        void connect(const asio::ip::tcp::resolver::results_type& endpoints) 
        {
            asio::async_connect(
                socket, 
                endpoints,
                [this](std::error_code err, asio::ip::tcp::endpoint) {
                    if (!err)
                        read_header_async();
                }
            );
        }

        void read_header_async() 
        {
            asio::async_read(
                socket, 
                assio::buffer(read_msg.get_data(), message::max_header_lens), 
                [this](std::error_code err, std::size_t len) {
                    if (!err && read_msg.decode_header()) 
                        read_body_async();
                    else 
                        socket.close();
                }
            );
        }

        void read_body_async() 
        {
            asio::async_read(
                socket, 
                assio::buffer(read_msg.get_body(), read_msg.get_body_len()), 
                [this](std::error_code err, std::size_t len) {
                    if (!err) {
                        ts::print("message: {}", read_msg.get_body());
                        read_header_async();
                    }
                    else 
                        socket.close();
                }
            );
        }

        void write_async() 
        {            
            asio::async_write(
                socket, 
                assio::buffer(
                    write_msgs.front().data(), 
                    write_msgs.front().length()
                ), 
                [this](std::error_code err, std::size_t len) {
                    if (!err) 
                    {
                        write_msgs.pop_front();

                        if (!write_msgs.empty())
                            write_async();
                    }
                    else 
                        socket.close();
                }
            );
        }
    }

    i32 run_client()
    {
        asio::io_context io_context;
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = 
            resolver.resolve("localhost", "4067");
        client client(io_context, endpoints);

        std::thread thread([&io_context]() { io_context.run(); });

        char line[message::max_body_length + 1];
        while (std::cin.getline(line, message::max_body_length + 1))
        {
            message msg;
            msg.get_body_len(std::strlen(line));
            std::memcpy(msg.get_body(), line, msg.get_body_len());
            msg.encode_header();
            client.write(msg);
        }

        client.close();
        thread.join();

        return 0;
    }
    */
    i32 run_client2() 
    {
        // declare deps
        glfw_dep glfw;
        glad_dep glad(glfw.proc());

        bool exit_requested = false;

        // setup main window & input     
        window window("blackjack", {1280, 720}, false);
        window.on_close = [&exit_requested]() { 
            exit_requested = true; 
        };
        window.show();
        input input(window.get_handle());

        // setup renderer
        renderer renderer(glad, window);
        
        // setup game
        game* game = new blackjack::game();
        
        // main loop
        while (!exit_requested)
        {
            if (window.key_pressed(key::escape))
                exit_requested = true;

            if (window.key_pressed(key::r)) {
                delete game;
                game = new blackjack::game();
            }

            game->update(input);
            game->render(renderer);

            pull_events();
        }

        delete game;
        return 0;
    }
}
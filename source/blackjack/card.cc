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

export module blackjack:card;
import std.core;
import std.filesystem;
import tornasol;

using namespace std;
using namespace tornasol;

namespace fs = std::filesystem;

export namespace blackjack {

    enum class card_suit : u8
    {
        back     = 0, // 🂠
        clubs    = 1, // ♣
        diamonds = 2, // ♦
        hearts   = 3, // ♥
        spades   = 4, // ♠
        joker    = 5, // 🂿
    };

    string suit_name(card_suit suit) {
        switch (suit) {
            case card_suit::back:     return "back";
            case card_suit::clubs:    return "clubs";
            case card_suit::diamonds: return "diamonds";
            case card_suit::hearts:   return "hearts";
            case card_suit::spades:   return "spades";  
            case card_suit::joker:    return "joker";
            default:                  return "unknown";
        }
    }

    string suit_pip(card_suit suit) {
        switch (suit) {
            case card_suit::back:     return "🂠";
            case card_suit::clubs:    return "♣";
            case card_suit::diamonds: return "♦";
            case card_suit::hearts:   return "♥";
            case card_suit::spades:   return "♠";
            case card_suit::joker:    return "🂿";
            default:                  return "?";
        }
    }

    class card : public entity {
    private:
        texture_renderer tex;
        u8 num;
        card_suit suit;
        
    public:
        card(u8 num, card_suit suit)
            : num(num), suit(suit)
        {
            string tmp = to_string(num) + suit_name(suit)[0];
            wstring card_name(tmp.begin(), tmp.end());
            fs::path path(L"./content/cards/" + card_name + L".png");

            image image(path);

            tex.set_rect({ (f32)image.width, (f32)image.height });
            tex.set_image(image);

            trans.sca = { 0.80f, 0.80f, 0.80f };
            tex.set_model(trans.get_mat());
        }

        // non-default-constructible
        card() = delete;

        // non-copyable
        card(const card& other) = delete;
        card& operator=(const card& other) = delete;

        // movable
        card(card&& other)
            : entity(move(other))
            , tex(move(other.tex))
            , num(other.num)
            , suit(other.suit)
        {
        }

        card& operator = (card&& other) 
        {
            entity::operator=(move(other));
            tex = move(other.tex);
            num = other.num;
            suit = other.suit;
            return *this;
        }

        u8 get_num() const {
            return num;
        }

        card_suit get_suit() const { 
            return suit; 
        }

        i32 get_value() const 
        {
            if (suit == card_suit::back || suit == card_suit::joker)
                return 0;

            if (num > 10) 
                return 10;

            if (num == 1) 
                return 11;

            return num;
        }

        void render(renderer& renderer) override 
        {
            if (!enable) 
                return;
            
            tex.set_model(trans.get_mat());
            renderer.render(tex);
        }       
    };
}
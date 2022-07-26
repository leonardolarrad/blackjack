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

export namespace blackjack {

    enum class card_suit 
    {
        clubs    = 1, // ♣
        diamonds = 2, // ♦
        hearts   = 3, // ♥
        spades   = 4  // ♠
    };

    string suit_name(card_suit suit)
    {
        switch (suit) {
            case card_suit::clubs:    return "clubs";
            case card_suit::diamonds: return "diamonds";
            case card_suit::hearts:   return "hearts";
            case card_suit::spades:   return "spades";
            default:                  return "";
        }
    }

    string suit_pip(card_suit suit) 
    {
        switch (suit) {
            case card_suit::clubs:    return "♣";
            case card_suit::diamonds: return "♦";
            case card_suit::hearts:   return "♥";
            case card_suit::spades:   return "♠";
            default:                  return "";
        }
    }

    class card : public entity {
    private:
        texture_renderer tex;

        card_suit suit;
        u8 number;
        
    public:
        card(card_suit suit, number number)) {
            
        }

        void update(const input& input) override
        {
            input.get_last_time()
            input.get_curr_time() 
            f32 d = input.get_delta();
        }

        void render() override {
            texture.render();
        }
        
        render_graph render() {
            return tex.render();
        }
    };
}
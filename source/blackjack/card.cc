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
namespace fs = std::filesystem;
using namespace tornasol;

export namespace blackjack {

    enum class card_suit 
    {
        back     = 0, // 🂠
        clubs    = 1, // ♣
        diamonds = 2, // ♦
        hearts   = 3, // ♥
        spades   = 4  // ♠
    };

    string suit_name(card_suit suit)
    {
        switch (suit) {
            case card_suit::back:     return "back";
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
            case card_suit::back:     return "🂠";
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
        card(card_suit suit, u8 number) 
            : suit(suit), number(number)
        {
            string tmp = suit_name(suit)[0] + to_string(number);
            wstring card_name(tmp.begin(), tmp.end());
            fs::path path(L"./content/cards/" + card_name + L".png");

            image image(path);

            tex.load_rect({ (f32)image.width, (f32)image.height });
            tex.load_image(image);

            transform.sca = { 0.75f, 0.75f, 0.75f };
            tex.set_model(transform.get_matrix());
        }

        void update(const input& input) override {
            // pass
        }

        void render(renderer& renderer) override {
            renderer.render(tex);
        }
        
    };
}
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

export module blackjack:hand;
import std.core;
import tornasol;
import :card;
using namespace std;
using namespace tornasol;

export namespace blackjack { 

    class hand : public entity {
    private:
        // place_holder ?? 
        vector<card> cards;

    public:            
        void arrange() 
        {
            random_device dev;
            mt19937 rng(dev());
            uniform_real_distribution<f32> degress(0.0f, 0.5f);
            uniform_int_distribution<u32> x(0, 10);
            uniform_int_distribution<u32> y(0, 5);
                        
            const vec3<> pivot = trans.pos;

            for (i32 i = 0; i < cards.size(); ++i) 
            {
                auto& c = cards[i];

                c.trans.pos.x = pivot.x + (50 * i) + x(rng);
                c.trans.pos.y = pivot.y + y(rng);
                c.trans.rot.z = -degress(rng) * (f32)numbers::pi/180.0f;
            }                
        }

        void add_card(u8 num, card_suit suit) 
        {
            cards.emplace_back(num, suit);
            arrange();
        }

        void remove_card(u8 num, card_suit suit) 
        {
            //for (auto it = cards.begin(); it != cards.end(); ++it) 
            //   if (it->get_num() == num && it->get_suit() == suit) {
            //      cards.erase(it); break;
            //   }         
        }

        i32 get_size() const { 
            return cards.size(); 
        }

        i32 get_value() const 
        {
            i32 value = 0;         
            for (const auto& c : cards) 
            value += c.get_value();    

            return value;
        }

        bool is_blackjack() const {
            return cards.size() == 2 && get_value() == 21;
        }

        bool is_bust() const {
            return get_value() > 21;
        }

        void render(renderer& renderer) override 
        {
            for (auto& c : cards)
            c.render(renderer);
        }
    };

}
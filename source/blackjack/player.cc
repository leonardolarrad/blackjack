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

export module blackjack:player;

import :button;
import :card;
import :hand;
import :image;

import std.core;
import std.filesystem;
import tornasol;

using namespace std;
using namespace std::filesystem;
using namespace tornasol;

export namespace blackjack {

    enum class player_state
    {
        idle,
		wait,
		play,
        win,
        lose,
		push,
		bust,
		blackjack
    };

    enum class player_action 
	{
		none,
		hit,
		stand
	};

    class player : public entity {
    protected:
        u8 num;
        bool curr;
        // state
        player_state state;
        // images
        ui_image label;
        ui_image placeholder;
        ui_image decor;
        ui_image busted;
        ui_image state_label;
        // buttons
        ui_button hit_button;
        ui_button stand_button;

    public:
        hand hand;

        player(u8 num, bool curr = false)
            : num(num), curr(curr), state(player_state::idle)
        {
            wstring label_str = L"player_" + to_wstring(num);

            if (curr) {
                label.set_image(
                    path(L"./content/player/player_you.png"));

                hit_button.on_click = [this]() { hit(); };
                stand_button.on_click = [this]() { stand(); };
            }                
            else {
                label.set_image(
                    path(L"./content/player/" + label_str + L".png"));

                hit_button.enable = false;
                stand_button.enable = false;
            }                

            placeholder.set_image(
                path(L"./content/player/placeholder.png"));
            decor.set_image(
                path(L"./content/player/decor.png"));
            busted.set_image(
                path(L"./content/player/busted.png"));
            hit_button.set_image(
                path(L"./content/player/hit.png"), 
                path(L"./content/player/hit_hover.png"));
            stand_button.set_image(
                path(L"./content/player/stand.png"), 
                path(L"./content/player/stand_hover.png"));            
        }

        player_state get_state() const {
            return state;
        }

        void set_state(player_state state) 
        {            
            this->state = state;
            hit_button.enable = state == player_state::play;
            stand_button.enable = state == player_state::play;

            switch (state) {
            case player_state::win:
                state_label.set_image(path(L"./content/player/win.png"));
                state_label.enable = true;
                break;
            case player_state::lose:
                state_label.set_image(path(L"./content/player/lose.png"));
                state_label.enable = true;
                break;
            case player_state::push:
                state_label.set_image(path(L"./content/player/tie.png"));
                state_label.enable = true;
                break;
		    case player_state::blackjack:
			    state_label.set_image(path(L"./content/player/blackjack.png"));
			    state_label.enable = true;
			    break;
			case player_state::bust:
				state_label.set_image(path(L"./content/player/bust.png"));
				state_label.enable = true;
				break;
            default: 
                state_label.enable = false;
            }
        }

        blackjack::hand& get_hand(){
            return hand;
        }

        void add_card(u8 num, card_suit suit)
        {
            hand.trans.pos = trans.pos + vec3<>{ -15.f, 52.f, 0.0f};
            hand.add_card(num, suit);

            if (hand.is_blackjack())
                set_state(player_state::blackjack);
            else if (hand.is_busted())
                set_state(player_state::bust);
        }

        void hit() {
            // pass
            print("hit");
        }

        void stand() {
            // pass
            print("stand");
        }

        void update(const input & in) override
        {
            if (!enable)
                return;

            hit_button.update(in);
            stand_button.update(in);
        }

        void render(renderer & renderer) override
        {
            if (!enable)
                return;

            vec3<> p = trans.pos;

            label.trans.pos = p;    
            label.render(renderer);
            
            placeholder.trans.pos = p + vec3<>{0.0f, 52.f, 0.0f};
            placeholder.render(renderer);

            state_label.trans.pos = p + vec3<>{-5.f, 312.f, 0.f};
            state_label.render(renderer);
            
            hand.trans.pos = p + vec3<>{ -15.f, 52.f, 0.0f};
            hand.render(renderer);
            
            hit_button.trans.pos = p + vec3<>{-5.f, 330.f, 0.0f};
            hit_button.render(renderer);
            
            stand_button.trans.pos = p + vec3<>{91.f, 330.f, 0.0f};
            stand_button.render(renderer);

            if (state == player_state::bust)
            {
                busted.trans.pos = p + vec3<>{-50.f, 65.f, 0.f};
                busted.render(renderer);
            }
            else if (state == player_state::blackjack) 
            {
                decor.trans.pos = p + vec3<>{-55.0f, 100.0f, 0.0f};
                decor.render(renderer);
            }               

            
        }
    };
}

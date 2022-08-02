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

    class player : public entity {
    private:
        u8 num;
        bool curr;
        ui_image label;
        ui_image placeholder;
        ui_button hit_button;
        ui_button stand_button;

    public:
        hand hand;

        player(u8 num, bool curr = false)
            : num(num), curr(curr)
        {
            wstring label_str = L"player_" + to_wstring(num);

            if (curr)
                label.set_image(
                    path(L"./content/player/player_you.png"));
            else 
                label.set_image(
                    path(L"./content/player/" + label_str + L".png"));

            placeholder.set_image(
                path(L"./content/player/placeholder.png"));
            hit_button.set_image(
                path(L"./content/player/hit.png"), 
                path(L"./content/player/hit_hover.png"));
            stand_button.set_image(
                path(L"./content/player/stand.png"), 
                path(L"./content/player/stand_hover.png"));
            
            hit_button.on_click = [this]() { hit(); };
            stand_button.on_click = [this]() { stand(); };
        }

        void hit() {
            // pass
        }

        void stand() {
            // pass
        }

        void update(const input & in) override
        {
            if (!enable || !curr)
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
            placeholder.trans.pos = p + vec3<>{0.0f, 52.f, 0.0f};
            hand.trans.pos = p + vec3<>{ -15.f, 52.f, 0.0f};
            

            label.render(renderer);
            placeholder.render(renderer);
            hand.render(renderer);

            if (curr) {
                hit_button.trans.pos = p + vec3<>{-5.f, 330.f, 0.0f};
                stand_button.trans.pos = p + vec3<>{91.f, 330.f, 0.0f};

                hit_button.render(renderer);
                stand_button.render(renderer);
            }
        }
    };
}

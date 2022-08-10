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

export module blackjack:game;

import :button;
import :hand;
import :card;
import :dealer;
import :player;
import std.core;
import std.filesystem;
import tornasol;

using namespace std;
using namespace std::filesystem;
using namespace tornasol;

export namespace blackjack {

    class game {
    private:
        // components
        color bg_color;
        texture_renderer bg; // background
        texture_renderer ls; // loading screen
        vector<player> players;
        dealer dea;

        // rng
        random_device dev;
        mt19937 rng;

    public:
        game()
            : rng(dev())
        {
            // setup game background
            image bg_img = image(path(L"./content/game/background.png"));
            image ls_img = image(path(L"./content/game/loading_screen.png"));

            bg_color = 0x095b43ff;
            bg.set_rect({ (f32)bg_img.width, (f32)bg_img.height });
            bg.set_image(bg_img);

            ls.set_rect({ (f32)ls_img.width, (f32)ls_img.height });
            ls.set_image(ls_img);

            // setup players
            players.emplace_back(1);
            players.emplace_back(2);
            players.emplace_back(3, true);
            players.emplace_back(4);

            uniform_int_distribution<u32> num_dist(1, 12);
            uniform_int_distribution<u32> suit_dist(1, 4);

            for (i32 i = 0; i < 4; ++i)
            {
                auto& p = players[i];

                p.trans.pos = vec3<>{ 70, 325, 0 } + f32(i) * vec3<>{320, 0, 0};
                
                p.add_card(num_dist(rng), (card_suit)suit_dist(rng));
                p.add_card(num_dist(rng), (card_suit)suit_dist(rng));
            }

            // setup dealer
            dea.trans.pos = { 560.0f, -40.0f, 0.0f };
            //dea.add_card(num_dist(rng), (card_suit)suit_dist(rng));
            //dea.add_card(num_dist(rng), (card_suit)suit_dist(rng));
            //dea.add_card(3, card_suit::back);
            dea.add_card(1,  (card_suit)suit_dist(rng));
            dea.add_card(1,  (card_suit)suit_dist(rng));
            dea.add_card(4,  (card_suit)suit_dist(rng));
            dea.add_card(10, (card_suit)suit_dist(rng));
            dea.add_card(1,  (card_suit)suit_dist(rng));
            
        }

        void update(const input& in)
        {
            for (auto& p : players)
                p.update(in);
        }

        void render(renderer& renderer)
        {   
            // render background
            renderer.clear(bg_color);
            renderer.render(bg);

            // render dealer & players            
            for (auto& p : players)
                p.render(renderer);

            dea.render(renderer);

            // present
            renderer.present();
        }
    };
}
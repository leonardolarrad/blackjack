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
import std.core;
import std.filesystem;
import tornasol;

using namespace std;
using namespace tornasol;

export namespace blackjack {

    i32 run_client() 
    {
        // declare deps
        glfw_dep glfw;
        glad_dep glad(glfw.proc());

        bool exit_requested = false;
        const color background = 0x003322ff;

        // setup main window & input     
        window window("blackjack", {1280, 720}, false);
        window.on_close = [&exit_requested]() { 
            exit_requested = true; 
        };
        window.show();
        input input(window.get_handle());

        // setup renderer
        renderer renderer(glad, window);
        
        // setup pseudo-random number generator        
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<u32> num_dist(1, 12);
        uniform_int_distribution<u32> suit_dist(1, 4);

        hand npc_hand;
        hand player_hand_1;
        hand player_hand_2;
        hand player_hand_3;
        hand player_hand_4;
    
        npc_hand.trans.pos = { 560.0f, 50.0f, 0.0f };
        player_hand_1.trans.pos = { 30.0f, 390.0f, 0.0f };
        player_hand_2.trans.pos = { 370.0f, 390.0f, 0.0f };
        player_hand_3.trans.pos = { 680.0f, 390.0f, 0.0f };
        player_hand_4.trans.pos = { 1000.0f, 390.0f, 0.0f };

        npc_hand.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        npc_hand.add_card(2, card_suit::back);

        player_hand_1.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        player_hand_1.add_card(num_dist(rng), (card_suit)suit_dist(rng));

        player_hand_2.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        player_hand_2.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        
        player_hand_3.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        player_hand_3.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        
        player_hand_4.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        player_hand_4.add_card(num_dist(rng), (card_suit)suit_dist(rng));
        

        //player_hand2.trans.pos.x = 500;
        //player_hand2.add_card(num_dist(rng), (card_suit)suit_dist(rng));

        // main loop
        while (!exit_requested)
        {
            if (window.key_pressed(key::escape))
                exit_requested = true;

            renderer.clear(background);

            npc_hand.render(renderer);
            player_hand_1.render(renderer);
            player_hand_2.render(renderer);
            player_hand_3.render(renderer);
            player_hand_4.render(renderer);

            window.swap_buffers();
            pull_events();
        }

        return 0;
    }
}
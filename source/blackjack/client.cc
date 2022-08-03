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
        vec3<> v = { 1, 2, 3 };
        
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
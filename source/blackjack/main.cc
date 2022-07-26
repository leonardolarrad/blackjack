/*
    Copyright (c) 2020-2022 Leonardo Larrad

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

import std.core;
import std.filesystem;
import tornasol;

using namespace std;
using namespace tornasol;
namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    // declare deps
    glfw_dep glfw;
    glad_dep glad(glfw.proc());

    bool exit_requested = false;

    // setup main window
    window win("blackjack", {1280, 720}, false);
    win.on_close = [&exit_requested]() { 
        exit_requested = true; 
    };
    win.show();

    // setup renderer
    renderer renderer(glad, win);
    renderer.set_clear_color(0x003322FF);

    image img0(fs::path(L"./content/cards/ah.png"));  
    image img1(fs::path(L"./content/cards/1b.png"));
    print("exe path: {}", fs::current_path().string());

    const auto to_radians = [](f32 angle) {
        return (angle * 3.14159265358979323846f) / 180.0f;
    };

    const f32 pi_4 = 3.14159265358979323846f * 0.5f;
    
    mat4<> transform = mat4<>(1.0f);
    
    move(transform, { 600.0f, 200.0f, 0.0f });
    scale(transform, { 0.75f, 0.75f, 0.0f });
    rotate(transform, to_radians(-5.0f), { 0.0f, 0.0f, 1.0f });

    mesh_renderer ah = mesh_renderer(img1);
    mesh_renderer b1 = mesh_renderer(img0);
    ah.set_transform(transform);
    
    renderer.add_mesh(ah);
    renderer.add_mesh(b1);

    f32 v = 100.0;
    f32 lf = 0.0;
    f32 cf = 0.0;
    f32 d = 0.0;

    // main loop
    while (!exit_requested)
    {
        if (win.key_pressed(key::escape))
            exit_requested = true;

        cf = get_time();
        d = cf - lf;
        lf = cf;

        v = 1000.0 * d;

        if (win.key_pressed(key::right))
            move(transform, { +v, 0.0f, 0.0f });

        if (win.key_pressed(key::left))
            move(transform, { -v, 0.0f, 0.0f });

        if (win.key_pressed(key::down))
            move(transform, { 0.0, +v, 0.0f });

        if (win.key_pressed(key::up))
            move(transform, { 0.0, -v, 0.0f });
        
        if (win.key_pressed(key::space))
            rotate(transform, to_radians(30.0f) * d, { 0.0f, 0.0f, 1.0f });
        
        ah.set_transform(transform);
        renderer.next_frame();
        pull_events();
    }

    // cleanup and exit
    return 0;
}
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

export module blackjack:button;

import std.core;
import std.filesystem;
import tornasol;

using namespace std;
namespace fs = std::filesystem;
using namespace std::filesystem;
using namespace tornasol;

export namespace blackjack {

    enum class button_state 
    {
        idle,
        hover,
        pressed,    
    };

    class ui_button : public entity {
    private:
        texture_renderer idle_tex;
        texture_renderer hover_tex;
        rect<> hitbox;
        button_state state;
    public:
        function<void()> on_click;
        function<void()> on_hover;

        ui_button() 
            : state(button_state::idle) {}

        button_state get_state() const { 
            return state; 
        }

        void set_image(path idle_path, path hover_path)
        {
            image idle_img = image(idle_path);
            image hover_img = image(hover_path);

            const f32 w = (f32)idle_img.width;
            const f32 h = (f32)idle_img.height;

            hitbox = { w, h };

            idle_tex.set_rect({ 0.0f, 0.0f, w, h });
            idle_tex.set_image(idle_img);

            hover_tex.set_rect({ 0.0f, 0.0f, w, h });
            hover_tex.set_image(hover_img);
        }

        void update(const input& in) override 
        {
            if (!enable) 
                return;
            
            hitbox = { 
                trans.pos.x, trans.pos.y, 
                hitbox.w, hitbox.h 
            };

            if (in.mouse_pressed(mouse_button::left) 
                && hitbox.contains(in.cursor_pos())) 
            {        
                state = button_state::pressed;
            } 
            else if (hitbox.contains(in.cursor_pos()))                
                state = button_state::hover;
            else
                state = button_state::idle;
            
            if (on_click && state == button_state::pressed)
                on_click();

            if (on_hover && state == button_state::hover)
                on_hover();
        }

        void render(renderer& r) override 
        {
            if (!enable) 
                return;
            
            idle_tex.set_model(trans.get_mat());
            hover_tex.set_model(trans.get_mat());

            switch (state) {
            case button_state::idle:
                r.render(idle_tex);
                break;
            case button_state::hover:
                r.render(hover_tex);
                break;
            case button_state::pressed:
                r.render(hover_tex);
                break;
            }
        }
    };
}
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

export module tornasol:input;
import :types;
import :glfw;
import :vector;

export namespace tornasol 
{
    using key            = glfw::key;
    using key_mod        = glfw::key_mod;
    using key_action     = glfw::input_action;
    using mouse_button   = glfw::mouse_button;
    using mouse_action   = glfw::input_action;
    using cursor_mode    = glfw::cursor_mode;
    using cursor_standar = glfw::cursor_standar;

    class input 
    {
    private:
        glfw::window_handle handle;

    public:
        input(glfw::window_handle handle) 
            : handle(handle) {}

        glfw::window_handle get_handle() {
            return handle;
        }
        
        bool key_pressed(key key) {
            return glfw::get_key(handle, key) == key_action::press;
        }

        bool key_released(key key) {
            return glfw::get_key(handle, key) == key_action::release;
        }

        bool mouse_pressed(mouse_button button) 
        {
            return glfw::get_mouse_button(handle, button) 
                == mouse_action::press;
        }

        bool mouse_released(mouse_button button) 
        {
            return glfw::get_mouse_button(handle, button) 
                == mouse_action::release;
        }

        vec2<> get_cursor_pos() 
        {
            f64 x, y;
            glfw::get_cursor_pos(handle, &x, &y);
            return vec2<>((f32)x, (f32)y);
        }
    };
    
    void pull_events() { 
        glfw::poll_events(); 
    }

    void wait_events() {         
        glfw::wait_events(); 
    }

    void wait_events_timeout(f64 timeout) {
        glfw::wait_events_timeout(timeout);
    }

    void post_empty_event() {
        glfw::post_empty_event();
    }

    f32 get_time() {
        return glfw::get_time();
    }
}
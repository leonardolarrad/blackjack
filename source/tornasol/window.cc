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

export module tornasol:window;
import :glfw;
import :input;
import :size;
import :types;
import :vector;

import std.core;
using namespace std;

export namespace tornasol 
{
    class window
    {
    private:
        glfw::window_handle handle;

    public:
        function<void(vec2<i32>)>     on_move;
        function<void(size2<i32>)>    on_resize;
        function<void(void)>          on_close;
        function<void(void)>          on_minimize;
        function<void(void)>          on_maximize;
        function<void()>              on_focus;
        function<void()>              on_blur;
        function<void()>              on_refresh;
        function<void(vec2<>)>        on_cursor_move;
        function<void()>              on_cursor_enter;
        function<void()>              on_cursor_leave;
        function<void(vec2<>)>        on_scroll;
        function<void(mouse_button, 
           mouse_action, key_mod)>    on_mouse_button;
        function<void(key, i32, 
           key_action, key_mod)>      on_key;
        function<void(u32)>           on_char;
        function<void(u32, key_mod)>  on_char_mods;
        function<void(size2<>)>       on_framebuffer_resize;

        window(string_view title, size2<> size, bool resizable = true)
        {
            glfw::window_hint(glfw::attribute::context_ver_major, 4);
            glfw::window_hint(glfw::attribute::context_ver_minor, 0);
            glfw::window_hint(glfw::attribute::gl_profile, 
                (int) glfw::gl_profile::core);
            glfw::window_hint(glfw::attribute::visible, false);
            glfw::window_hint(glfw::attribute::resizable, resizable);
            glfw::window_hint(glfw::attribute::samples, 4);

            handle = glfw::create_window(size.w, size.h,
                title.data(), nullptr, nullptr);

            glfw::set_window_user_pointer(handle, this);
            glfw::set_window_pos_callback(handle, move_callback);
            glfw::set_window_size_callback(handle, resize_callback);
            glfw::set_window_close_callback(handle, close_callback);
            glfw::set_window_iconify_callback(handle, minimize_callback);
            glfw::set_window_maximize_callback(handle, maximize_callback);
            glfw::set_window_focus_callback(handle, focus_callback);
            glfw::set_window_refresh_callback(handle, refresh_callback);
            glfw::set_cursor_pos_callback(handle, cursor_move_callback);
            glfw::set_cursor_enter_callback(handle, cursor_enter_callback);
            glfw::set_scroll_callback(handle, scroll_callback);
            glfw::set_mouse_button_callback(handle, mouse_button_callback);
            glfw::set_key_callback(handle, key_callback);
            glfw::set_char_callback(handle, char_callback);
            glfw::set_char_mods_callback(handle, char_mods_callback);
            glfw::set_window_framebuffer_size_callback(handle, 
                framebuffer_resize_callback);            
        }

        ~window() {
            glfw::destroy_window(handle);
        }

        window(const window&) = delete;
        window& operator=(const window&) = delete;

        glfw::window_handle get_handle() const {
            return handle;
        }

        void show() {
            glfw::show_window(handle);
        }

        void hide() {
            glfw::hide_window(handle);
        }

        void close() {
            glfw::set_window_should_close(handle, true);
            glfw::destroy_window(handle);
        }

        void maximize() {
            glfw::maximize_window(handle);
        }

        void minimize() {
            glfw::iconify_window(handle);
        }

        void restore() {
            glfw::restore_window(handle);
        }

        void request_focus() {
            glfw::focus_window(handle);
        }

        vec2<i32> get_pos() const 
        {
            vec2<i32> pos;
            glfw::get_window_pos(handle, &pos.x, &pos.y);
            return pos;
        }

        void set_pos(vec2<i32> pos) {
            glfw::set_window_pos(handle, pos.x, pos.y);
        }

        size2<> get_size() const {
            size2<> size;
            glfw::get_window_size(handle, &size.w, &size.h);
            return size;
        }

        void set_size(size2<> size) {
            glfw::set_window_size(handle, size.w, size.h);
        }

        bool key_pressed(key key)
        {
            return glfw::get_key(handle, key) 
                == key_action::press;
        }

        bool key_released(key key)
        {
            return glfw::get_key(handle, key) 
                == key_action::release;
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

        void set_cursor_pos(vec2<> pos) {
            glfw::set_cursor_pos(handle, pos.x, pos.y);
        }

        void make_context_current() {
            glfw::make_context_current(handle);
        }

        void swap_buffers() {
            glfw::swap_buffers(handle);
        }

    private:
        static void move_callback(glfw::window_handle handle,
            i32 x, i32 y)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_move)
                self->on_move({ x, y });
        }

        static void resize_callback(glfw::window_handle handle,
            i32 w, i32 h)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_resize)
                self->on_resize({ w, h });
        }

        static void close_callback(glfw::window_handle handle)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_close)
                self->on_close();
        }

        static void minimize_callback(glfw::window_handle handle, i32 min)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_minimize)
                self->on_minimize();
        }

        static void maximize_callback(glfw::window_handle handle, i32 max)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_maximize)
                self->on_maximize();
        }

        static void focus_callback(glfw::window_handle handle,
            i32 focused)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);            
            if (focused) 
                if (self->on_focus) self->on_focus();
            else
                if (self->on_blur) self->on_blur();
        }

        static void refresh_callback(glfw::window_handle handle)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_refresh) self->on_refresh();
        }

        static void cursor_move_callback(glfw::window_handle handle,
            f64 x, f64 y)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_cursor_move)
                self->on_cursor_move({ (f32)x, (f32)y });
        }

        static void cursor_enter_callback(glfw::window_handle handle,
            int entered)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (entered)
                if (self->on_cursor_enter) self->on_cursor_enter();
            else
                if (self->on_cursor_leave) self->on_cursor_leave();
        }

        static void scroll_callback(glfw::window_handle handle,
            f64 x, f64 y)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_scroll) self->on_scroll({ (f32)x, (f32)y });
        }

        static void mouse_button_callback(glfw::window_handle handle,
            i32 button, i32 action, i32 mods)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_mouse_button)
                self->on_mouse_button(
                    (mouse_button)button, (mouse_action)action, (key_mod)mods
                );
        }

        static void key_callback(glfw::window_handle handle,
            i32 keycode, i32 scancode, i32 action, i32 mods)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_key)
                self->on_key(
                    (key)keycode, scancode, (key_action)action, (key_mod)mods
                );
        }

        static void char_callback(glfw::window_handle handle,
            u32 codepoint)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_char) self->on_char(codepoint);
        }

        static void char_mods_callback(glfw::window_handle handle,
            u32 codepoint, i32 mods)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_char_mods)
                self->on_char_mods(codepoint, (key_mod)mods);
        }

        static void framebuffer_resize_callback(glfw::window_handle handle,
            i32 w, i32 h)
        {
            auto* self = (window*)glfw::get_window_user_pointer(handle);
            if (self->on_framebuffer_resize)
                self->on_framebuffer_resize({ w, h });
        }
    };
}
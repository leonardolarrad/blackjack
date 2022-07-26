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

export module tornasol:renderer;

import :buffer;
import :color;
import :gl;
import :glad;
import :mesh;
import :rect;
import :shader;
import :size;
import :transform;
import :types;
import :vector;
import :window;

import std.core;
using namespace std;

export namespace tornasol
{
    struct render_stat
    {
        u64 frame;
        u64 calls;
    };

    class renderer
    {
    private:
        render_stat stat;
        window& win;
        set<mesh_renderer*> requests;
        color clear_color;

    public:
        renderer(glad_dep& glad, window& win)
            : win(win)
        {
            win.make_context_current();
            size2<i32> viewport = win.get_size();
            
            glad.load();
            gl::viewport(0, 0, viewport.w, viewport.h);
            gl::enable(gl::multisample);
            gl::enable(gl::blend);
            gl::blend_func(gl::src_alpha, gl::one_minus_src_alpha);
            win.on_framebuffer_resize = [](size2<> s) {
                gl::viewport(0, 0, s.w, s.h);
            };

            stat.frame = 0;
            stat.calls = 0;
        }

        render_stat get_stat() const {
            return stat;
        }

        window& get_window() const {
            return win;
        }

        void set_clear_color(color c) {
            clear_color = c;
        }

        void add_mesh(mesh_renderer& mesh) {
            requests.insert(&mesh);
        }

        bool is_pending_to_render() 
        {
            for (auto& r : requests) 
                if (r->is_pending_to_render())
                    return true;                
            
            return false;
        }
         
        void next_frame() 
        {
            if (!is_pending_to_render())
                return;

            clear(clear_color);
            for (auto& r: requests) {
                render(*r); 
                r->set_pending_to_render(false);
            }
                           
            present();
            ++stat.frame;
        }

        void clear(color bg)
        {
            gl::clear_color(bg.r, bg.g, bg.b, bg.a);
            gl::clear(gl::color_buffer_bit);
        }

        void render(mesh_renderer& mesh)
        {
            size2<i32> screen = win.get_size();
            mat4<> proj = ortho(0.0f, (f32)screen.w, (f32)screen.h, 0.0f);

            mesh.get_vao().bind();
            mesh.get_shader().use();
            mesh.get_shader().set_uniform("proj", proj);
            mesh.get_texture().bind();

            if (mesh.is_wireframe())
                gl::polygon_mode(gl::front_and_back, gl::line);

            gl::draw_elements(gl::triangles, 6, gl::type_uint, 0);

            ++stat.calls;
        }

        void present() {
            win.swap_buffers();            
        }
    };
}
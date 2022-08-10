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
import :rect;
import :shader;
import :size;
import :texture;
import :transform;
import :types;
import :vector;
import :window;

export namespace tornasol {

    class render_stats {
    public:
        u64 frame;
        u64 calls;

        render_stats() 
            : frame(0), calls(0) {}
    };

    class renderer {
    private:
        render_stats stats;
        window& win;

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
        }

        render_stats get_stats() const {
            return stats;
        }

        window& get_window() const {
            return win;
        }

        mat4<> get_proj_mat() const
        {
            size2<i32> viewport = win.get_size();
            return ortho(0.0f, (f32)viewport.w, (f32)viewport.h, 0.0f, -1.0f, 1.0f);
        }

        void clear(color bg)
        {
            gl::clear_color(bg.r, bg.g, bg.b, bg.a);
            gl::clear(gl::color_buffer_bit);
        }

        void render(texture_renderer& tex) 
        {
            tex.get_vao().bind();
            tex.get_vbo().bind();
            tex.get_ibo().bind();
            tex.get_texture().bind();
            tex.set_proj(get_proj_mat());

            if (tex.is_wireframe())
                gl::polygon_mode(gl::front_and_back, gl::line);

            gl::draw_elements(gl::triangles, 6, gl::type_uint, 0);
            ++stats.calls;
        }

        void present() {
            win.swap_buffers();
        }
    };
}
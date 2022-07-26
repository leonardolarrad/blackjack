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

export module tornasol:mesh;
import :vector;
import :matrix;
import :buffer;
import :shader;
import :rect;
import :color;
import :texture;

import std.core;
using namespace std;

export namespace tornasol {

    class vertex 
    {
    public:
        vec3<> pos;
        vec2<> tex;
    };

    class mesh 
    {
    public:
        vector<vertex> vertices;
        vector<u32>    indices;
    };

    class mesh_renderer
    {
    private:
        vertex_array  vao;
        vertex_buffer vbo;
        vertex_buffer ibo;
        texture tex;
        shader program;
        bool wireframe;
        bool pending_to_render;

    public:        
        mesh_renderer() = delete;

        mesh_renderer(rect<> r, color c, bool wireframe = false)
            : vao(), program(),
              vbo(buffer_type::vertex), ibo(buffer_type::index),
              wireframe(wireframe), pending_to_render(true)
        {
            // default shader
            const char vertex_src[] =
                " #version 400 core\n                                "
                " layout (location = 0) in vec3 pos;\n               "
                " uniform mat4 model;\n                              "
                " uniform mat4 proj;\n                               "
                " void main()\n                                      "
                " {\n                                                "
                "     gl_Position = proj * model * vec4(pos, 1.0);\n "
                " }\0                                                ";

            const char fragment_src[] =
                " #version 400 core\n         "
                " out vec4 frag;\n            "
                " uniform vec4 fill_color;\n  "
                " void main()\n               "
                " {                           "
                "    frag = fill_color;\n     "
                " }\0                         ";

            shader_source vertex(shader_type::vertex);
            vertex.compile(vertex_src);
            shader_source fragment(shader_type::fragment);
            fragment.compile(fragment_src);

            // shader program;
            program.attach(vertex);
            program.attach(fragment);
            program.link();
            program.use();
            program.set_uniform("fill_color", c);
            program.set_uniform("model", mat4<>(1.0f));

            // load mesh data to gpu memory
            const f32 x = r.a.x;
            const f32 y = r.a.y;
            const f32 w = r.b.x;
            const f32 h = r.b.y;

            const f32 vertices[] = {
                x + w, y    , 0.0f,
                x + w, y + h, 0.0f,
                    x, y + h, 0.0f,
                    x, y    , 0.0f
            };

            const u32 indices[] = {
                0, 1, 3,
                1, 2, 3
            };

            vao.bind();
            vbo.bind();
            vbo.load(vertices, sizeof(vertices), buffer_usage::static_draw);
            ibo.bind();
            ibo.load(indices, sizeof(indices), buffer_usage::static_draw);

            vao.attribute(0, 3, gl::type_float, false, sizeof(f32) * 3, 0);
            vao.enable_attribute(0);
        }

        mesh_renderer(const image& img) 
            : vbo(buffer_type::vertex), ibo(buffer_type::index),
              wireframe(false), pending_to_render(true)
        {
            // default shader
            const char vertex_src[] =
                " #version 400 core\n                                "
                " layout (location = 0) in vec3 pos;\n               "
                " layout (location = 1) in vec3 tex;\n               "
                " out vec2 tex_coord;\n                              "
                " uniform mat4 model;\n                              "
                " uniform mat4 proj;\n                               "
                " void main()\n                                      "
                " {\n                                                "
                "     gl_Position = proj * model * vec4(pos, 1.0);\n "
                "     tex_coord = vec2(tex.x, tex.y);\n              "
                " }\0                                                ";

            const char fragment_src[] =
                " #version 400 core\n                   "
                " out vec4 frag;\n                      "
                " in  vec2 tex_coord;\n                 "
                " uniform sampler2D tex;\n              "
                " void main()\n                         "
                " {\n                                   "
                "    frag = texture(tex, tex_coord);\n  "
                " }\0                                   ";

            shader_source vertex(shader_type::vertex);
            vertex.compile(vertex_src);
            shader_source fragment(shader_type::fragment);
            fragment.compile(fragment_src);

            // shader program;
            program.attach(vertex);
            program.attach(fragment);
            program.link();
            program.use();
            //program.set_uniform("fill_color", c);
            program.set_uniform("model", mat4<>(1.0f));

            // load mesh data to gpu memory
            const f32 x = 0.0f;
            const f32 y = 0.0f;
            const f32 w = img.width;
            const f32 h = img.height;

            const f32 vertices[] = {
                // pos                   // tex
                x + w, y    , 0.0f,      1.0f, 1.0f,
                x + w, y + h, 0.0f,      1.0f, 0.0f,
                    x, y + h, 0.0f,      0.0f, 0.0f,
                    x, y    , 0.0f,      0.0f, 1.0f
            };

            const u32 indices[] = {
                0, 1, 3,
                1, 2, 3
            };

            vao.bind();
            vbo.bind();
            vbo.load(vertices, sizeof(vertices), buffer_usage::static_draw);
            ibo.bind();
            ibo.load(indices, sizeof(indices), buffer_usage::static_draw);

            vao.attribute(0, 3, gl::type_float, false, sizeof(f32) * 5, 0);
            vao.enable_attribute(0);

            vao.attribute(1, 2, gl::type_float, false, sizeof(f32) * 5, 
                sizeof(f32) * 3);
            vao.enable_attribute(1);

            tex.bind();
            tex.set_wrap(texture_wrap::repeat, texture_wrap::repeat);
            tex.set_filter(texture_filter::linear_mipmap_linear, 
                texture_filter::linear);
            tex.load(img);
            tex.generate_mipmap();

            cout << program.log() << endl;
        }
        
        void set_transform(const mat4<>& m) {
            program.use();
            program.set_uniform("model", m);
            pending_to_render = true;
        }

        shader& get_shader() {
            return program;
        }

        texture& get_texture () {
            return tex;
        }

        vertex_array& get_vao() {
            return vao;
        }

        vertex_buffer& get_vbo() {
            return vbo;
        }

        vertex_buffer& get_ibo() {
            return ibo;
        }

        bool is_wireframe() const{
            return wireframe;
        }

        void set_pending_to_render(bool value) {
            pending_to_render = value;
        }

        bool is_pending_to_render() const {
            return pending_to_render;
        }
    };


}
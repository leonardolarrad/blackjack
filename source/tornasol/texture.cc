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

export module tornasol:texture;
import :buffer;
import :gl;
import :image;
import :rect;
import :shader;
import :types;
import :util;
import std.core;

using namespace std;
namespace ts = tornasol;

export namespace tornasol {

    enum class texture_wrap 
    {
        repeat = gl::repeat
    };

    enum class texture_filter 
    {
        linear               = gl::linear,
        linear_mipmap_linear = gl::linear_mipmap_linear,
        nearest              = gl::nearest
    };

    enum class texture_format 
    {
        rgb  = gl::rgb,
        rgba = gl::rgba,
    };

    class texture {
    private:
        u32 id;

    public:
        texture() {
            id = gl::gen_texture();
        }

        ~texture() {
            gl::delete_texture(id);
        }

        u32 get_id() const {
            return id;
        }

        // non-copyable 
        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;

        // movable
        texture(texture&& other) 
            : id(other.id) 
        {
            other.id = 0;
        }

        texture& operator=(texture&& other) 
        {
            id = other.id;
            other.id = 0;
            return *this;
        }

        void bind() {
            gl::bind_texture(gl::texture_2d, id);
        }

        void set_wrap(texture_wrap x, texture_wrap y)
        {
            gl::tex_parameteri(gl::texture_2d, gl::texture_wrap_s, (gl::def)x);
            gl::tex_parameteri(gl::texture_2d, gl::texture_wrap_t, (gl::def)y);
        }

        void set_filter(texture_filter min, texture_filter mag)
        {
            gl::tex_parameteri(gl::texture_2d, gl::texture_min_filter,
                (gl::def)min);
            gl::tex_parameteri(gl::texture_2d, gl::texture_mag_filter,
                (gl::def)mag);
        }

        void load(const image& img) 
        {
            texture_format format = 
                img.channels == 3 ? texture_format::rgb : texture_format::rgba;

            gl::tex_image_2d(
                gl::texture_2d, 
                0, 
                (gl::def) format, 
                img.width, 
                img.height,
                0, 
                (gl::def) format, 
                gl::type_ubyte, 
                img.data
            );
        }

        void generate_mipmap() {
            gl::generate_mipmap(gl::texture_2d);
        }
    };

    class texture_renderer {
    private: 
        vertex_array  vao;
        vertex_buffer vbo;
        vertex_buffer ibo;
        texture texture;
        shader shader;
        bool wireframe;

    public:
        texture_renderer()
            : vbo(buffer_type::vertex), ibo(buffer_type::index),
              wireframe(false)
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
            
            shader.attach(vertex);
            shader.attach(fragment);
            shader.link();
            shader.use();
            shader.set_uniform("model", mat4<>(1.0f));
        }

        // non-copyable
        texture_renderer(const texture_renderer&) = delete;
        texture_renderer& operator=(const texture_renderer&) = delete;

        // movable
        texture_renderer(texture_renderer&& other) 
            : vao(move(other.vao)), 
              vbo(move(other.vbo)), 
              ibo(move(other.ibo)),
              texture(move(other.texture)), 
              shader(move(other.shader)),
              wireframe(other.wireframe)
        {}

        texture_renderer& operator=(texture_renderer&& other) 
        {
            vao = move(other.vao);
            vbo = move(other.vbo);
            ibo = move(other.ibo);
            texture = move(other.texture);
            shader = move(other.shader);
            wireframe = other.wireframe;
            return *this;
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

        ts::texture& get_texture() {
            return texture;
        }

        ts::shader& get_shader() {
            return shader;
        }

        bool is_wireframe() const {
            return wireframe;
        }

        void set_wireframe(bool value) {
            wireframe = value;
        }

        void set_model(const mat4<>& model) 
        {
            shader.use();
            shader.set_uniform("model", model);
        }

        void set_proj(const mat4<>& proj) 
        {
            shader.use();
            shader.set_uniform("proj", proj);
        }

        void set_rect(const rect<>& rect) 
        {
            const f32 vertices[] = {
                // pos                                    // tex
                // x             // y             // z    // x  // y
                rect.x + rect.w, rect.y         , 0.0f,   1.0f, 1.0f,
                rect.x + rect.w, rect.y + rect.h, 0.0f,   1.0f, 0.0f,
                         rect.x, rect.y + rect.h, 0.0f,   0.0f, 0.0f,
                         rect.x, rect.y         , 0.0f,   0.0f, 1.0f
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
        }

        void set_image(const image& image) 
        {
            texture.bind();
            texture.set_wrap(texture_wrap::repeat, texture_wrap::repeat);
            texture.set_filter(texture_filter::linear_mipmap_linear, 
                texture_filter::linear);
            texture.load(image);
            texture.generate_mipmap();
        }
    };
}
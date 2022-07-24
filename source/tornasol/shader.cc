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

export module tornasol:shader;
import std.core;
import :color;
import :gl;
import :types;
import :vector;
import :matrix;

using namespace std;

export namespace tornasol 
{
    enum class shader_type
    { 
        vertex   = gl::vertex,
        fragment = gl::fragment,
        geometry = gl::geometry
    };

    class shader_source 
    {
    private:
        u32 id;

    public:
        shader_source(shader_type type) {
            id = gl::create_shader((gl::def) type);
        }

        ~shader_source() {
            gl::delete_shader(id);
        }

        u32 get_id() {
            return id;
        }

        void compile(const char* src)
        {
            gl::shader_source(id, 1, src, nullptr);
            gl::compile_shader(id);

            i32 status;
            gl::get_shader_iv(id, gl::compile_status, &status);

            if (!status)
                throw runtime_error(log());
        }

        string log() 
        {
            i32 len;
            gl::get_shader_iv(id, gl::info_log_length, &len);

            if (len <= 0)
                return "";

            string log; 
            log.resize(len);
            gl::get_shader_info_log(id, len, &len, &log[0]);
            return log;
        }
    };

    class shader
    {
    private:
        u32 id;

    public:
        shader() {
            id = gl::create_program();
        }

        ~shader() {
            gl::delete_program(id);
        }

        u32 get_id() {
            return id;
        }

        void attach(shader_source& src) {
            gl::attach_shader(id, src.get_id());
        }

        void link() 
        {
            gl::link_program(id);

            i32 status;
            gl::get_program_iv(id, gl::link_status, &status);

            if (!status)
                throw runtime_error(log());
        }

        void use() {
            gl::use_program(id);
        }

        i32 get_location(const char* name) {
            return gl::get_uniform_location(id, name);
        }

        void set_uniform(const char* name, const vec2<>& v) {
            gl::uniform_2f(get_location(name), v.x, v.y);
        }

        void set_uniform(const char* name, const vec3<>& v) {
            gl::uniform_3f(get_location(name), v.x, v.y, v.z);
        }

        void set_uniform(const char* name, const vec4<>& v) {
            gl::uniform_4f(get_location(name), v.x, v.y, v.z, v.w);
        }

        void set_uniform(const char* name, const mat2<>& m) {
            gl::uniform_matrix_2fv(get_location(name), 1, false, &m[0][0]);
        }

        void set_uniform(const char* name, const mat3<>& m) {
            gl::uniform_matrix_3fv(get_location(name), 1, false, &m[0][0]);
        }

        void set_uniform(const char* name, const mat4<>& m) {
            gl::uniform_matrix_4fv(get_location(name), 1, false, &m[0][0]);
        }

        string log() 
        {
            i32 len;
            gl::get_program_iv(id, gl::info_log_length, &len);

            if (len <= 0)
                return "";

            string log;
            log.resize(len);
            gl::get_program_info_log(id, len, &len, &log[0]);
            return log;
        }
    };    
}
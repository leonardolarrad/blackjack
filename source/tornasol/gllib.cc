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

export module tornasol:gl;
import :types;
import "glad.h";

export namespace tornasol::gl 
{
    enum def : u32
    {
        // types
        type_byte            = GL_BYTE,
        type_ubyte           = GL_UNSIGNED_BYTE,
        type_short           = GL_SHORT,
        type_ushort          = GL_UNSIGNED_SHORT,
        type_int             = GL_INT,
        type_uint            = GL_UNSIGNED_INT,
        type_float           = GL_FLOAT,
        type_double          = GL_DOUBLE,
        // buffer bit
        color_buffer_bit     = GL_COLOR_BUFFER_BIT,
        depth_buffer_bit     = GL_DEPTH_BUFFER_BIT,
        stencil_buffer_bit   = GL_STENCIL_BUFFER_BIT,
        // polygon 
        points               = GL_POINTS,
        lines                = GL_LINES,
        line_strip           = GL_LINE_STRIP,
        line_loop            = GL_LINE_LOOP,
        triangles            = GL_TRIANGLES,
        triangle_strip       = GL_TRIANGLE_STRIP,
        triangle_fan         = GL_TRIANGLE_FAN,        
        // draw mode 
        fill                 = GL_FILL,
        point                = GL_POINT,
        line                 = GL_LINE,
        // face
        front                = GL_FRONT,
        back                 = GL_BACK,
        front_and_back       = GL_FRONT_AND_BACK,
        // shader type
        vertex               = GL_VERTEX_SHADER,
        fragment             = GL_FRAGMENT_SHADER,
        geometry             = GL_GEOMETRY_SHADER,
        // shader program
        shader_type          = GL_SHADER_TYPE,
        compile_status       = GL_COMPILE_STATUS,
        link_status          = GL_LINK_STATUS,
        info_log_length      = GL_INFO_LOG_LENGTH,
        delete_status        = GL_DELETE_STATUS,
        source_len           = GL_SHADER_SOURCE_LENGTH,
        // buffer type  
        array_buffer         = GL_ARRAY_BUFFER,
        element_buffer       = GL_ELEMENT_ARRAY_BUFFER,
        // draw
        static_draw          = GL_STATIC_DRAW,
        dynamic_draw         = GL_DYNAMIC_DRAW,
        stream_draw          = GL_STREAM_DRAW,
        // texture
        texture_2d           = GL_TEXTURE_2D,
        texture_wrap_s       = GL_TEXTURE_WRAP_S,
        texture_wrap_t       = GL_TEXTURE_WRAP_T,
        texture_min_filter   = GL_TEXTURE_MIN_FILTER,
        texture_mag_filter   = GL_TEXTURE_MAG_FILTER,
        repeat               = GL_REPEAT,
        linear               = GL_LINEAR,
        nearest              = GL_NEAREST,
        linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR,   
        // color
        red                  = GL_RED,
        green                = GL_GREEN,
        blue                 = GL_BLUE,
        rgb                  = GL_RGB,
        rgba                 = GL_RGBA,
        // blending
        blend                = GL_BLEND,
        one_minus_src_alpha  = GL_ONE_MINUS_SRC_ALPHA,
        one_minus_dst_alpha  = GL_ONE_MINUS_DST_ALPHA,
        src_alpha            = GL_SRC_ALPHA,
        dst_alpha            = GL_DST_ALPHA,
        // anti-aliasing
        multisample          = GL_MULTISAMPLE,
    };

    void viewport(i32 x, i32 y, i32 width, i32 height) {
        glViewport(x, y, width, height);
    }

    void clear_color(f32 r, f32 g, f32 b, f32 a) {
        glClearColor(r, g, b, a);
    }

    void clear(def mask) {
        glClear(mask);
    }

    u32 gen_buffer() {
        u32 id;
        glGenBuffers(1, &id);
        return id;
    }

    void delete_buffer(u32 id) {
        glDeleteBuffers(1, &id);
    }

    void bind_buffer(def target, u32 id) {
        glBindBuffer(target, id);
    }

    void buffer_data(def target, i32 size, const void* data, def usage) {
        glBufferData(target, size, data, usage);
    }

    u32 gen_vertex_array() {
        u32 id;
        glGenVertexArrays(1, &id);
        return id;
    }

    void delete_vertex_array(u32 id) {
        glDeleteVertexArrays(1, &id);
    }

    void bind_vertex_array(u32 id) {
        glBindVertexArray(id);
    }

    void vertex_attrib_pointer(u32 index, i32 size, def type, 
        bool normalized, i32 stride, i32 offset) 
    {
        glVertexAttribPointer(index, size, type, 
            normalized, stride, (void*)offset);
    }

    void enable_vertex_attrib_array(u32 index) {
        glEnableVertexAttribArray(index);
    }

    void disable_vertex_attrib_array(u32 index) {
        glDisableVertexAttribArray(index);
    }

    u32 create_shader(def type) {
        return glCreateShader(type);
    }

    void delete_shader(u32 shader) {
        glDeleteShader(shader);
    }

    void shader_source(u32 shader, i32 count, 
        const char* src, const i32* len) 
    {
        glShaderSource(shader, count, &src, len);
    }

    void compile_shader(u32 shader) {
        glCompileShader(shader);
    }

    void get_shader_iv(u32 shader, def pname, i32* params) {
        glGetShaderiv(shader, pname, params);
    }

    void get_shader_info_log(u32 shader, i32 max_len, 
        i32* len, char* info_log) 
    {
        glGetShaderInfoLog(shader, max_len, len, info_log);
    }

    u32 create_program() {
        return glCreateProgram();
    }

    void delete_program(u32 program) {
        glDeleteProgram(program);
    }

    void attach_shader(u32 program, u32 shader) {
        glAttachShader(program, shader);
    }

    void link_program(u32 program) {
        glLinkProgram(program);
    }

    void get_program_iv(u32 program, def pname, i32* params) {
        glGetProgramiv(program, pname, params);
    }

    void get_program_info_log(u32 program, i32 max_len, 
        i32* len, char* info_log) 
    {
        glGetProgramInfoLog(program, max_len, len, info_log);
    }

    void use_program(u32 program) {
        glUseProgram(program);
    }

    i32 get_attrib_location(u32 program, const char* name) {
        return glGetAttribLocation(program, name);
    }

    i32 get_uniform_location(u32 program, const char* name) {
        return glGetUniformLocation(program, name);
    }

    void uniform_1i(i32 location, i32 v0) {
        glUniform1i(location, v0);
    }

    void uniform_2i(i32 location, i32 v0, i32 v1) {
        glUniform2i(location, v0, v1);
    }

    void uniform_3i(i32 location, i32 v0, i32 v1, i32 v2) {
        glUniform3i(location, v0, v1, v2);
    }

    void uniform_4i(i32 location, i32 v0, i32 v1, i32 v2, i32 v3) {
        glUniform4i(location, v0, v1, v2, v3);
    }

    void uniform_1f(i32 location, f32 v0) {
        glUniform1f(location, v0);
    }

    void uniform_2f(i32 location, f32 v0, f32 v1) {
        glUniform2f(location, v0, v1);
    }

    void uniform_3f(i32 location, f32 v0, f32 v1, f32 v2) {
        glUniform3f(location, v0, v1, v2);
    }

    void uniform_4f(i32 location, f32 v0, f32 v1, f32 v2, f32 v3) {
        glUniform4f(location, v0, v1, v2, v3);
    }

    void uniform_matrix_2fv(i32 location, i32 count, bool transpose, 
        const f32* value) 
    {
        glUniformMatrix2fv(location, count, transpose, value);
    }

    void uniform_matrix_3fv(i32 location, i32 count, bool transpose, 
        const f32* value) 
    {
        glUniformMatrix3fv(location, count, transpose, value);
    }

    void uniform_matrix_4fv(i32 location, i32 count, bool transpose, 
        const f32* value) 
    {
        glUniformMatrix4fv(location, count, transpose, value);
    }

    u32 gen_texture() {
        u32 id;
        glGenTextures(1, &id);
        return id;
    }

    void delete_texture(u32 id) {
        glDeleteTextures(1, &id);
    }

    void bind_texture(def target, u32 id) {
        glBindTexture(target, id);
    }

    void tex_parameteri(def target, def pname, i32 param) {
        glTexParameteri(target, pname, param);
    }

    void tex_parameterf(def target, def pname, f32 param) {
        glTexParameterf(target, pname, param);
    }

    void tex_image_2d(def target, i32 level, def internal_format, 
        i32 width, i32 height, i32 border, def format, def type, const void* data) 
    {
        glTexImage2D(target, level, internal_format, width, height, 
            border, format, type, data);
    }

    void generate_mipmap(def target) {
        glGenerateMipmap(target);
    }
    
    void enable(def cap) {
        glEnable(cap);
    }

    void blend_func(def sfactor, def dfactor) {
        glBlendFunc(sfactor, dfactor);
    }

    void polygon_mode(def face, def mode) {
        glPolygonMode(face, mode);
    }

    void draw_arrays(def mode, i32 first, i32 count) {
        glDrawArrays(mode, first, count);
    }

    void draw_elements(def mode, i32 count, def type, void* indices) {
        glDrawElements(mode, count, type, indices);
    }
}
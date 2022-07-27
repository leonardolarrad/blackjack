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

export module tornasol:buffer;
import :types;
import :gl;

export namespace tornasol
{
    enum class buffer_type 
    {
        vertex = gl::array_buffer,
        index  = gl::element_buffer,
    };

    enum class buffer_usage 
    {
        static_draw  = gl::static_draw,
        dynamic_draw = gl::dynamic_draw,
        stream_draw  = gl::stream_draw
    };

    class vertex_buffer    
    {
    private:
        u32 id;
        buffer_type type;
        u32 size;

    public: 
        vertex_buffer() = delete;
        vertex_buffer(const vertex_buffer&) = delete;
        vertex_buffer& operator=(const vertex_buffer&) = delete;

        vertex_buffer(buffer_type type) 
            : id(gl::gen_buffer()), type(type), size(0) {}
        
        ~vertex_buffer() {
            gl::delete_buffer(id);
        }

        u32 get_id() const {
            return id;
        }

        u32 get_size() const {
            return size;
        }
        
        void bind() {
            gl::bind_buffer((gl::def)type, id);
        }
        
        void unbind() {
            gl::bind_buffer((gl::def)type, 0);
        }

        void load(const void* data, u32 size, buffer_usage usage) {
            gl::buffer_data((gl::def)type, size, data, (gl::def)usage);
            this->size = size;
        }
    };

    class vertex_array 
    {
    private:
        u32 id;

    public:
        vertex_array(const vertex_array&) = delete;
        vertex_array& operator=(const vertex_array&) = delete;

        vertex_array() {
            id = gl::gen_vertex_array();
        }
        
        ~vertex_array() {
            gl::delete_vertex_array(id);
        }
        
        u32 get_id() const {
            return id;
        }
        
        void bind() {
            gl::bind_vertex_array(id);
        }
        
        void unbind() {
            gl::bind_vertex_array(0);
        }        

        void attribute(u32 index, i32 size, gl::def type, 
            bool normalized, i32 stride, i32 offset) 
        {
            gl::vertex_attrib_pointer(index, size, type, 
                normalized, stride, offset);
        }

        void enable_attribute(u32 index) {
            gl::enable_vertex_attrib_array(index);
        }

        void disable_attribute(u32 index) {
            gl::disable_vertex_attrib_array(index);
        }
    };
}
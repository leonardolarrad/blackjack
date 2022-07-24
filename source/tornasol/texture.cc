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

export module tornasol:texture;
import :types;
import :gl;
import :image;

export namespace tornasol 
{
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

   class texture
   {
   private:
       u32 id;

   public:
       texture() {
           id = gl::gen_texture();
       }

       ~texture() {
           gl::delete_texture(id);
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

       void load(const image& img) {
           gl::tex_image_2d(gl::texture_2d, 0, gl::rgb, img.width, img.height,
               0, gl::rgb, gl::type_ubyte, img.data);
       }

       void generate_mipmap() {
           gl::generate_mipmap(gl::texture_2d);
       }
   };
}
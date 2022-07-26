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

export module tornasol:stbi;
import :types;
import "stb_image.h";
import <stdexcept>;

export namespace tornasol::stbi {

   void set_flip_vertically_on_load(bool flip) {
      stbi_set_flip_vertically_on_load(flip);
   }

   byte* load(const char* filename, int* x, int* y, int* comp, int req_comp)
   {
      byte* data = (byte*) stbi_load(filename, x, y, comp, req_comp);
      
      if (data == nullptr)
         throw std::runtime_error("failed to load image");
      
      return data;
   }

   void free(byte* data) {
      stbi_image_free(data);
   }
}
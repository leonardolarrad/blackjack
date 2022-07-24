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

export module tornasol:types;
import std.core;
import std.memory;

export namespace tornasol 
{
   using i8  = std::int8_t;
   using i16 = std::int16_t;
   using i32 = std::int32_t;
   using i64 = std::int64_t;

   using u8  = std::uint8_t;
   using u16 = std::uint16_t;
   using u32 = std::uint32_t;
   using u64 = std::uint64_t;

   using f32 = std::float_t;
   using f64 = std::double_t;

   using isize = std::ptrdiff_t;
   using usize = std::size_t;

   template <typename T> using shared = std::shared_ptr<T>;
   template <typename T> using unique = std::unique_ptr<T>;
   template <typename T> using weak   = std::weak_ptr<T>;
}
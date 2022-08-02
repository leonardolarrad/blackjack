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

export module tornasol:rect;
import :size;
import :types;
import :vector;

export namespace tornasol {
     
    template <typename T = f32> 
    class rect {
    public:
        T x, y, w, h;

        rect() = default;

        rect(T x, T y, T w, T h) 
            : x(x), y(y), w(w), h(h) {}

        rect(T w, T h) 
            : x(0), y(0), w(w), h(h) {}        

        bool operator != (const rect<T>& other) const = default;
        bool operator == (const rect<T>& other) const = default;

        explicit 
        operator vec2<T> () const { return {x, y}; }

        explicit
        operator size2<T> () const { return {w, h}; }

        bool contains (const vec2<T>& point) const 
        {
            return point.x >= x && point.x < x + w &&
                   point.y >= y && point.y < y + h;
        }
    };
}
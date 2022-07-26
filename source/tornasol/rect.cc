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

export namespace tornasol 
{ 
    template <typename T = f32>
    class rect 
    {
    public:
        vec2<T> a, b;

        rect() = default;

        rect(vec2<T> a, vec2<T> b)
            : a(a), b(b) {}

        rect(size2<T> size) 
            : a(T(0), T(0))
            , b(size.w, size.h) {}

        bool operator == (const rect<T>& other) const = default;
        bool operator != (const rect<T>& other) const = default;
            
        T width()  const { return b.x - a.x; }
        T height() const { return b.y - a.y; }
        T area()   const { return width() * height(); }
        
        vec2<T> center() const { 
            return { width() / 2, height() /2}; 
        }

        explicit operator size2<T> () const {
            return { width(), height() };
        }   

        bool contains(vec2<T> point) const 
        {        
            return point.x >= a.x && point.x <= b.x &&
                   point.y >= a.y && point.y <= b.y;        
        }

        bool contains(rect<T> rect) const 
        {
            return this->a.x <= rect.a.x && this->a.y <= rect.a.y &&
                   this->b.x >= rect.b.x && this->b.y >= rect.b.y;
        }
    };
}
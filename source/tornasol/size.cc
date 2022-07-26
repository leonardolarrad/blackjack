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

export module tornasol:size;
import :types;

export namespace tornasol 
{
    template <typename T = i32>
    class size2
    {    
    public:
        T w, h;
        
        bool operator == (const size2<T>& other) const = default;
        bool operator != (const size2<T>& other) const = default;
    };

    template <typename T = i32>
    size2<T> operator + (const size2<T>& left, const size2<T>& right) 
    {
        return {
            left.w  + right.w,
            left.h + right.h
        };
    }

    template <typename T = i32>
    size2<T> operator - (const size2<T>& left, const size2<T>& right) 
    {
        return {
            left.w  - right.w,
            left.h - right.h
        };
    }

    template <typename T = i32>
    size2<T> operator * (const size2<T>& left, const size2<T>& right) 
    {
        return {
            left.w  * right.w,
            left.h * right.h
        };
    }

    template <typename T = i32>
    size2<T> operator / (const size2<T>& left, const size2<T>& right) 
    {
        return {
            left.w  / right.w,
            left.h / right.h
        };
    }

    template <typename T = i32>
    size2<T> operator * (const size2<T>& size, T scalar) 
    {
        return {
            size.w  * scalar,
            size.h * scalar
        };
    }

    template <typename T = i32>
    size2<T> operator * (T scalar, const size2<T>& size) 
    {
        return {
            scalar * size.w,
            scalar * size.h
        };
    }

    template <typename T = i32>
    size2<T> operator / (const size2<T>& size, T scalar) 
    {
        return {
            size.w  / scalar,
            size.h / scalar
        };
    }

    template <typename T = i32>
    size2<T> operator / (T scalar, const size2<T>& size) 
    {
        return {
            scalar / size.w,
            scalar / size.h
        };
    }
}
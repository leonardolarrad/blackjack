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

#include <assert.h>
export module tornasol:vector;
import std.core;
import :types;
using namespace std;

export namespace tornasol {

    template <typename T, usize N>
    class vec;

    template <typename T = f32> using vec2 = vec<T, 2>;
    template <typename T = f32> using vec3 = vec<T, 3>;
    template <typename T = f32> using vec4 = vec<T, 4>;

    template <typename T, usize N>
    class vec {
    private: 
        T values[N];

    public:    
        vec() = default;

        vec(initializer_list<T> arr)
        {
            assert(arr.size() == N); 
            copy(arr.begin(), arr.end(), values);
        }

        T& operator [] (usize i) { 
            assert(i < N); return values[i]; 
        }

        const T& operator [] (usize i) const {
            assert(i < N); return values[i]; 
        }
    };

    template <typename T>
    class vec<T, 2> {
    public:
        T x, y;

        vec() = default;
        vec(T x, T y) : x(x), y(y) {}    

        T& operator [] (usize i) 
        {
            assert(i < 2);
            return reinterpret_cast<T*>(this)[i]; 
        }
        
        const T& operator [] (usize i) const
        {
            assert(i < 2);
            return reinterpret_cast<const T*>(this)[i]; 
        }
    };

    template <typename T>
    class vec<T, 3> {   
    public:
        T x, y, z;

        vec() = default;    
        vec(T x, T y, T z) : x(x), y(y), z(z) {}

        vec<T, 2> xy() const { return { x, y }; }
        vec<T, 2> xz() const { return { x, z }; }
        vec<T, 2> yx() const { return { y, x }; }
        vec<T, 2> yz() const { return { y, z }; }
        vec<T, 2> zx() const { return { z, x }; }
        vec<T, 2> zy() const { return { z, y }; }

        T& operator [] (usize i) 
        {
            assert(i < 3);
            return reinterpret_cast<T*>(this)[i]; 
        }

        const T& operator [] (usize i) const
        {
            assert(i < 3);
            return reinterpret_cast<const T*>(this)[i]; 
        }
    };

    template <typename T>
    class vec<T, 4> {   
    public:
        T x, y, z, w;

        vec() = default;

        vec(T x, T y, T z, T w) :
            x(x), y(y), z(z), w(w) {}

        vec(const vec<T, 3>& v, T w = T(0))
            : x(v.x), y(v.y), z(v.z), w(w) {}

        vec<T, 3> xyz() const { return { x, y, z }; }; 
        vec<T, 3> xyw() const { return { x, y, w }; };
        vec<T, 3> xzy() const { return { x, z, y }; };
        vec<T, 3> xzw() const { return { x, z, w }; };
        vec<T, 3> xwy() const { return { x, w, y }; };
        vec<T, 3> xwz() const { return { x, w, z }; };
        vec<T, 3> yxz() const { return { y, x, z }; };
        vec<T, 3> yxw() const { return { y, x, w }; };
        vec<T, 3> yzx() const { return { y, z, x }; };
        vec<T, 3> yzw() const { return { y, z, w }; };
        vec<T, 3> ywx() const { return { y, w, x }; };
        vec<T, 3> ywz() const { return { y, w, z }; };
        vec<T, 3> zxy() const { return { z, x, y }; };
        vec<T, 3> zxw() const { return { z, x, w }; };
        vec<T, 3> zyx() const { return { z, y, x }; };
        vec<T, 3> zyw() const { return { z, y, w }; };
        vec<T, 3> zwx() const { return { z, w, x }; };
        vec<T, 3> zwy() const { return { z, w, y }; };
        vec<T, 3> wxy() const { return { w, x, y }; };
        vec<T, 3> wxz() const { return { w, x, z }; };
        vec<T, 3> wyx() const { return { w, y, x }; };
        vec<T, 3> wyz() const { return { w, y, z }; };
        vec<T, 3> wzx() const { return { w, z, x }; };
        vec<T, 3> wzy() const { return { w, z, y }; };
        
        T& operator [] (usize i) 
        {
            assert(i < 4);
            return reinterpret_cast<T*>(this)[i]; 
        }

        const T& operator [] (usize i) const
        {
            assert(i < 4);
            return reinterpret_cast<const T*>(this)[i]; 
        }
    };

    template <typename T, usize N>
    bool operator == (const vec<T, N>& u, const vec<T, N>& v)
    {
        for (int i = 0; i < N; ++i)
            if (u[i] != v[i]) return false;

        return true;
    }

    template <typename T, usize N>
    bool operator != (const vec<T, N>& u, const vec<T, N>& v)
    {
        return !(u == v);
    }

    template <typename T, usize N>
    vec<T, N> operator + (const vec<T, N>& v)
    {
        return v;
    }

    template <typename T, usize N>
    vec<T, N> operator - (const vec<T, N>& v)
    {
        vec<T, N> r;
        for (int i = 0; i < N; ++i)
            r[i] = -v[i];
        return r;
    }

    template <typename T, usize N>
    vec<T, N> operator + (const vec<T, N>& u, const vec<T, N>& v)
    {
        vec<T, N> r;
        for (int i = 0; i < N; ++i)
            r[i] = u[i] + v[i];
        return r;
    }

    template <typename T, usize N>
    vec<T, N> operator - (const vec<T, N>& u, const vec<T, N>& v)
    {
        vec<T, N> r;
        for (int i = 0; i < N; ++i)
            r[i] = u[i] - v[i];
        return r;
    }

    template <typename T, usize N>
    vec<T, N> operator * (const vec<T, N>& v, T s)
    {
        vec<T, N> r;
        for (int i = 0; i < N; ++i)
            r[i] = v[i] * s;

        return r;
    }

    template <typename T, usize N>
    vec<T, N> operator * (T s, const vec<T, N>& v)
    {
        return v * s;
    }

    template <typename T, usize N>
    vec<T, N> operator / (const vec<T, N>& v, T s)
    {
        vec<T, N> r;
        for (int i = 0; i < N; ++i)
            r[i] = v[i] / s;
        return r;
    }

    template <typename T, usize N>
    T len(const vec<T, N>& v)
    {
        T lensqr = T(0);

        for (int i = 0; i < N; ++i)
            lensqr += v[i] * v[i];

        return (T) sqrt(lensqr);
    }

    template <typename T, usize N>
    vec<T, N> normalize(const vec<T, N>& v)
    {
        return v / len(v);
    }

    template <typename T, usize N>
    T dot(const vec<T, N>& u, const vec<T, N>& v)
    {
        T r = T(0);
        for (int i = 0; i < N; ++i)
            r += u[i] * v[i];
        return r;
    }

    template <typename T>
    vec<T, 3> cross(const vec<T, 3>& u, const vec<T, 3>& v)
    {
        return {
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x
        };
    }

    template <typename T, usize N>
    T distance(const vec<T, N>& u, const vec<T, N>& v)
    {
        return len(u - v);
    }

    template <typename T, usize N>
    T angle(const vec<T, N>& u, const vec<T, N>& v)
    {
        const T divisor = len(u) * len(v);

        if (divisor == T(0))
            return T(0);

        const T cos = dot(u, v) / divisor;
        return (cos <= T(1)) ? acos(cos) : T(0);
    }

    template <typename T, usize N>
    vec<T, N> lerp(const vec<T, N>& u, const vec<T, N>& v, T percent)
    {
        vec<T, N> r;
        for (int i = 0; i < N; ++i)
            r[i] = (T(1) - percent) * u[i] + percent * v[i];
        return r;
    }
}
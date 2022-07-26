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
export module tornasol:matrix;
import std.core;
import :types;
import :vector;

using namespace std;

export namespace tornasol 
{
    template <typename T, usize M, usize N = M>
    class mat;

    template <typename T = float> using mat2 = mat<T, 2>;
    template <typename T = float> using mat3 = mat<T, 3>;
    template <typename T = float> using mat4 = mat<T, 4>;

    template <typename T, usize M, usize N>
    class mat
    {
    private:
        vec<T, N> data[M];    

    public:
        mat() = default;

        mat(initializer_list<T> arr) 
        {   
            assert(arr.size() == M * N);

            for (usize i = 0; i < M; ++i)
            for (usize j = 0; j < N; ++j)
                data[i][j] = *(arr.begin() + j * M + i);
        }

        explicit 
        mat(T value) 
        {
            for (usize i = 0; i < M; ++i)
            for (usize j = 0; j < N; ++j)
                if (i == j) data[i][j] = value;
                else        data[i][j] = T(0);
        }

        vec<T, N>& operator [] (usize i) {
            assert(i < M); return data[i];
        }

        const vec<T, N>& operator [] (usize i) const {
            assert(i < M); return data[i];
        }
    };

    template <typename T, usize M, usize N>
    bool operator == (const mat<T, M, N>& a, const mat<T, M, N>& b)
    {
        for (usize i = 0; i < M; ++i)
            if (a[i] != b[i]) return false;

        return true;
    }

    template <typename T, usize M, usize N>
    bool operator != (const mat<T, M, N>& a, const mat<T, M, N>& b)
    {
        return !(a == b);
    }


    template <typename T, usize M, usize N>
    mat<T, M, N> operator - (const mat<T, M, N>& m)
    {
        mat<T, M, N> r;
        for (usize i = 0; i < M; ++i)
            r[i] = -m[i];
        return r;
    }

    template <typename T, usize M, usize N>
    mat<T, M, N> operator + (const mat<T, M, N>& m)
    {
        return m;
    }

    template <typename T, usize M, usize N>
    mat<T, M, N> operator + (const mat<T, M, N>& a, const mat<T, M, N>& b)
    {
        mat<T, M, N> c;
        for (usize i = 0; i < M; ++i)
            c[i] = a[i] + b[i];
        return c;
    }

    template <typename T, usize M, usize N>
    mat<T, M, N> operator - (const mat<T, M, N>& a, const mat<T, M, N>& b)
    {
        mat<T, M, N> c;
        for (usize i = 0; i < M; ++i)
            c[i] = a[i] - b[i];
        return c;
    }

    template <typename T, usize M, usize N>
    mat<T, M, N> operator * (const mat<T, M, N>& m, T s)
    {
        mat<T, M, N> r;
        for (usize i = 0; i < M; ++i)
            r[i] = m[i] * s;
        return r;
    }

    template <typename T, usize M, usize N>
    mat<T, M, N> operator * (T s, const mat<T, M, N>& m)
    {
        mat<T, M, N> r;
        for (usize i = 0; i < M; ++i)
            r[i] = s * m[i];
        return r;
    }

    template <typename T, usize M, usize N>
    mat<T, M, N> operator / (const mat<T, M, N>& m, T s)
    {
        mat<T, M, N> r;
        for (usize i = 0; i < M; ++i)
            r[i] = m[i] / s;
        return r;
    }

    template <typename T, usize M, usize N, usize P>
    mat<T, P, N> operator * (const mat<T, M, N>& a, const mat<T, P, M>& b)
    {
        mat<T, P, N> c;

        for (usize i = 0; i < P; ++i)
        for (usize j = 0; j < N; ++j)
        {
            c[i][j] = T(0);

            for (usize k = 0; k < M; ++k)
                c[i][j] += a[k][j] * b[i][k];
        }

        return c;
    }

    template <typename T, usize M, usize N> 
    vec<T, N> operator * (const mat<T, M, N>& m, const vec<T, M>& v)
    {
        vec<T, N> r;

        for (usize i = 0; i < N; ++i)
        {
            r[i] = T(0);

            for (usize j = 0; j < M; ++j)
                r[i] += m[j][i] * v[j];
        }

        return r;    
    }

    template <typename T, usize M, usize N>
    vec<T, M> operator * (const vec<T, N> &v, const mat<T, M, N>& m)
    {
        vec<T, M> r;

        for (usize i = 0; i < M; ++i)
        {
            r[i] = T(0);

            for (usize j = 0; j < N; ++j)
                r[i] += v[j] * m[i][j];
        }

        return r;
    }

    template <typename T, usize M, usize N>
    mat<T, N, M> transpose(const mat<T, M, N>& m)
    {
        mat<T, N, M> t;

        for (usize i = 0; i < N; ++i)
        for (usize j = 0; j < M; ++j)
            t[j][i] = m[i][j];

        return t;
    }

    template <typename T, usize M>
    mat<T, M-1> submat(const mat<T, M>& m, usize col, usize row)
    {
        mat<T, M-1> c;
        
        for (usize i = 0; i < M; ++i) 
        for (usize j = 0; j < M; ++j)
            if (i != col && j != row) 
                c[i < col ? i : i-1][j < row ? j : j-1] = m[i][j];
        return c;
    }

    template <typename T, usize M>
    T cofactor(const mat<T, M>& m, usize col, usize row)
    {
        mat<T, M-1> c = submat(m, col, row);  
    
        return ((col + row) % 2 == 0) ? +det(c) : -det(c);
    }

    template <typename T>
    T det(const mat<T, 1>& m)
    {
        return m[0][0];
    }

    template <typename T, usize M>
    T det(const mat<T, M>& m)
    {
        T d = T(0);

        for (usize i = 0; i < M; ++i)
            d += m[0][i] * cofactor(m, 0, i);

        return d;
    }

    template <typename T, usize M>
    mat<T, M> adj(const mat<T, M>& m)
    {
        mat<T, M> a;

        for (usize i = 0; i < M; ++i)
        for (usize j = 0; j < M; ++j)
            a[i][j] = cofactor(m, i, j);

        return transpose(a);
    }

    template <typename T, usize M>
    mat<T, M> inv(const mat<T, M, M>& m)
    {
        assert(det(m) != 0);
        return adj(m) / det(m);
    }
}
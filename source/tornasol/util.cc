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

export module tornasol:util;
import std.core;
import :matrix;
import :types;
import :vector;

using namespace std;

export namespace tornasol 
{
    template <typename ... A>
    void print(string_view fmt, A&& ...args)
    {
        cout << vformat(fmt, make_format_args(forward<A>(args)...)) 
             << endl;
    }

    template <typename T, usize N>
    void print(const vec<T, N>& v)
    {
        for (usize i = 0; i < N; ++i)
            cout << format("{}", v[i]) << endl;
        cout << endl;
    }

    template <typename T, usize M, usize N>
    void print(const mat<T, M, N>& m)
    {
        for (usize row = 0; row < N; ++row)
        {
            for (usize col = 0; col < M; ++col)
                cout << format("{} ", m[col][row]);
            cout << endl;
        }
        cout << endl;
    }
}
/*
    Copyright (c) 2020-2022 Leonardo Larrad

    This software is provided 'as-is', without any express or implied
    warranty.  In no event will the authors be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to al ter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.
    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
*/

export module tornasol:transform;
import std.core;
import :types;
import :matrix;
using namespace std;

export namespace tornasol 
{
    template<typename T = f32>
    mat4<T> ortho(T left, T right, T bottom, T top, T near, T far)
    {
        mat4<T> r(T(1));
        r[0][0] = +T(2) / (right - left);
        r[1][1] = +T(2) / (top - bottom);
        r[2][2] = -T(2) / (far - near);
        r[3][0] = -(right + left) / (right - left);
        r[3][1] = -(top + bottom) / (top - bottom);
        r[3][2] = -(far + near) / (far - near);
        return r;
    }

    template<typename T = f32>
    mat4<T> ortho(T left, T right, T bottom, T top) 
    {
        return ortho<T>(left, right, bottom, top, T(-1), T(1));
    }

    template<typename T = f32>
    mat4<T>& move(mat4<T>& m, const vec3<T>& v)
    {
        m[3][0] += v.x;
        m[3][1] += v.y;
        m[3][2] += v.z;
        return m;
    }

    template<typename T = f32>
    mat4<T>& scale(mat4<T>& m, const vec3<T>& v)
    {
        m[0][0] *= v.x;
        m[1][1] *= v.y;
        m[2][2] *= v.z;
        return m;
    }

    template<typename T = f32>
    mat4<T>& rotate(mat4<T>& m, const vec3<T>& v)
    {
        // where v is a vector in the form (x, y, z)
        // of angles to rotate
        // x is the angle to rotate around the x axis
        // y is the angle to rotate around the y axis
        // z is the angle to rotate around the z axis

        // create the rotation matrices
        mat4<T> rx(T(1));
        rx[1][1] = +cos(v.x);
        rx[1][2] = -sin(v.x);
        rx[2][1] = +sin(v.x);
        rx[2][2] = +cos(v.x);
        mat4<T> ry(T(1));
        ry[0][0] = +cos(v.y);
        ry[0][2] = +sin(v.y);
        ry[2][0] = -sin(v.y);
        ry[2][2] = +cos(v.y);
        mat4<T> rz(T(1));
        rz[0][0] = +cos(v.z);
        rz[0][1] = -sin(v.z);
        rz[1][0] = +sin(v.z);
        rz[1][1] = +cos(v.z);

        // rotate the matrix
        m = (rz + ry + rx) * m;
        return m;
    }



}
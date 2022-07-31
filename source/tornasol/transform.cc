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
    mat4<T>& translate(mat4<T>& m, const vec3<T>& v)
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
    mat4<T>& rotate(mat4<T>& m, T a,  const vec3<T>& v)
    {   
        T c = cos(a);
        T s = sin(a);

        vec3<T> axis = normalize(v);
        vec3<T> temp = (T(1)-c) * axis;
        
        mat4<T> r;
        r[0][0] = c + temp.x * axis.x;
        r[0][1] = temp.x * axis.y + s * axis.z;
        r[0][2] = temp.x * axis.z - s * axis.y;
        r[1][0] = temp.y * axis.x - s * axis.z;
        r[1][1] = c + temp.y * axis.y;
        r[1][2] = temp.y * axis.z + s * axis.x;
        r[2][0] = temp.z * axis.x + s * axis.y;
        r[2][1] = temp.z * axis.y - s * axis.x;
        r[2][2] = c + temp.z * axis.z;

        mat4<T> z;
        z[0] = m[0] * r[0][0] + m[1] * r[0][1] + m[2] * r[0][2];
        z[1] = m[0] * r[1][0] + m[1] * r[1][1] + m[2] * r[1][2];
        z[2] = m[0] * r[2][0] + m[1] * r[2][1] + m[2] * r[2][2];
        z[3] = m[3];
        m = z;
        return m;
    }

    class transform {
    public:
        vec3<> pos;
        vec3<> rot;
        vec3<> sca;
            
        transform() 
            : pos({0.0f, 0.0f, 0.0f}),
              rot({0.0f, 0.0f, 0.0f}),
              sca({1.0f, 1.0f, 1.0f}) {}

        transform(vec3<> pos) 
            : pos(pos),
              rot({0.0f, 0.0f, 0.0f}),
              sca({1.0f, 1.0f, 1.0f}) {}

        mat4<> get_mat() const
        {
            mat4<> m(1.0f);
            rotate(m, rot.x, { 1, 0, 0 });
            rotate(m, rot.y, { 0, 1, 0 });
            rotate(m, rot.z, { 0, 0, 1 });
            translate(m, pos);
            scale(m, sca);
            return m;
        }
    };
}
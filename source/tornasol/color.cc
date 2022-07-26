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

export module tornasol:color;
import :types;
import :vector;

export namespace tornasol 
{
    class color
    {
    public:
        float r, g, b, a;

        color() = default;

        color(float r, float g, float b)
            : r(r), g(g), b(b), a(1.0f) {}

        color(float r, float g, float b, float a)
            : r(r), g(g), b(b), a(a) {}

        color(u32 hex)
            : r(((hex >> 24) & 0xFF) / 255.0f)
            , g(((hex >> 16) & 0xFF) / 255.0f)
            , b(((hex >> 8)  & 0xFF) / 255.0f)
            , a(((hex >> 0)  & 0xFF) / 255.0f) {}

        bool operator == (const color& other) const = default;
        bool operator != (const color& other) const = default;

        explicit
        operator vec3<>() const { return { r, g, b }; }
        operator vec4<>() const { return { r, g, b, a }; }
    };

    color darken(const color& c, float percent)
    {
        return {
            c.r * (1.0f - percent),
            c.g * (1.0f - percent),
            c.b * (1.0f - percent),
            c.a
        };
    }

    color lighten(const color& c, float percent)
    {
        return {
            c.r + (1.0f - c.r) * percent,
            c.g + (1.0f - c.g) * percent,
            c.b + (1.0f - c.b) * percent,
            c.a
        };
    }

    color blend(const color& under, const color& over)
    {
        float alpha = under.a * (1.0f - over.a) + over.a;

        if (alpha == 0.0f)
            return { 0.0f, 0.0f, 0.0f, 0.0f };

        return {
            (under.r * under.a * (1.0f - over.a) + over.r * over.a) / alpha,
            (under.g * under.a * (1.0f - over.a) + over.g * over.a) / alpha,
            (under.b * under.a * (1.0f - over.a) + over.b * over.a) / alpha,
            alpha
        };
    }

    color lerp(const color& from, const color& to, float percent)
    {
        return {
            (1.0f - percent) * from.r + percent * to.r,
            (1.0f - percent) * from.g + percent * to.g,
            (1.0f - percent) * from.b + percent * to.b,
            (1.0f - percent) * from.a + percent * to.a
        };
    }

    color operator + (const color& left, const color& right)
    {
        return {
            left.r + right.r,
            left.g + right.g,
            left.b + right.b,
            left.a + right.a
        };
    }

    color operator - (const color& left, const color& right)
    {
        return {
            left.r - right.r,
            left.g - right.g,
            left.b - right.b,
            left.a - right.a
        };
    }

    color operator * (const color& left, const color& right)
    {
        return {
            left.r * right.r,
            left.g * right.g,
            left.b * right.b,
            left.a * right.a
        };
    }

    color operator / (const color& left, const color& right)
    {
        return {
            left.r / right.r,
            left.g / right.g,
            left.b / right.b,
            left.a / right.a
        };
    }

    color operator * (const color& c, float scalar)
    {
        return {
            c.r * scalar,
            c.g * scalar,
            c.b * scalar,
            c.a * scalar
        };
    }

    color operator * (float scalar, const color& c)
    {
        return c * scalar;
    }

    color operator / (const color& c, float scalar)
    {
        return {
            c.r / scalar,
            c.g / scalar,
            c.b / scalar,
            c.a / scalar
        };
    }

    color operator / (float scalar, const color& c)
    {
        return c / scalar;
    }

    color operator - (const color& c)
    {
        return {
            1.0f / c.r,
            1.0f / c.g,
            1.0f / c.b,
            1.0f / c.a
        };
    }
}
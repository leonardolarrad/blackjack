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

#include <thirdparty/glad/glad.h>;
export module tornasol:glad;
import std.core;

export namespace tornasol::glad
{
    using load_proc = GLADloadproc;

    int load_gl_loader(load_proc load) {
        return gladLoadGLLoader(load);
    }
}

export namespace tornasol 
{    
    class glad_dep
    {
    private:
        const glad::load_proc proc;

    public:
        glad_dep(glad::load_proc proc)
            : proc(proc) {}

        void load() 
        {
            if (!glad::load_gl_loader(proc))
                throw std::runtime_error("failed to load glad");
        }
    };
} 
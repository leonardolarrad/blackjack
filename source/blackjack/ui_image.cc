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

export module blackjack:image;

import std.core;
import std.filesystem;
import tornasol;

using namespace std;
using namespace std::filesystem;
using namespace tornasol;

export namespace blackjack {

    class ui_image : public entity {
    private:
        texture_renderer tex;
    public:
        ui_image() = default;

        void set_image(path path) 
        {
            image img = image(path);
            tex.set_rect({ 0.0f, 0.0f, (f32)img.width, (f32)img.height });
            tex.set_image(img);
        }

        void render(renderer& renderer) override 
        {
            if (!enable)
                return;

            tex.set_model(trans.get_mat());
            renderer.render(tex);
        }
    };
}
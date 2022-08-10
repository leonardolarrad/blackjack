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

export module blackjack:def;
import tornasol;

export 
namespace blackjack {

    using ts::byte;
    
    using ts::u8;
    using ts::u16;
    using ts::u32;
    using ts::u64;
    using ts::i8;
    using ts::i16;
    using ts::i32;
    using ts::i64;
    using ts::f32;
    using ts::f64;

    using ts::usize;
    using ts::isize;

    using ts::shared;
    using ts::weak;
    using ts::unique;
}

export 
namespace bk = blackjack;
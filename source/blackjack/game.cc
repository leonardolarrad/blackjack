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

export module blackjack:game;

import :hand;
import :card;

import tornasol;

export namespace blackjack {

    enum class game_state : u8 {
        idle,
        playing,
        finished,
    };

    enum class game_result : u8 {
        none,
        player_win,
        dealer_win,
        tie,
    };

    string game_result_name(game_result result) {
        switch (result) {
            case game_result::none:     return "none";
            case game_result::player_win:    return "player_win";
            case game_result::dealer_win:    return "dealer_win";
            case game_result::tie:      return "tie";
            default:                     return "unknown";
        }
    }

    enum class game_action : u8 {
        none,
        hit,
        stand,
        double_down,
        split,
        surrender,
    };

    string game_action_name(game_action action) {
        switch (action) {
            case game_action::none:     return "none";
            case game_action::hit:      return "hit";
            case game_action::stand:    return "stand";
            case game_action::double_down:  return "double_down";
            case game_action::split:    return "split";
            case game_action::surrender: return "surrender";
            default:                     return "unknown";
        }
    }

    enum class game_result_type : u8 {
        none,
        player_win,
        dealer_win,
        tie,
    };

    string game_result_type_name(game_result_type type) {
        switch (type) {
            case game_result_type::none:     return "none";
            case game_result_type::player_win:    return "player_win";
            case game_result_type::dealer_win:    return "dealer_win";
            case game_result_type::tie:      return "tie";
            default:                     return "unknown";
        }
    }

    enum class game_result_type_action : u8

}
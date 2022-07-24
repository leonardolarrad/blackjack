/*
    Copyright (c) 2020-2022 Leonardo Larrad

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
#include <thirdparty/glfw/glfw3.h>

export module tornasol:glfw;
import std.core;
import :size;
import :types;
import :vector;
import :version;

using namespace std;

export namespace tornasol::glfw {

    /* initialization, version and error module */

    using error_func = GLFWerrorfun;

    enum class error
    {
        no_error            = GLFW_NO_ERROR,
        not_initialized     = GLFW_NOT_INITIALIZED,
        no_current_context  = GLFW_NO_CURRENT_CONTEXT,
        invalid_value       = GLFW_INVALID_VALUE,
        invalid_enum        = GLFW_INVALID_ENUM,
        out_of_memory       = GLFW_OUT_OF_MEMORY,
        api_unavailable     = GLFW_API_UNAVAILABLE,
        version_unavailable = GLFW_VERSION_UNAVAILABLE,
        platform_error      = GLFW_PLATFORM_ERROR,
        format_unavailable  = GLFW_FORMAT_UNAVAILABLE,
        no_window_context   = GLFW_NO_WINDOW_CONTEXT
    };

    version get_version() 
    {
        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);
        return version(major, minor, rev);
    }

    int init() 
    { return glfwInit(); } 

    void terminate()
    { glfwTerminate(); }   

    error get_error(const char** desc)
    { return error(glfwGetError(desc)); }

    void set_error_callback(error_func callback) 
    { glfwSetErrorCallback(callback); }

    /* window module */

    using image_handle          = GLFWimage*;
    using user_handle           = void*;
    using window_handle         = GLFWwindow*;
    using monitor_handle        = GLFWmonitor*;
    using window_pos_func       = void (*)(window_handle, int, int);
    using window_size_func      = void (*)(window_handle, int, int);
    using window_close_func     = void (*)(window_handle);
    using window_refresh_func   = void (*)(window_handle);
    using window_focus_func     = void (*)(window_handle, int);
    using window_iconify_func   = void (*)(window_handle, int);
    using window_maximize_func  = void (*)(window_handle, int);
    using framebuffer_size_func = void (*)(window_handle, int, int);

    enum class attribute
    {  
        resizable                = GLFW_RESIZABLE,
        visible                  = GLFW_VISIBLE,
        decorated                = GLFW_DECORATED,
        focused                  = GLFW_FOCUSED,
        auto_iconify             = GLFW_AUTO_ICONIFY,
        floating                 = GLFW_FLOATING,
        maximized                = GLFW_MAXIMIZED,
        center_cursor            = GLFW_CENTER_CURSOR,
        transparent_framebuffer  = GLFW_TRANSPARENT_FRAMEBUFFER,
        focus_on_show            = GLFW_FOCUS_ON_SHOW,
        scale_to_monitor         = GLFW_SCALE_TO_MONITOR,
        red_bits                 = GLFW_RED_BITS,
        green_bits               = GLFW_GREEN_BITS,
        blue_bits                = GLFW_BLUE_BITS,
        alpha_bits               = GLFW_ALPHA_BITS,
        depth_bits               = GLFW_DEPTH_BITS,
        stencil_bits             = GLFW_STENCIL_BITS,
        accum_red_bits           = GLFW_ACCUM_RED_BITS,
        accum_green_bits         = GLFW_ACCUM_GREEN_BITS,
        accum_blue_bits          = GLFW_ACCUM_BLUE_BITS,
        accum_alpha_bits         = GLFW_ACCUM_ALPHA_BITS,
        aux_buffers              = GLFW_AUX_BUFFERS,
        samples                  = GLFW_SAMPLES,
        refresh_rate             = GLFW_REFRESH_RATE,
        stereo                   = GLFW_STEREO,
        srgb_capable             = GLFW_SRGB_CAPABLE,
        doublebuffer             = GLFW_DOUBLEBUFFER,
        client_api               = GLFW_CLIENT_API,
        context_ver_major        = GLFW_CONTEXT_VERSION_MAJOR,
        context_ver_minor        = GLFW_CONTEXT_VERSION_MINOR,
        context_robustness       = GLFW_CONTEXT_ROBUSTNESS,
        context_release_behavior = GLFW_CONTEXT_RELEASE_BEHAVIOR,
        gl_forward_compat        = GLFW_OPENGL_FORWARD_COMPAT,
        gl_debug_context         = GLFW_OPENGL_DEBUG_CONTEXT,
        gl_profile               = GLFW_OPENGL_PROFILE
    };  
     
    enum class client_api
    {
        opengl    = GLFW_OPENGL_API,
        opengl_es = GLFW_OPENGL_ES_API,
        none      = GLFW_NO_API
    };

    enum class gl_profile
    {
        any           = GLFW_OPENGL_ANY_PROFILE,
        core          = GLFW_OPENGL_CORE_PROFILE,
        compatibility = GLFW_OPENGL_COMPAT_PROFILE
    };

    void set_default_window_hints() 
    { glfwDefaultWindowHints(); }
    
    void window_hint(attribute hint, int value) 
    { glfwWindowHint((int)hint, value); }      

    void window_hint(attribute hint, bool value) 
    { glfwWindowHint((int)hint, (int)value); }  

    void window_hint(attribute hint, const char* value) 
    { glfwWindowHintString((int)hint, value); }
    
    window_handle create_window(int width, int height, const char* title,
        monitor_handle monitor, window_handle share) 
    { return glfwCreateWindow(width, height, title, monitor, share); }
    
    void destroy_window(window_handle window) 
    { glfwDestroyWindow(window); }
            
    void set_window_user_pointer(window_handle window, user_handle pointer) 
    { glfwSetWindowUserPointer(window, pointer); }

    user_handle get_window_user_pointer(window_handle window) 
    { return glfwGetWindowUserPointer(window); }

    bool window_should_close(window_handle window) 
    { return (bool) glfwWindowShouldClose(window); }

    void set_window_should_close(window_handle window, bool value) 
    { glfwSetWindowShouldClose(window, (int) value); }

    void set_window_title(window_handle window, const char* title) 
    { glfwSetWindowTitle(window, title); }

    void set_window_icon(window_handle window, int count, 
        const image_handle images) 
    { glfwSetWindowIcon(window, count, images); }

    void set_window_monitor(window_handle window, monitor_handle monitor,
        int x, int y, int w, int h, int refresh_rate) 
    { glfwSetWindowMonitor(window, monitor, x, y, w, h, refresh_rate); }

    void set_window_pos(window_handle window, int xpos, int ypos) 
    { glfwSetWindowPos(window, xpos, ypos); }
    
    void get_window_pos(window_handle window, int* xpos, int* ypos) 
    { glfwGetWindowPos(window, xpos, ypos); }

    void set_window_size(window_handle window, int width, int height) 
    { glfwSetWindowSize(window, width, height); }

    void get_window_size(window_handle window, int* width, int* height) 
    { glfwGetWindowSize(window, width, height); }

    void set_window_size_limits(window_handle window, 
        int min_w, int min_h, int max_w, int max_h) 
    { glfwSetWindowSizeLimits(window, min_w, min_h, max_w, max_h); }
    
    void set_window_aspect_ratio(window_handle window, int num, int den) 
    { glfwSetWindowAspectRatio(window, num, den); }
                    
    void get_window_framebuffer_size(window_handle window, int* w, int* h) 
    { glfwGetFramebufferSize(window, w, h); }

    void set_window_opacity(window_handle window, float opacity) 
    { glfwSetWindowOpacity(window, opacity); }

    float get_window_opacity(window_handle window) 
    { return glfwGetWindowOpacity(window); }

    void get_window_content_scale(window_handle window, float* x, float* y) 
    { glfwGetWindowContentScale(window, x, y); }
    
    void iconify_window(window_handle window) 
    { glfwIconifyWindow(window); }

    void restore_window(window_handle window) 
    { glfwRestoreWindow(window); }

    void show_window(window_handle window) 
    { glfwShowWindow(window); }

    void hide_window(window_handle window) 
    { glfwHideWindow(window); }

    void focus_window(window_handle window) 
    { glfwFocusWindow(window); }

    void request_window_attention(window_handle window) 
    { glfwRequestWindowAttention(window); }

    void maximize_window(window_handle window) 
    { glfwMaximizeWindow(window); }

    monitor_handle get_window_monitor(window_handle window) 
    { return glfwGetWindowMonitor(window); }

    void set_window_attribute(window_handle window, 
        attribute attrib, int value) 
    { glfwSetWindowAttrib(window, (int)attrib, value); }

    void set_window_attribute(window_handle window, 
        attribute attrib, bool value) 
    { glfwSetWindowAttrib(window, (int)attrib, (int) value); }

    int get_window_attribute(window_handle window, 
        attribute attrib) 
    { return glfwGetWindowAttrib(window, (int)attrib); }

    window_pos_func set_window_pos_callback(window_handle window, 
        window_pos_func callback) 
    { return glfwSetWindowPosCallback(window, callback); }

    window_size_func set_window_size_callback(window_handle window, 
        window_size_func callback) 
    { return glfwSetWindowSizeCallback(window, callback); }

    window_close_func set_window_close_callback(window_handle window, 
        window_close_func callback) 
    { return glfwSetWindowCloseCallback(window, callback); }

    window_refresh_func set_window_refresh_callback(window_handle window, 
        window_refresh_func callback) 
    { return glfwSetWindowRefreshCallback(window, callback); }

    window_focus_func set_window_focus_callback(window_handle window, 
        window_focus_func callback) 
    { return glfwSetWindowFocusCallback(window, callback); }

    window_iconify_func set_window_iconify_callback(window_handle window, 
        window_iconify_func callback) 
    { return glfwSetWindowIconifyCallback(window, callback); }

    window_maximize_func set_window_maximize_callback(window_handle window, 
        window_maximize_func callback) 
    { return glfwSetWindowMaximizeCallback(window, callback); }

    framebuffer_size_func set_window_framebuffer_size_callback(
        window_handle window, framebuffer_size_func callback) 
    { return glfwSetFramebufferSizeCallback(window, callback); }

    void poll_events() 
    { glfwPollEvents(); }

    void wait_events() 
    { glfwWaitEvents(); }

    void wait_events_timeout(double timeout) 
    { glfwWaitEventsTimeout(timeout); }

    void post_empty_event() 
    { glfwPostEmptyEvent(); }

    void swap_buffers(window_handle window) 
    { glfwSwapBuffers(window); }

    /* input module */
    
    using cursor_handle     = GLFWcursor*;
    using mouse_button_func = GLFWmousebuttonfun;
    using cursor_pos_func   = GLFWcursorposfun;
    using cursor_enter_func = GLFWcursorenterfun;
    using scroll_func       = GLFWscrollfun;
    using mouse_scroll_func = GLFWscrollfun;
    using key_func          = GLFWkeyfun;
    using char_func         = GLFWcharfun;
    using char_mods_func    = GLFWcharmodsfun;
    using drop_func         = GLFWdropfun;
   
    enum class key 
    {
        unknown       = GLFW_KEY_UNKNOWN,
        space         = GLFW_KEY_SPACE,
        apostrophe    = GLFW_KEY_APOSTROPHE,
        comma         = GLFW_KEY_COMMA,
        minus         = GLFW_KEY_MINUS,
        period        = GLFW_KEY_PERIOD,
        slash         = GLFW_KEY_SLASH,
        num_0         = GLFW_KEY_0,
        num_1         = GLFW_KEY_1,
        num_2         = GLFW_KEY_2,
        num_3         = GLFW_KEY_3,
        num_4         = GLFW_KEY_4,
        num_5         = GLFW_KEY_5,
        num_6         = GLFW_KEY_6,
        num_7         = GLFW_KEY_7,
        num_8         = GLFW_KEY_8,
        num_9         = GLFW_KEY_9,
        semicolon     = GLFW_KEY_SEMICOLON,
        equal         = GLFW_KEY_EQUAL,
        a             = GLFW_KEY_A,
        b             = GLFW_KEY_B,
        c             = GLFW_KEY_C,
        d             = GLFW_KEY_D,
        e             = GLFW_KEY_E,
        f             = GLFW_KEY_F,
        g             = GLFW_KEY_G,
        h             = GLFW_KEY_H,
        i             = GLFW_KEY_I,
        j             = GLFW_KEY_J,
        k             = GLFW_KEY_K,
        l             = GLFW_KEY_L,
        m             = GLFW_KEY_M,
        n             = GLFW_KEY_N,
        o             = GLFW_KEY_O,
        p             = GLFW_KEY_P,
        q             = GLFW_KEY_Q,
        r             = GLFW_KEY_R,
        s             = GLFW_KEY_S,
        t             = GLFW_KEY_T,
        u             = GLFW_KEY_U,
        v             = GLFW_KEY_V,
        w             = GLFW_KEY_W,
        x             = GLFW_KEY_X,
        y             = GLFW_KEY_Y,
        z             = GLFW_KEY_Z,
        left_bracket  = GLFW_KEY_LEFT_BRACKET,
        backslash     = GLFW_KEY_BACKSLASH,
        right_bracket = GLFW_KEY_RIGHT_BRACKET,
        grave_accent  = GLFW_KEY_GRAVE_ACCENT,
        world_1       = GLFW_KEY_WORLD_1,
        world_2       = GLFW_KEY_WORLD_2,
        escape        = GLFW_KEY_ESCAPE,
        enter         = GLFW_KEY_ENTER,
        tab           = GLFW_KEY_TAB,
        backspace     = GLFW_KEY_BACKSPACE,
        insert        = GLFW_KEY_INSERT,
        del           = GLFW_KEY_DELETE,
        right         = GLFW_KEY_RIGHT,
        left          = GLFW_KEY_LEFT,
        down          = GLFW_KEY_DOWN,
        up            = GLFW_KEY_UP,
        page_up       = GLFW_KEY_PAGE_UP,
        page_down     = GLFW_KEY_PAGE_DOWN,
        home          = GLFW_KEY_HOME,
        end           = GLFW_KEY_END,
        caps_lock     = GLFW_KEY_CAPS_LOCK,
        scroll_lock   = GLFW_KEY_SCROLL_LOCK,
        num_lock      = GLFW_KEY_NUM_LOCK,
        print_screen  = GLFW_KEY_PRINT_SCREEN,
        pause         = GLFW_KEY_PAUSE,
        f1            = GLFW_KEY_F1,
        f2            = GLFW_KEY_F2,
        f3            = GLFW_KEY_F3,
        f4            = GLFW_KEY_F4,
        f5            = GLFW_KEY_F5,
        f6            = GLFW_KEY_F6,
        f7            = GLFW_KEY_F7,
        f8            = GLFW_KEY_F8,
        f9            = GLFW_KEY_F9,
        f10           = GLFW_KEY_F10,
        f11           = GLFW_KEY_F11,
        f12           = GLFW_KEY_F12,
        f13           = GLFW_KEY_F13,
        f14           = GLFW_KEY_F14,
        f15           = GLFW_KEY_F15,
        f16           = GLFW_KEY_F16,
        f17           = GLFW_KEY_F17,
        f18           = GLFW_KEY_F18,
        f19           = GLFW_KEY_F19,
        f20           = GLFW_KEY_F20,
        f21           = GLFW_KEY_F21,
        f22           = GLFW_KEY_F22,
        f23           = GLFW_KEY_F23,
        f24           = GLFW_KEY_F24,
        f25           = GLFW_KEY_F25,
        kp_0          = GLFW_KEY_KP_0,
        kp_1          = GLFW_KEY_KP_1,
        kp_2          = GLFW_KEY_KP_2,
        kp_3          = GLFW_KEY_KP_3,
        kp_4          = GLFW_KEY_KP_4,
        kp_5          = GLFW_KEY_KP_5,
        kp_6          = GLFW_KEY_KP_6,
        kp_7          = GLFW_KEY_KP_7,
        kp_8          = GLFW_KEY_KP_8,
        kp_9          = GLFW_KEY_KP_9,
        kp_decimal    = GLFW_KEY_KP_DECIMAL,
        kp_divide     = GLFW_KEY_KP_DIVIDE,
        kp_multiply   = GLFW_KEY_KP_MULTIPLY,
        kp_subtract   = GLFW_KEY_KP_SUBTRACT,
        kp_add        = GLFW_KEY_KP_ADD,
        kp_enter      = GLFW_KEY_KP_ENTER,
        kp_equal      = GLFW_KEY_KP_EQUAL,
        left_shift    = GLFW_KEY_LEFT_SHIFT,
        left_control  = GLFW_KEY_LEFT_CONTROL,
        left_alt      = GLFW_KEY_LEFT_ALT,
        left_super    = GLFW_KEY_LEFT_SUPER,
        right_shift   = GLFW_KEY_RIGHT_SHIFT,
        right_control = GLFW_KEY_RIGHT_CONTROL,
        right_alt     = GLFW_KEY_RIGHT_ALT,
        right_super   = GLFW_KEY_RIGHT_SUPER,
        menu          = GLFW_KEY_MENU
    };

    enum class key_mod 
    {
        shift     = GLFW_MOD_SHIFT,
        control   = GLFW_MOD_CONTROL,
        alt       = GLFW_MOD_ALT,
        super     = GLFW_MOD_SUPER,
        caps_lock = GLFW_MOD_CAPS_LOCK,
        num_lock  = GLFW_MOD_NUM_LOCK
    };

    enum class mouse_button
    {
        button_1 = GLFW_MOUSE_BUTTON_1,
        button_2 = GLFW_MOUSE_BUTTON_2,
        button_3 = GLFW_MOUSE_BUTTON_3,
        button_4 = GLFW_MOUSE_BUTTON_4,
        button_5 = GLFW_MOUSE_BUTTON_5,
        button_6 = GLFW_MOUSE_BUTTON_6,
        button_7 = GLFW_MOUSE_BUTTON_7,
        button_8 = GLFW_MOUSE_BUTTON_8,

        left     = GLFW_MOUSE_BUTTON_LEFT,
        right    = GLFW_MOUSE_BUTTON_RIGHT,
        middle   = GLFW_MOUSE_BUTTON_MIDDLE
    };

    enum class input_action 
    {
        press   = GLFW_PRESS,
        release = GLFW_RELEASE,
        repeat  = GLFW_REPEAT
    };

    enum class cursor_mode
    {
        cursor_normal   = GLFW_CURSOR_NORMAL,
        cursor_hidden   = GLFW_CURSOR_HIDDEN,
        cursor_disabled = GLFW_CURSOR_DISABLED
    };

    enum class cursor_standar
    {
        arrow             = GLFW_ARROW_CURSOR,
        ibeam             = GLFW_IBEAM_CURSOR,
        crosshair         = GLFW_CROSSHAIR_CURSOR,
        hand              = GLFW_HAND_CURSOR,
        resize_horizontal = GLFW_HRESIZE_CURSOR,
        resize_vertical   = GLFW_VRESIZE_CURSOR
    };

    int get_key_scancode(key key) 
    { return glfwGetKeyScancode((int)key); }

    input_action get_key(window_handle window, key key) 
    { return (input_action)glfwGetKey((GLFWwindow*)window, (int)key); }

    input_action get_mouse_button(window_handle w, mouse_button b) 
    { return (input_action)glfwGetMouseButton((GLFWwindow*)w, (int)b); }

    void get_cursor_pos(window_handle w, double* x, double* y) 
    { glfwGetCursorPos((GLFWwindow*)w, x, y); }

    void set_cursor_pos(window_handle w, double x, double y) 
    { glfwSetCursorPos((GLFWwindow*)w, x, y); }

    key_func set_key_callback(window_handle w, key_func f) 
    { return (key_func)glfwSetKeyCallback(w, f); }

    char_func set_char_callback(window_handle w, char_func f) 
    { return (char_func)glfwSetCharCallback(w, f); }

    char_mods_func set_char_mods_callback(window_handle w, 
        char_mods_func f)
    { return (char_mods_func)glfwSetCharModsCallback(w, f); }

    mouse_button_func set_mouse_button_callback(window_handle w, 
        mouse_button_func f)
    { return (mouse_button_func)glfwSetMouseButtonCallback(w, f); }

    cursor_pos_func set_cursor_pos_callback(window_handle w, 
        cursor_pos_func f)
    { return (cursor_pos_func)glfwSetCursorPosCallback(w, f); }

    cursor_enter_func set_cursor_enter_callback(window_handle w, 
        cursor_enter_func f)
    { return (cursor_enter_func)glfwSetCursorEnterCallback(w, f); }

    scroll_func set_scroll_callback(window_handle w, scroll_func f)
    { return (scroll_func)glfwSetScrollCallback(w, f); }

    /* context module */
    
    using gl_proc         = GLFWglproc;
    using gl_proc_address = void* (*)(const char* name);

    gl_proc get_proc_address(const char* proc_name) 
        { return glfwGetProcAddress(proc_name); }

    void make_context_current(window_handle window) 
        { glfwMakeContextCurrent(window); }

    window_handle get_current_context() 
        { return glfwGetCurrentContext(); }

    void swap_interval(int interval) 
        { glfwSwapInterval(interval); }

    int extension_supported(const char* extension) 
        { return glfwExtensionSupported(extension); }

    float get_time() { 
        return glfwGetTime(); 
    }

} /* namespace tornasol::glfw */

export namespace tornasol {

    class glfw_dep
    {
    private:
        static void error_callback(int code, const char* message)
        {
            assert(code != (int) glfw::error::not_initialized);
            assert(code != (int) glfw::error::no_current_context);
            assert(code != (int) glfw::error::no_window_context);
            assert(code != (int) glfw::error::invalid_value);
            assert(code != (int) glfw::error::invalid_enum);
            assert(code != (int) glfw::error::no_error);

            if (code == (int) glfw::error::out_of_memory)
                throw bad_alloc();
            else
                throw runtime_error(message);
        }

    public:
        glfw_dep() 
        {
            glfw::set_error_callback(error_callback);

            if (!glfw::init())
                throw runtime_error("failed to initialize glfw");
        }

        ~glfw_dep() {
            glfw::terminate();
        }

        glfw::gl_proc_address proc() {
            return (glfw::gl_proc_address) glfw::get_proc_address;
        }
    };

} /* namespace tornasol */
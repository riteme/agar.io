//
// Copyright 2016 HNSDFZ-OIER
//

#ifndef RENDER_OPENGL330_HPP_
#define RENDER_OPENGL330_HPP_

#ifdef __UNIX__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <glew.h>
#endif  // IFDEF __UNIX__

#include <cstdint>
#include <vector>
#include <functional>
#include <unordered_map>

// thirdparty library glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define BACKEND_OPENGL330

namespace render {

typedef char16_t CharType;

void Initialize();
void Terminate();

///////////////
// Resources //
///////////////

class Image {
 public:
    Image() = delete;
    Image(const CharType *filepath);
    ~Image();

    Image(const Image &) = delete;
    auto operator=(const Image &) -> Image & = delete;

    Image(Image &&) = delete;
    auto operator=(Image && ) -> Image & = delete;

    void Save(const CharType *filepath);
    auto GetWidth() const -> int;
    auto GetHeight() const -> int;
    auto IsValid() const -> bool;

 private:
    friend class Window;

    SDL_Surface *m_pSurface;
};  // class Image

//////////////
// Platform //
//////////////

enum class EventType {
    Close,
    Resize,
    MouseMotion,
    MouseWheel,
    MouseClick,
    Keyboard,
};  // enum class EventType

enum class MouseButton {
    Left = SDL_BUTTON_LEFT,
    Middle = SDL_BUTTON_MIDDLE,
    Right = SDL_BUTTON_RIGHT,
};  // enum class MouseButton

enum class Keycode {
    Unknown = 0,
    A = SDLK_a,
    B = SDLK_b,
    C = SDLK_c,
    D = SDLK_d,
    E = SDLK_e,
    F = SDLK_f,
    G = SDLK_g,
    H = SDLK_h,
    I = SDLK_i,
    J = SDLK_j,
    K = SDLK_k,
    L = SDLK_l,
    M = SDLK_m,
    N = SDLK_n,
    O = SDLK_o,
    P = SDLK_p,
    Q = SDLK_q,
    R = SDLK_r,
    S = SDLK_s,
    T = SDLK_t,
    U = SDLK_u,
    V = SDLK_v,
    W = SDLK_w,
    X = SDLK_x,
    Y = SDLK_y,
    Z = SDLK_z,
    Num0 = SDLK_0,
    Num1 = SDLK_1,
    Num2 = SDLK_2,
    Num3 = SDLK_3,
    Num4 = SDLK_4,
    Num5 = SDLK_5,
    Num6 = SDLK_6,
    Num7 = SDLK_7,
    Num8 = SDLK_8,
    Num9 = SDLK_9,
    Numpad0 = SDLK_KP_0,
    Numpad1 = SDLK_KP_1,
    Numpad2 = SDLK_KP_2,
    Numpad3 = SDLK_KP_3,
    Numpad4 = SDLK_KP_4,
    Numpad5 = SDLK_KP_5,
    Numpad6 = SDLK_KP_6,
    Numpad7 = SDLK_KP_7,
    Numpad8 = SDLK_KP_8,
    Numpad9 = SDLK_KP_9,
    Quote = SDLK_QUOTE,
    Backslash = SDLK_BACKSLASH,
    Backspace = SDLK_BACKSPACE,
    CapsLock = SDLK_CAPSLOCK,
    Comma = SDLK_COMMA,
    Delete = SDLK_DELETE,
    Down = SDLK_DOWN,
    End = SDLK_END,
    Equal = SDLK_EQUALS,
    Escape = SDLK_ESCAPE,
    F1 = SDLK_F1,
    F2 = SDLK_F2,
    F3 = SDLK_F3,
    F4 = SDLK_F4,
    F5 = SDLK_F5,
    F6 = SDLK_F6,
    F7 = SDLK_F7,
    F8 = SDLK_F8,
    F9 = SDLK_F9,
    F10 = SDLK_F10,
    F11 = SDLK_F11,
    F12 = SDLK_F12,
    F13 = SDLK_F13,
    F14 = SDLK_F14,
    F15 = SDLK_F15,
    F16 = SDLK_F16,
    F17 = SDLK_F17,
    F18 = SDLK_F18,
    F19 = SDLK_F19,
    F20 = SDLK_F20,
    F21 = SDLK_F21,
    F22 = SDLK_F22,
    F23 = SDLK_F23,
    F24 = SDLK_F24,
    Backquote = SDLK_BACKQUOTE,
    Home = SDLK_HOME,
    Insert = SDLK_INSERT,
    LeftAlt = SDLK_LALT,
    LeftControl = SDLK_LCTRL,
    Left = SDLK_LEFT,
    Leftbracket = SDLK_LEFTBRACKET,
    LeftShift = SDLK_LSHIFT,
    Minus = SDLK_MINUS,
    NumLock = SDLK_NUMLOCKCLEAR,
    PageDown = SDLK_PAGEDOWN,
    PageUp = SDLK_PAGEUP,
    Period = SDLK_PERIOD,
    PrintScreen = SDLK_PRINTSCREEN,
    RightAlt = SDLK_RALT,
    RightControl = SDLK_RCTRL,
    RightShift = SDLK_RSHIFT,
    Return = SDLK_RETURN,
    Right = SDLK_RIGHT,
    Rightbracket = SDLK_RIGHTBRACKET,
    ScrollLock = SDLK_SCROLLLOCK,
    Semicolon = SDLK_SEMICOLON,
    Slash = SDLK_SLASH,
    Space = SDLK_SPACE,
    Tab = SDLK_TAB,
    Up = SDLK_UP,
    Ampersand = SDLK_AMPERSAND,
    Asterisk = SDLK_ASTERISK,
    At = SDLK_AT,
    Caret = SDLK_CARET,
    Colon = SDLK_COLON,
    Dollar = SDLK_DOLLAR,
    Exclaim = SDLK_EXCLAIM,
    Greater = SDLK_GREATER,
    Hash = SDLK_HASH,
    LeftParen = SDLK_LEFTPAREN,
    Less = SDLK_LESS,
    Percent = SDLK_PERCENT,
    Plus = SDLK_PLUS,
    Question = SDLK_QUESTION,
    DoubleQuote = SDLK_QUOTEDBL,
    RightParen = SDLK_RIGHTPAREN,
    Underscore = SDLK_UNDERSCORE,
};  // enum class Keycode

enum Modifier : unsigned {
    LCTRL = 1 << 0,
    RCTRL = 1 << 1,
    LSHIFT = 1 << 2,
    RSHIFT = 1 << 3,
    LALT = 1 << 4,
    RALT = 1 << 5,
    NUM_LOCK = 1 << 6,
    SCROLL_LOCK = 1 << 7,
    CAPS_LOCK = 1 << 8,
};  // enum Modifier

struct EventArgs {};  // struct EventArgs

struct CloseEventArgs : public EventArgs {};  // struct CloseEventArgs

struct ResizeEventArgs : public EventArgs {
    int width;
    int height;
};  // struct ResizeEventArgs

struct MouseMotionEventArgs : public EventArgs {
    int x;
    int y;
};  // struct MouseMotionEventArgs

struct MouseWheelEventArgs : public EventArgs {
    int x;
    int y;
    int offest_x;
    int offest_y;
};  // struct MouseWheelEventArgs

struct MouseClickEventArgs : public EventArgs {
    int x;
    int y;
    MouseButton button;
    bool pressed;
    bool released;
};  // struct MouseClickEventArgs

struct KeyboardEventArgs : public EventArgs {
    Keycode code;
    unsigned modifiers;
    bool pressed;
    bool released;
};  // struct KeyboardEventArgs

typedef std::function<void(void *, EventArgs *)> CallbackType;

}  // namespace render

template <>
struct std::hash<render::EventType> {
    auto operator()(const render::EventType &value) const noexcept -> size_t {
        return static_cast<size_t>(value);
    }
};  // struct std::hash<render::EventType>

namespace render {

class Window {
 public:
    Window() = delete;
    Window(const int width,
           const int height,
           const CharType *title,
           const Image &icon,
           const bool fullscreen = false);
    ~Window();

    Window(const Window &) = delete;
    auto operator=(const Window &) -> Window & = delete;

    Window(Window &&) = delete;
    auto operator=(Window && ) -> Window & = delete;

    void DoEvents();
    void AddHandler(const EventType &type, const CallbackType &callback);
    void RemoveHandlers(const EventType &type);

    void Close();
    void Resize(const int width, const int height);

    auto IsValid() const -> bool;

    void Raise(const EventType &type, EventArgs *args);

 private:
    friend void do_events();

    SDL_Window *m_pWindow;
    std::unordered_map<EventType, std::vector<CallbackType>> m_handlers;
};  // class Window

///////////////
// Rendering //
///////////////

class Texture {
 public:
    Texture() = delete;
    Texture(const Image &image);
    ~Texture();

    Texture(const Texture &) = delete;
    auto operator=(const Texture &) -> Texture & = delete;

    Texture(Texture &&) = delete;
    auto operator=(Texture && ) -> Texture & = delete;

    auto IsValid() const -> bool;
};  // class Texture

struct Vertex {
    float x, y, z;
    float r, g, b, a;
    float u, v;
    float nx, ny, nz;
};  // struct Vertex

class VertexBuffer {
 public:
    VertexBuffer() = delete;
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer &) = delete;
    auto operator=(const VertexBuffer &) -> VertexBuffer & = delete;

    VertexBuffer(VertexBuffer &&) = delete;
    auto operator=(VertexBuffer && ) -> VertexBuffer & = delete;

    auto IsValid() const -> bool;
};  // class VertexBuffer

class IndexBuffer {
 public:
    IndexBuffer() = delete;
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer &) = delete;
    auto operator=(const IndexBuffer &) -> IndexBuffer & = delete;

    IndexBuffer(IndexBuffer &&) = delete;
    auto operator=(IndexBuffer && ) -> IndexBuffer & = delete;

    auto IsValid() const -> bool;
};  // class IndexBuffer

enum class ShaderType {
    VertexShader,
    PixelShader,
};  // enum class ShaderType

class Shader {
 public:
    Shader() = delete;
    Shader(const CharType *filepath, const ShaderType &type);
    ~Shader();

    Shader(const Shader &) = delete;
    auto operator=(const Shader &) -> Shader & = delete;

    Shader(Shader &&) = delete;
    auto operator=(Shader && ) -> Shader & = delete;

    auto IsValid() const -> bool;
};  // class Shader

class ShaderProgram {
 public:
    ShaderProgram() = delete;
    ShaderProgram(Shader *vertex, Shader *pixel);
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram &) = delete;
    auto operator=(const ShaderProgram &) -> ShaderProgram & = delete;

    ShaderProgram(ShaderProgram &&) = delete;
    auto operator=(ShaderProgram && ) -> ShaderProgram & = delete;

    auto IsValid() const -> bool;
};  // class ShaderProgram

class Renderer {
 public:
    Renderer() = delete;
    Renderer(Window *window, ShaderProgram *program);
    ~Renderer();

    Renderer(const Renderer &) = delete;
    auto operator=(const Renderer &) -> Renderer & = delete;

    Renderer(Renderer &&) = delete;
    auto operator=(Renderer && ) -> Renderer & = delete;

    void SetProjectionMatrix(const glm::mat4 &matrix);
    void SetModelMatrix(const glm::mat4 &matrix);
    void SetViewMatrix(const glm::mat4 &matrix);

    void BindTexture(const Texture &texture);
    void UnbindAllTexture();

    void ResetShaderProgram(ShaderProgram *program);

    void CreateVertexBuffer(VertexBuffer *target, const int size, Vertex *data);
    void CreateIndexBuffer(IndexBuffer *target, const int size, unsigned *data);

    template <typename TContainer>
    void CreateVertexBuffer(VertexBuffer *target, const TContainer &data) {
        CreateVertexBuffer(target, data.size(), data.data());
    }

    template <typename TContainer>
    void CreateIndexBuffer(IndexBuffer *target, const TContainer &data) {
        CreateIndexBuffer(target, data.size(), data.data());
    }

    void Clear(const float red = 0.0f,
               const float green = 0.0f,
               const float blue = 0.0f,
               const float alpha = 1.0f);
    void Begin();
    void End();
    void Present();

    template <typename TBuffer>
    void DrawBuffer(const TBuffer &buffer);

    // In implementation
    // template <>
    // void Renderer::DrawBuffer(const VertexBuffer &buffer) {}
    // template <>
    // void Renderer::DrawBuffer(const IndexBuffer &buffer) {}
};  // class Renderer

}  // namespace render

#endif  // RENDER_OPENGL330_HPP_
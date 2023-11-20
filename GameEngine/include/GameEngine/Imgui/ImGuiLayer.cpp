#include <GameEngine/Imgui/ImGuiLayer.h>
#include <GameEnginePrecompiledHeader.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <GameEngine/Application.h>
#include <GameEngine/core.h>

namespace RendererEngine{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::onAttach(){
        // IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark(); // using dark colors

        // We are setting imgui flags
        // ImGuiIO& io = ImGui::GetIO()
        // Setting back end flags to mouse cursor and mouse positions.
        // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // // TEMPORARY: should eventually use the Game Engines key codes
		// io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		// io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		// io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		// io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		// io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		// io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		// io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		// io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		// io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		// io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		// io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		// io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		// io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		// io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		// io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		// io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		// io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		// io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		// io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		// io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		// io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;


        // Initializing the OpenGL3 ()
        ImGui_ImplGlfw_InitForOpenGL(Application::Get().GetWindow().ptr(), true);
        ImGui_ImplOpenGL3_Init("#version 120"); // We should check the version of GLSL (if there is an error with this version)
    }
    
    void ImGuiLayer::onDetach(){

    }

    void ImGuiLayer::onUpdate() {
        ImGuiIO& io = ImGui::GetIO();

        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().getWidth(), app.GetWindow().getHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = _time > 0.0f ? (time - _time) : (1.0f / 60.0f);
        _time = time;

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        bool show = true;

        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event& event) {
        // To dispatch out callback function we need to bind it (therefore using our bind function in core.h)

        // Here we need to now, start to dispatch all of these events
        // - When an event gets into a layer, we need to chheck that type
        // - Then to forward that event to this layer.
        // - Then we pass in a type of event, then propagate those events to these functions
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(bind_function(this, &ImGuiLayer::onMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(bind_function(this, &ImGuiLayer::onMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(bind_function(this, &ImGuiLayer::onMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(bind_function(this, &ImGuiLayer::onMouseButtonScrollEvent));
        dispatcher.Dispatch<KeyPressedEvent>(bind_function(this, &ImGuiLayer::onKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(bind_function(this, &ImGuiLayer::onKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(bind_function(this, &ImGuiLayer::onKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(bind_function(this, &ImGuiLayer::onWindowResizedEvent));
    }

    // In these functions the reasons why we return false is because we essentially want other layers to handle this.
    bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& e){
        ImGuiIO& io = ImGui::GetIO();

        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::onMouseButtonScrollEvent(MouseScrolledEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();

        return false;
    }

    // NOTE: The onKeyPressedEvent and onKeyReleasedEvent works! But just adding these two functions
    // Because eventually we may want to create our own key handler and mouse handler stuff as well. (Being from scratch)
    bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        // io.KeysDown[e.GetKeyCode()] = true;
        // io.AddKeyEvent((ImGuiKey)e.GetKeyCode(), true); 
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT] || io.KeysDown[GLFW_KEY_RIGHT];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER]; // This is dependent on platform key modified: cmd, super, windows
        return false;
    }

    bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;
        // io.AddKeyEvent((ImGuiKey)e.GetKeyCode(), false);
        return false;
    }

    bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();

        if(keycode > 0 && keycode < 0x10000){
            io.AddInputCharacter((unsigned short)keycode);
        }

        return false;
    }

    bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);

        glViewport(0, 0, e.GetWidth(), e.GetHeight());
        return false;
    }
};
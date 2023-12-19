if(APPLE)
    set(imgui_include "/usr/local/include/imgui")
elseif(WIN32)
    set(imgui_include "C:\\Desktop\\Libraries\\imgui")
elseif(UNIX AND NOT APPLE) # Linux-specific
    set(imgui_include "/usr/local/include/imgui")
endif()
include_directories(${imgui_include})

set(
    imgui_src
    ${imgui_include}/imgui_draw.cpp
    ${imgui_include}/imgui_widgets.cpp
    ${imgui_include}/imgui_tables.cpp
    ${imgui_include}/imgui_demo.cpp
    ${imgui_include}/imgui.cpp


    # ${imgui_include}/backends/imgui_impl_opengl2.cpp
    # ${imgui_include}/backends/imgui_impl_glut.cpp
    ${imgui_include}/backends/imgui_impl_glfw.cpp
    ${imgui_include}/backends/imgui_impl_opengl3.cpp
    # ${imgui_include}/backends/imgui_impl_sdl2.cpp
    # ${imgui_include}/backends/imgui_impl_sdl3.cpp
    # ${imgui_include}/backends/imgui_impl_sdlrenderer2.cpp
    # ${imgui_include}/backends/imgui_impl_sdlrenderer3.cpp

    # ${imgui_include}/backends/imgui_impl_dx9.cpp
    # ${imgui_include}/backends/imgui_impl_dx12.cpp
    # ${imgui_include}/backends/imgui_impl_dx11.cpp
    # ${imgui_include}/backends/imgui_impl_dx10.cpp
    # ${imgui_include}/backends/imgui_impl_android.cpp
    # ${imgui_include}/backends/imgui_impl_allegro5.cpp

    # ${imgui_include}/backends/imgui_impl_vulkan.cpp
    # ${imgui_include}/backends/imgui_impl_wgpu.cpp
    # ${imgui_include}/backends/imgui_impl_win32.cpp
)
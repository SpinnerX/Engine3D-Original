
set(imgui_include /usr/local/include/imgui)

# NOTE
# We are checking if imgui has been found and moved to folder /usr/local/include as /usr/local/include/imgui
# If that directory is not found then go to the imgui github link and git clone and move those files into /usr/local/include
# Github Installation Link: https://github.com/ocornut/imgui

# NOTE ** in case you forget **
# - Uncomment some of the .cpp files if you installed everything correctly, and are having errors
# - Errors involving opengl2, dx v9, v12, v11, and v10, or using android, allegro and other interfaces
#   depending on OS and mobile requirements



# We want to check before proceeding
if(EXISTS ${imgui_include})
    message(STATUS "Imgui in /usr/local/include/imgui has been found")
    set(
        imgui_src
        ${imgui_include}/imgui_draw.cpp
        ${imgui_include}/imgui_widgets.cpp
        ${imgui_include}/imgui_tables.cpp
        ${imgui_include}/imgui_demo.cpp
        ${imgui_include}/imgui.cpp


        # ${imgui_include}/backends/imgui_impl_opengl2.cpp
        ${imgui_include}/backends/imgui_impl_glut.cpp
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
else()
    message(SEND_ERROR "Imgui in /usr/local/include has not been found")
endif()

# target_include_directories(
#     ${PROJECT_NAME}
#     PRIVATE
#     /usr/local/include/imgui
# )



set(imgui_include /usr/local/include/imgui)

# NOTE
# We are checking if imgui has been found and moved to folder /usr/local/include as /usr/local/include/imgui
# If that directory is not found then go to the imgui github link and git clone and move those files into /usr/local/include
# Github Installation Link: https://github.com/ocornut/imgui

# We want to check before proceeding
if(EXISTS ${imgui_include})
    message(STATUS "imgui in /usr/local/include/imgui has been found")
    set(
        imgui_src
        ${imgui_include}/imgui.cpp
        ${imgui_include}/imgui_draw.cpp
        ${imgui_include}/imgui_widgets.cpp
        ${imgui_include}/imgui_tables.cpp
        ${imgui_include}/imgui_demo.cpp
    )
else()
    message(SEND_ERROR "imgui in /usr/local/include has not been found")
endif()

# target_include_directories(
#     ${PROJECT_NAME}
#     PRIVATE
#     /usr/local/include/imgui
# )


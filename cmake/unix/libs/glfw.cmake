# Ref Link: https://stackoverflow.com/questions/56682058/opengl-is-present-in-the-mingw-folder-but-clion-cant-reach-see-it


# Opengl cmake that makes sure we have glfw, glew, glut, and glad installed.

############################################################################
############ [ CMAKE MESSAGE-RELATED COLORED TEXT] #########################
############################################################################
# This is to allow coloring text
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# glm is basically an opengl math library for graphics programming
# API page for glm link: http://glm.g-truc.net/0.9.9/api/modules.html

# if(EXISTS ${GLM_DIR})
#     message(STATUS "Glm in ${GLM_DIR} has been found")
#     find_package(glm REQUIRED)
#     target_link_libraries(${PROJECT_NAME} glm::glm)
# else()
#     message(SEND_ERROR "\n===== [CMAKE] ===== >>> Glm in ${GLM_DIR} has not been found\n")
#     if(APPLE)
#         message(SEND_ERROR "\n===== [CMAKE] ===== >>> Since your on Mac you need to install via homebrew!!!\n")
#         message(SEND_ERROR "\n===== [CMAKE] ===== >>> Since your on Windows you need to install via going to GLM link to install it, and thhen set the directory before find_package!!!\n")
#     elseif(WIN32) # Give us error message if we are on Windows
#         message(SEND_ERROR "\n===== [CMAKE] ===== >>> Since your on Windows you need to install via going to GLM link to install it, and thhen set the directory before find_package!!!\n")
#         message(SEND_ERROR "\nOnce you installed it from the website then set the directory to ==> set(glm_DIR <installation prefix>/lib/cmake/glm)\n")
#     endif(APPLE)
# endif()

# Searching for glm
find_package(glm REQUIRED)


############################################################################
############################################################################

# Finding opengl, glfw, glew, glut, and possibly freetype and even freeglut
find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
# find_package(FREEGLUT REQUIRED)

# Checking if glfw3 has been found meaning installed
if(NOT TARGET glfw)
    # message("GLFW HAS BEEN FOUND - NOT THE CMAKE MESSAGE BY YOUR MESSAGE!\n\n\n")
    message("glfw.cmake ERROR MESSAGE - glfw3 has not been found!")
    message("glfw.cmake ERROR MESSAGE - you should check if glfw has been installed!\n")
endif()


# Checking if OPENGL/GLEW/GLUT is found meaning installed
if(NOT OPENGL_FOUND)
    message("${Red}NOT CMAKE ACTUAL MESSAGE --> OPENGL NOT FOUND!\n\n")
endif()

if(NOT GLEW_FOUND)
    message("${Red}NOT CMAKE ACTUAL MESSAGE --> GLEW NOT FOUND!\n\n")
endif()

if(NOT GLUT_FOUND)
    message("${Red}NOT CMAKE ACTUAL MESSAGE --> GLUT NOT FOUND!\n\n")
endif()




if(APPLE)
    # This is making sure we find the SDL libraries on mac
    include_directories(${SDL2_INCLUDE_DIRS})


    target_link_libraries(${PROJECT_NAME} pthread)
    # Linking the libraries for Cocoa, OpenGL, IOKit, and glfw
    # Need this for opengl
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME}
        glfw
        ${OPENGL_gl_LIBRARY}
        GLEW::GLEW
        ${GLUT_LIBRARIES} # NOTE: If you want to use freeglut, then you need this to link freeglut to get working
		glm::glm
    )
endif(APPLE)

if(LINUX)
    target_link_libraries(${PROJECT_NAME}
        glfw
        OpenGL::GL
        GLEW::GLEW
        ${GLUT_LIBRARIES} # NOTE: If you want to use freeglut, then you need this to link freeglut to get working
		glm::glm
    )
endif(LINUX)

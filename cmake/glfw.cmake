# Ref Link: https://stackoverflow.com/questions/56682058/opengl-is-present-in-the-mingw-folder-but-clion-cant-reach-see-it


# Opengl cmake that makes sure we have glfw, glew, glut, and glad installed.
# include(modules/colors.cmake)
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


# Finding opengl, glfw, glew, glut, and possibly freetype and even freeglut
# Apple - uses glfw 4.5 and older versions
# Windows & Linux - uses glfw 4.5+ (depends on which linux distro as well...)
if(APPLE) # Apple uses glfw 4.5 and older versions
	find_package(glfw3 3.4 REQUIRED)
elseif(UNIX AND NOT APPLE) # Since Linux's glfw-x11 does not have 3.4 but 3.3.9-1 then we call this find_package
	find_package(glfw3 3.3 REQUIRED)
endif()

# Searching for glm
find_package(glm REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)

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



# Linking the libraries for Cocoa, OpenGL, IOKit for APPLE OSX
if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
endif(APPLE)

target_link_libraries(${PROJECT_NAME}
    glfw
    OpenGL::GL
    GLEW::GLEW
    ${GLUT_LIBRARIES} # NOTE: If you want to use freeglut, then you need this to link freeglut to get working
    glm::glm
)
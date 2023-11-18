set(glad_include /usr/local/include/glad)

# NOTE
# If glad is not found then go this website to install it and move the folders to /usr/local/include/ as /usr/local/include/glad
# Glad Installation Link: https://glad.dav1d.de/generated/tmptmea9cbvglad/
# We want to check if this directory exists if not then we proceed
if(EXISTS ${glad_include})
    message(STATUS "Glad in /usr/local/include has been found")
    set(glad_src ${glad_include}/src/glad.c)
else()
    message(SEND_ERROR "Glad in /usr/local/include was not found")
endif()
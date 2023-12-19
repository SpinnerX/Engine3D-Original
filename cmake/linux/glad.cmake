set(glad_DIR /usr/local/include/glad)

if(NOT EXISTS ${glad_DIR})
	message(SEND_ERROR "${glad_DIR} not found!")
endif()

include_directories(
    ${glad_DIR}/include
    ${glad_DIR}/include/glad
    ${glad_DIR}/include/KHR
)

set(
    glad_src
    ${glad_DIR}/src/glad.c
)


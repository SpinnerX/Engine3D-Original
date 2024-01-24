include(FetchContent)

# FetchContent_Declare(
# 	yaml-cpp
# 	GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
# )

# FetchContent_GetProperties(yaml-cpp)

# if(NOT yaml-cpp_POPULATED)
# 	message(STATUS "Fetching yaml-cpp...")
# 	FetchContent_Populate(yaml-cpp)
	# add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
# endif()

find_package(yaml-cpp REQUIRED)


target_link_libraries(${PROJECT_NAME} yaml-cpp::yaml-cpp)



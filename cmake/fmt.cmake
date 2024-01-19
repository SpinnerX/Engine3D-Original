find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} fmt::fmt spdlog::spdlog Threads::Threads)

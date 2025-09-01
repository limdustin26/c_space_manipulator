cmake_minimum_required(VERSION 3.16)
project(cspace_manipulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Gui)
find_package(Eigen3 REQUIRED    )

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/views/main_window.cpp
    src/views/link_config_view.cpp
    src/views/user_config_view.cpp
    src/views/app_view.cpp
    src/views/workspace_view.cpp
    src/controllers/manipulator_controller.cpp

    # Add header paths so AUTOMOC definitely scans them.
    # Use the exact real paths under your source tree:
    include/c_space_manipulator/views/main_window.hpp
    include/c_space_manipulator/views/link_config_view.hpp
    include/c_space_manipulator/views/user_config_view.hpp
    include/c_space_manipulator/views/app_view.hpp
    include/c_space_manipulator/views/workspace_view.hpp
    include/c_space_manipulator/models/models.hpp
    include/c_space_manipulator/controllers/manipulator_controller.hpp
    )

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

target_link_libraries(${PROJECT_NAME} Qt::Widgets Qt::Gui Eigen3::Eigen)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

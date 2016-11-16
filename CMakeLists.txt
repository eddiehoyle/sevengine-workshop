cmake_minimum_required(VERSION 2.8.11)

# App
project(sevengine-workshop)
set(APP sev-workshop)

# QT settings
set(QT5_PATH $ENV{HOME}/Qt/5.7/clang_64)
set(CMAKE_INCLUDE_CURRENT_DIR ON )
set(CMAKE_AUTOMOC ON)
set(QT5_MODULE_PATH ${QT5_PATH}/lib/cmake)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT5_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/cmake/modules)

# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Find packages
find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(SOIL REQUIRED)

# Includes
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Temporary sevengine location
set(SEV_ROOT /Users/eddiehoyle/Code/cpp/game/sevengine)
set(SEV_INCLUDE_DIR ${SEV_ROOT}/include)
set(SEV_LIB ${SEV_ROOT}/lib/libsev.a)
include_directories(${SEV_INCLUDE_DIR})

# Source files
file(GLOB_RECURSE SOURCE_FILES "*.cc" "*.hh")

add_executable(${APP} ${SOURCE_FILES} src/examples/03_rectTextured/Example.cc src/examples/03_rectTextured/Example.hh)

#Link the helloworld executable to the Qt 5 widgets library.
target_link_libraries(${APP}
        ${Qt5Widgets_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${SOIL_LIBRARY}
        ${SEV_LIB})

# If Apple...
target_link_libraries(${APP} "-framework OpenGL")
target_link_libraries(${APP} "-framework Cocoa")
target_link_libraries(${APP} "-framework IOKit")
target_link_libraries(${APP} "-framework CoreVideo")

#message(WARNING ${SOURCE_FILES})
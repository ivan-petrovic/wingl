cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)
# add_definitions(-DUNICODE -D_UNICODE)

# cmake -G "MinGW Makefiles" ../src
project(WinGL VERSION 0.1 LANGUAGES CXX)

find_package(OpenGL REQUIRED)
# find_package(OpenGL REQUIRED COMPONENTS OpenGL)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
# message(${OPENGL_LIBRARY})

# Bring the headers into the project
include_directories(include)

# Can manually add the sources using the set command as follows:
# set(SOURCES src/mainapp.cpp src/Student.cpp)

# However, the file(GLOB...) allows for wildcard additions:
# file(GLOB SOURCES "src/*.cpp")
file(GLOB SOURCES "*.cpp")

message(${SOURCES})
# add_executable(wingl WIN32 ${SOURCES})
add_executable(wingl WIN32 main.cpp OpenGLWindow.cpp)

# add_executable(wingl WIN32
#    main.cpp
#    ${SOURCES}
# )
# add_dependencies(wingl opengl32)
# target_link_libraries(wingl OpenGL::OpenGL )
# target_link_libraries(wingl PRIVATE ${OPENGL_gl_LIBRARY})
message(${OPENGL_LIBRARIES})
target_link_libraries(wingl opengl32)
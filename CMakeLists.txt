cmake_minimum_required(VERSION 3.6.0)
project(OpenGL_Learn CXX)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_subdirectory(external/GLTools)

include_directories( 
    ${OPENGL_INCLUDE_DIRS}  
    ${GLUT_INCLUDE_DIRS}
    external/GLTools/include
    )
# message(${OPENGL_INCLUDE_DIRS})
# message(${GLUT_INCLUDE_DIRS})



set(SRC_LIST src/Hello.cpp)


add_executable(hello ${SRC_LIST})


set(Trangle_src src/Triangle.cpp)

add_executable(triangle ${Trangle_src})
# set_target_properties(triangle PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(triangle PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} gltools)








cmake_minimum_required(VERSION 2.8)

project(HelloSLAM)

add_executable(helloSLAM src/helloSLAM.cpp)
# 정적 라이브러리를 만드는 방법
add_library(hello src/libHelloSLAM.cpp)


add_executable(useHello src/useHello.cpp)
# target_link_libraries(useHello hello)

#shared를 사용해서 공유라이브러리를 만드는 방법
add_library(hello_shared SHARED src/libHelloSLAM.cpp)
target_link_libraries(useHello hello_shared)

include_directories(${PROJECT_SOURCE_DIR}/include)

cmake_minimum_required(VERSION 3.26)
project(MyListWidget VERSION 0.1.0)
set(HEAD_PATH ${PROJECT_SOURCE_DIR}/head)
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
file(GLOB HEAD_FILES ${HEAD_PATH}/*.h)
file(GLOB SOURCE_FILES ${SRC_PATH}/*.cpp)

message(NOTICE "widget ${SOURCE_FILES} ${HEAD_FILES}")

add_library(MyListWidget_static STATIC ${SOURCE_FILES} ${HEAD_FILES})
target_link_libraries(MyListWidget_static PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
target_include_directories(MyListWidget_static PRIVATE
        ${HEAD_PATH})
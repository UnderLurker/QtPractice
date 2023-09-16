cmake_minimum_required(VERSION 3.26)
project(MyListWidget VERSION 0.1.0)
set(HEAD_PATH ${PROJECT_SOURCE_DIR}/head)
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
set(HEAD_FILES
        ${HEAD_PATH}/MyListWidget.h
)
aux_source_directory(${SRC_PATH} SOURCE_FILES)

include_directories(${HEAD_PATH})


add_library(MyListWidget_static STATIC ${SOURCE_FILES} ${HEAD_FILES})
target_link_libraries(MyListWidget_static
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)
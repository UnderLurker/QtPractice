cmake_minimum_required(VERSION 3.26)
project(ButtonTest VERSION 0.1.0)
set(HEAD_PATH ${PROJECT_SOURCE_DIR}/include)
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
set(HEAD_FILES
        ${HEAD_PATH}/CustomWindow.h
)
aux_source_directory(${SRC_PATH} SOURCE_FILES)


include_directories(${HEAD_PATH})

add_subdirectory(${THIRD_PARTY}/MyListWidget MyListWidget_static.dir)
add_subdirectory(${THIRD_PARTY}/MyBar MyBar_static.dir)
add_subdirectory(${THIRD_PARTY}/MyButton MyButton_static.dir)

add_executable(ButtonTest ${SOURCE_FILES} ${HEAD_FILES})
target_link_libraries(ButtonTest PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        MyListWidget_static
        MyBar_static
        MyButton_static
)
target_include_directories(ButtonTest PUBLIC
        ${THIRD_PARTY}/MyListWidget/head
        ${THIRD_PARTY}/MyBar/head
        ${THIRD_PARTY}/MyButton/head
)

add_test(ButtonTest ButtonTest)

#####################################################

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
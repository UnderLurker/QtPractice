cmake_minimum_required(VERSION 3.26)
project(ClionWidget)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)
set(QT_INSTALL_PATH ${CMAKE_PREFIX_PATH}/../../)

set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(THIRD_PARTY ${PROJECT_SOURCE_DIR}/third_party)

message(NOTICE "CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin")
message(NOTICE "CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin")
message(NOTICE "CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin")

file(GLOB QRC_SOURCE_FILE ./qrc/*.qrc)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(ClionWidget Sources/main.cpp)
target_link_libraries(ClionWidget
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

###########################################################
enable_testing()

#add_subdirectory(${PROJECT_SOURCE_DIR}/test/WidgetTest)
add_subdirectory(${PROJECT_SOURCE_DIR}/test/ButtonTest)

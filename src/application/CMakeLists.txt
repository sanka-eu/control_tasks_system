set(Qt5_DIR C:/Qt/5.15.2/mingw81_64/lib/cmake/Qt5)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_subdirectory(changeDataBD)
add_subdirectory(changeDataDialog)
add_subdirectory(loginDialog)

add_executable(app
    main.cpp
    MainWindow.cpp
    MainWindow.ui
)

target_link_libraries(app changeData login Qt5::Widgets)
set(Qt5_DIR C:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_executable(app
    MainWindow.ui
    MainWindow.cpp
    main.cpp
)

target_link_libraries(app Qt5::Widgets)
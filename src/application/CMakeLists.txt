find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(app
    MainWindow.ui
    MainWindow.cpp
    main.cpp
    MainWindow.h
)

target_link_libraries(app Qt5::Widgets)
add_library(login
    LoginWidget.cpp
    LoginWidget.ui
)

target_link_libraries(login changeBD Qt5::Widgets)
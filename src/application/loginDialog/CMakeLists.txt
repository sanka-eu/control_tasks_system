add_library(login
    LoginDialog.cpp
    LoginDialog.ui
)

target_link_libraries(login changeBD Qt5::Widgets)
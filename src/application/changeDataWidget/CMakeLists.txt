add_library(changeData 
    ChangeDataWidget.cpp
    ChangeDataWidget.ui
)

target_link_libraries(changeData changeBD Qt5::Widgets)
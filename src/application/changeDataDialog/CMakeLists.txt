add_library(changeData 
    ChangeDataDialog.cpp
    ChangeDataDialog.ui
)

target_link_libraries(changeData changeBD Qt5::Widgets)
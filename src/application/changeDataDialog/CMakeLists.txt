add_subdirectory(addEmployeeDialog)

add_library(changeData 
    ChangeDataDialog.cpp
    ChangeDataDialog.ui
)

target_link_libraries(changeData addEmployeeDialog changeBD Qt5::Widgets)
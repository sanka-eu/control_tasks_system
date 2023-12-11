add_library(addEmployeeDialog 
    AddEmployeeDialog.cpp
    AddEmployeeDialog.ui
)

target_link_libraries(addEmployeeDialog changeBD Qt5::Widgets)
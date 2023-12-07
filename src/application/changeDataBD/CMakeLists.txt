add_subdirectory(sqlite)

add_library(changeBD
    ChangeDataBD.cpp
    ChangeDataBD.h
)

target_link_libraries(changeBD sqlite3)
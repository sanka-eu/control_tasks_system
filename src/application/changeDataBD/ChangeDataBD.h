#ifndef CHANGEDATABD_H
#define CHANGEDATABD_H
#include <string>
#include <libpq-fe.h>
#include <iostream>
#include "sqlite/sqlite3.h"
class ChangeDataBD
{

public:
    ChangeDataBD();
    ~ChangeDataBD();
    void addEmployee(const std::string& fullName, int experience, int department, int positionId);
    void addDepartment(int departmentNumber, const std::string& title);
    void addPosition(int positionId, const std::string& title);
    void addTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate,
        const std::string& dueDate, int issuedById);
    void takeTask(int taskNumber, int executorId, const std::string& assignmentTakenDate);
    void changeDepartmentTitle(int departmentNumber, const std::string& newTitle);
    void changePositionTitle(int positionId, const std::string& newTitle);
    void updateTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate,
        const std::string& dueDate, int issuedById, const std::string& assignmentTakenDate,
        int executorId, int isCompleted, const std::string& actualCompletionDate);
    void changeEmployee(int employeeId, const std::string& fullName, int experience,
        int department, int positionId);
private:
    sqlite3* db;
    bool executeNonQuery(const char* query);
}; // class ChangeDataWidget

#endif //CHANGEDATABD_H
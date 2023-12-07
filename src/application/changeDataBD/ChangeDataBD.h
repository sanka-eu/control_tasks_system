#ifndef CHANGEDATABD_H
#define CHANGEDATABD_H
#include <string>
#include <iostream>
#include "sqlite/sqlite3.h"
#include <vector>
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
    std::vector<std::vector<std::string>> getDepartments();
    std::vector<std::vector<std::string>> getPositions();
    std::vector<std::vector<std::string>> getEmployees();
    std::vector<std::vector<std::string>> getUsers();
    std::vector<std::vector<std::string>> getTasks();
    int getEmployeePositionId(const std::string& login, const std::string& password);
private:
    sqlite3* db;
    bool executeNonQuery(const char* query);
}; // class ChangeDataWidget

#endif //CHANGEDATABD_H
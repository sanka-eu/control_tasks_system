#ifndef CHANGEDATABD_H
#define CHANGEDATABD_H
#include <string>
#include <libpq-fe.h>
#include <iostream>
class ChangeDataBD
{

public:
    ChangeDataBD();
    ~ChangeDataBD();
    bool connectDB();
    void disconnectDB();
    //методы мен€ют поле Ѕƒ объ€вленное в private секции, возвращают true если изменение прошло удачно, если нет - false
    bool addUser(std::string login, std::string password, std::string userType);
    bool changeUser(std::string login, std::string newPassword, std::string newWorkerId, std::string newUserType);
    bool deleteUser(std::string login);
    bool addAssigment(const char* department, const std::string& issueDate, const std::string& dueDate, bool taken, bool overdue, const std::string& issuedByLogin);
    bool changeAssigment(const std::string& assignmentId, const std::string& newIssueDate, const std::string& newDueDate, bool newTaken, bool newOverdue);
    bool deleteAssigment(const std::string& assignmentId);
    bool addDepartment(const std::string& departmentName);
    bool changeDepartment(const char* departmentId);
    bool deleteDepartment(const char* id);
    bool addPosition(const std::string& positionName);
    bool changePosition(const char* positionId, const std::string& newPositionName);
    bool deletePosition(const char* positionId);
    bool addEmployee(const char* userId, const std::string& fullName, const char* experience, const char* departmentId, const char* positionId);
    bool checkPositionExists(const char* positionId);
    bool checkDepartmentExists(const char* departmentId);
private:
    //поле с базой данных, в реализации public методов обращатьс€ и работать с этим полем, измен€€ Ѕƒ
    //som_type DataBase;
    PGconn* connection;
}; // class ChangeDataWidget

#endif //CHANGEDATABD_H
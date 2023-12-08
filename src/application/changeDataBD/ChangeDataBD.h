#ifndef CHANGEDATABD_H
#define CHANGEDATABD_H

#include <src/application/changeDataBD/sqlite/sqlite3.h>

#include <string>
#include <iostream>
#include <vector>

class ChangeDataBD
{

public:
    ChangeDataBD();
    ~ChangeDataBD();
    void addEmployee(const std::string& fullName, int experience, int department, int positionId);//Добавить сотрудника
    void addDepartment(int departmentNumber, const std::string& title);//Добавить отдел
    void addPosition(int positionId, const std::string& title);//Добавить должность
    void addTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate, //Добавить задачу
        const std::string& dueDate, int issuedById);
    <<<<<< < HEAD
        void takeTask(int taskNumber, int executorId, const std::string & assignmentTakenDate);//Взять задачу(добавляет недостающие данные в таблицу задач: кто взял когда и тд, и меняет isTaken на 1)
    void changeDepartmentTitle(int departmentNumber, const std::string& newTitle);//Изменить название отдела по id
    void changePositionTitle(int positionId, const std::string& newTitle);//Изменить название должности по id
    void updateTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate, //Изменить данные в задаче по id
        ====== =
        void giveTask(int taskNumber, int executorId, const std::string & assignmentTakenDate);
    void changeDepartmentTitle(int departmentNumber, const std::string& newTitle);
    void changePositionTitle(int positionId, const std::string& newTitle);
    void updateTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate,
        >>>>>> > d1a2ebb2748792ccd703ed44f0f76d8012b50507
        const std::string& dueDate, int issuedById, const std::string& assignmentTakenDate,
        int executorId, int isCompleted, const std::string& actualCompletionDate);
    void changeEmployee(int employeeId, const std::string& fullName, int experience, // Изменить данные сотрудника по id
        int department, int positionId);
    std::vector<std::vector<std::string>> getDepartments();//Получить таблицу Отделы
    std::vector<std::vector<std::string>> getPositions();//Получить таблицу должности
    std::vector<std::vector<std::string>> getEmployees();//Получить таблицу сотрудники
    std::vector<std::vector<std::string>> getUsers();//Получить таблицу пользователи
    std::vector<std::vector<std::string>> getTasks();//Получить таблицу задачи
    int getEmployeePositionId(const std::string& login, const std::string& password);///Проверить логин пароль и вернуть должность если есть, если нет вернуть 0(вообще там своя ошибка возвращается до того как вернется 0)
    bool isTaskTaken(int taskNumber);//Проверить взята ли задача
private:
    sqlite3* db;
    bool executeNonQuery(const char* query);
}; // class ChangeDataWidget

#endif //CHANGEDATABD_H
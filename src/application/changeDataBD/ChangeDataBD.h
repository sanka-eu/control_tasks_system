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
    void addEmployee(const std::string& fullName, int experience, int department, int positionId);//�������� ����������
    void addDepartment(int departmentNumber, const std::string& title);//�������� �����
    void addPosition(int positionId, const std::string& title);//�������� ���������
    void addTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate, //�������� ������
        const std::string& dueDate, int issuedById);
    <<<<<< < HEAD
        void takeTask(int taskNumber, int executorId, const std::string & assignmentTakenDate);//����� ������(��������� ����������� ������ � ������� �����: ��� ���� ����� � ��, � ������ isTaken �� 1)
    void changeDepartmentTitle(int departmentNumber, const std::string& newTitle);//�������� �������� ������ �� id
    void changePositionTitle(int positionId, const std::string& newTitle);//�������� �������� ��������� �� id
    void updateTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate, //�������� ������ � ������ �� id
        ====== =
        void giveTask(int taskNumber, int executorId, const std::string & assignmentTakenDate);
    void changeDepartmentTitle(int departmentNumber, const std::string& newTitle);
    void changePositionTitle(int positionId, const std::string& newTitle);
    void updateTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate,
        >>>>>> > d1a2ebb2748792ccd703ed44f0f76d8012b50507
        const std::string& dueDate, int issuedById, const std::string& assignmentTakenDate,
        int executorId, int isCompleted, const std::string& actualCompletionDate);
    void changeEmployee(int employeeId, const std::string& fullName, int experience, // �������� ������ ���������� �� id
        int department, int positionId);
    std::vector<std::vector<std::string>> getDepartments();//�������� ������� ������
    std::vector<std::vector<std::string>> getPositions();//�������� ������� ���������
    std::vector<std::vector<std::string>> getEmployees();//�������� ������� ����������
    std::vector<std::vector<std::string>> getUsers();//�������� ������� ������������
    std::vector<std::vector<std::string>> getTasks();//�������� ������� ������
    int getEmployeePositionId(const std::string& login, const std::string& password);///��������� ����� ������ � ������� ��������� ���� ����, ���� ��� ������� 0(������ ��� ���� ������ ������������ �� ���� ��� �������� 0)
    bool isTaskTaken(int taskNumber);//��������� ����� �� ������
private:
    sqlite3* db;
    bool executeNonQuery(const char* query);
}; // class ChangeDataWidget

#endif //CHANGEDATABD_H
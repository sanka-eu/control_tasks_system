#include "ChangeDataBD.h"

ChangeDataBD::ChangeDataBD() : connection(nullptr) {
    // ����������� � ���� ������ ��� �������� �������
    if (!connectDB()) {
        std::cerr << "Failed to connect to the database." << std::endl;
    }
}

ChangeDataBD::~ChangeDataBD() {
    // ���������� �� ���� ������ ��� ����������� �������
    disconnectDB();
}

bool ChangeDataBD::connectDB() {
    const char* conninfo = "dbname=kursdb user=bogdan32113 password=I0m1VQqzFjnJ host=ep-young-truth-04408351.eu-central-1.aws.neon.tech port=5432 client_encoding=WINDOWS-1251";

    // ��������� ����������
    connection = PQconnectdb(conninfo);

    // �������� �� �������� �����������
    if (PQstatus(connection) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(connection) << std::endl;
        return false;
    }
    std::cout << "Connected"<<std::endl;
    return true;
}

void ChangeDataBD::disconnectDB() {
    // �������� ����������
    if (connection != nullptr) {
        PQfinish(connection);
        connection = nullptr;
    }
}


bool ChangeDataBD::addUser(std::string login,std::string password,std::string userType) {

    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ������� ������ ������������ � �������
    const char* addUserQuery = "INSERT INTO users (�����, ������, ���������������) VALUES ($1, $2, $3) RETURNING id����������";

    // �������� ���������� ��� ���������� ������������
    const char* addUserValues[3] = { login.c_str(), password.c_str(), userType.c_str() };

    // ����� ���������� ��� ���������� ������������
    int addUserLengths[3] = { static_cast<int>(login.length()), static_cast<int>(password.length()),
                              static_cast<int>(userType.length()) };

    // ������ ���������� ��� ���������� ������������ (1 ��� ��������� ��������)
    int addUserFormats[3] = { 1, 1, 1 };

    // ��������� ������ ��� ���������� ������������ � ��������� id����������
    PGresult* addUserResult = PQexecParams(connection, addUserQuery, 3, nullptr, addUserValues, addUserLengths, addUserFormats, 0);

    if (PQresultStatus(addUserResult) != PGRES_TUPLES_OK || PQntuples(addUserResult) == 0) {
        std::cerr << "Failed to add user: " << PQresultErrorMessage(addUserResult) << std::endl;
        PQclear(addUserResult);
        return false;
    }

    // �������� id���������� �� ���������� �������
    std::string employeeId = std::to_string(atoi(PQgetvalue(addUserResult, 0, 0)));

    // ����������� ��������� �������
    PQclear(addUserResult);

    // ������� ����������������� SQL-������ ��� ������� ������ ���������� � �������
    const char* addEmployeeQuery = "INSERT INTO ���������� (id����������) VALUES ($1)";

    // �������� ���������� ��� ���������� ����������
    const char* addEmployeeValues[1] = { employeeId.c_str() };

    // ����� ���������� ��� ���������� ����������
    int addEmployeeLengths[1] = { 0 };

    // ������ ���������� ��� ���������� ���������� (0 ��� ������������� ��������)
    int addEmployeeFormats[1] = { 0 };

    // ��������� ������ ��� ���������� ����������
    PGresult* addEmployeeResult = PQexecParams(connection, addEmployeeQuery, 1, nullptr, addEmployeeValues, addEmployeeLengths, addEmployeeFormats, 0);

    if (PQresultStatus(addEmployeeResult) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add employee: " << PQresultErrorMessage(addEmployeeResult) << std::endl;
        PQclear(addEmployeeResult);
        return false;
    }

    // ����������� ��������� �������
    PQclear(addEmployeeResult);

    return true;
}

bool ChangeDataBD::changeUser(std::string login,std::string newPassword,std::string newWorkerId,std::string newUserType)
{

    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ��������� ������ ������������
    const char* query = "UPDATE users SET "
        "������ = CASE WHEN $1 <> '' THEN $1 ELSE ������ END, "
        "id���������� = CASE WHEN $2 <> '' THEN $2 ELSE id���������� END, "
        "��������������� = CASE WHEN $3 <> '' THEN $3 ELSE ��������������� END "
        "WHERE ����� = $4";

    // �������� ����������
    const char* values[4] = { newPassword.c_str(), newWorkerId.c_str(), newUserType.c_str(), login.c_str() };

    // ����� ���������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[4] = { static_cast<int>(newPassword.length()), static_cast<int>(newWorkerId.length()),
                       static_cast<int>(newUserType.length()), static_cast<int>(login.length()) };

    // ������ ���������� (1 ��� ��������� ��������)
    int formats[4] = { 1, 1, 1, 1 };

    // ��������� ������ � �������������� ����������
    PGresult* result = PQexecParams(connection, query, 4, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to change user: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}

bool ChangeDataBD::deleteUser(std::string login)
{   
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� �������� ������������
    const char* query = "DELETE FROM users WHERE ����� = $1";

    // �������� ���������
    const char* values[1] = { login.c_str() };

    // ����� ��������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[1] = { static_cast<int>(login.length()) };

    // ������ ��������� (1 ��� ���������� ��������)
    int formats[1] = { 1 };

    // ��������� ������ � �������������� ���������
    PGresult* result = PQexecParams(connection, query, 1, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to delete user: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}


bool ChangeDataBD::addAssigment(const char* department,const std::string& issueDate,const std::string& dueDate,bool taken,bool overdue,const std::string& issuedByLogin) {
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // �������� id���������� (���������) �� ������� users �� ������
    const char* getUserIdQuery = "SELECT id���������� FROM users WHERE ����� = $1";

    // �������� ��������� ��� ������� �� ��������� id����������
    const char* getUserIdValues[1] = { issuedByLogin.c_str() };

    // ����� ��������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int getUserIdLengths[1] = { static_cast<int>(issuedByLogin.length()) };

    // ������ ��������� (1 ��� ���������� ��������)
    int getUserIdFormats[1] = { 1 };

    // ��������� ������ ��� ��������� id����������
    PGresult* getUserIdResult = PQexecParams(connection, getUserIdQuery, 1, nullptr, getUserIdValues, getUserIdLengths, getUserIdFormats, 0);

    if (PQresultStatus(getUserIdResult) != PGRES_TUPLES_OK || PQntuples(getUserIdResult) == 0) {
        std::cerr << "Failed to get user ID for assignment: " << PQresultErrorMessage(getUserIdResult) << std::endl;
        PQclear(getUserIdResult);
        return false;
    }

    // �������� id���������� �� ���������� �������
    int issuedById = atoi(PQgetvalue(getUserIdResult, 0, 0));
    std::string issuedByIdValue = std::to_string(issuedById);
    std::cout << issuedByIdValue;
    // ����������� ��������� �������
    PQclear(getUserIdResult);

    // ������� ����������������� SQL-������ ��� ������� ������ ���������
    const char* addAssignmentQuery = "INSERT INTO ��������� (�����������������, ����������, �������������, ����������������, ����������, ���������) "
        "VALUES ($1, $2, $3, $4, $5, $6)";

    // �������� ����������
    const char* addAssignmentValues[6] = { department, issueDate.c_str(), dueDate.c_str(),
                                           taken ? "true" : "false", overdue ? "true" : "false", issuedByIdValue.c_str()};

    // ����� ���������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int addAssignmentLengths[6] = { 0, static_cast<int>(issueDate.length()), static_cast<int>(dueDate.length()), 5, 5, 0 };

    // ������ ���������� (0 ��� ������������� ��������, 1 ��� ��������� ��������)
    int addAssignmentFormats[6] = { 0, 1, 1, 0, 0, 0 };


    // ��������� ������ � �������������� ����������
    PGresult* addAssignmentResult = PQexecParams(connection, addAssignmentQuery, 6, nullptr, addAssignmentValues, addAssignmentLengths, addAssignmentFormats, 0);

    if (PQresultStatus(addAssignmentResult) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add assignment: " << PQresultErrorMessage(addAssignmentResult) << std::endl;
        PQclear(addAssignmentResult);
        return false;
    }

    PQclear(addAssignmentResult);
    return true;
}

bool ChangeDataBD::changeAssigment(const std::string& assignmentId ,const std::string& newIssueDate,const std::string& newDueDate,bool newTaken,bool newOverdue) {
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ���������� ���������
    const char* changeAssignmentQuery = "UPDATE ��������� SET "
        "���������� = CASE WHEN $2 <> '' THEN $2 ELSE ���������� END, "
        "������������� = CASE WHEN $3 <> '' THEN $3 ELSE ������������� END, "
        "���������������� = CASE WHEN $4 <> '' THEN ($4::boolean) ELSE ���������������� END, "
        "���������� = CASE WHEN $5 <> '' THEN ($5::boolean) ELSE ���������� END "
        "WHERE �������������� = $1";

    // �������� ����������
    const char* changeAssignmentValues[5] = { assignmentId.c_str(), newIssueDate.c_str(), newDueDate.c_str(),
                                             newTaken ? "true" : "false", newOverdue ? "true" : "false" };

    // ����� ���������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int changeAssignmentLengths[5] = { static_cast<int>(assignmentId.length()), static_cast<int>(newIssueDate.length()),
                                       static_cast<int>(newDueDate.length()), 5, 5 };

    // ������ ���������� (0 ��� ������������� ��������, 1 ��� ��������� ��������)
    int changeAssignmentFormats[5] = { 0, 1, 1, 0, 0 };

    // ��������� ������ � �������������� ����������
    PGresult* changeAssignmentResult = PQexecParams(connection, changeAssignmentQuery, 5, nullptr, changeAssignmentValues, changeAssignmentLengths, changeAssignmentFormats, 0);

    if (PQresultStatus(changeAssignmentResult) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to change assignment: " << PQresultErrorMessage(changeAssignmentResult) << std::endl;
        PQclear(changeAssignmentResult);
        return false;
    }

    PQclear(changeAssignmentResult);
    return true;
}

bool ChangeDataBD::deleteAssigment(const std::string& assignmentId)
{
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� �������� ������������
    const char* query = "DELETE FROM ��������� WHERE �������������� = $1";

    // �������� ���������
    const char* values[1] = { assignmentId.c_str() };

    // ����� ��������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[1] = { static_cast<int>(assignmentId.length()) };

    // ������ ��������� (1 ��� ���������� ��������)
    int formats[1] = { 0 };

    // ��������� ������ � �������������� ���������
    PGresult* result = PQexecParams(connection, query, 1, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to delete user: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}


bool ChangeDataBD::addDepartment(const std::string& departmentName )
{
    
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ���������� ������
    const char* addDepartmentQuery = "INSERT INTO ������ (��������������) VALUES ($1)";

    // �������� ���������
    const char* values[1] = { departmentName.c_str() };

    // ����� ��������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[1] = { static_cast<int>(departmentName.length()) };

    // ������ ��������� (1 ��� ���������� ��������)
    int formats[1] = { 1 };

    // ��������� ������ � �������������� ���������
    PGresult* result = PQexecParams(connection, addDepartmentQuery, 1, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add department: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}

bool ChangeDataBD::changeDepartment(const char* departmentId)
{
    const std::string& newDepartmentName = "���������";
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ��������� ������
    const char* changeDepartmentQuery = "UPDATE ������ SET �������������� = $2 WHERE ����������� = $1";

    // �������� ����������
    const char* values[2] = { departmentId, newDepartmentName.c_str() };

    // ����� ���������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[2] = { 0, static_cast<int>(newDepartmentName.length()) };

    // ������ ���������� (0 ��� ������������� ��������, 1 ��� ��������� ��������)
    int formats[2] = { 0, 1 };

    // ��������� ������ � �������������� ����������
    PGresult* result = PQexecParams(connection, changeDepartmentQuery, 2, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to change department: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}

bool ChangeDataBD::deleteDepartment(const char* departmentId)
{
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� �������� ������
    const char* deleteDepartmentQuery = "DELETE FROM ������ WHERE ����������� = $1";

    // �������� ���������
    const char* values[1] = { departmentId };

    // ����� ��������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[1] = { 0 };

    // ������ ��������� (0 ��� ������������� ��������)
    int formats[1] = { 0 };

    // ��������� ������ � �������������� ���������
    PGresult* result = PQexecParams(connection, deleteDepartmentQuery, 1, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to delete department: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}


bool ChangeDataBD::addPosition(const std::string& positionName)
{
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ���������� ���������
    const char* addPositionQuery = "INSERT INTO ��������� (�����������������) VALUES ($1)";

    // �������� ���������
    const char* values[1] = { positionName.c_str() };

    // ����� ��������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[1] = { static_cast<int>(positionName.length()) };

    // ������ ��������� (1 ��� ���������� ��������)
    int formats[1] = { 1 };

    // ��������� ������ � �������������� ���������
    PGresult* result = PQexecParams(connection, addPositionQuery, 1, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add position: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}

bool ChangeDataBD::changePosition(const char* positionId, const std::string& newPositionName)
{
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ��������� ���������
    const char* changePositionQuery = "UPDATE ��������� SET ����������������� = $2 WHERE id��������� = $1";

    // �������� ����������
    const char* values[2] = {positionId, newPositionName.c_str() };

    // ����� ���������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[2] = { 0, static_cast<int>(newPositionName.length()) };

    // ������ ���������� (0 ��� ������������� ��������, 1 ��� ��������� ��������)
    int formats[2] = { 0, 1 };

    // ��������� ������ � �������������� ����������
    PGresult* result = PQexecParams(connection, changePositionQuery, 2, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to change position: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}

bool ChangeDataBD::deletePosition(const char* positionId)
{
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� �������� ���������
    const char* deletePositionQuery = "DELETE FROM ��������� WHERE id��������� = $1";

    // �������� ���������
    const char* values[1] = { positionId };

    // ����� ��������� (����� ������������ nullptr, ���� ������ ��������� ������� ��������)
    int lengths[1] = { 0 };

    // ������ ��������� (0 ��� ������������� ��������)
    int formats[1] = { 0 };

    // ��������� ������ � �������������� ���������
    PGresult* result = PQexecParams(connection, deletePositionQuery, 1, nullptr, values, lengths, formats, 0);

    if (PQresultStatus(result) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to delete position: " << PQresultErrorMessage(result) << std::endl;
        PQclear(result);
        return false;
    }

    PQclear(result);
    return true;
}


bool ChangeDataBD::addEmployee(const char* userId, const std::string& fullName, const char*  experience, const char* departmentId, const char* positionId) {
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // �������� ������������� ������
    if (!checkDepartmentExists(departmentId)) {
        std::cerr << "Department with id " << departmentId << " does not exist." << std::endl;
        return false;
    }

    // �������� ������������� ���������
    if (!checkPositionExists(positionId)) {
        std::cerr << "Position with id " << positionId << " does not exist." << std::endl;
        return false;
    }


    // ��������� ��������� Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // ������� ����������������� SQL-������ ��� ���������� ����������
    const char* addEmployeeQuery = "UPDATE ���������� SET ��� = $1, ���� = $2, ����� = $3, id��������� = $4 WHERE id���������� = $5";

    // �������� ���������� ��� ���������� ����������
    const char* addEmployeeValues[5] = { fullName.c_str(),
                                         experience,
                                         departmentId,
                                         positionId,
                                         userId };

    // ����� ���������� ��� ���������� ����������
    int addEmployeeLengths[5] = { static_cast<int>(fullName.length()), 0, 0, 0, 0 };

    // ������ ���������� ��� ���������� ���������� (1 ��� ��������� ��������, 0 ��� ������������� ��������)
    int addEmployeeFormats[5] = { 1, 0, 0, 0, 0 };

    // ��������� ������ ��� ���������� ����������
    PGresult* addEmployeeResult = PQexecParams(connection, addEmployeeQuery, 5, nullptr, addEmployeeValues, addEmployeeLengths, addEmployeeFormats, 0);

    if (PQresultStatus(addEmployeeResult) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add employee: " << PQresultErrorMessage(addEmployeeResult) << std::endl;
        PQclear(addEmployeeResult);
        return false;
    }

    // ����������� ��������� �������
    PQclear(addEmployeeResult);

    return true;
}

bool ChangeDataBD::checkDepartmentExists(const char* departmentId) {
    // �������� ������������� ������ � ������� ������
    const char* checkDepartmentQuery = "SELECT 1 FROM ������ WHERE ����������� = $1";

    // �������� ��������� ��� �������� ������������� ������
    const char* checkDepartmentValues[1] = {departmentId};

    // ����� ��������� ��� �������� ������������� ������
    int checkDepartmentLengths[1] = { 0 };

    // ������ ��������� ��� �������� ������������� ������ (0 ��� ������������� ��������)
    int checkDepartmentFormats[1] = { 0 };

    // ��������� ������ ��� �������� ������������� ������
    PGresult* checkDepartmentResult = PQexecParams(connection, checkDepartmentQuery, 1, nullptr, checkDepartmentValues, checkDepartmentLengths, checkDepartmentFormats, 0);

    bool departmentExists = (PQresultStatus(checkDepartmentResult) == PGRES_TUPLES_OK && PQntuples(checkDepartmentResult) > 0);

    // ����������� ��������� �������
    PQclear(checkDepartmentResult);

    return departmentExists;
}

bool ChangeDataBD::checkPositionExists(const char*  positionId) {
    // �������� ������������� ��������� � ������� ���������
    const char* checkPositionQuery = "SELECT 1 FROM ��������� WHERE id��������� = $1";

    // �������� ��������� ��� �������� ������������� ���������
    const char* checkPositionValues[1] = { positionId };

    // ����� ��������� ��� �������� ������������� ���������
    int checkPositionLengths[1] = { 0 };

    // ������ ��������� ��� �������� ������������� ��������� (0 ��� ������������� ��������)
    int checkPositionFormats[1] = { 0 };

    // ��������� ������ ��� �������� ������������� ���������
    PGresult* checkPositionResult = PQexecParams(connection, checkPositionQuery, 1, nullptr, checkPositionValues, checkPositionLengths, checkPositionFormats, 0);

    bool positionExists = (PQresultStatus(checkPositionResult) == PGRES_TUPLES_OK && PQntuples(checkPositionResult) > 0);

    // ����������� ��������� �������
    PQclear(checkPositionResult);

    return positionExists;
}

#include "ChangeDataBD.h"

ChangeDataBD::ChangeDataBD() : connection(nullptr) {
    // Подключение к базе данных при создании объекта
    if (!connectDB()) {
        std::cerr << "Failed to connect to the database." << std::endl;
    }
}

ChangeDataBD::~ChangeDataBD() {
    // Отключение от базы данных при уничтожении объекта
    disconnectDB();
}

bool ChangeDataBD::connectDB() {
    const char* conninfo = "dbname=kursdb user=bogdan32113 password=I0m1VQqzFjnJ host=ep-young-truth-04408351.eu-central-1.aws.neon.tech port=5432 client_encoding=WINDOWS-1251";

    // Установка соединения
    connection = PQconnectdb(conninfo);

    // Проверка на успешное подключение
    if (PQstatus(connection) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(connection) << std::endl;
        return false;
    }
    std::cout << "Connected"<<std::endl;
    return true;
}

void ChangeDataBD::disconnectDB() {
    // Закрытие соединения
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для вставки нового пользователя в таблицу
    const char* addUserQuery = "INSERT INTO users (Логин, Пароль, ТипПользователя) VALUES ($1, $2, $3) RETURNING idСотрудника";

    // Значения параметров для добавления пользователя
    const char* addUserValues[3] = { login.c_str(), password.c_str(), userType.c_str() };

    // Длины параметров для добавления пользователя
    int addUserLengths[3] = { static_cast<int>(login.length()), static_cast<int>(password.length()),
                              static_cast<int>(userType.length()) };

    // Формат параметров для добавления пользователя (1 для текстовых значений)
    int addUserFormats[3] = { 1, 1, 1 };

    // Выполняем запрос для добавления пользователя и получения idСотрудника
    PGresult* addUserResult = PQexecParams(connection, addUserQuery, 3, nullptr, addUserValues, addUserLengths, addUserFormats, 0);

    if (PQresultStatus(addUserResult) != PGRES_TUPLES_OK || PQntuples(addUserResult) == 0) {
        std::cerr << "Failed to add user: " << PQresultErrorMessage(addUserResult) << std::endl;
        PQclear(addUserResult);
        return false;
    }

    // Получаем idСотрудника из результата запроса
    std::string employeeId = std::to_string(atoi(PQgetvalue(addUserResult, 0, 0)));

    // Освобождаем результат запроса
    PQclear(addUserResult);

    // Создаем параметризованный SQL-запрос для вставки нового сотрудника в таблицу
    const char* addEmployeeQuery = "INSERT INTO Сотрудники (idСотрудника) VALUES ($1)";

    // Значения параметров для добавления сотрудника
    const char* addEmployeeValues[1] = { employeeId.c_str() };

    // Длины параметров для добавления сотрудника
    int addEmployeeLengths[1] = { 0 };

    // Формат параметров для добавления сотрудника (0 для целочисленных значений)
    int addEmployeeFormats[1] = { 0 };

    // Выполняем запрос для добавления сотрудника
    PGresult* addEmployeeResult = PQexecParams(connection, addEmployeeQuery, 1, nullptr, addEmployeeValues, addEmployeeLengths, addEmployeeFormats, 0);

    if (PQresultStatus(addEmployeeResult) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add employee: " << PQresultErrorMessage(addEmployeeResult) << std::endl;
        PQclear(addEmployeeResult);
        return false;
    }

    // Освобождаем результат запроса
    PQclear(addEmployeeResult);

    return true;
}

bool ChangeDataBD::changeUser(std::string login,std::string newPassword,std::string newWorkerId,std::string newUserType)
{

    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для изменения данных пользователя
    const char* query = "UPDATE users SET "
        "Пароль = CASE WHEN $1 <> '' THEN $1 ELSE Пароль END, "
        "idСотрудника = CASE WHEN $2 <> '' THEN $2 ELSE idСотрудника END, "
        "ТипПользователя = CASE WHEN $3 <> '' THEN $3 ELSE ТипПользователя END "
        "WHERE Логин = $4";

    // Значения параметров
    const char* values[4] = { newPassword.c_str(), newWorkerId.c_str(), newUserType.c_str(), login.c_str() };

    // Длины параметров (можно использовать nullptr, если строки завершены нулевым символом)
    int lengths[4] = { static_cast<int>(newPassword.length()), static_cast<int>(newWorkerId.length()),
                       static_cast<int>(newUserType.length()), static_cast<int>(login.length()) };

    // Формат параметров (1 для текстовых значений)
    int formats[4] = { 1, 1, 1, 1 };

    // Выполняем запрос с использованием параметров
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для удаления пользователя
    const char* query = "DELETE FROM users WHERE Логин = $1";

    // Значение параметра
    const char* values[1] = { login.c_str() };

    // Длина параметра (можно использовать nullptr, если строка завершена нулевым символом)
    int lengths[1] = { static_cast<int>(login.length()) };

    // Формат параметра (1 для текстового значения)
    int formats[1] = { 1 };

    // Выполняем запрос с использованием параметра
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Получаем idСотрудника (КемВыдано) из таблицы users по логину
    const char* getUserIdQuery = "SELECT idСотрудника FROM users WHERE Логин = $1";

    // Значение параметра для запроса на получение idСотрудника
    const char* getUserIdValues[1] = { issuedByLogin.c_str() };

    // Длина параметра (можно использовать nullptr, если строка завершена нулевым символом)
    int getUserIdLengths[1] = { static_cast<int>(issuedByLogin.length()) };

    // Формат параметра (1 для текстового значения)
    int getUserIdFormats[1] = { 1 };

    // Выполняем запрос для получения idСотрудника
    PGresult* getUserIdResult = PQexecParams(connection, getUserIdQuery, 1, nullptr, getUserIdValues, getUserIdLengths, getUserIdFormats, 0);

    if (PQresultStatus(getUserIdResult) != PGRES_TUPLES_OK || PQntuples(getUserIdResult) == 0) {
        std::cerr << "Failed to get user ID for assignment: " << PQresultErrorMessage(getUserIdResult) << std::endl;
        PQclear(getUserIdResult);
        return false;
    }

    // Получаем idСотрудника из результата запроса
    int issuedById = atoi(PQgetvalue(getUserIdResult, 0, 0));
    std::string issuedByIdValue = std::to_string(issuedById);
    std::cout << issuedByIdValue;
    // Освобождаем результат запроса
    PQclear(getUserIdResult);

    // Создаем параметризованный SQL-запрос для вставки нового поручения
    const char* addAssignmentQuery = "INSERT INTO Поручения (отделДляПоручения, ДатаВыдачи, ДатаОкончания, ВзятоВИсполнение, Просрочено, КемВыдано) "
        "VALUES ($1, $2, $3, $4, $5, $6)";

    // Значения параметров
    const char* addAssignmentValues[6] = { department, issueDate.c_str(), dueDate.c_str(),
                                           taken ? "true" : "false", overdue ? "true" : "false", issuedByIdValue.c_str()};

    // Длины параметров (можно использовать nullptr, если строки завершены нулевым символом)
    int addAssignmentLengths[6] = { 0, static_cast<int>(issueDate.length()), static_cast<int>(dueDate.length()), 5, 5, 0 };

    // Формат параметров (0 для целочисленных значений, 1 для текстовых значений)
    int addAssignmentFormats[6] = { 0, 1, 1, 0, 0, 0 };


    // Выполняем запрос с использованием параметров
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для обновления поручения
    const char* changeAssignmentQuery = "UPDATE Поручения SET "
        "ДатаВыдачи = CASE WHEN $2 <> '' THEN $2 ELSE ДатаВыдачи END, "
        "ДатаОкончания = CASE WHEN $3 <> '' THEN $3 ELSE ДатаОкончания END, "
        "ВзятоВИсполнение = CASE WHEN $4 <> '' THEN ($4::boolean) ELSE ВзятоВИсполнение END, "
        "Просрочено = CASE WHEN $5 <> '' THEN ($5::boolean) ELSE Просрочено END "
        "WHERE номерПоручения = $1";

    // Значения параметров
    const char* changeAssignmentValues[5] = { assignmentId.c_str(), newIssueDate.c_str(), newDueDate.c_str(),
                                             newTaken ? "true" : "false", newOverdue ? "true" : "false" };

    // Длины параметров (можно использовать nullptr, если строки завершены нулевым символом)
    int changeAssignmentLengths[5] = { static_cast<int>(assignmentId.length()), static_cast<int>(newIssueDate.length()),
                                       static_cast<int>(newDueDate.length()), 5, 5 };

    // Формат параметров (0 для целочисленных значений, 1 для текстовых значений)
    int changeAssignmentFormats[5] = { 0, 1, 1, 0, 0 };

    // Выполняем запрос с использованием параметров
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для удаления пользователя
    const char* query = "DELETE FROM Поручения WHERE номерПоручения = $1";

    // Значение параметра
    const char* values[1] = { assignmentId.c_str() };

    // Длина параметра (можно использовать nullptr, если строка завершена нулевым символом)
    int lengths[1] = { static_cast<int>(assignmentId.length()) };

    // Формат параметра (1 для текстового значения)
    int formats[1] = { 0 };

    // Выполняем запрос с использованием параметра
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для добавления отдела
    const char* addDepartmentQuery = "INSERT INTO Отделы (НазваниеОтдела) VALUES ($1)";

    // Значение параметра
    const char* values[1] = { departmentName.c_str() };

    // Длина параметра (можно использовать nullptr, если строка завершена нулевым символом)
    int lengths[1] = { static_cast<int>(departmentName.length()) };

    // Формат параметра (1 для текстового значения)
    int formats[1] = { 1 };

    // Выполняем запрос с использованием параметра
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
    const std::string& newDepartmentName = "Аналитика";
    if (connection == nullptr) {
        std::cerr << "Not connected to the database." << std::endl;
        return false;
    }

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для изменения отдела
    const char* changeDepartmentQuery = "UPDATE Отделы SET НазваниеОтдела = $2 WHERE номерОтдела = $1";

    // Значения параметров
    const char* values[2] = { departmentId, newDepartmentName.c_str() };

    // Длины параметров (можно использовать nullptr, если строки завершены нулевым символом)
    int lengths[2] = { 0, static_cast<int>(newDepartmentName.length()) };

    // Формат параметров (0 для целочисленных значений, 1 для текстовых значений)
    int formats[2] = { 0, 1 };

    // Выполняем запрос с использованием параметров
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для удаления отдела
    const char* deleteDepartmentQuery = "DELETE FROM Отделы WHERE номерОтдела = $1";

    // Значение параметра
    const char* values[1] = { departmentId };

    // Длина параметра (можно использовать nullptr, если строка завершена нулевым символом)
    int lengths[1] = { 0 };

    // Формат параметра (0 для целочисленных значений)
    int formats[1] = { 0 };

    // Выполняем запрос с использованием параметра
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для добавления должности
    const char* addPositionQuery = "INSERT INTO Должность (НазваниеДолжности) VALUES ($1)";

    // Значение параметра
    const char* values[1] = { positionName.c_str() };

    // Длина параметра (можно использовать nullptr, если строка завершена нулевым символом)
    int lengths[1] = { static_cast<int>(positionName.length()) };

    // Формат параметра (1 для текстового значения)
    int formats[1] = { 1 };

    // Выполняем запрос с использованием параметра
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для изменения должности
    const char* changePositionQuery = "UPDATE Должность SET НазваниеДолжности = $2 WHERE idДолжности = $1";

    // Значения параметров
    const char* values[2] = {positionId, newPositionName.c_str() };

    // Длины параметров (можно использовать nullptr, если строки завершены нулевым символом)
    int lengths[2] = { 0, static_cast<int>(newPositionName.length()) };

    // Формат параметров (0 для целочисленных значений, 1 для текстовых значений)
    int formats[2] = { 0, 1 };

    // Выполняем запрос с использованием параметров
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

    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для удаления должности
    const char* deletePositionQuery = "DELETE FROM Должность WHERE idДолжности = $1";

    // Значение параметра
    const char* values[1] = { positionId };

    // Длина параметра (можно использовать nullptr, если строка завершена нулевым символом)
    int lengths[1] = { 0 };

    // Формат параметра (0 для целочисленных значений)
    int formats[1] = { 0 };

    // Выполняем запрос с использованием параметра
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

    // Проверка существования отдела
    if (!checkDepartmentExists(departmentId)) {
        std::cerr << "Department with id " << departmentId << " does not exist." << std::endl;
        return false;
    }

    // Проверка существования должности
    if (!checkPositionExists(positionId)) {
        std::cerr << "Position with id " << positionId << " does not exist." << std::endl;
        return false;
    }


    // Указываем кодировку Windows-1251
    PQexec(connection, "SET client_encoding TO 'WIN1251'");

    // Создаем параметризованный SQL-запрос для добавления сотрудника
    const char* addEmployeeQuery = "UPDATE Сотрудники SET ФИО = $1, Стаж = $2, Отдел = $3, idДолжности = $4 WHERE idСотрудника = $5";

    // Значения параметров для добавления сотрудника
    const char* addEmployeeValues[5] = { fullName.c_str(),
                                         experience,
                                         departmentId,
                                         positionId,
                                         userId };

    // Длины параметров для добавления сотрудника
    int addEmployeeLengths[5] = { static_cast<int>(fullName.length()), 0, 0, 0, 0 };

    // Формат параметров для добавления сотрудника (1 для текстовых значений, 0 для целочисленных значений)
    int addEmployeeFormats[5] = { 1, 0, 0, 0, 0 };

    // Выполняем запрос для добавления сотрудника
    PGresult* addEmployeeResult = PQexecParams(connection, addEmployeeQuery, 5, nullptr, addEmployeeValues, addEmployeeLengths, addEmployeeFormats, 0);

    if (PQresultStatus(addEmployeeResult) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add employee: " << PQresultErrorMessage(addEmployeeResult) << std::endl;
        PQclear(addEmployeeResult);
        return false;
    }

    // Освобождаем результат запроса
    PQclear(addEmployeeResult);

    return true;
}

bool ChangeDataBD::checkDepartmentExists(const char* departmentId) {
    // Проверка существования отдела в таблице Отделы
    const char* checkDepartmentQuery = "SELECT 1 FROM Отделы WHERE номерОтдела = $1";

    // Значение параметра для проверки существования отдела
    const char* checkDepartmentValues[1] = {departmentId};

    // Длина параметра для проверки существования отдела
    int checkDepartmentLengths[1] = { 0 };

    // Формат параметра для проверки существования отдела (0 для целочисленных значений)
    int checkDepartmentFormats[1] = { 0 };

    // Выполняем запрос для проверки существования отдела
    PGresult* checkDepartmentResult = PQexecParams(connection, checkDepartmentQuery, 1, nullptr, checkDepartmentValues, checkDepartmentLengths, checkDepartmentFormats, 0);

    bool departmentExists = (PQresultStatus(checkDepartmentResult) == PGRES_TUPLES_OK && PQntuples(checkDepartmentResult) > 0);

    // Освобождаем результат запроса
    PQclear(checkDepartmentResult);

    return departmentExists;
}

bool ChangeDataBD::checkPositionExists(const char*  positionId) {
    // Проверка существования должности в таблице Должность
    const char* checkPositionQuery = "SELECT 1 FROM Должность WHERE idДолжности = $1";

    // Значение параметра для проверки существования должности
    const char* checkPositionValues[1] = { positionId };

    // Длина параметра для проверки существования должности
    int checkPositionLengths[1] = { 0 };

    // Формат параметра для проверки существования должности (0 для целочисленных значений)
    int checkPositionFormats[1] = { 0 };

    // Выполняем запрос для проверки существования должности
    PGresult* checkPositionResult = PQexecParams(connection, checkPositionQuery, 1, nullptr, checkPositionValues, checkPositionLengths, checkPositionFormats, 0);

    bool positionExists = (PQresultStatus(checkPositionResult) == PGRES_TUPLES_OK && PQntuples(checkPositionResult) > 0);

    // Освобождаем результат запроса
    PQclear(checkPositionResult);

    return positionExists;
}

#include "ChangeDataBD.h"
//Обязательно srand(time(NULL)); в main без него не будут случайно генериться все что генериться!!!!!!!!!!!!
//////////////////////////////////////////////////
std::string generateRandomString(int length) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string randomString;
    randomString.reserve(length);

    for (int i = 0; i < length; ++i) {
        randomString += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return randomString;
}

ChangeDataBD::ChangeDataBD() {
    // Open or create the SQLite database file
// Open or create the SQLite database file
    int rc = sqlite3_open("./src/application//changeDataBD/your_database.db", &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        // Handle error...
    }
    else {
        std::cout << "Opened database successfully!" << std::endl;

        // Create Users table
        const char* createUsersTableQuery = "CREATE TABLE IF NOT EXISTS Users ("
            "Login TEXT PRIMARY KEY NOT NULL,"
            "Password TEXT NOT NULL,"
            "EmployeeId INTEGER);";

        executeNonQuery(createUsersTableQuery);


        // Create Positions table
        const char* createPositionsTableQuery = "CREATE TABLE IF NOT EXISTS Positions ("
            "PositionId INTEGER PRIMARY KEY NOT NULL,"
            "Title VARCHAR(255) NOT NULL);";

        executeNonQuery(createPositionsTableQuery);

        // Create Departments table
        const char* createDepartmentsTableQuery = "CREATE TABLE IF NOT EXISTS Departments ("
            "DepartmentNumber INTEGER PRIMARY KEY NOT NULL,"
            "Title VARCHAR(255) NOT NULL);";

        executeNonQuery(createDepartmentsTableQuery);

        // Create Tasks table
        const char* createTasksTableQuery = "CREATE TABLE IF NOT EXISTS Tasks ("
            "TaskNumber INTEGER PRIMARY KEY NOT NULL,"
            "DepartmentForAssignment INTEGER NOT NULL,"
            "AssignmentDate TEXT NOT NULL,"
            "DueDate TEXT NOT NULL,"
            "IsTaken INTEGER NOT NULL DEFAULT (0),"
            "IsOverdue INTEGER NOT NULL  DEFAULT (0),"
            "IssuedById INTEGER NOT NULL,"
            "AssignmentTakenDate TEXT,"
            "ExecutorId INTEGER,"
            "IsCompleted INTEGER  DEFAULT (0),"
            "ActualCompletionDate TEXT);";

        executeNonQuery(createTasksTableQuery);

        // Create Employees table
        const char* createEmployeesTableQuery = "CREATE TABLE IF NOT EXISTS Employees ("
            "EmployeeId INTEGER PRIMARY KEY NOT NULL,"
            "FullName VARCHAR(255) NOT NULL,"
            "Experience INTEGER NOT NULL,"
            "Department INTEGER NOT NULL,"
            "PositionId INTEGER NOT NULL);";

        executeNonQuery(createEmployeesTableQuery);
    
    }
}


ChangeDataBD::~ChangeDataBD() {
    // Закрываем базу данных SQLite
    if (db) {
        sqlite3_close(db);
    }
}

bool ChangeDataBD::executeNonQuery(const char* query) {
    // Execute a non-query SQL statement
    int rc = sqlite3_exec(db, query, nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    return true;
}

//Добавить сотрудника
void ChangeDataBD::addEmployee(const std::string& fullName, int experience, int department, int positionId) {
    // Генерация случайного employeeId из 8 знаков
    int employeeId = rand() % 90000000 + 10000000;

    // Генерация случайного логина и пароля из 8 знаков
    std::string login = generateRandomString(8);
    std::string password = generateRandomString(8);

    // Добавление записи в Users
    const char* addUserQuery = "INSERT INTO Users (Login, Password, EmployeeId) VALUES (?, ?, ?)";
    sqlite3_stmt* addUserStatement;
    int rc = sqlite3_prepare_v2(db, addUserQuery, -1, &addUserStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare addUserStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(addUserStatement, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(addUserStatement, 2, password.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(addUserStatement, 3, employeeId);

    rc = sqlite3_step(addUserStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute addUserStatement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(addUserStatement);
        return;
    }

    sqlite3_finalize(addUserStatement);

    // Добавление записи в Employees
    const char* addEmployeeQuery = "INSERT INTO Employees (EmployeeId, FullName, Experience, Department, PositionId) VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* addEmployeeStatement;
    rc = sqlite3_prepare_v2(db, addEmployeeQuery, -1, &addEmployeeStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare addEmployeeStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(addEmployeeStatement, 1, employeeId);
    sqlite3_bind_text(addEmployeeStatement, 2, fullName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(addEmployeeStatement, 3, experience);
    sqlite3_bind_int(addEmployeeStatement, 4, department);
    sqlite3_bind_int(addEmployeeStatement, 5, positionId);

    rc = sqlite3_step(addEmployeeStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute addEmployeeStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(addEmployeeStatement);
}
//Добавить отдел
void ChangeDataBD::addDepartment(int departmentNumber, const std::string& title) {
    const char* addDepartmentQuery = "INSERT INTO Departments (DepartmentNumber, Title) VALUES (?, ?)";
    sqlite3_stmt* addDepartmentStatement;

    int rc = sqlite3_prepare_v2(db, addDepartmentQuery, -1, &addDepartmentStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare addDepartmentStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(addDepartmentStatement, 1, departmentNumber);
    sqlite3_bind_text(addDepartmentStatement, 2, title.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(addDepartmentStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute addDepartmentStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(addDepartmentStatement);
}
//Добавить должность
void ChangeDataBD::addPosition(int positionId, const std::string& title) {
    const char* addPositionQuery = "INSERT INTO Positions (PositionId, Title) VALUES (?, ?)";
    sqlite3_stmt* addPositionStatement;

    int rc = sqlite3_prepare_v2(db, addPositionQuery, -1, &addPositionStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare addPositionStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(addPositionStatement, 1, positionId);
    sqlite3_bind_text(addPositionStatement, 2, title.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(addPositionStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute addPositionStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(addPositionStatement);
}
//Добавить задачу
void ChangeDataBD::addTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate,
    const std::string& dueDate, int issuedById) {
    const char* addTaskQuery = "INSERT INTO Tasks (TaskNumber, DepartmentForAssignment, AssignmentDate, DueDate, IssuedById) "
        "VALUES (?, ?, ?, ?, ?)";
    sqlite3_stmt* addTaskStatement;

    int rc = sqlite3_prepare_v2(db, addTaskQuery, -1, &addTaskStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare addTaskStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(addTaskStatement, 1, taskNumber);
    sqlite3_bind_int(addTaskStatement, 2, departmentForAssignment);
    sqlite3_bind_text(addTaskStatement, 3, assignmentDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(addTaskStatement, 4, dueDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(addTaskStatement, 5, issuedById);


    rc = sqlite3_step(addTaskStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute addTaskStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(addTaskStatement);
}
//Назначить задачу
void ChangeDataBD::giveTask(int taskNumber, int executorId, const std::string& assignmentTakenDate) {
    const char* takeTaskQuery = "UPDATE Tasks SET ExecutorId = ?, IsTaken = 1, AssignmentTakenDate = ? WHERE TaskNumber = ?";
    sqlite3_stmt* takeTaskStatement;

    int rc = sqlite3_prepare_v2(db, takeTaskQuery, -1, &takeTaskStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare takeTaskStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(takeTaskStatement, 1, executorId);
    sqlite3_bind_text(takeTaskStatement, 2, assignmentTakenDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(takeTaskStatement, 3, taskNumber);

    rc = sqlite3_step(takeTaskStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute takeTaskStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(takeTaskStatement);
}
//Изменить название отдела по id
void ChangeDataBD::changeDepartmentTitle(int departmentNumber, const std::string& newTitle) {
    const char* changeDepartmentQuery = "UPDATE Departments SET Title = ? WHERE DepartmentNumber = ?";
    sqlite3_stmt* changeDepartmentStatement;

    int rc = sqlite3_prepare_v2(db, changeDepartmentQuery, -1, &changeDepartmentStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare changeDepartmentStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(changeDepartmentStatement, 1, newTitle.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(changeDepartmentStatement, 2, departmentNumber);

    rc = sqlite3_step(changeDepartmentStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute changeDepartmentStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(changeDepartmentStatement);
}
//Изменить название должности по id
void ChangeDataBD::changePositionTitle(int positionId, const std::string& newTitle) {
    const char* changePositionQuery = "UPDATE Positions SET Title = ? WHERE PositionId = ?";
    sqlite3_stmt* changePositionStatement;

    int rc = sqlite3_prepare_v2(db, changePositionQuery, -1, &changePositionStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare changePositionStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(changePositionStatement, 1, newTitle.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(changePositionStatement, 2, positionId);

    rc = sqlite3_step(changePositionStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute changePositionStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(changePositionStatement);
}
//Изменить содержание задачи по id
void ChangeDataBD::updateTask(int taskNumber, int departmentForAssignment, const std::string& assignmentDate,
    const std::string& dueDate, int issuedById, const std::string& assignmentTakenDate,
    int executorId, int isCompleted, const std::string& actualCompletionDate) {
    const char* updateTaskQuery = "UPDATE Tasks SET DepartmentForAssignment = ?, "
        "AssignmentDate = ?, DueDate = ?, IssuedById = ?, AssignmentTakenDate = ?, "
        "ExecutorId = ?, IsCompleted = ?, ActualCompletionDate = ? WHERE TaskNumber = ?";
    sqlite3_stmt* updateTaskStatement;

    int rc = sqlite3_prepare_v2(db, updateTaskQuery, -1, &updateTaskStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare updateTaskStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(updateTaskStatement, 1, departmentForAssignment);
    sqlite3_bind_text(updateTaskStatement, 2, assignmentDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(updateTaskStatement, 3, dueDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(updateTaskStatement, 4, issuedById);
    sqlite3_bind_text(updateTaskStatement, 5, assignmentTakenDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(updateTaskStatement, 6, executorId);
    sqlite3_bind_int(updateTaskStatement, 7, isCompleted);
    sqlite3_bind_text(updateTaskStatement, 8, actualCompletionDate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(updateTaskStatement, 9, taskNumber);

    rc = sqlite3_step(updateTaskStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute updateTaskStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(updateTaskStatement);
}
//Изменить параметры сотрудника по id
void ChangeDataBD::changeEmployee(int employeeId, const std::string& fullName, int experience,
    int department, int positionId) {
    const char* changeEmployeeQuery = "UPDATE Employees SET FullName = ?, Experience = ?, "
        "Department = ?, PositionId = ? WHERE EmployeeId = ?";
    sqlite3_stmt* changeEmployeeStatement;

    int rc = sqlite3_prepare_v2(db, changeEmployeeQuery, -1, &changeEmployeeStatement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare changeEmployeeStatement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(changeEmployeeStatement, 1, fullName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(changeEmployeeStatement, 2, experience);
    sqlite3_bind_int(changeEmployeeStatement, 3, department);
    sqlite3_bind_int(changeEmployeeStatement, 4, positionId);
    sqlite3_bind_int(changeEmployeeStatement, 5, employeeId);

    rc = sqlite3_step(changeEmployeeStatement);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute changeEmployeeStatement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(changeEmployeeStatement);
}
//для заполнения вектора данными из таблицы
static int callback(void* data, int argc, char** argv, char** azColName) {
    std::vector<std::string> row;

    for (int i = 0; i < argc; i++) {
        row.push_back(argv[i] ? argv[i] : "NULL");
    }

    std::vector<std::vector<std::string>>* result = static_cast<std::vector<std::vector<std::string>>*>(data);
    result->push_back(row);

    return 0;
}

//Получить таблицу отделов
std::vector<std::vector<std::string>> ChangeDataBD::getDepartments() {
    std::vector<std::vector<std::string>> result;

    const char* query = "SELECT * FROM Departments;";
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query, callback, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return result;
}
//Получить таблицу должностей
std::vector<std::vector<std::string>> ChangeDataBD::getPositions() {
    std::vector<std::vector<std::string>> result;

    const char* query = "SELECT * FROM Positions;";
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query, callback, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return result;
}
//Получить таблицу сотрудников
std::vector<std::vector<std::string>> ChangeDataBD::getEmployees() {
    std::vector<std::vector<std::string>> result;

    const char* query = "SELECT * FROM Employees;";
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query, callback, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return result;
}
//Получить таблицу пользователей
std::vector<std::vector<std::string>> ChangeDataBD::getUsers() {
    std::vector<std::vector<std::string>> result;

    const char* query = "SELECT * FROM Users;";
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query, callback, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return result;
}
//Получить таблицу задач
std::vector<std::vector<std::string>> ChangeDataBD::getTasks() {
    std::vector<std::vector<std::string>> result;

    const char* query = "SELECT * FROM Tasks;";
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, query, callback, &result, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return result;
}
//Проверить логин пароль и вернуть должность если есть, если нет вернуть 0(вообще там своя ошибка возвращается до того как вернется 0)
int ChangeDataBD::getEmployeePositionId(const std::string& login, const std::string& password) {
    const char* query = "SELECT e.PositionId FROM Users u JOIN Employees e ON u.EmployeeId = e.EmployeeId "
        "WHERE u.Login = ? AND u.Password = ?;";
    sqlite3_stmt* statement;

    int rc = sqlite3_prepare_v2(db, query, -1, &statement, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    }

    sqlite3_bind_text(statement, 1, login.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(statement);

    if (rc == SQLITE_ROW) {
        int positionId = sqlite3_column_int(statement, 0);
        sqlite3_finalize(statement);
        return positionId;
    }
    else {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(statement);
        return 0;
    }
}
//Обязательно srand(time(NULL)); в main без него не будут случайно генериться все что генериться!!!!!!!!!!!!


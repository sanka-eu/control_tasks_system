#ifndef CHANGEDATABD_H
#define CHANGEDATABD_H


class ChangeDataBD
{

public:
    ChangeDataBD();

    //методы меняют поле БД объявленное в private секции, возвращают true если изменение прошло удачно, если нет - false
    bool addUser();
    bool changeUser();
    bool deleteUser();
    bool addAssigment();
    bool changeAssigment();
    bool deleteAssigment();

private:
    //поле с базой данных, в реализации public методов обращаться и работать с этим полем, изменяя БД
    //som_type DataBase;
}; // class ChangeDataWidget

#endif //CHANGEDATABD_H
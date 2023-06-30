#pragma once
#ifndef _dbmsLib8_
#define _dbmsLib8_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;
namespace dbmsLib8

{
    static enum Condition { Undefined, Equal, NotEqual, Less, Greater, LessOrEqual, GreaterOrEqual };
    //const char* typeNames[]={
    //  "NoType",
    //  "Int32",
    //  "Double",
    //  "String",
    //  "DBDate"
    //};
    //DBType-перечисление типов полей таблиц БД:
    enum DBType { NoType, Int32, Double, String, DBDate };
    //Condition-перечисление условий, по которым могут сравниваться поля таблиц БД:
    //enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
    const int LENGTH7 = 24;//длина имени таблицы и имени столбца.
    //ColumnDesc - описание данных в столбце таблицы 
    //данные типа string имеют одинаковую длину (length) внутри одного столбца, 
    //но в разных столбцах их длина может отличаться
    struct ColumnDesc {
        char colName[LENGTH7];//имя столбца
        DBType colType;//тип данных в столбце таблицы
        int length; //максимальное число символов, допустимое 
        //для представления данных в столбце
    };
    struct Strip {//полоса распечатки таблицы
        int nField;//число полей 
        int* fieldWidth;//ширина полей в полосе (массив)
    };
    typedef map<string, void*> Row;
    typedef map<string, ColumnDesc> Header;

    //----------------class DBTable8--------------------------------------
    class DBDate8
    {
        int day, month, year;
        const int arrDaysInLeapMonths[13] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
        const int arrDaysInNonLeapMonths[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

    public:
        DBDate8(string date);//формат строки: dd.mm.yyyy
        DBDate8(int d, int m, int y);
        DBDate8() :day(0), month(0), year(0) {};//???конструктор по умолчанию
        DBDate8(DBDate8& dat) :day(dat.day), month(dat.month), year(dat.year) {}
        friend string DateToStr(DBDate8& date);
        int GetDay();
        int GetMonth();
        int GetYear();
        void SetDay(int d);
        void SetMonth(int m);
        void SetYear(int y);
        bool IsLeapYear(int year); //год високосный?
        int GetDaysInMonth(int month, int year);//Количество дней в месяце
        int DaysInCurYear();//Количество дней от начала года до текущей даты
        bool operator==(DBDate8& date);
        bool operator<(DBDate8& date);
        bool operator>(DBDate8& date);
        bool operator<= (DBDate8& date);
        bool operator>= (DBDate8& date);
        bool operator!= (DBDate8& date);
        friend ostream& operator<<(ostream& out, DBDate8& date) {
            return out << std::to_string(date.GetDay()) + "." + to_string(date.GetMonth()) + "." + to_string(date.GetYear());
        }
        DBDate8& operator+=(int days);//Прибавляет к текущей дате days дней
        DBDate8& operator-=(int days);//Вычитает из текущей даты days дней
        int operator-(DBDate8& date);//Количество дней между текущей датой и date
                 //Если текущая дата > date, результат < 0.
    };

    //--------------DaBTable8--------------------
    class DBTable8 {
    public:
        DBType GetType8(string columnName);
        const char* TypeName8(DBType type);
        virtual ~DBTable8() {};//виртуальный деструктор
        //virtual Header GetHeader8()=0;
        //virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
        //по значению ключа определяет 
        //порядковый номер (индекс) строки (записи) в data.
        // keyValue-значение ключа (указатель на string, int или DBDate)
        // keyColumnName-имя ключевого столбца (первичный или вторичный ключ)
        //в таблице может быть несколько записей с одинаковым значением вторичного   //ключа.
        //virtual Row operator[](int index)=0;
        virtual string valueToString8(Row& row, string columnName) = 0;
        /*virtual int GetSize()=0;
        virtual void SetHeader(Header& hdr)=0;*/
        virtual void ReadDBTable8(string  fileName) = 0;       //fileName="..\\"+dbName+"\\"+tableName+".bin"|".txt"  
        virtual void WriteDBTable8(string fileName) = 0;
        /*virtual void SetTableName(string tName)=0;
        virtual void SetPrimaryKey(string key)=0;
        virtual string GetTableName()=0;
        virtual string GetPrimaryKey()=0;
        virtual void SetFileName(string path)=0;
        virtual string GetFileName()=0;*/
        virtual void PrintTable8(int screenWidth) = 0;
        //virtual Row CreateRow()=0;
        //virtual void AddRow(Row row,int index)=0;
      //  virtual DBTable1* SelfRows(string colName,Condition cond, void* value)=0;
    };
    bool comparator(/*TableDataType*/DBType type, void* obj1, Condition condition, void* obj);
    //=============== class DBTableTxt8 =============================
    class DBTableTxt8 :public DBTable8 {
    private:
        Header columnHeaders;
        string tableName;
        string primaryKey;
        vector<Row> data;
        string fileName;
    public:
        DBTableTxt8() {}
        DBTableTxt8(string tabName)
        {
            tableName = tabName;
        }
        DBTableTxt8(const DBTableTxt8& obj)
        {

        }/*: DBTable(tabName){}*/
        DBTableTxt8(string tabName, Header hdr, string primKey);   /*:DBTable(tabName,hdr,primKey){}*/
        ~DBTableTxt8() {};//!!!деструктор перегружен,чтобы память,выделенная void*,не           //утекала
        vector<int> IndexOfRecord(void* keyValue, string keyColumnName);
        string valueToString8(Row& row, string columnName);
        string ignoreBlanc(const string str);
        void task1();
        void ReadDBTable8(string fileName);//tabName=path+tableName
        //void ReadTableBin(string fileName);//чтение таблицы из бинарного файла
        void PrintTable8(int screenWidth);
        void WriteDBTable8(string fileName);//tabName=path+tableName  
        //void WriteTableBin(string fileName);//запись таблицы в бинарный файл
        int GetSize8() { return data.size(); };
        Row operator[](int ind);
        //  Row operator[](int ind);
        //  void SetFileName(string path);
        //  void SetTableName(string tName);
        //  void SetPrimaryKey(string key);
        //  string GetFileName();
        string GetTableName();
        //  string GetPrimaryKey(){return primaryKey;}
        //Header GetHeader8();
        //  void SetHeader(Header& hdr);
        Row CreateRow();
        Row GetRow(int index);
        void AddRow(Row row, int index);
        DBTable8* SelfRows8(string columnName, Condition cond, void* value);
        //Макет распечатки таблицы:
        //screenWidth - ширина экрана (входной параметр)
        //nStrips - число полос в распечатке (выходной параметр)
        //strips[nStrips] - описание полос таблицы: 
        //число столбцов и ширина каждого столбца в полосе (выходной параметр)
        void CreateTableMaket(Strip*& strips, int& nStrips, int screenWidth);

    };
    //=====================Класс DBTableBin8=====================================
    class DBTableBin8 : public DBTable8 {
        string tableName;
        char tabName[LENGTH7];
        char primaryKey[LENGTH7];//имя столбца со значениями первичного ключа
      //  int nColumn;
      //  ColumnDesc* header;        
      //  int nRows; 
      //  int RowLength();
      //  int DataBegin();
      //  int FieldPosition(string colName);//смещение поля colName от начала строки в байтах
      //  int FieldLength(string colName);//длина поля colName в байтах
      //  void ResizeData(int deltaRows);
      //  char** data;    
      //  int maxRows;//число строк в data с учетом DELTA (при считывании таблицы
      //  //из файла устанавливается равным nRows+DELTA).В файл не записывается
        //  char fileName[80];//В файл не записывается. Используется в методах для
//  //обращения к файлу
//  void CreateTableMaket(Strip *&strips,int &nStrips,int screenWidth);
    public:
        DBTableBin8() {}
        DBTableBin8(string tabName)
        {
            tableName = tabName;
        }/*: DBTable(tabName){}*/
        DBTableBin8(string tabName, Header hdr, string primKey);   /*:DBTable(tabName,hdr,primKey){}*/
        ~DBTableBin8()
        {
            cout << "~DBTableBin()" << endl;
        }
        /*  DBTableBin8()
          {}
          DBTableBin8(string tableName){}
          //DBTableBin8(string tableName,Header GetHeader(),string primKey);
          ~DBTableBin8()
          {
            cout<<"~DBTableBin()"<<endl;
          }
          */
          //Header GetHeader();
        vector<int> IndexOfRecord(void* keyPtr, string keyName);
        //по значению ключа определяет 
        //порядковый номер (индекс) строки (записи) в data.
        // keyPtr-значение ключа (указатель на string, int или DBDate)
        // keyName-имя ключевого столбца (первичный или вторичный ключ)
        //в таблице может быть несколько записей с одинаковым значением вторичнего ключа.
      //  int FieldPosInFile(int rowIndex,string columnName);
      //  Row GetRow(int index);
      //  Row operator[](int index);
        string valueToString8(Row& row, string columnName);
        //  int GetSize(){return nRows;}
        //  //void SetHeader(Header& hdr);
        
        void ReadDBTable8(string fileName);//fileName="..\\"+dbName+"\\"+tableName+".bin"                      
        void WriteDBTable8(string fileName);
        //  void SetTableName(string tName);
        //  void SetPrimaryKey(string key);
        //  string GetTableName(){return tabName;}
        //  string GetPrimaryKey(){return primaryKey;}
        //  void SetFileName(string path){
        //    strcpy_s(fileName,80,(path+"//"+tabName+".bin").c_str());
        //  } 
        //  string GetFileName(){return fileName;}
        void PrintTable8(int screenWidth);
        //  Row CreateRow();
        //  void AddRow(Row row,int index);
        //  DBTable8* SelfRows(string colName,Condition cond, void* value);
    };
    //===============class DBTableSet8=============================
    class DBTableSet8 {
    private:
        string dbName;
        map<string, DBTable8*> db;
    public:
        DBTableSet8() {};
        DBTableSet8(string name) {
            dbName = name;
            ReadDB8(dbName);
        }

        int ReadDB8(string lib);
        int PrintDB8(int screenWidth);
        int WriteDB8();
        string GetDBName8() { return dbName; }
        DBTable8* operator[](string tableName);
        /*Relation GetRelation(string relationName);
        Row ParentRow(Relation& relation,Row& childRow);
        DBTable* ChildRows(Relation& relation,Row& parentRow);*/
    };
}
#endif //конец _dbmsLib8_
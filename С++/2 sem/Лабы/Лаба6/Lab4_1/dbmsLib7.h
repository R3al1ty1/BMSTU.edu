#pragma once
#ifndef _dbmsLib7_
#define _dbmsLib7_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;
namespace dbmsLib7
{
//const char* typeNames[]={
//	"NoType",
//	"Int32",
//	"Double",
//	"String",
//	"DBDate"
//};
//DBType-перечисление типов полей таблиц БД:
enum DBType{ NoType, Int32, Double, String, Date};
//Condition-перечисление условий, по которым могут сравниваться поля таблиц БД:
enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
const int LENGTH1 = 24;//длина имени таблицы и имени столбца.
//ColumnDesc - описание данных в столбце таблицы 
//данные типа string имеют одинаковую длину (length) внутри одного столбца, 
//но в разных столбцах их длина может отличаться
struct ColumnDesc { 
	char colName[LENGTH1];//имя столбца
	DBType colType;//тип данных в столбце таблицы
	int length; //максимальное число символов, допустимое 
	//для представления данных в столбце
}; 
struct Strip{//полоса распечатки таблицы
	int nField;//число полей 
	int* fieldWidth;//ширина полей в полосе (массив)
};
 typedef map<string, void*> Row;
 typedef map<string, ColumnDesc> Header;
 //----------------class DBTable1--------------------------------------
 class DBDate7
 {	
	friend string DateToStr(DBDate7& date);
	friend ostream& operator<<(ostream& out,DBDate7& date);
	int day, month, year;
	bool IsLeapYear (int year); //год високосный?
	int GetDaysInMonth(int month,int year);//Количество дней в месяце
	int DaysInCurYear();//Количество дней от начала года до текущей даты
  public:
	DBDate7(string date);//формат строки: dd.mm.yyyy
	DBDate7(int d,int m,int y);		DBDate7():day(0),month(0),year(0){};//???конструктор по умолчанию
	DBDate7(DBDate7& dat):day(dat.day),month(dat.month),year(dat.year){}		int GetDay();
	int GetMonth();
	int GetYear();
	bool operator==(DBDate7& date);
	bool operator<(DBDate7& date); 
	bool operator>(DBDate7& date);
	bool operator<= (DBDate7& date);
	bool operator>= (DBDate7& date);
	bool operator!= (DBDate7& date);
	DBDate7& operator+=(int days);//Прибавляет к текущей дате days дней
	DBDate7& operator-=(int days);//Вычитает из текущей даты days дней
	int operator-(DBDate7& date);//Количество дней между текущей датой и date
	 				//Если текущая дата > date, результат < 0.
};
class DBTable7{
public:
	DBType GetType7(char* columnName);
	const char* TypeName1(DBType type);
	virtual ~DBTable7(){};//виртуальный деструктор
	virtual Header GetHeader7()=0;
	//virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
	//по значению ключа определяет 
	//порядковый номер (индекс) строки (записи) в data.
	// keyValue-значение ключа (указатель на string, int или DBDate)
	// keyColumnName-имя ключевого столбца (первичный или вторичный ключ)
	//в таблице может быть несколько записей с одинаковым значением вторичного 	//ключа.
	//virtual Row operator[](int index)=0;
	virtual string valueToString7(Row& row,string columnName)=0;
	/*virtual int GetSize()=0;
	virtual void SetHeader(Header& hdr)=0;*/
	virtual void ReadDBTable7(string  fileName)=0; 			//fileName="..\\"+dbName+"\\"+tableName+".bin"|".txt"					virtual void WriteDBTable1(string fileName)=0;
	/*virtual void SetTableName(string tName)=0;
	virtual void SetPrimaryKey(string key)=0;
	virtual string GetTableName()=0;
	virtual string GetPrimaryKey()=0;
	virtual void SetFileName(string path)=0;
	virtual string GetFileName()=0;*/
	virtual void PrintTable7(int screenWidth)=0;
	//virtual Row CreateRow()=0;
	//virtual void AddRow(Row row,int index)=0;
//	virtual DBTable1* SelfRows(string colName,Condition cond, void* value)=0;
};
//=============== class DBTableTxt1 =============================
class DBTableTxt7:public DBTable7{
private:
	Header columnHeaders;
	string tableName;
	string primaryKey; 
	vector<Row> data;
	string fileName;
  public:
	DBTableTxt7(){}
	DBTableTxt7(string tabName);/*: DBTable(tabName){}*/
	DBTableTxt7(string tabName,Header hdr,string primKey); 	/*:DBTable(tabName,hdr,primKey){}*/
	~DBTableTxt7(){};//!!!деструктор перегружен,чтобы память,выделенная void*,не 					//утекала
	//vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
 	string valueToString7(Row& row,string columnName);
	void ReadDBTable7(string fileName);//tabName=path+tableName
	//void ReadTableBin(string fileName);//чтение таблицы из бинарного файла
	void PrintTable7(int screenWidth);
	void WriteDBTable7(string fileName);//tabName=path+tableName	
	//void WriteTableBin(string fileName);//запись таблицы в бинарный файл
	int GetSize7();
	//	Row operator[](int ind);
	//	void SetFileName(string path);
	//	void SetTableName(string tName);
	//	void SetPrimaryKey(string key);
	//	string GetFileName();
	//	string GetTableName();
	//	string GetPrimaryKey(){return primaryKey;}
	Header GetHeader7();
	//	void SetHeader(Header& hdr);
	//	Row CreateRow();
	//	Row GetRow(int index);
	//	void AddRow(Row row,int index);
	//	DBTable1* SelfRows(string columnName,Condition cond, void* value);
		//Макет распечатки таблицы:
		//screenWidth - ширина экрана (входной параметр)
		//nStrips - число полос в распечатке (выходной параметр)
		//strips[nStrips] - описание полос таблицы: 
		//число столбцов и ширина каждого столбца в полосе (выходной параметр)
	void CreateTableMaket(Strip* &strips,int &nStrips,int screenWidth);
	
	};
//===============class DBTableSet1=============================
class DBTableSet7{
private:
	string dbName;
	map<string, DBTable7*> db;
public: 
	DBTableSet7(){};
	DBTableSet7(string name);
	int ReadDB1();
	void PrintDB1(int screenWidth);
	void WriteDB1();
	string GetDBName(){return dbName;}
	DBTable7* operator[](string tableName); 
	/*Relation GetRelation(string relationName);
	Row ParentRow(Relation& relation,Row& childRow);
	DBTable* ChildRows(Relation& relation,Row& parentRow);*/
};
}
 #endif //конец _dbmsLib1_

#pragma once
#ifndef _dbmsLib5_
#define _dbmsLib5_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;
namespace dbmsLib5
{
	//-----------------класс DBDate5----------------------------
	class DBDate5
	{
		static const int arrDays[13];	
		friend string DateToStr(DBDate5& date);
		friend ostream& operator<<(ostream& out,DBDate5& date);
		int GetJDN(); // Получает из даты номер юлианского дня
		DBDate5 GetDateFromJDN(int jdn); // Получает дату из номера юлианского дня
		int day, month, year;
		bool IsLeapYear (int year); //год високосный?
		int GetDaysInMonth(int month,int year);//Количество дней в месяце
		int DaysInCurYear();//Количество дней от начала года до текущей даты
	public:
		DBDate5(string date);//формат строки: dd.mm.yyyy
		DBDate5(int d,int m,int y);		DBDate5():day(0),month(0),year(0){};//???конструктор по умолчанию
		DBDate5(DBDate5& dat):day(dat.day),month(dat.month),year(dat.year){}		
		int GetDay();
		int GetMonth();
		int GetYear();
		bool operator==(DBDate5& date);
		bool operator<(DBDate5& date); 
		bool operator>(DBDate5& date);
		bool operator<= (DBDate5& date);
		bool operator>= (DBDate5& date);
		bool operator!= (DBDate5& date);
		DBDate5& operator+=(int days);//Прибавляет к текущей дате days дней
		DBDate5& operator-=(int days);//Вычитает из текущей даты days дней
		int operator-(DBDate5& date);//Количество дней между текущей датой и date
		//Отсчитывается от текущей даты. Если текущая дата > date, результат < 0.
	};

	static const char* typeNames[]={
		"NoType",
		"Int32",
		"Double",
		"String",
		"DBDate"
	}; 
	//DBType-перечисление типов полей таблиц БД:
	const int LENGTH = 24;
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

	typedef map<string, void*> Row;
	typedef map<string, ColumnDesc> Header;
	//----------------class DBTable5--------------------------------------
	class DBTable5{//Абстрактный базовый класс
	public:
		DBTable5() {}
		DBTable5(string tabName) {}
		DBType GetType1(char* columnName);
		const char* TypeName1(DBType type);
		virtual ~DBTable5(){};//виртуальный деструктор
		virtual string GetTableName() = 0;
		//virtual Header GetHeader1()=0;
		//virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
		//по значению ключа определяет порядковый номер (индекс) строки (записи) в data.
		// keyValue-значение ключа (указатель на string, int или DBDate)
		// keyColumnName-имя ключевого столбца (первичный или вторичный ключ)
		//в таблице может быть несколько записей с одинаковым значением вторичного//ключа.
		//virtual Row operator[](int index)=0;
		virtual string valueToString5(Row& row,string columnName)=0;
		/*virtual int GetSize()=0;
		virtual void SetHeader(Header& hdr)=0;*/
		virtual void ReadDBTable5(string  fileName)=0; 			//fileName="..\\"+dbName+"\\"+tableName+".bin"|".txt"					
		virtual void WriteDBTable5(string fileName)=0;
		/*virtual void SetTableName(string tName)=0;
		virtual void SetPrimaryKey(string key)=0;
		virtual string GetTableName()=0;
		virtual string GetPrimaryKey()=0;
		virtual void SetFileName(string path)=0;
		virtual string GetFileName()=0;*/
		virtual void PrintTable5(int screenWidth)=0;
		//virtual Row CreateRow()=0;
		//virtual void AddRow(Row row,int index)=0;
		//	virtual DBTable5* SelfRows(string colName,Condition cond, void* value)=0;
	};
	//=============== class DBTableTxt5 =============================
	class DBTableTxt5:public DBTable5{
	private:
		Header columnHeaders;
		string tableName;
		string primaryKey; 
		vector<Row> data;
		string fileName;
	public:
		DBTableTxt5() {}
		DBTableTxt5(string tabName): DBTable5(tabName){}
		DBTableTxt5(string tabName,Header hdr,string primKey); 	/*DBTable(tabName,hdr,primKey){}*/
		~DBTableTxt5(){
			for (size_t i = 0; i < data.size(); ++i)
			{
				for (auto iter = data[i].begin(); iter != data[i].end(); ++iter) {
					delete iter->second;
				}
			}	
		}
		//vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
		string valueToString5(Row& row,string columnName);
		void ReadDBTable5(string fileName);//tabName=path+tableName
		void ReadTableBin5(string fileName);//чтение таблицы из бинарного файла
		void PrintTable5(int screenWidth);
		string GetTableName(){return tableName;}
		void WriteDBTable5(string fileName);//tabName=path+tableName	
		void WriteTableBin5(string fileName);//запись таблицы в бинарный файл
		int GetSize5();
		//	Row operator[](int ind);
		//	void SetFileName(string path);
		//	void SetTableName(string tName);
		//	void SetPrimaryKey(string key);
		//	string GetFileName();
		//	string GetTableName();
		//	string GetPrimaryKey(){return primaryKey;}
		Header GetHeader5();
		//	void SetHeader(Header& hdr);
		//	Row CreateRow();
		Row GetRow(int index);
		//	void AddRow(Row row,int index);
		//	DBTable5* SelfRows(string columnName,Condition cond, void* value);

	};
	class DBTableBin5: public DBTable5{
		char tabName[LENGTH];
		char primaryKey[LENGTH];//имя столбца со значениями первичного ключа
		int nColumn;
		ColumnDesc* header;				
		int nRows; 
		int RowLength();
		int DataBegin();
		int FieldPosition(string colName);//смещение поля colName от начала строки в байтах
		int FieldLength(string colName);//длина поля colName в байтах
		void ResizeData(int deltaRows);
		char** data;		
		int maxRows;//число строк в data с учетом DELTA (при считывании таблицы
		//из файла устанавливается равным nRows+DELTA).В файл не записывается
		char fileName[80];//В файл не записывается. Используется в методах для
		//обращения к файлу
	public:
		DBTableBin5(){}
		DBTableBin5(string tableName) { cout << "sd"; }
		DBTableBin5(string tableName,Header hdr,string primKey);		
		~DBTableBin5(){}
		Header GetHeader();
		void DBTableClear();
		//vector<int> IndexOfRecord(void* keyPtr,string keyName);
		int FieldPosInFile(int rowIndex,string columnName);
		Row GetRow(int index);
		//Row operator[](int index);
		string valueToString5(Row& row,string columnName);
		int GetSize(){return nRows;}
		//void SetHeader(Header& hdr);
		void ReadDBTable5(string fileName);											
		void WriteDBTable5(string fileName);
		//void SetTableName(string tName);
		//void SetPrimaryKey(string key);
		string GetTableName(){return tabName;}
		string GetPrimaryKey(){return primaryKey;}
		void SetFileName(string path){
			strcpy_s(fileName,80,(path+"//"+tabName+".bin").c_str());
		} 
		string GetFileName(){return fileName;}
		void PrintTable5(int screenWidth);
		//Row CreateRow();
		//void AddRow(Row row,int index);
		//DBTable5* SelfRows(string colName,Condition cond, void* value);
	};

	//===============class DBTableSet5=============================
	class DBTableSet5{
	private:
		string dbName;
		map<string, DBTable5*> db;
	public: 
		DBTableSet5(){}
		DBTableSet5(string name) { 
			dbName = name;
			ReadDB5(dbName);
		}
		int ReadDB5(string dbName);
		void PrintDB5(int screenWidth);
		void WriteDB5();
		string GetDBName(){return dbName;}
		DBTable5* operator[](string tableName); 
		/*Relation GetRelation(string relationName);
		Row ParentRow(Relation& relation,Row& childRow);
		DBTable* ChildRows(Relation& relation,Row& parentRow);*/
	};
}
#endif //конец _dbmsLib5_

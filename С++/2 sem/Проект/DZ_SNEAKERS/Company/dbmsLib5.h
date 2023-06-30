#pragma once
#ifndef _dbmsLib5_
#define _dbmsLib5_
#include <iostream>
#include <fstream>
#include <strstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;
namespace dbmsLib5
{
	//-----------------����� DBDate5----------------------------
	class DBDate5
	{
		static const int arrDays[13];	
		friend string DateToStr(DBDate5& date);
		friend ostream& operator<<(ostream& out,DBDate5& date);
		int GetJDN(); // �������� �� ���� ����� ���������� ���
		DBDate5 GetDateFromJDN(int jdn); // �������� ���� �� ������ ���������� ���
		int day, month, year;
		bool IsLeapYear (int year); //��� ����������?
		int GetDaysInMonth(int month,int year);//���������� ���� � ������
		int DaysInCurYear();//���������� ���� �� ������ ���� �� ������� ����
	public:
		DBDate5(string date);//������ ������: dd.mm.yyyy
		DBDate5(int d,int m,int y);		
		DBDate5():day(0),month(0),year(0){};//???����������� �� ���������
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
		DBDate5& operator+=(int days);//���������� � ������� ���� days ����
		DBDate5& operator-=(int days);//�������� �� ������� ���� days ����
		int operator-(DBDate5& date);//���������� ���� ����� ������� ����� � date
		//������������� �� ������� ����. ���� ������� ���� > date, ��������� < 0.
	};

	static const char* typeNames[]={
		"NoType",
		"Int32",
		"Double",
		"String",
		"DBDate"
	}; 
	//DBType-������������ ����� ����� ������ ��:
	const int LENGTH = 24;
	enum DBType{ NoType, Int32, Double, String, Date};
	//Condition-������������ �������, �� ������� ����� ������������ ���� ������ ��:
	enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
	bool comparator(DBType type, void *obj1, Condition condition, void *obj2);
	const int LENGTH1 = 24;//����� ����� ������� � ����� �������.
	//ColumnDesc - �������� ������ � ������� ������� 
	//������ ���� string ����� ���������� ����� (length) ������ ������ �������, 
	//�� � ������ �������� �� ����� ����� ����������
	struct ColumnDesc { 
		char colName[LENGTH1];//��� �������
		DBType colType;//��� ������ � ������� �������
		int length; //������������ ����� ��������, ���������� 
		//��� ������������� ������ � �������
	}; 

	typedef map<string, void*> Row;
	typedef map<string, ColumnDesc> Header;
	
	
	//----------------class DBTable5--------------------------------------
	class DBTable5{//����������� ������� �����
	public:
		DBTable5() {}
		DBTable5(string tabName) {}
		virtual DBType GetType(string columnName)=0;
		virtual string TypeName(DBType type)=0;
		virtual void* GetValue(string value, string columnName, dbmsLib5::Header hdr)=0;
		virtual ~DBTable5(){};//����������� ����������
		virtual Row operator[](int index)=0;
		virtual string valueToString5(Row& row,string columnName)=0;
		virtual void ReadDBTable5(string  fileName)=0; 			//fileName="..\\"+dbName+"\\"+tableName+".bin"|".txt"					
		virtual void WriteDBTable5(string fileName)=0;
		virtual void SetTableName(string tName)=0;
		virtual void SetPrimaryKey(string key)=0;
		virtual int GetSize() = 0;
		virtual string GetPrimaryKey() = 0;
		virtual string GetTableName() = 0;
		virtual void SetFileName(string path)=0;
		virtual string GetFileName()=0;
		virtual void PrintTable5(int screenWidth) = 0;
		virtual Row CreateRow() = 0;
		virtual void AddRow(Row row,int index)=0;
		virtual void DeleteRow(int index)=0;
		virtual void SetRow(Row row, int index)=0;
		virtual Row GetRow(int index)=0;
		virtual Header GetHeader()=0;
		virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
		virtual DBTable5* SelfRows(string colName,Condition cond, void* value)=0;
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
		~DBTableTxt5();
		string TypeName(DBType type);
		DBType GetType(string columnName);
		string valueToString5(Row& row,string columnName);
		void* GetValue(string value, string columnName, dbmsLib5::Header hdr);
		void ReadDBTable5(string fileName);//tabName=path+tableName
		void ReadTableBin5(string fileName);//������ ������� �� ��������� �����
		void PrintTable5(int screenWidth);
		void WriteDBTable5(string fileName);//tabName=path+tableName	
		void WriteTableBin5(string fileName);//������ ������� � �������� ����
		int GetSize();
		Row operator[](int ind);
		void SetFileName(string path);
		void SetTableName(string tName);
		void SetPrimaryKey(string key);
		string GetFileName();
		string GetTableName();
		string GetPrimaryKey();
		Header GetHeader();
		Row CreateRow();
		Row GetRow(int index);
		void AddRow(Row row,int index);
		void PushRow(Row row);
		void DeleteRow(int index);
		void SetRow(Row row, int index);
		vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
		DBTable5* SelfRows(string colName,Condition cond, void* value);
	};

	//=============== class DBTableBin5 =============================
	class DBTableBin5: public DBTable5{
		char tabName[LENGTH];
		char primaryKey[LENGTH];//��� ������� �� ���������� ���������� �����
		int nColumn;
		ColumnDesc* header;				
		int nRows; 
		int RowLength();
		int DataBegin();
		int FieldPosition(string colName); //�������� ���� colName �� ������ ������ � ������
		int FieldLength(string colName); //����� ���� colName � ������
		void ResizeData(int deltaRows);
		char** data;		
		int maxRows; //����� ����� � data � ������ DELTA (��� ���������� �������
		//�� ����� ��������������� ������ nRows+DELTA).� ���� �� ������������
		char fileName[80];//� ���� �� ������������. ������������ � ������� ���
		//��������� � �����
	public:
		DBTableBin5(){}
		DBTableBin5(string tableName) { cout << "sd"; }
		DBTableBin5(string tableName,Header hdr,string primKey);		
		~DBTableBin5(){}
		string TypeName(DBType type);
		DBType GetType(string columnName);
		Header GetHeader();
		void DBTableClear();
		int FieldPosInFile(int rowIndex,string columnName);
		Row GetRow(int index);
		Row operator[](int index);
		string valueToString5(Row& row,string columnName);
		void* GetValue(string value, string columnName, dbmsLib5::Header hdr);
		int GetSize();
		void ReadDBTable5(string fileName);											
		void WriteDBTable5(string fileName);
		void SetTableName(string tName);
		void SetPrimaryKey(string key);
		string GetTableName();
		string GetPrimaryKey();
		void SetFileName(string path);
		string GetFileName();
		Row CreateRow();
		void AddRow(Row row,int index);
		void PrintTable5(int screenWidth);
		void DeleteRow(int index);
		void SetRow(Row row, int index);
		vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
		DBTable5* SelfRows(string colName,Condition cond, void* value);
	};

	//===============class DBTableSet5=============================
	class DBTableSet5{
	private:
		string dbName;
		map<string, DBTable5*> db;
	public: 
		DBTableSet5(){}
		DBTableSet5(string name);
		int ReadDB5(string dbName);
		void PrintDB5(int screenWidth);
		void WriteDB5();
		string GetDBName();
		DBTable5* operator[](string tableName);
		int GetSize();
		bool is_found(string tabName);
	};
}
#endif //����� _dbmsLib5_

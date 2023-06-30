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
//DBType-������������ ����� ����� ������ ��:
enum DBType{ NoType, Int32, Double, String, Date};
//Condition-������������ �������, �� ������� ����� ������������ ���� ������ ��:
enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
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
struct Strip{//������ ���������� �������
	int nField;//����� ����� 
	int* fieldWidth;//������ ����� � ������ (������)
};
 typedef map<string, void*> Row;
 typedef map<string, ColumnDesc> Header;
 //----------------class DBTable1--------------------------------------
 class DBDate7
 {	
	friend string DateToStr(DBDate7& date);
	friend ostream& operator<<(ostream& out,DBDate7& date);
	int day, month, year;
	bool IsLeapYear (int year); //��� ����������?
	int GetDaysInMonth(int month,int year);//���������� ���� � ������
	int DaysInCurYear();//���������� ���� �� ������ ���� �� ������� ����
  public:
	DBDate7(string date);//������ ������: dd.mm.yyyy
	DBDate7(int d,int m,int y);		DBDate7():day(0),month(0),year(0){};//???����������� �� ���������
	DBDate7(DBDate7& dat):day(dat.day),month(dat.month),year(dat.year){}		int GetDay();
	int GetMonth();
	int GetYear();
	bool operator==(DBDate7& date);
	bool operator<(DBDate7& date); 
	bool operator>(DBDate7& date);
	bool operator<= (DBDate7& date);
	bool operator>= (DBDate7& date);
	bool operator!= (DBDate7& date);
	DBDate7& operator+=(int days);//���������� � ������� ���� days ����
	DBDate7& operator-=(int days);//�������� �� ������� ���� days ����
	int operator-(DBDate7& date);//���������� ���� ����� ������� ����� � date
	 				//���� ������� ���� > date, ��������� < 0.
};
class DBTable7{
public:
	DBType GetType7(char* columnName);
	const char* TypeName1(DBType type);
	virtual ~DBTable7(){};//����������� ����������
	virtual Header GetHeader7()=0;
	//virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
	//�� �������� ����� ���������� 
	//���������� ����� (������) ������ (������) � data.
	// keyValue-�������� ����� (��������� �� string, int ��� DBDate)
	// keyColumnName-��� ��������� ������� (��������� ��� ��������� ����)
	//� ������� ����� ���� ��������� ������� � ���������� ��������� ���������� 	//�����.
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
	~DBTableTxt7(){};//!!!���������� ����������,����� ������,���������� void*,�� 					//�������
	//vector<int> IndexOfRecord(void* keyValue,string keyColumnName);
 	string valueToString7(Row& row,string columnName);
	void ReadDBTable7(string fileName);//tabName=path+tableName
	//void ReadTableBin(string fileName);//������ ������� �� ��������� �����
	void PrintTable7(int screenWidth);
	void WriteDBTable7(string fileName);//tabName=path+tableName	
	//void WriteTableBin(string fileName);//������ ������� � �������� ����
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
		//����� ���������� �������:
		//screenWidth - ������ ������ (������� ��������)
		//nStrips - ����� ����� � ���������� (�������� ��������)
		//strips[nStrips] - �������� ����� �������: 
		//����� �������� � ������ ������� ������� � ������ (�������� ��������)
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
 #endif //����� _dbmsLib1_

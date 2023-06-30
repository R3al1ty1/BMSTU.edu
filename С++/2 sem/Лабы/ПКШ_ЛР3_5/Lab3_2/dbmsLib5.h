#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>


	using namespace std;
	class DBDate5
	{	
	private:
		static const int arrDays[13];
		friend string DateToStr(const DBDate5& date);
		friend ostream& operator<<(ostream& out,DBDate5& date);
		int GetJDN(); // �������� �� ���� ����� ���������� ���
		DBDate5 GetDateFromJDN(int jdn); // �������� ���� �� ������ ���������� ���
		int day, month, year;
	public:
		DBDate5(string date);// ������ ������: dd.mm.yyyy
		DBDate5(int d,int m,int y); 
		DBDate5():day(1),month(1),year(1){};//����������� �� ���������
		DBDate5(const DBDate5& dat):day(dat.day),month(dat.month),year(dat.year){} // ����������� �����������
		int GetDay();
		int GetMonth();
		int GetYear();
		bool IsLeapYear (int year); //��� ����������?
		int GetDaysInMonth(int month,int year);//���������� ���� � ������
		int DaysInCurYear();//���������� ���� �� ������ ���� �� ������� ����
		bool operator==(const DBDate5& date);
		bool operator<(const DBDate5& date); 
		bool operator>(const DBDate5& date);
		bool operator<= (const DBDate5& date);
		bool operator>= (const DBDate5& date);
		bool operator!= (const DBDate5& date);
		DBDate5& operator+=(int days);//���������� � ������� ���� days ����
		DBDate5& operator-=(int days);//�������� �� ������� ���� days ����
		int operator-(DBDate5& date);	//���������� ���� ����� ������� ����� � date
		//���� ������� ���� > date, ��������� < 0.
	};

	const int LENGTH = 24;
	enum DBType {
		NoType,
		Int32,
		Double,
		String,
		Date
	};
	struct ColumnDesc { 
		char colName[LENGTH];
		DBType colType;
		int length; 

	}; 
	typedef map<string, void*> Row;
	typedef map<string, ColumnDesc> Header;

	string GetTabNameFromPath(string path);
	void* GetValue(string value, string columnName,Header hdr);
	DBType GetDBType(string type);
	string ignoreBlanc(const string str);
	string GetDBTypeName(DBType type);

	class DBTableTxt5{

		Header columnHeaders;
		string tableName;
		string primaryKey; 	
		vector<Row> data;
		string fileName;
	public:
		DBTableTxt5(){}
		DBTableTxt5(string tabName);
		DBTableTxt5(string tabName,Header hdr,string primKey);
		void ReadDBTable(string fileName);
		void PrintTable(int screenWidth);
		void WriteDBTable(string fileName);
		Row GetRow(int index);
		string valueToString(Row& row,string columnName);
	};




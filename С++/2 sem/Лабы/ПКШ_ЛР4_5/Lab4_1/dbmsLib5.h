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
		int GetJDN(); // Получает из даты номер юлианского дня
		DBDate5 GetDateFromJDN(int jdn); // Получает дату из номера юлианского дня
		int day, month, year;
	public:
		DBDate5(string date);// формат строки: dd.mm.yyyy
		DBDate5(int d,int m,int y); 
		DBDate5():day(1),month(1),year(1){};//конструктор по умолчанию
		DBDate5(const DBDate5& dat):day(dat.day),month(dat.month),year(dat.year){} // Конструктор копирования
		int GetDay();
		int GetMonth();
		int GetYear();
		bool IsLeapYear (int year); //год высокосный?
		int GetDaysInMonth(int month,int year);//Количество дней в месяце
		int DaysInCurYear();//Количество дней от начала года до текущей даты
		bool operator==(const DBDate5& date);
		bool operator<(const DBDate5& date); 
		bool operator>(const DBDate5& date);
		bool operator<= (const DBDate5& date);
		bool operator>= (const DBDate5& date);
		bool operator!= (const DBDate5& date);
		DBDate5& operator+=(int days);//Прибавляет к текущей дате days дней
		DBDate5& operator-=(int days);//Вычитает из текущей даты days дней
		int operator-(DBDate5& date);	//Количество дней между текущей датой и date
		//Если текущая дата > date, результат < 0.
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




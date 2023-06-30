#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "dbmsLib_v1_1.h"

using namespace std;

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
		void ReadDBTable(DBTableTxt5& tab, string fileName);
		Row GetRow(int index);
  };

string GetTabNameFromPath(string path);
void* GetValue(string value, string columnName,Header hdr);\
DBType GetDBType(string type);
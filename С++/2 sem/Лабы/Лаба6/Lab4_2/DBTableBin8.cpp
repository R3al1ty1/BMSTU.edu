#include <iostream>
#include <iomanip>
#include "Lab42_8.h"
#include <string.h>
#include <fstream>
using namespace dbmsLib8;

string DBTableBin8::valueToString8(Row& row,string columnName){
	return(columnName);
}
void DBTableBin8::ReadDBTable8(string fileName){
	cout << endl << "ReadDBTable8  вызвана для файла bin "<< this->tableName <<endl;
}

void DBTableBin8::WriteDBTable8(string fileName)
{
		cout << endl << "WriteDBTable8  вызвана для файла bin " << this->tableName << endl;
}

vector<int> dbmsLib8::DBTableBin8::IndexOfRecord(void* keyValue, string keyColumnName)
{
	return vector<int>();
}




void DBTableBin8::PrintTable8(int screenWidth)
{
		cout << endl << "PrintTable8  вызвана для файла bin " << this->tableName << endl;

}
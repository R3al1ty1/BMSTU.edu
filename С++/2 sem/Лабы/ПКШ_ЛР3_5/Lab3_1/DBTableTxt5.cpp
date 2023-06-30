#include "DBTableTxt5.h"
#include "dbmsLib5.h"

DBType GetDBType(string type){
	if (type == "Int32")  return  Int32; 
	if (type == "Double") return  Double; 
	if (type == "String") return  String; 
	if (type == "Date")   return  Date; 
	return NoType;
}

void* GetValue(string value, string columnName,Header hdr)
{
	switch (hdr[columnName].colType)
	{
	case Int32:		return new int(stoi(value)); break;
	case Double:	return new double(stod(value)); break;
	case String:	return new string(value); break;
	case Date:		return new dbmsLib5::DBDate5(value); break;
	default: cout<<"Недопустимый тип данных в столбце\n"<<
				 columnName<<endl;
	}
	return 0;
} 

string GetTabNameFromPath(string path){
	char tName[100];
	int pos1=path.find_last_of('\\');
	int pos2=path.find_last_of('.');
	strcpy_s(tName,100,path.c_str());
	tName[pos2]='\0';
	strcpy_s(tName,80,tName+pos1+1);
	return tName;
}



void DBTableTxt5::ReadDBTable(DBTableTxt5& tab, string fileName) {
	ifstream in;
	in.open(fileName);
	if (in.is_open())
	{
		vector<string> columns;
		string current;
		in >> current;
		string mytabName = current.substr(0, current.find_first_of("|"));
		string tabName = GetTabNameFromPath(fileName);
		cout <<"\nResult is " << (mytabName == tabName) << endl;
		in >> current;
		Header myHeader;
		int l = 0, 
			k = 0;
		while(current[l] != '\0')
		{
			if (current[l] == '|') k++;
			l++;
		}
		k += 1;
		k /= 3;
		for(int i = 0; i < k; i++)
		{
			ColumnDesc myColumnDesc;
			string temp = current.substr(0, current.find_first_of("|"));
			string name = temp;
			columns.push_back(name);
			for (auto j = 0; j < temp.size(); j++) myColumnDesc.colName[j] = temp[j];
			myColumnDesc.colName[temp.size()] = '\0';
			current = current.substr( current.find_first_of("|") + 1);

			temp = current.substr(0, current.find_first_of("|"));
			myColumnDesc.colType = GetDBType(temp);
			current = current.substr( current.find_first_of("|") + 1);

			if (current.find('|') != -1 ) temp = current.substr(0, current.find_first_of("|"));
			else temp = current;
			int m=0;
			for (auto j = 0; j < temp.size(); j++) m = m * 10 + int(temp[j]) - 48;  
			myColumnDesc.length = m;
			current = current.substr( current.find_first_of("|") + 1);
			myHeader[name] = myColumnDesc;
		}
		for (auto it = myHeader.begin(); it != myHeader.end(); it++) 
			cout << endl << it->first << " " << it->second.colName << "/" << it->second.colType << "/" << it->second.length << endl;


		tab.columnHeaders = myHeader;
		tab.tableName = mytabName;
		tab.fileName = fileName;
		Row currentRow;
		k=0;
		while (!in.eof())
		{
			in >> current;
			if (current.find('|') != -1 ) current = current.substr(0, current.find_first_of("|"));
			void* data_ = GetValue(current, columns[k], myHeader);
			currentRow[columns[k]] = data_;
			k++;
			if (k == columns.size()) 
			{
				k = 0;
				data.push_back(currentRow);
				currentRow.clear();
			}
		}
	}
	else
	{
		cout<<"Error 404"<<endl;
	}

	cout<< "ReadDBTable11 "<<fileName<<endl;//отладочная печать
}

Row DBTableTxt5::GetRow(int index) { return data[index]; }
void PrintRow(Row row) {
	
}
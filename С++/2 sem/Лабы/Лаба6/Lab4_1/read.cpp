#include <iostream>
#include <iomanip>
#include "dbmsLib_v2.h"
#include <string.h>
#include <fstream>

using namespace std;
using namespace dbmsLib;

char* typeNames[]={"NoType","Int32","Double","String","DBDate"};
char* TypeName7(DBType type)
{
	return typeNames[type];
}






dbmsLib::DBType GetType7(string typeName){
	string a[]={"NoType","Int32","Double","String","Date"};
	for(int i=0; i<5;i++){
		if (typeName == a[i]) 
			return (dbmsLib::DBType)i;
	}
}
void* GetValue7(string value, string columnName,Header hdr)
	//возвращает значение переменной value, преобразованное из типа   
	//string в тип typeName, имя которого указано в заголовке  
	//столбца таблицы в C-файле.
{
	switch (hdr[columnName].colType)
	{
	case Int32:		return new int(stoi(value)); break;
	case Double:	return new double(stod(value)); break;
	case String:	return new string(value); break;
	default: cout<<"Недопустимый тип данных в столбце\n"<<
				 columnName<<endl;
	}
	return 0;
} 
string FileType (string name)
{
	string FT;
	int len=1;
	while (name[len] != '.') len++;
	for (int i = len; i<name.length();i++)
		FT+=name[i]; 
	return(FT);
}

void dbmsLib::ReadDB7(DBTableSet& tab)
{
	string fn = "DBTables";
	string path="..\\LibraryTxt\\";
	fn = path+fn+".txt";
	ifstream in (fn);
	if (!in.is_open()){
		cout<<"ReadDB7: Ошибка открытия файла "<<fn<<endl;
		return;
	}
	char line[200];
		in.getline(line,200);
		char *token, *next_token=line;
		vector <string> strArray;
		int i=0;
		string fileName;
	while( (token = strtok_s( next_token, "|", &next_token)) != NULL ){
		strArray.push_back(token);
	}
	i=0;
	string fileType=FileType(strArray[i]);
 		for(unsigned int i=0; i<strArray.size(); i++){
			if(fileType==".txt"){
				//инициализация DBTable* адресом DBTableTxt
				string str;
				int j=0;
				while (strArray[i][j]!='.')
				{
					str+=strArray[i][j];
					j++;
				}
				strArray[i]=str;
				cout << strArray[i] << endl;
				tab.db[strArray[i]]=new DBTableTxt(strArray[i]);
			//else if(fileType==".bin")
				//инициализация DBTable* адресом DBTableBin
				//db[strArray[i]]=new DBTableBin(strArray[i]);
			}
			else{
				cout<<"ReadDB1:Ошибка имени БД"<<endl;
				break;
			}
			//полиморфный вызов виртуальной функции
			tab.db[strArray[i]]->ReadDBTable(path+strArray[i]+".txt");
			//tab.db[strArray[i]]->PrintTable(80);
	}
}
void dbmsLib::PrintDB7(DBTableSet& tab, int screenWidth)
{
	map <string , DBTable*>::iterator iter;
	for(iter=tab.db.begin();iter!=tab.db.end();iter++)
	{
		iter->second->PrintTable(screenWidth);
	}
}
void dbmsLib::WriteDB7(DBTableSet& tab)
{
	map <string , DBTable*>::iterator iter;
	string path="..\\LibraryTxt\\";
	for(iter=tab.db.begin();iter!=tab.db.end();iter++)
	{
		string tabname = (iter->first);
		cout << tabname << endl;
		string tabName1= tabname+"1.txt";
		iter->second->WriteDBTable(path+tabName1);
	}
}



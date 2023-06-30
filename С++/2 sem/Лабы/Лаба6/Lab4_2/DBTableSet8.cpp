#include <iostream>
#include <iomanip>
#include "Lab42_8.h"
#include <string.h>
#include <fstream>

using namespace std;
using namespace dbmsLib8;


char* typeNames[]={"NoType","Int32","Double","String","DBDate"};
const char* dbmsLib8::DBTable8::TypeName8(DBType type)
{
	return typeNames[type];
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

int DBTableSet8::ReadDB8(string lib)
{
	string fn = "DBTables";
	
	string path="..\\" + lib + "\\";
	fn = path+fn+".txt";
	cout << fn;
	ifstream in (fn);
	if (!in.is_open()){
		cout<<"ReadDB8: Ошибка открытия файла "<<fn<<endl;
	}
	char line[200];
		in.getline(line,200);
		char *token, *next_token=line;
		vector <string> strArray;
		int i=0;
		
		
	while((token = strtok_s( next_token, "|", &next_token)) != NULL ){
		strArray.push_back(token);
	}
	//i=0;
		string fileType=FileType(strArray[i]);
 		for(unsigned int i=0; i<strArray.size(); i++){
			if(fileType==".txt"){
				//инициализация DBTable* адресом DBTableTxt
				int j=0;
				strArray[i].erase(strArray[i].find_first_of("."));
				cout << strArray[i] << endl;
				db[strArray[i]]=new DBTableTxt8(strArray[i]);
			}
			else if (fileType == ".bin")
				//инициализация DBTable* адресом DBTableBin1
				db[strArray[i]] = new DBTableBin8(strArray[i]);						
			else {
				cout << "ReadDB1:Ошибка имени БД" << endl;
				return -1;
			}
			//полиморфный вызов виртуальной функции
			db[strArray[i]]->ReadDBTable8(path+strArray[i]+fileType);
			
			//tab.db[strArray[i]]->PrintTable(80);
	}
		return 0;
}


int dbmsLib8::DBTableSet8::PrintDB8(int screenWidth)
{
	map <string , DBTable8*>::iterator iter;
	for(iter=db.begin();iter!=db.end();iter++)
	{
		iter->second->PrintTable8(screenWidth);
	}
	return 0;
}
int dbmsLib8::DBTableSet8::WriteDB8()
{
	map <string , DBTable8*>::iterator iter;
	string path="..\\LibraryTxt\\";
	for(iter=db.begin();iter!=db.end();iter++)
	{
		string dbname = (iter->first);
		cout << dbname << endl;
		string tabName1=path + dbname+".txt";
		iter->second->WriteDBTable8(tabName1);
	}
	return 0;
}

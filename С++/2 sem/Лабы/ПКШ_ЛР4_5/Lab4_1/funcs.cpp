#include "dbmsLib_v2.h"

string FileType(string dbName) {
	return '.'+dbName.substr(dbName.size() - 3);
}

// Вектор имен таблиц
vector<string> strArray;

int dbmsLib::ReadDB5(dbmsLib::DBTableSet& db1) {
	db1.db.clear();
	ifstream in;
	string path="..\\"+db1.dbName+"\\";
	in.open(path+"DBTables.txt");
	if (in.is_open()) {
		
		// Заполнение вектора имен таблиц
		string str;
		getline(in,str);
		string res;
		while (str.find('|') != string::npos) {
			res = str.substr(0, str.find_first_of('|'));
			strArray.push_back(res);
			str = str.substr(str.find_first_of('|') + 1);
		}
		strArray.push_back(str);
		
		// Считывание таблиц в map с учетом полиморфизма
		string fileType=FileType(db1.dbName);
 		for(size_t i=0; i<strArray.size(); i++){
			if(fileType==".Txt") {
				db1.db[strArray[i]]=new DBTableTxt(strArray[i]);
			}
			else {
				if(fileType==".Bin") {
					db1.db[strArray[i]]=new DBTableBin (strArray[i]);
				}				
				else {
				cout<<"ReadDB5: Ошибка имени БД"<<endl;
				return -1;
				}
			}
			db1.db[strArray[i]]->ReadDBTable(path+strArray[i]+fileType);
		}
	} else {
		cout << "Ошибка открытия DBTables.txt" << endl;
	}

}

void dbmsLib::WriteDB5(dbmsLib::DBTableSet& db1) {
	string path="..\\"+db1.dbName+"\\";
	int i = 0;
	for(auto iter=db1.db.begin(); iter!=db1.db.end(); iter++) {
		iter->second->WriteDBTable(path+strArray[i]);
		++i;
	}
}

void dbmsLib::PrintDB5(dbmsLib::DBTableSet& db1, int numcol) {
	for(auto iter= db1.db.begin();iter != db1.db.end();iter++) {
		iter->second->PrintTable(numcol);
	}
}




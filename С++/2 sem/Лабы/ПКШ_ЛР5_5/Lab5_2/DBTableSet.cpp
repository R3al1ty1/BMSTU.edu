#include "dbmsLib5.h"

string FileType(string dbName) {
	return '.'+dbName.substr(dbName.size() - 3);
}

// Вектор имен таблиц
vector<string> strArray;

int dbmsLib5::DBTableSet5::ReadDB5(string dbName) {
	db.clear();
	ifstream in;
	ifstream in1;
	string path="..\\"+dbName+"\\";
	string fileType=FileType(dbName);
	in.open(path+"DBTables.txt");
	if (in.is_open()) {
		
		// Заполнение вектора имен таблиц
		strArray.clear();
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
 		for(size_t i=0; i<strArray.size(); i++){
			if(fileType==".Txt") {
				db[strArray[i]]=new DBTableTxt5(strArray[i]);
			}
			else {
				if(fileType==".Bin") {
					db[strArray[i]]=new DBTableBin5(strArray[i]);
				}				
				else {
				cout<<"ReadDB5: Ошибка имени БД"<<endl;
				return -1;
				}
			}
			db[strArray[i]]->ReadDBTable5(path+strArray[i]+fileType);
		}
	} else {
		cout << "Ошибка открытия DBTables.txt" << endl;
	}

}

void dbmsLib5::DBTableSet5::WriteDB5() {
	string path="..\\"+dbName+"\\";
	for(auto iter=db.begin(); iter!=db.end(); iter++) {
		string name = iter->second->GetTableName();
		iter->second->WriteDBTable5(path+name+FileType(dbName));
	}
}


void dbmsLib5::DBTableSet5::PrintDB5(int numcol) {
	for(auto iter = db.begin();iter != db.end();iter++) {
		iter->second->PrintTable5(numcol);
	}
}




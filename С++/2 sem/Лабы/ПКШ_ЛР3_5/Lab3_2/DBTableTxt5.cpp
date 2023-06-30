#include "dbmsLib5.h"


DBType GetDBType(string type){
	if (type == "Int32")  return  DBType::Int32; 
	if (type == "Double") return  DBType::Double; 
	if (type == "String") return  DBType::String; 
	if (type == "DBDate")   return  DBType::Date; 
	return DBType::NoType;
}

string GetDBTypeName(DBType type){
	if (type == Int32)  return  "Int32"; 
	if (type == Double) return  "Double"; 
	if (type == String) return  "String"; 
	if (type == Date)   return  "DBDate"; 
	return "NoType";
}

void* GetValue(string value, string columnName,Header hdr)
{
	switch (hdr[columnName].colType)
	{
	case Int32:		return new int(stoi(value)); break;
	case Double:	return new double(stod(value)); break;
	case String:	return new string(value); break;
	case Date:		return new DBDate5(value); break;
	default: cout<<"Недопустимый тип данных в столбце\n"<<
				 columnName<<endl;
	}
	return 0;
} 

string ignoreBlanc(const string str){		
	string bufStr=str;
	int begStr=bufStr.find_first_not_of(' ');
	return bufStr.substr(begStr);
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

string DBTableTxt5::valueToString(Row& row,string columnName)
{
	char buf[80]={0};
	if (this->columnHeaders.find(columnName)!= this->columnHeaders.end())  
	{ 		
		void* value=row[columnName];
		ostrstream os(buf,80);
		switch(columnHeaders[columnName].colType){
		case Int32: os<<setw(8)<<*(int*) value<<'\0'; break;
		case Double: os<<setw(12)<<*(double*) value<<'\0'; break;
		case String:os<<setw(columnHeaders[columnName].length)<<
						ignoreBlanc(*(string*)value)<<'\0'; break;
		case Date: os<<setw(12)<<*(DBDate5*) value<<'\0'; break;
		default: cout<<setw(8)<<"NoType"<<'\0'; 
			system("pause");break;
		}	
	}else
		cout << "column not found " << endl;
	return buf;
}


vector<string> columnsOrder;

void DBTableTxt5::ReadDBTable(string fileName) {
	columnsOrder.clear();
		ifstream in;
		in.open(fileName);
		if (in.is_open())
		{
			string s;
			int z = 0;
		while (in.peek() != EOF) {
			getline(in, s);
			z++;
		}
		in.close();
		in.open(fileName);

			
			string current;
			getline(in, current); 
			string mytabName = current.substr(0, current.find_first_of("|"));
			primaryKey = current.substr(current.find_first_of("|") + 1);
			string tabName = GetTabNameFromPath(fileName);
			getline(in, current); 
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
				columnsOrder.push_back(name);
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

			data.clear();
			columnHeaders = myHeader;
			tableName = mytabName;
			fileName = fileName;
			Row currentRow;
			for (int l = 0; l < z - 2; l++){
				getline(in, current); 
				current = ignoreBlanc(current);
				string temp;
				for (int i = 0; i < columnsOrder.size(); i++) {
					if (current.find('|') != -1 ) temp = current.substr(0, current.find_first_of("|"));
					else temp = ignoreBlanc(current);
					current = current.substr(current.find_first_of("|") + 1);
					temp = ignoreBlanc(temp);
					void* data_ = GetValue(temp, columnsOrder[i], myHeader);
					currentRow[columnsOrder[i]] = data_;
				}

				data.push_back(currentRow);
				currentRow.clear();
			}
		}
		else
		{
			cout<<"Error 404"<<endl;
		}	
}

void DBTableTxt5::PrintTable(int screenWidth){
	vector<int> columnsLength;
	int sum = 1;
	for (int j = 0; j < columnsOrder.size(); j++){
		int w1 = columnHeaders[columnsOrder[j]].length+2;
		int w2 = columnsOrder[j].size()+2;
		w1 = w1 > w2 ? w1 : w2;
		columnsLength.push_back(w1);
		sum += w1;
	}
	bool flag = true;
	int badColumnIndex = -1;
	for (int j = 0; j < columnsOrder.size(); j++){
		if (columnsLength[j] > screenWidth) {
			flag = false;
			badColumnIndex = j + 1;
		    break;
		}
	}
	if (flag) {
		sum = 0;
		int maxIndex = -1;
		for (size_t i = 0; i < columnsLength.size(); i++)
		{
			sum +=  columnsLength[i];
			if (sum > screenWidth) {
				break;
			}
			maxIndex = i+1;
			
		}
		int tempCols = columnsOrder.size();
		
		cout << "\nТаблица " << tableName << endl;
		cout <<setfill('=')<<setw(screenWidth-1)<<'='<<setfill(' ')<<endl;
		
		while (tempCols != 0) {
			if (tempCols != columnsOrder.size()) {
				cout << "\nПродолжение таблицы " << tableName << endl;
				cout <<setfill('=')<<setw(screenWidth-1)<<'='<<setfill(' ')<<endl;
			}
			int lastIndex = columnsOrder.size() - tempCols;
			for (int j = lastIndex; j < lastIndex + maxIndex; j++){
				cout << setw(columnsLength[j]) << right << columnHeaders[columnsOrder[j]].colName;
			}
			cout << endl;
			for (int j = lastIndex; j < lastIndex + maxIndex; j++){
				cout << setw(columnsLength[j]) << right << GetDBTypeName(columnHeaders[columnsOrder[j]].colType);
			}
			cout << endl;
			cout<<setfill('-')<<setw(screenWidth-1)<<'-'<<setfill(' ')<<endl;
			for (int j = 0; j < data.size(); j++){
				for (int i = lastIndex; i < lastIndex + maxIndex; i++){
					cout << setw(columnsLength[i]) << right << valueToString(data[j],columnsOrder[i]);
				}
				
				cout << endl;
			}
			tempCols -= maxIndex;
			if (tempCols < maxIndex) {
				maxIndex = tempCols;
			}
			
			cout<<setfill('=')<<setw(screenWidth-1)<<'='<<setfill(' ')<<endl;
			
		}
		cout << endl;
	} else {
		cout<<"Ширина столбца "<< badColumnIndex <<" больше ширины экрана\n";
			cout<<"Таблицу нельзя распечатать" << endl << endl;

	}
}

void DBTableTxt5::WriteDBTable(string fileName){
	ofstream out;
	out.open(fileName);
	if (out.is_open()){
		out << tableName << "|" << primaryKey << endl;
		auto iter=columnHeaders.begin();
		auto iterWhile=iter;
		
		while(++iterWhile!=columnHeaders.end())
		{
			out<< iter->second.colName<<"|"<< GetDBTypeName(iter->second.colType)<<			"|"<<iter->second.length<<"|";
			iter++;
		}
		out<<iter->first<<"|"<< GetDBTypeName(iter->second.colType)<<"|"<<iter->second.length <<endl;
		
		for (int j = 0; j < data.size(); j++){
			for (int i = 0; i < columnsOrder.size(); i++){
				out << valueToString(data[j],columnsOrder[i]);
				if (i != columnsOrder.size() - 1){
					out << 	'|';			
				}
			}
			out << endl;
		}

	}

	else{
		cout<<"Error 404"<<endl;
	}

}

Row DBTableTxt5::GetRow(int index) { return data[index]; }

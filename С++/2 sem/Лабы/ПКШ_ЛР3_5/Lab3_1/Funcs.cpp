#include "dbmsLib_v1_1.h"

dbmsLib::DBType GetDBType(string type){
	if (type == "Int32")  return  dbmsLib::Int32; 
	if (type == "Double") return  dbmsLib::Double; 
	if (type == "String") return  dbmsLib::String; 
	if (type == "DBDate")   return dbmsLib::Date; 
	return dbmsLib::NoType;
}

string GetDBTypeName(dbmsLib::DBType type){
	if (type == dbmsLib::Int32)  return  "Int32"; 
	if (type == dbmsLib::Double) return  "Double"; 
	if (type == dbmsLib::String) return  "String"; 
	if (type == dbmsLib::Date)   return  "DBDate"; 
	return "NoType";
}

vector<string> columnsOrder;


void dbmsLib::ReadDBTable5(dbmsLib::DBTableTxt& tab, string fileName) {
		//columnsOrder.clear();
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
			tab.primaryKey = current.substr(current.find_first_of("|") + 1);
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


			tab.columnHeaders = myHeader;
			tab.tableName = mytabName;
			tab.fileName = fileName;
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

				tab.data.push_back(currentRow);
				currentRow.clear();
			}
		}
		else
		{
			cout<<"Error 404"<<endl;
		}
}


void dbmsLib::PrintTable5(DBTableTxt& tab,int screenWidth){
	vector<int> columnsLength;
	int sum = 1;
	for (int j = 0; j < columnsOrder.size(); j++){
		int w1 = tab.columnHeaders[columnsOrder[j]].length+2;
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
		
		cout << "\nТаблица " << tab.tableName << endl;
		cout <<setfill('=')<<setw(screenWidth-1)<<'='<<setfill(' ')<<endl;
		
		while (tempCols != 0) {
			if (tempCols != columnsOrder.size()) {
				cout << "\nПродолжение таблицы " << tab.tableName << endl;
				cout <<setfill('=')<<setw(screenWidth-1)<<'='<<setfill(' ')<<endl;
			}
			int lastIndex = columnsOrder.size() - tempCols;
			for (int j = lastIndex; j < lastIndex + maxIndex; j++){
				cout << setw(columnsLength[j]) << right << tab.columnHeaders[columnsOrder[j]].colName;
			}
			cout << endl;
			for (int j = lastIndex; j < lastIndex + maxIndex; j++){
				cout << setw(columnsLength[j]) << right << GetDBTypeName(tab.columnHeaders[columnsOrder[j]].colType);
			}
			cout << endl;
			cout<<setfill('-')<<setw(screenWidth-1)<<'-'<<setfill(' ')<<endl;
			for (int j = 0; j < tab.data.size(); j++){
				for (int i = lastIndex; i < lastIndex + maxIndex; i++){
					cout << setw(columnsLength[i]) << right << tab.valueToString(tab.data[j],columnsOrder[i]);
				}
				
				cout << endl;
			}
			tempCols -= maxIndex;
			if (tempCols < maxIndex) {
				maxIndex = tempCols;
			}
			
			cout<<setfill('=')<<setw(screenWidth-1)<<'='<<setfill(' ')<<endl;
			
		}

		//if (colNum !=) 
	} else {
		cout<<"Ширина столбца "<< .<<" больше ширины экрана\n";
			cout<<"Таблицу нельзя распечатать"<<endl;

	}
}


void dbmsLib::WriteDBTable5(DBTableTxt& tab,string fileName){
	ofstream out;
	out.open(fileName);
	if (out.is_open()){
		out << tab.tableName << "|" << tab.primaryKey << endl;
		auto iter=tab.columnHeaders.begin();
		auto iterWhile=iter;
		
		while(++iterWhile!=tab.columnHeaders.end())
		{
			out<< iter->second.colName<<"|"<< GetDBTypeName(iter->second.colType)<<			"|"<<iter->second.length<<"|";
			iter++;
		}
		out<<iter->first<<"|"<< GetDBTypeName(iter->second.colType)<<"|"<<iter->second.length <<endl;
		
		for (int j = 0; j < tab.data.size(); j++){
			for (int i = 0; i < columnsOrder.size(); i++){
				out << tab.valueToString(tab.data[j],columnsOrder[i]);
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





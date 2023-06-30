#include "dbmsLib5.h"

dbmsLib5::DBType GetDBType(string type) {
  if (type == "Int32") return dbmsLib5::DBType::Int32;
  if (type == "Double") return dbmsLib5::DBType::Double;
  if (type == "String") return dbmsLib5::DBType::String;
  if (type == "DBDate") return dbmsLib5::DBType::Date;
  return dbmsLib5::DBType::NoType;
}

string GetDBTypeName(dbmsLib5::DBType type) {
  if (type == dbmsLib5::DBType::Int32) return "Int32";
  if (type == dbmsLib5::DBType::Double) return "Double";
  if (type == dbmsLib5::DBType::String) return "String";
  if (type == dbmsLib5::DBType::Date) return "DBDate";
  return "NoType";
}

void *GetValue(string value, string columnName, dbmsLib5::Header hdr) {
  switch (hdr[columnName].colType) {
    case dbmsLib5::DBType::Int32:
      return new int(stoi(value));
      break;
    case dbmsLib5::DBType::Double:
      return new double(stod(value));
      break;
    case dbmsLib5::DBType::String:
      return new string(value);
      break;
    case dbmsLib5::DBType::Date:
      return new dbmsLib5::DBDate5(value);
      break;
    default:
      cout << "Недопустимый тип данных в столбце\n" << columnName << endl;
  }
  return 0;
}

string ignoreBlanc(const string str) {
  string bufStr = str;
  int begStr = bufStr.find_first_not_of(' ');
  return bufStr.substr(begStr);
}

string GetTabNameFromPath(string path) {
  char tName[100];
  int pos1 = path.find_last_of('\\');
  int pos2 = path.find_last_of('.');
  strcpy_s(tName, 100, path.c_str());
  tName[pos2] = '\0';
  strcpy_s(tName, 80, tName + pos1 + 1);
  return tName;
}

string dbmsLib5::DBTableTxt5::valueToString5(Row &row, string columnName) {
  char buf[80] = {0};
  if (this->columnHeaders.find(columnName) != this->columnHeaders.end()) {
    void *value = row[columnName];
    ostrstream os(buf, 80);
    switch (columnHeaders[columnName].colType) {
      case DBType::Int32:
        os << setw(8) << *(int *)value << '\0';
        break;
      case DBType::Double:
        os << setw(12) << *(double *)value << '\0';
        break;
      case DBType::String:
        os << setw(columnHeaders[columnName].length) << ignoreBlanc(*(string *)value) << '\0';
        break;
      case DBType::Date:
        os << setw(12) << DateToStr(*(DBDate5 *)value) << '\0';
        break;
      default:
        cout << setw(8) << "NoType" << '\0';
        break;
    }
  } else
    cout << "column not found " << endl;
  return buf;
}

map<string, vector<string>> columnsOrder;

void dbmsLib5::DBTableTxt5::ReadDBTable5(string fileName) {
  ifstream in;
  in.open(fileName);
  if (in.is_open()) {
    string s;
    int z = 0;
    while (in.peek() != EOF) {
      getline(in, s);
      z++;
    }
    in.close();
    /*if (z < 2) {
            cout << "Ошибка чтения таблицы " << fileName << endl;
    }*/
    in.open(fileName);

    string current;
    getline(in, current);
    string mytabName = current.substr(0, current.find_first_of("|"));
    primaryKey = current.substr(current.find_first_of("|") + 1);
    string tabName = GetTabNameFromPath(fileName);
    getline(in, current);
    tableName = mytabName;
    columnsOrder[tableName].clear();
    this->fileName = fileName;
    Header myHeader;
    myHeader.clear();
    int l = 0, k = 0;
    while (current[l] != '\0') {
      if (current[l] == '|') k++;
      l++;
    }
    k += 1;
    k /= 3;
    for (int i = 0; i < k; i++) {
      ColumnDesc myColumnDesc;
      string temp = current.substr(0, current.find_first_of("|"));
      string name = temp;
      columnsOrder[tableName].push_back(name);
      for (auto j = 0; j < temp.size(); j++) myColumnDesc.colName[j] = temp[j];
      myColumnDesc.colName[temp.size()] = '\0';
      current = current.substr(current.find_first_of("|") + 1);

      temp = current.substr(0, current.find_first_of("|"));
      myColumnDesc.colType = GetDBType(temp);
      current = current.substr(current.find_first_of("|") + 1);

      if (current.find('|') != -1)
        temp = current.substr(0, current.find_first_of("|"));
      else
        temp = current;
      int m = 0;
      for (auto j = 0; j < temp.size(); j++) m = m * 10 + int(temp[j]) - 48;
      myColumnDesc.length = m;
      current = current.substr(current.find_first_of("|") + 1);
      myHeader[name] = myColumnDesc;
    }

    data.clear();
    columnHeaders = myHeader;

    Row currentRow;
    for (int l = 0; l < z - 2; l++) {
      getline(in, current);
      current = ignoreBlanc(current);
      string temp;
      for (int i = 0; i < columnsOrder[tableName].size(); i++) {
        if (current.find('|') != -1)
          temp = current.substr(0, current.find_first_of("|"));
        else
          temp = ignoreBlanc(current);
        current = current.substr(current.find_first_of("|") + 1);
        temp = ignoreBlanc(temp);
        void *data_ = GetValue(temp, columnsOrder[tableName][i], columnHeaders);
        currentRow[columnsOrder[tableName][i]] = data_;
      }

      data.push_back(currentRow);
      currentRow.clear();
    }
  } else {
    cout << "Error 404" << endl;
  }
}

void dbmsLib5::DBTableTxt5::PrintTable5(int screenWidth) {
  vector<int> columnsLength;
  int sum = 1;
  for (int j = 0; j < columnsOrder[tableName].size(); j++) {
    int w1 = columnHeaders[columnsOrder[tableName][j]].length + 2;
    int w2 = columnsOrder[tableName][j].size() + 2;
    w1 = w1 > w2 ? w1 : w2;
    columnsLength.push_back(w1);
    sum += w1;
  }
  bool flag = true;
  int badColumnIndex = -1;
  for (int j = 0; j < columnsOrder[tableName].size(); j++) {
    if (columnsLength[j] > screenWidth) {
      flag = false;
      badColumnIndex = j + 1;
      break;
    }
  }
  if (flag) {
    sum = 0;
    int maxIndex = -1;
    for (size_t i = 0; i < columnsLength.size(); i++) {
      sum += columnsLength[i];
      if (sum > screenWidth) {
        break;
      }
      maxIndex = i + 1;
    }
    int tempCols = columnsOrder[tableName].size();

    cout << "\nТаблица " << tableName << endl;
    cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;

    while (tempCols != 0) {
      if (tempCols != columnsOrder[tableName].size()) {
        cout << "\nПродолжение таблицы " << tableName << endl;
        cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
      }
      int lastIndex = columnsOrder[tableName].size() - tempCols;
      for (int j = lastIndex; j < lastIndex + maxIndex; j++) {
        cout << setw(columnsLength[j]) << right << columnHeaders[columnsOrder[tableName][j]].colName;
      }
      cout << endl;
      for (int j = lastIndex; j < lastIndex + maxIndex; j++) {
        cout << setw(columnsLength[j]) << right << GetDBTypeName(columnHeaders[columnsOrder[tableName][j]].colType);
      }
      cout << endl;
      cout << setfill('-') << setw(screenWidth - 1) << '-' << setfill(' ') << endl;
      for (size_t j = 0; j < data.size(); j++) {
        for (int i = lastIndex; i < lastIndex + maxIndex; i++) {
          cout << setw(columnsLength[i]) << right << valueToString5(data[j], columnsOrder[tableName][i]);
        }

        cout << endl;
      }
      tempCols -= maxIndex;
      if (tempCols < maxIndex) {
        maxIndex = tempCols;
      }

      cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
    }
    cout << endl;
  } else {
    cout << "Ширина столбца " << badColumnIndex << " больше ширины экрана\n";
    cout << "Таблицу нельзя распечатать" << endl << endl;
  }
}

void dbmsLib5::DBTableTxt5::WriteDBTable5(string fileName) {
  ofstream out;
  out.open(fileName);
  if (out.is_open()) {
    out << tableName << "|" << primaryKey << endl;
    auto iter = columnHeaders.begin();
    auto iterWhile = iter;

    while (++iterWhile != columnHeaders.end()) {
      out << iter->second.colName << "|" << GetDBTypeName(iter->second.colType) << "|" << iter->second.length << "|";
      iter++;
    }
    out << iter->first << "|" << GetDBTypeName(iter->second.colType) << "|" << iter->second.length << endl;

    for (int j = 0; j < data.size(); j++) {
      for (int i = 0; i < columnsOrder[tableName].size(); i++) {
        out << valueToString5(data[j], columnsOrder[tableName][i]);
        if (i != columnsOrder[tableName].size() - 1) {
          out << '|';
        }
      }
      out << endl;
    }

  }

  else {
    cout << "Error 404" << endl;
  }
}

dbmsLib5::Row dbmsLib5::DBTableTxt5::GetRow(int index) { return data[index]; }

void dbmsLib5::DBTableTxt5::WriteTableBin5(string fileName) {
	ofstream fout;
	fout.open((fileName).c_str(),ios::binary|ios::out);
	if (!fout.is_open()) 
	{ 
		cout<<"Ошибка открытия файла "<<fileName<< endl; 
		system("pause");
		return;
	}
	Header::iterator iter;
	Row ::iterator dataIter;
	//Запись в бинарный файл первой строки .txt-файла:
	//имени таблицы  и 
	//(длины имён таблиц и столбцов фиксированы и равны 24 байтам, включая \0) 
	char buf[80];
	strcpy_s(buf,80,tableName.c_str());
	int len=LENGTH;
	fout.write((char*)&len,4);
	fout.write(buf,len);
	 //Запись имени столбца primaryKey
	strcpy_s(buf,80,primaryKey.c_str());
	fout.write((char*)&len,4);
	fout.write(buf,len);
	//Запись в бинарный файл заголовка таблицы (вторая строка.txt-файла)
	int size = columnHeaders.size();
	fout.write((char*)&size,4);
	size=sizeof(ColumnDesc);
	for(iter=columnHeaders.begin();iter!=columnHeaders.end();iter++)
		fout.write((char*)&(iter->second),size);
	//Запись строк таблицы.
	int nRows=(int)data.size();
	fout.write((char*)&nRows,4);
	for (int i = 0; i < nRows; i++)	{
   		dataIter = data[i].begin();
for(iter=columnHeaders.begin();iter!=columnHeaders.end();dataIter++,iter++)
{//iter->second указывает на ColumnDesc, dataIter->second указывает на void*.
	switch((iter->second).colType) {
	case Int32: fout.write((char*)((dataIter->second)),sizeof(int));
			break;
	case Double: fout.write((char*)((dataIter->second)),sizeof(double));
				break;
	case Date:	

		fout.write((char*)(dataIter->second), sizeof(DBDate5));
		break;
	case String: strcpy_s(buf,80,(*(string*)(dataIter->second)).c_str());
			fout.write(buf,iter->second.length);
			//buf+1 - для того, чтобы length не обрубал конец строки '\0'
				break;
			default: cout<<"Недопустимый тип данных в БД\n";
				return;
			}
		}
	}
}		

void dbmsLib5::DBTableTxt5::ReadTableBin5(string fileName) {
	ifstream fin;
	fin.open((fileName).c_str(),ios::binary|ios::in);
	if (!fin.is_open()) 
	{ 
		cout<<"Ошибка открытия файла\n"<< endl; 
		system("pause");
		return;
	}
//Прочитать имя таблицы и имя столбца с primaryKey из первой строки файла
	int len;
	char buf[80];
	fin.read((char*)&len,4);
	fin.read((char*)buf,len);
	if(len>79){
		cout<<"Ошибка: длина имени таблицы "<< tableName <<endl;
		return;
	}
	buf[len]='\0';
	tableName=buf;
//Прочитать имя столбца с primaryKey
	fin.read((char*)&len,4);
	fin.read((char*)buf,len);
	if(len>79){
		cout<<"Ошибка: длина имени primaryKey"<< tableName <<endl;
		return;
	}
//Прочитать из файла заголовок таблицы и записать его в table.columnHeaders
	int size=0;	//число столбцов в заголовке таблицы
	fin.read((char*)&size,sizeof(int));
	len=sizeof(ColumnDesc);
	ColumnDesc colDesc;
	columnHeaders.clear();
	for(int i=0; i<size; i++){
		fin.read((char*)&colDesc,len);
		columnHeaders[colDesc.colName]=colDesc;
	}
//Чтение строк таблицы
	Header::iterator hdrIter; 
	Row ::iterator dataIter;
	data.clear();
	int nRows;
	fin.read((char*)&nRows,4);
	len=sizeof(colDesc.colName);//длина имени столбца (=24 байта) 
	for (int i = 0; i < nRows; i++)
	{
		Row row;//буфер для формирования строки таблицы
		dataIter=row.begin();
		pair<string,void*> pr;
		for(hdrIter=columnHeaders.begin();hdrIter!=columnHeaders.end();hdrIter++){
			pr.first=hdrIter->first;
			switch((hdrIter->second).colType) {//чтение данных
			case Int32:	pr.second=new int;
				fin.read((char*)pr.second,sizeof(int));
				row.insert(pr);	
				break;
			case Double: 
					pr.second=new double;
				fin.read((char*)pr.second,sizeof(double));
				row.insert(pr);	
				break;
			case Date:
				pr.second=new DBDate5;
				fin.read((char*)pr.second,sizeof(DBDate5));
				row.insert(pr);	
				break;
			case String:if(hdrIter->second.length>79){
				cout<<"Ошибка: длина поля "<<hdrIter->second.colName<<
					" таблицы "<<tableName<<endl;
				return;
				}
				fin.read(buf,hdrIter->second.length);
				buf[hdrIter->second.length]='\0';
				pr.second=new string(ignoreBlanc(buf));
				row.insert(pr);	
				//cout<<*(string*)row[pr.first]<<endl;
				break;
			default: cout<<"Недопустимый тип данных в БД\n";
				return;
			}
		}
		data.push_back(row);
	}  	
	fin.close();
}



#include <iostream>
#include <iomanip>
#include "Lab42_8.h"
#include <string.h>
#include <fstream>
using namespace dbmsLib8;


/*void dbmsLib8::DBTableTxt8::task1()
{
    int s = 0;
    
    
    for (int i = 0; i < data.size(); i++) {
        s+= *(int*)data[i]["Sum"];
    }
    
    cout << "Доход за выбранный период " << s;
}*/

void* GetValue8(string value, string columnName, Header hdr)
//возвращает значение переменной value, преобразованное из типа   
//string в тип typeName, имя которого указано в заголовке  
//столбца таблицы в C-файле.
{
    switch (hdr[columnName].colType)
    {
    case Int32:    return new int(stoi(value)); break;
    case Double:  return new double(stod(value)); break;
    case String:  return new string(value); break;
    case DBDate:    return new dbmsLib8::DBDate8(value); break;
    default: cout << "Недопустимый тип данных в столбце\n" << columnName << endl;
    }
    return 0;
}

string dbmsLib8::DBTableTxt8::GetTableName() {
    return this->tableName;
}

void dbmsLib8::DBTableTxt8::AddRow(Row row, int index)
{
    if (row == Row())
        return;
    if (index == data.size())
        data.push_back(row);
    else
        data[index] = row;
}

Row dbmsLib8::DBTableTxt8::operator[](int ind)
{
    return this->data[ind];
}

Row dbmsLib8::DBTableTxt8::CreateRow()
{
    Row row;
    Header::iterator iter;
    void* id;

    cout << "Введите строку таблицы: " << GetTableName() << endl;
    string str;
    for (iter = columnHeaders.begin(); iter != columnHeaders.end(); ++iter) {
        cout << iter->first << endl;
        cin >> str;

        row[iter->first] = GetValue8(str, iter->first, columnHeaders);

       if (iter->first == primaryKey && IndexOfRecord(row[iter->first], iter->first).size() != 0) {
         cout << "Данное ключевое значение уже присутствует, невозможно ввести его повторно\n";
         return Row();
        }

    }

    return row;
}

bool dbmsLib8::comparator(/*TableDataType*/DBType type, void* obj1, Condition condition, void* obj2) {
    string s1, s2, buf, buf2;
    int begStr, begStr2;
    switch (type) {
        case Int32: switch (condition) {
            case Equal:  return *(int*)obj1 == *(int*)obj2;
            case NotEqual: return *(int*)obj1 != *(int*)obj2;
            case Less: return *(int*)obj1 < *(int*)obj2;
            case Greater:  return *(int*)obj1 > *(int*)obj2;
            case LessOrEqual: return *(int*)obj1 <= *(int*)obj2;
            case GreaterOrEqual: return *(int*)obj1 >= *(int*)obj2;
            default: cout << "Недопустимая операция сравнения\n" << endl;
                return false;
        }
        case Double: switch (condition) {
            case Equal:  return *(double*)obj1 == *(double*)obj2;
            case NotEqual: return *(double*)obj1 != *(double*)obj2;
            case Less: return *(double*)obj1 < *(double*)obj2;
            case Greater:  return *(double*)obj1 > *(double*)obj2;
            case LessOrEqual: return *(double*)obj1 <= *(double*)obj2;
            case GreaterOrEqual: return *(double*)obj1 >= *(double*)obj2;
            default: cout << "Недопустимая операция сравнения\n" << endl;
                return false;
        }
        case String:

            buf = *(string*)obj1;
            begStr = buf.find_first_not_of(' ');
            s1 =  buf.substr(begStr);
            buf2 = *(string*)obj2;
            begStr2 = buf2.find_first_not_of(' ');
            s2 = buf2.substr(begStr2);


            switch (condition) {
            case Equal:  return s1 == s2;
            case NotEqual: return s1 != s2;
            case Less: return s1 < s2;
            case Greater:  return s1 > s2;
            case LessOrEqual: return s1 <= s2;
            case GreaterOrEqual: return s1 >= s2;
            default: cout << "Недопустимая операция сравнения\n" << endl;
                return false;
        }
        case DBDate: switch (condition) {
            case Equal:  return *(DBDate8*)obj1 == *(DBDate8*)obj2;
            case NotEqual: return *(DBDate8*)obj1 != *(DBDate8*)obj2;
            case Less: return *(DBDate8*)obj1 < *(DBDate8*)obj2;
            case Greater:  return *(DBDate8*)obj1 > *(DBDate8*)obj2;
            case LessOrEqual: return *(DBDate8*)obj1 <= *(DBDate8*)obj2;
            case GreaterOrEqual: return *(DBDate8*)obj1 >= *(DBDate8*)obj2;
            default: cout << "Недопустимая операция сравнения\n" << endl;
                return false;
        }
    }
}

vector<int> dbmsLib8::DBTableTxt8::IndexOfRecord(void* keyValue, string keyColumnName)
{
    vector<int> Indexes;
        for (int i = 0; i < data.size(); i++) {
            // std::cout << "rowIdx: " << rowIdx << endl;
            Row row = data[i];
            // if (row[keyColumnName] == keyValue) {
            if (comparator(
                columnHeaders[keyColumnName].colType,
                row[keyColumnName],
                Equal,
                keyValue
            )) {
                Indexes.push_back(i);
            }
        }

    return Indexes;
}

dbmsLib8::DBTable8* dbmsLib8::DBTableTxt8::SelfRows8(string colName, dbmsLib8::Condition cond, void* value)
{
    string tabName = "SR" + GetTableName();//новое имя таблицы по умолчанию
    DBTableTxt8* tab = new DBTableTxt8(tabName);
    tab->columnHeaders = columnHeaders;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        if (comparator(columnHeaders[colName].colType,
            data[i][colName], cond, value))
            tab->data.push_back(data[i]);
    }
    return tab;
}

dbmsLib8::DBType DBTable8::GetType8(string typeName) {
    string a[] = { "NoType","Int32","Double","String","DBDate" };
    for (int i = 0; i < 5; i++) {
        if (typeName == a[i])
            return (dbmsLib8::DBType)i;
    }
}

string dbmsLib8::DBTableTxt8::ignoreBlanc(const string str) {
    string bufStr = str;
    int begStr = bufStr.find_first_not_of(' ');
    return bufStr.substr(begStr);
}

void DBTableTxt8::CreateTableMaket(Strip*& strips, int& nStrips, int screenWidth)
{
    Header::iterator headerIter, contHeaderIter;
    int nColumn = (int)columnHeaders.size();
    //Заполнение массива ширины полей для печати таблицы 
    int* fieldW = new int[nColumn];
    headerIter = columnHeaders.begin();
    for (int k = 0; k < nColumn; k++) {
        //что шире: заголовок или данные?
        fieldW[k] = headerIter->second.length > headerIter->first.size() ?
            headerIter->second.length + 2 : headerIter->first.size() + 2;
        headerIter++;
    }
    int currCol = 0;//порядковый номер столбца в таблице
    nStrips = 1;//число полос в распечатке таблицы
    int sumWidth = 0;//суммарная ширина столбцов в полосе
    int n = 0;//число столбцов в полосе
    int buff[40] = { 0 };//объявление и обнуление буфера для временного 
    //хранения числа столбцов в полосе (n<40)
    for (currCol = 0; currCol < nColumn; currCol++) {
        if (fieldW[currCol] >= screenWidth - 1) {
            cout << "Ширина столбца " << currCol << " больше ширины экрана\n";
            cout << "Таблицу нельзя распечатать" << endl;
            nStrips = 0;
            return;
        }
        sumWidth += fieldW[currCol];
        if ((sumWidth < screenWidth - 1) && (currCol < nColumn - 1)) {
            n++;
            continue;
        }
        if ((sumWidth >= screenWidth - 1)) {//выход за границу экрана 
            currCol--;
            buff[nStrips - 1] = n;
            nStrips++;
            n = 0;
            sumWidth = 0;
            continue;
        }
        if (currCol == nColumn - 1) {//последняя полоса
            n++;
            buff[nStrips - 1] = n;
        }
    }
    strips = new Strip[nStrips];
    int col = 0;
    for (int i = 0; i < nStrips; i++) {
        strips[i].nField = buff[i];
        strips[i].fieldWidth = new int[strips[i].nField];
        for (int j = 0; j < strips[i].nField; j++)
            strips[i].fieldWidth[j] = fieldW[col++];
    }
    //cout << "Количество полос:" << nStrips << endl;
}

Row DBTableTxt8::GetRow(int index) {
    return data[index];
}

string DBTableTxt8::valueToString8(Row& row, string columnName)
//возвращает значение переменной value, преобразованное из типа   
//typeName, имя которого указано в заголовке columnName столбца  
//таблицы, в тип string.
//!!! Вставить проверку наличия columnName в  DBTableTxt
{
    char buf[80] = { 0 };
    if (this->columnHeaders.find(columnName) != this->columnHeaders.end())
    {
        void* value = row[columnName];//потенциально опасная операция
        ostrstream os(buf, 80);
        switch (columnHeaders[columnName].colType) {
        case Int32: os << setw(8) << *(int*)value << '\0'; break;
        case Double: os << setw(12) << *(double*)value << '\0'; break;
        case String:os << setw(columnHeaders[columnName].length) <<
            ignoreBlanc(*(string*)value) << '\0'; break;
        case DBDate: os << setw(12) << *(DBDate8*)value << '\0'; break;
        default: cout << setw(8) << "NoType" << '\0';
            system("pause"); break;
        }
    }
    else
        cout << "column not found " << endl;
    return buf;
}

void dbmsLib8::DBTableTxt8::ReadDBTable8(string fileName)
{
    cout << "ReadDBTable8 " << fileName << endl;
    ifstream in(fileName);
    if (!in.is_open()) {
        cout << "ReadDBTable8: Ошибка открытия файла " << fileName << endl;
        return;
    }
    char line[200];
    in.getline(line, 200);
    char* token, * next_token = line;
    tableName = strtok_s(next_token, "|", &next_token);
    primaryKey = next_token;
    cout << "tableName: " << tableName << " primaryKey: " << primaryKey << endl;
    in.getline(line, 200);
    next_token = line;
    ColumnDesc colHdr;
    pair<string, ColumnDesc> parHdr;
    columnHeaders.clear();
    while ((token = strtok_s(next_token, "|", &next_token)) != NULL) {
        strcpy_s(colHdr.colName, token);
        token = strtok_s(next_token, "|", &next_token);
        colHdr.colType = GetType8(token);
        token = strtok_s(next_token, "|", &next_token);
        colHdr.length = stoi(token);
        parHdr.first = colHdr.colName;
        parHdr.second = colHdr;
        columnHeaders.insert(parHdr);
    }
    data.clear();
    Header::iterator hdrIter;
    pair<string, void*> parRow;
    while (in.getline(line, 200)) {
        Row row = *(new Row());
        next_token = line;
        for (hdrIter = columnHeaders.begin(); hdrIter != columnHeaders.end(); hdrIter++)
        {
            token = strtok_s(next_token, "|", &next_token);
            parRow.first = hdrIter->first;
            parRow.second = GetValue8(token, hdrIter->first, columnHeaders);
            row.insert(parRow);
        }
        data.push_back(row);
    }

}

void DBTableTxt8::PrintTable8(int screenWidth)
{
    cout << "Таблица " << tableName << endl;


    Strip* strips;
    int nStrip;
    Header::iterator headerIter, contHeaderIter;
    Row::iterator rowIter, contRowIter;
    CreateTableMaket(strips, nStrip, screenWidth);
    contHeaderIter = columnHeaders.begin();
    if (data.begin() != data.end()) {


        contRowIter = data[0].begin();

        for (int r = 0; r < nStrip; r++)
        {
            if (r > 0)
                cout << "Продолжение таблицы" << endl;
            cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;
            headerIter = contHeaderIter;
            for (int j = 0; j < strips[r].nField; j++)
            {
                cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << headerIter->first;
                headerIter++;
            }
            cout << endl;
            headerIter = contHeaderIter;
            for (int j = 0; j < strips[r].nField; j++)
            {
                cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << TypeName8(headerIter->second.colType);
                headerIter++;
            }
            cout << endl;
            cout << setfill('-') << setw(screenWidth - 1) << '-' << setfill(' ') << endl;
            for (int i = 0; i < data.size(); i++)
            {
                rowIter = contRowIter;
                for (int j = 0; j < strips[r].nField; j++)
                {
                    cout << setw(strips[r].fieldWidth[j]) << valueToString8(data[i], rowIter->first);
                    rowIter++;
                }
                cout << endl;
            }
            cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl << endl;
            contHeaderIter = headerIter;
            contRowIter = rowIter;
        }
    }
    else
    {
        headerIter = contHeaderIter;
        for (int r = 0; r < nStrip; r++)
        {
            if (r > 0)
                cout << "Продолжение таблицы" << endl;
            cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl;

            for (int j = 0; j < strips[r].nField; j++)
            {
                cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << headerIter->first;
                headerIter++;
            }
            cout << endl;
            headerIter = contHeaderIter;
            for (int j = 0; j < strips[r].nField; j++)
            {
                cout << setfill(' ') << setw(strips[r].fieldWidth[j]) << TypeName8(headerIter->second.colType);
                headerIter++;
            }
            cout << endl;
            cout << setfill('=') << setw(screenWidth - 1) << '=' << setfill(' ') << endl << endl;
        }
    }
    delete strips;


}

void DBTableTxt8::WriteDBTable8(string fileName)
{
    cout << "ReadDBTable1" << fileName << endl;
    //ofstream out (fileName, ios::app);
    ofstream out;
    out.open(fileName, ofstream::out | ofstream::trunc);
    if (!out.is_open()) {
        cout << "WriteDBTable8: Ошибка открытия файла " << fileName << endl;
        return;
    }
        out << tableName << "|" << primaryKey << endl;
    Header::iterator headerIter;
    Row::iterator rowIter;
    for (headerIter = columnHeaders.begin(); headerIter != columnHeaders.end(); headerIter++)
    {
        if (headerIter == columnHeaders.begin())
        {
            out << headerIter->first << "|" << TypeName8(headerIter->second.colType) << "|" << headerIter->second.length;
        }
        else
        {
            out << "|" << headerIter->first << "|" << TypeName8(headerIter->second.colType) << "|" << headerIter->second.length;
        }
    }
    out << endl;
    for (int i = 0; i < data.size(); i++)
    {
        for (rowIter = data[i].begin(); rowIter != data[i].end(); rowIter++)
        {
            if (rowIter == data[i].begin())
                out << valueToString8(data[i], rowIter->first);
            else
                out << "|" << valueToString8(data[i], rowIter->first);
        }
        out << endl;
    }
}

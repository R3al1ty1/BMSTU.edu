#include "dbmsLib5.h"
#include <iostream>
#include <cmath>

using namespace std;

int menu (){
	cout<<"============ ГЛАВНОЕ МЕНЮ ============\n";
	cout<<"\t1 - Распечатка всех таблиц БД\n";
	cout<<"\t2 - Подсчет дохода компании от продажи обуви за указанный период времени\n"; 
	cout<<"\t3 - Подсчет расходов указанного покупателя за указанный период времени\n"; 
	cout<<"\t4 - Определение покупателя, который потратил больше всех денег за указанный период времени\n"; 
	cout<<"\t5 - Дополнительное меню\n"; 
	cout<<"\t6 - Выход\n"; 
	int choice;
	cout<<"Выберите действие\n";
	cin>>choice;
	while(cin.fail()){
	cout<<"Ошибка ввода. Повторите ввод\n";	
	cin.clear();
	cin.ignore(10,'\n');
	cin>>choice;
	}
	return choice;
}

int adv_menu (){
	cout<<"============ ДОПОЛНИТЕЛЬНОЕ МЕНЮ ============\n";
	cout<<"\t1 - Распечатка таблицы БД по имени\n";
	cout<<"\t2 - Добавление строки данных в таблицу по имени таблицы\n";
	cout<<"\t3 - Удаление строки таблицы БД по ее номеру\n";
	cout<<"\t4 - Изменение элемента строки данных по имени столбца, номеру строки и имени БД\n";
	cout<<"\t5 - Считывание всех таблиц БД из файлов\n";
	cout<<"\t6 - Запись всех таблиц БД в файл\n";
	cout<<"\t7 - Считывание таблицы БД из файла по ее имени\n";
	cout<<"\t8 - Запись таблицы в файл по ее имени\n";
	cout<<"\t9 - Главное меню\n"; 
	int choice;
	cout<<"Выберите действие\n";
	cin>>choice;
	while(cin.fail()){
	cout<<"Ошибка ввода. Повторите ввод\n";	
	cin.clear();
	cin.ignore(10,'\n');
	cin>>choice;
	}
	return choice;
}

void PrintAllDB(dbmsLib5::DBTableSet5& db, int scrW) {
	db.PrintDB5(scrW);
}

void PrintSpecDB(dbmsLib5::DBTableSet5& db, int scrW) {
	string tabName;
	do {
		cout << endl << "Введите имя таблицы: ";
		cin >> tabName;
		if (!db.is_found(tabName)) cout << "Таблица не найдена. Повторите ввод." << endl;
	} while (!db.is_found(tabName));
	db[tabName]->PrintTable5(scrW);
}

void AddRecord(dbmsLib5::DBTableSet5& db, string path) {
	string tabName;
	do {
		cout << endl << "Введите имя таблицы: ";
		cin >> tabName;
		if (!db.is_found(tabName)) cout << "Таблица не найдена. Повторите ввод." << endl;
	} while (!db.is_found(tabName));
	int in = db[tabName]->GetSize() + 2;

	cout << endl << "Введите порядковый номер для новой строки (по умолчанию последняя в таблице (нажмите ENTER)): ";

	string tempStr;
	cin.get();
	getline(cin, tempStr);
	cout << endl;
	if (tempStr != "" ) {
		int tempInt = stoi(tempStr);
		if (tempInt > -1 && tempInt < INT_MAX) {
			in = tempInt;
		} else {
			cout << "Ошибка ввода. Запись в конец таблицы." << endl;
		}
	}

	dbmsLib5::Row res = db[tabName]->CreateRow();
	db[tabName]->AddRow(res, in);
	db[tabName]->WriteDBTable5(path+tabName+".txt");
	db.ReadDB5(db.GetDBName());
}

void DeleteRow(dbmsLib5::DBTableSet5& db, string path) {
	string tabName;
	do {
		cout << endl << "Введите имя таблицы: ";
		cin >> tabName;
		if (!db.is_found(tabName)) cout << "Таблица не найдена. Повторите ввод." << endl;
	} while (!db.is_found(tabName));
	int choice;
	cout << endl << "Введите порядковый номер строки для удаления: ";
	cin >> choice;
	while(cin.fail() || choice < 1 || (choice > db[tabName]->GetSize())) {
		cout << endl << "Ошибка ввода. Повторите ввод: ";	
		cin.clear();
		cin.ignore(10,'\n');
		cin>>choice;
	}
	cout << endl;
	db[tabName]->DeleteRow(choice);
	db[tabName]->WriteDBTable5(path+tabName+".txt");
	db.ReadDB5(db.GetDBName());
}

void ChangeRow(dbmsLib5::DBTableSet5& db, string path) {
	string tabName;
	do {
		cout << endl << "Введите имя таблицы: ";
		cin >> tabName;
		if (!db.is_found(tabName)) cout << "Таблица не найдена. Повторите ввод." << endl;
	} while (!db.is_found(tabName));
	int choice;
	cout << endl << "Введите порядковый номер строки для изменения: ";
	cin >> choice;
	while(cin.fail() || choice < 1 || (choice > db[tabName]->GetSize())) {
		cout << endl << "Ошибка ввода. Повторите ввод: ";	
		cin.clear();
		cin.ignore(10,'\n');
		cin>>choice;
	}

	dbmsLib5::Row row = db[tabName]->GetRow(choice-1);
	cout << endl << "Доступные имена столбцов таблицы :" << endl;
	for (auto it = row.begin(); it != row.end(); ++it) {
		cout << it->first << "\t";
	}
	cout << endl;


	string columnName;
	do {
		cout << endl << "Введите имя столбца: ";
		cin >> columnName;
		if (row.find(columnName) == row.end()) cout << "Cтолбец не найден. Повторите ввод." << endl;
	} while (row.find(columnName) == row.end());
	cout << endl;

	dbmsLib5::Header hdr = db[tabName]->GetHeader();
	auto it = row.find(columnName);
	auto hit = hdr.find(columnName);
	string temp = "0";
	cout << "Столбец: " <<  it->first
		<< "\tТип: " << db[tabName]->TypeName(hit->second.colType) 
		<< "\tМаксимальная длина: " << hit->second.length << endl;
	cout << "Введите данные: " << endl;
	if(char(cin.peek()) == '\n') cin.ignore();
	getline(std::cin, temp);
	bool exp = (static_cast<int>(temp.size()) > hit->second.length);
	while (exp) {
			cout << endl << "Неверный ввод (Максимальная длина - " << hit->second.length << "). Повторите попытку." << endl;
			cout << "Введите данные: " << endl;
			if(char(cin.peek()) == '\n') cin.ignore();
			getline(std::cin, temp);
			exp = (static_cast<int>(temp.size()) > hit->second.length);
		}
	void *data_ = db[tabName]->GetValue(temp, columnName, hdr);
	row[columnName] = data_;
	db[tabName]->SetRow(row, choice-1);
	db[tabName]->WriteDBTable5(path+tabName+".txt");
	db.ReadDB5(db.GetDBName());
}

void ReadAllDB(dbmsLib5::DBTableSet5& db) {
	string name = db.GetDBName();
	db.ReadDB5(name);
}

void WriteAllDB(dbmsLib5::DBTableSet5& db) {
	db.WriteDB5();
}

void ReadSpecDB(dbmsLib5::DBTableSet5& db, string path) {
	string tabName;
	do {
		cout << endl << "Введите имя таблицы: ";
		cin >> tabName;
		if (!db.is_found(tabName)) cout << "Таблица не найдена. Повторите ввод." << endl;
	} while (!db.is_found(tabName));
	db[tabName]->ReadDBTable5(path+tabName+".txt");
}

void WriteSpecDB(dbmsLib5::DBTableSet5& db, string path){
	string tabName;
	do {
		cout << endl << "Введите имя таблицы: ";
		cin >> tabName;
		if (!db.is_found(tabName)) cout << "Таблица не найдена. Повторите ввод." << endl;
	} while (!db.is_found(tabName));
	db[tabName]->WriteDBTable5(path+tabName+".txt");
}

//void testing(dbmsLib5::DBTableSet5& db, string path) {
//	/*void* val = new string("OREMBA");
//	vector<int> o = db["Customers"]->IndexOfRecord(val, "CustomerID");
//	for (size_t i = 0; i < o.size(); ++i) {
//		cout << o[i] << endl;
//	}*/
//
//	void* val = new string("OREMBA");
//	db["Customers"]->SelfRows("CustomerID", dbmsLib5::Equal, val)->PrintTable5(80);
//}

void CountIncome(dbmsLib5::DBTableSet5& db) {
	cout << endl << "Требуется ввести промежуток расчета (Даты вводятся в формате ДД.ММ.ГГГГ)." << endl;
	cout << "Введите дату (начало отсчёта): ";
	string strdate1;
	cin >> strdate1;
	cout << "Введите дату (конец отсчёта): ";
	string strdate2;
	cin >> strdate2;
	
	void* date1 = new dbmsLib5::DBDate5(strdate1);
	void* date2 = new dbmsLib5::DBDate5(strdate2);
	double income = 0;
	for(int i = 0; i < db["OrderDetails"]->GetSize(); ++i) {
		dbmsLib5::Row currentRow = db["OrderDetails"]->GetRow(i);
		vector<int> date_ind = db["Orders"]->IndexOfRecord(currentRow["OrderID"], "OrderID");
		void* currentOrderDate = db["Orders"]->GetRow(date_ind[0])["OrderDate"];
		double total_amount = *(double*)currentRow["TotalAmount"];
		int quantity = *(int*)currentRow["Quantity"];
		if(dbmsLib5::comparator(dbmsLib5::Date, date1, dbmsLib5::LessOrEqual, currentOrderDate) && dbmsLib5::comparator(dbmsLib5::Date, currentOrderDate, dbmsLib5::LessOrEqual, date2)) {
			vector<int> cost_ind = db["Products"]->IndexOfRecord(currentRow["ProductID"], "ProductID");
			double unit_buy = *(double*)db["Products"]->GetRow(cost_ind[0])["UnitBuy"];
			income += total_amount - quantity*unit_buy;
		}
	}
	cout << endl << "Доходы компании за промежуток " << strdate1 <<" - "<<  strdate2 << " составляют: " << fabs(income) << endl;
}

void CountExpences(dbmsLib5::DBTableSet5& db) {
	cout << endl << "Требуется ввести имя покупателя." << endl;
	cout << "Введите имя: ";
	string name;
	if(char(cin.peek()) == '\n') cin.ignore();
	getline(cin, name);
	void* name_ptr = new string(name);
	vector<int> cust_ind = db["Customers"]->IndexOfRecord(name_ptr, "ContactName");
	if(cust_ind.size() == 0) {
		cout << "Не найдено клиента с таким именем." << endl;
		return;
	}
	cout << endl << "Требуется ввести промежуток расчета (Даты вводятся в формате ДД.ММ.ГГГГ)." << endl;
	cout << "Введите дату (начало отсчёта): ";
	string strdate1;
	cin >> strdate1;
	cout << "Введите дату (конец отсчёта): ";
	string strdate2;
	cin >> strdate2;
	void* date1 = new dbmsLib5::DBDate5(strdate1);
	void* date2 = new dbmsLib5::DBDate5(strdate2);
	void* customerID = db["Customers"]->GetRow(cust_ind[0])["CustomerID"];

	vector<int> orders_raw_ind = db["Orders"]->IndexOfRecord(customerID, "CustomerID");
	vector<void*> ordersID;
	for (size_t i = 0; i < orders_raw_ind.size(); i++)
	{
		void* currentOrderDate = db["Orders"]->GetRow(orders_raw_ind[i])["OrderDate"];
		if(dbmsLib5::comparator(dbmsLib5::Date, date1, dbmsLib5::LessOrEqual, currentOrderDate) && dbmsLib5::comparator(dbmsLib5::Date, currentOrderDate, dbmsLib5::LessOrEqual, date2)) {
			ordersID.push_back(db["Orders"]->GetRow(orders_raw_ind[i])["OrderID"]);
		}
	}
	double total = 0;
	for (size_t i = 0; i < ordersID.size(); i++) {
		vector<int> amount_ind = db["OrderDetails"]->IndexOfRecord(ordersID[i], "OrderID");
		for (size_t j = 0; j < amount_ind.size(); j++) {
			total += *(double*)(db["OrderDetails"]->GetRow(amount_ind[j])["TotalAmount"]);
		}
	}
	cout << endl << "Расходы клиента " << name << " за промежуток " << strdate1 <<" - "<<  strdate2 << " составляет: " << total << endl;

}

void FindMostExpenceCustomer(dbmsLib5::DBTableSet5& db) {
	cout << endl << "Требуется ввести промежуток расчета (Даты вводятся в формате ДД.ММ.ГГГГ)." << endl;
	cout << "Введите дату (начало отсчёта): ";
	string strdate1;
	cin >> strdate1;
	cout << "Введите дату (конец отсчёта): ";
	string strdate2;
	cin >> strdate2;
	
	void* date1 = new dbmsLib5::DBDate5(strdate1);
	void* date2 = new dbmsLib5::DBDate5(strdate2);
	vector<void*> orders;
	for(int i = 0; i < db["Orders"]->GetSize(); ++i) {
		void* currentDate= db["Orders"]->GetRow(i)["OrderDate"];
		if(dbmsLib5::comparator(dbmsLib5::Date, date1, dbmsLib5::LessOrEqual, currentDate) && dbmsLib5::comparator(dbmsLib5::Date, currentDate, dbmsLib5::LessOrEqual, date2)) {
			orders.push_back(db["Orders"]->GetRow(i)["OrderID"]);
		}
	}
	if (orders.size() == 0) {
		cout << "Не найдено заказов за указанный период" << endl;
		return;
	}
	map<void*, double> ordersSum;
	for(int i = 0; i < orders.size(); ++i) {
		ordersSum[orders[i]] = 0;
	}
	for(int i = 0; i < orders.size(); ++i) 
		for(int j = 0; j < db["OrderDetails"]->GetSize(); ++j) {
			void* currentOrderID = db["OrderDetails"]->GetRow(j)["OrderID"];
			if(dbmsLib5::comparator(dbmsLib5::Int32, orders[i], dbmsLib5::Equal, currentOrderID)) {
				ordersSum[orders[i]] += *(double*)db["OrderDetails"]->GetRow(j)["TotalAmount"];
			}
		}

	void* maxOrderID;
	auto it = ordersSum.begin();
	auto max_it = it;
	for (it; it != ordersSum.end(); ++it) {
		if (it->second > max_it->second) max_it = it;
	}
	maxOrderID = max_it->first;

	vector<int> id_ind = db["Orders"]->IndexOfRecord(maxOrderID, "OrderID");
	void* maxID = db["Orders"]->GetRow(id_ind[0])["CustomerID"];
	vector<int> name_ind = db["Customers"]->IndexOfRecord(maxID, "CustomerID");
	cout << endl << "Максимальные расходы за период " << strdate1 <<" - "<<  strdate2 << " совершил: " << *(string*)(db["Customers"]->GetRow(name_ind[0])["ContactName"]) << " (Cумма: " << ordersSum[maxOrderID] << ")." << endl ;
}

int main() {
	system("chcp 1251>nul");
	string ch;
	cout << "Введите имя БД	(по умолчанию CompanyTxt - нажмите ENTER)): ";
	string dbName ("CompanyTxt");
	getline(cin,ch);
	if ((ch) != "" || ch.size() > 2) {
		dbName = ch;
	}

	int scrW = 80;

	cout << endl << dbName << endl;
	string path="..\\"+dbName+"\\";
	
	dbmsLib5::DBTableSet5 db(dbName);

	while(true) {
		cout << endl;
		switch(menu()) {
			case 1:
				PrintAllDB(db, scrW);
				break;
			case 2:
				CountIncome(db);
				break;
			case 3: 
				CountExpences(db);
				break;
			case 4: 
				FindMostExpenceCustomer(db);
				break;
			case 5: 
				while (true) {
					cout << endl;
					bool ex = false;
					switch(adv_menu()) {
						case 1:
							PrintSpecDB (db, scrW);
							break;
						case 2:
							AddRecord(db, path);
							break;
						case 3: 
							DeleteRow(db, path);
							break;
						case 4: 
							ChangeRow(db, path);
							break;
						case 5:
							ReadAllDB(db);
							break;
						case 6:
							WriteAllDB(db);
							break;
						case 7: 
							ReadSpecDB(db, path);
							break;
						case 8: 
							WriteSpecDB(db, path);
							break;
						case 9:
							ex = true;
							break;
						default:
							cout << "Недопустимое действие. Повторите выбор\n";
							break;
					}
					if (ex) break;
				}
				break;
			case 6: 
				return 0;  //завершение работы
				break;
			default:
				cout << "Недопустимое действие. Повторите выбор\n";
				break;
		}
	}
  return 0;
}
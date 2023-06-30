#include <iostream>
#include <iomanip>
#include "dbmsLib_v1_1.h"
#include "dbmsLib5.h"
using namespace dbmsLib5;

int menu(){
	cout<<"============���������� � ������������ ������ DBDate1 ===================\n";
cout<<"\t1 - �������� �������� DBDate1 � �������� �������������\n";
cout<<"\t2 - ���������� � ������������ ���������� ���������� ���������\n";
cout<<"\t3 - ���������� � ������������ ��������� DBDate1& operator+=(int days)\n"; 
cout<<"\t4 - ���������� � ������������ ��������� DBDate1& operator-=(int days)\n"; 
cout<<"\t5 - ���������� � ������������ ��������� int operator-(DBD1ate& date)\n"; 
cout<<"\t8 - ������������\n";
cout<<"\t10 - �����\n";
int choice;
cout<<"�������� ��������\n";
cin>>choice;
while(cin.fail()){
	cout<<"������ �����. ��������� ����\n";
	cin.clear();
	cin.ignore(10,'\n');
	cin>>choice;
	}
return choice;
}

void testing(){
	string str2("  29.2.2021   ");
	dbmsLib5::DBDate5 datStr2;
	cout<<"str2="<<str2<<" dat2="<<datStr2<<endl;
	cout<<endl;
dbmsLib::DBDate datStr;
	cout<<"str2="<<str2<<" dat2="<<datStr<<endl;
	cout<<endl;

} 

void create_date() {
	cout << "�������� 29.2.1900\n\n";
	dbmsLib5::DBDate5 date1(29, 2, 1900);
	dbmsLib::DBDate date2("29.2.1900");
	cout << "DBDate5: " << date1 << "\t DBDate: " << date2 << endl;

	cout << endl << endl << dbmsLib5::DateToStr(date1) << endl << endl;
}

void all_compares(DBDate5& a, DBDate5& b) {
	dbmsLib::DBDate a1(DateToStr(a));
	dbmsLib::DBDate b1(DateToStr(b));
	cout << endl << "DBDate5\tDBDate" << endl;
	cout << (a > b) << "\t" << (a1 > b1) << endl;
	cout << (a < b) << "\t" << (a1 < b1) << endl;
	cout << (a >= b) << "\t" << (a1 >= b1) << endl;
	cout << (a <= b) << "\t" << (a1 <= b1) << endl;
	cout << (a != b) << "\t" << (a1 != b1) << endl;
	cout << (a == b) << "\t" << (a1 == b1) << endl;
}

void bools_ops() {
	cout << "25.02.2001 op 25.02.2002";
	dbmsLib5::DBDate5 date1("25.02.2001");
	dbmsLib5::DBDate5 date2("25.02.2002");
	all_compares(date1, date2);

	cout << "25.02.2001 op 25.02.2001";
	dbmsLib5::DBDate5 date3("25.02.2001");
	dbmsLib5::DBDate5 date4("25.02.2001");
	all_compares(date3, date4);
}




//=================================================
int main(){
	system("chcp 1251>nul");
	while(true){
		switch(menu()){
		case 1: 
			create_date();
			break;
		case 2: 
			bools_ops();
			break;
		case 3: 
			break;
		case 4: 
			break;
		case 5: 
			break;
		case 8: 
			testing();
			break;
		case 10: 
			return 0;
		default:
			cout << "�������� �����! ��������� ����� \n\n";
			break;
		}
	}
		return 0;
}
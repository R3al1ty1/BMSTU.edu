#include <iostream>
#include <iomanip>
#include "dbmsLib_v2.h"
using namespace std;
using namespace dbmsLib;
int menu(){
	cout<<"================= ����� ���� ===================\n";
	/*cout<<"\t1 - ������ ������� �� �����\n";
	cout<<"\t2 - ������ �������\n";
	cout<<"\t3 - ������ ������� � ����\n";
	cout<<"\t4 - ���������� ������ � �������\n";
	cout<<"\t5 - ��������� �������� � ������ ������\n";
	cout<<"\t6 - ����������� ������� ��������, StudentID �������� ����� 3\n";
	cout<<"\t7 - ��������� �� 1 ���������� ����������� ���� ���� � ���������� \n";*/
	cout<<"\t8 - ������������\n";
	//cout<<"\t10 - �����\n"; 
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


void testing(string dbName,string tabName){
	string path="..\\"+dbName+"\\";
//��� �������� ���������� Lab4_1 ���������� ������������ �������
	dbmsLib::DBTableSet db(dbName); 
	/*db.PrintDB(80);
	db[tabName]->ReadDBTable(path+tabName+".txt");
	db[tabName]->PrintTable(80);*/
	dbmsLib::DBTableSet tab;
	dbmsLib::ReadDB7(tab);
	dbmsLib::PrintDB7(tab,80);
	dbmsLib::WriteDB7(tab);
}


int main(){
	system("chcp 1251>nul");
	string dbName("LibraryTxt");
	string tabName("Students");	
	string fileName("Students");
	dbmsLib::DBTableTxt tab;
	string path="..\\"+dbName+"\\";
	while(true){
		switch(menu()){
		    case 1: tab.ReadDBTable(path+tabName+".txt");
		
			case 8:testing( dbName, tabName);
				break;
			case 10: return 0;
		}
	}
}
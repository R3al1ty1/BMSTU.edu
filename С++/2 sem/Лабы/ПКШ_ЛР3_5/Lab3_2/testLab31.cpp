#include <iostream>
#include <iomanip>
#include "dbmsLib5.h"
using namespace std;
int menu(){
	cout<<"================= ����� ���� ===================\n";
	cout<<"\t1 - ������ ������� �� �����\n";
	cout<<"\t2 - ������ �������\n";
	cout<<"\t3 - ������ ������� � ����\n";
	cout<<"\t4 - ���������� ������ � �������\n";
	cout<<"\t5 - ��������� �������� � ������ ������\n";
	cout<<"\t6 - ����������� ������� ��������, StudentID �������� ����� 3\n";
	cout<<"\t7 - ��������� �� 1 ���������� ����������� ���� ���� � ���������� \n";
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

//-----------------------------------------------------------------

void testing(string dbName, string tabName){	
	//cout <<"dbName="<<dbName<<"  tabName="<<tabName<<endl;
	string path="..\\"+dbName+"\\";
	DBTableTxt5 tab;
	//DBTableTxt5 tab1;
	//tab.ReadDBTable(path+tabName+".txt");
	//tab.PrintTable(80);//�������� ����� � ��
	string fileName =  path+tabName+".txt";
	tab.ReadDBTable(fileName);
	tab.PrintTable(80);//�������� ��������� ��������� 
	tab.WriteDBTable(path+"Buffer.txt");
	tab.ReadDBTable(path+"Buffer.txt");
	tab.ReadDBTable(path+"Buffer.txt");
	tab.PrintTable(80);


}


//=================================================
int main(){
	system("chcp 1251>nul");
	//cout<<"������� ��� ��\n"; //"LibraryTxt" 
	//��� �������� ������������ ��� ������� ��������� ������������
	string dbName("LibraryTxt");
	//cin>>dbName;
	cout<<dbName<<endl;
	//cout<<"������� ��� ������� ��\n";
	//"Students" "Abonements" "Books"- ��� LibraryTxt
	//��� �������� ������������ ��� ������� ��������� ������������
	string tabName("Books");	
	//cin>>tabName;
	DBTableTxt5 tab;//�������� ������ ������� ������ DBTableTxt,
		//������������� � ������������ � ������� ���������� dbmsLib
	string path="..\\"+dbName+"\\";
	//	cout<<"������� ������� ���� dd.mm.yyyy\n";
	//��� �������� ������������ ��� ������� ��������� ������������
	string str("11.02.2020");
	//	cin>>str;
	DBDate5 today(str);
	//	cout<<"������� ������ ������ � ��������\n";
	int screenWidth=78;
	//	cin>>screenWidth;
	int ind;
	vector<int> indexes;	
	while(true){
		switch(menu()){
		case 1: tab.ReadDBTable(path+tabName+".txt");//������ ������ ��. 
			//�� �������� � ����� "..\\"+dbName+". 
			//��� �� ������������ ��� �� Txt, ���� ������� �� �������� � ��������� ������,
			//������ ������� �������� � ��������� ����� � ������ = <��� �������>+".txt"
			//��������� �����:
			//������ ������ ����� �������� ��� ������� � ��� ������� � ��������� ������
			//������ ������ ����� - ��������� �������
			//��� ����������� ������ - ������ �������. 
				break;
			case 2: tab.PrintTable(screenWidth);//������ ������� �� (screenWidth-������ ������)
				break;
			case 3: tab.WriteDBTable(path+tabName+".txt");
				break;
			case 4: //tab.AddRow(tab.CreateRow(),tab.GetSize());
				break;
			case 5://*(string*)tab[3]["Group"]="IU5-24b";
				break;
			case 6: //ind=3;
				// indexes=tab.IndexOfRecord(&ind,"StudentID");
				//cout<<*(string*)tab[indexes[0]]["Name"]<<endl;
				break;
			case 7: //tabName="Books";
				//tab.ReadDBTable(path+tabName+".txt");
				//for(int i=0;i<tab.GetSize();i++)
					//(*(int*)tab[i]["Quantity"])++;
				break;
			case 8:testing( dbName, tabName);
				break;
			case 10: return 0;//���������� ������
			default:cout<<"������������ ��������. ��������� �����\n"; 
				break;
		}
	}
		return 0;
}
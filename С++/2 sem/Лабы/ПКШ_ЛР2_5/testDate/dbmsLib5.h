#include <iostream>

using namespace std;
namespace dbmsLib5 {
	class DBDate5
	{	
	  
		/**/static const int arrDays[13];
		/**/friend string DateToStr(DBDate5& date);
		/**/friend ostream& operator<<(ostream& out,DBDate5& date);
		int day, month, year;
	public:
		/**/ DBDate5(string date);// ������ ������: dd.mm.yyyy
		/**/ DBDate5(int d,int m,int y); 
		/**/ DBDate5():day(1),month(1),year(1){};//����������� �� ���������
		/**/DBDate5(DBDate5& dat):day(dat.day),month(dat.month),year(dat.year){} // ����������� �����������
		/**/int GetDay();
		/**/int GetMonth();
		/**/int GetYear();
		/**/bool IsLeapYear (int year); //��� ����������?
		/**/int GetDaysInMonth(int month,int year);//���������� ���� � ������
		/**/int DaysInCurYear();//���������� ���� �� ������ ���� �� ������� ����
		/**/bool operator==(DBDate5& date);
		/**/bool operator<(DBDate5& date); 
		/**/bool operator>(DBDate5& date);
		/**/bool operator<= (DBDate5& date);
		/**/bool operator>= (DBDate5& date);
		/**/bool operator!= (DBDate5& date);
		DBDate5& operator+=(int days);//���������� � ������� ���� days ����
		DBDate5& operator-=(int days);//�������� �� ������� ���� days ����
		int operator-(DBDate5& date);	//���������� ���� ����� ������� ����� � date
									//���� ������� ���� > date, ��������� < 0.
	};
}
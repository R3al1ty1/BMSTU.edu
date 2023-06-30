#define _MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;
double eps = 1.0e-8;

double FuncAny(double x) {
	return (sin(x));
}

double cos5(double x) {
	return (x - 5 * cos(x));
}

double cos10(double x) {
	return (x - 10 * cos(x));
}

int menu() {
	cout << "\n================ЛР №4===================\n";
	cout << "\t1. y = x - 5cos(x)\n";
	cout << "\t2. y = x - 10cos(x)\n";
	cout << "\t3. y = f(x)\n";
	cout << "\t4. Выход\n";
	cout << "========================================\n";
	int choice;
	cout << "Выберите действие\n";
	cin >> choice;
	while (cin.fail()) {//исключение зацикливания в случае ввода недопустимых символов
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();//сброс в потоке флага ошибки
		cin.ignore(10, '\n');//извлечение из буфера потока введенных символов
		cin >> choice;//повторный ввод
	}
	return choice;
}

vector <double> bisec(double (*fPtr)(double), double xl, double xr, double step, vector<double> roots) {
	double xi = 0;
	vector<double>rts = roots;
	int cnt = 0;

	cout << "\nВведите границы xn, xk" << endl;
	cout << "\nxn = "; cin >> xl; cout << "xk = "; cin >> xr;

	for (double i = xl; i <= xr; i += step) {
		double xl = i;
		double xr = i + step;
		if ((fPtr(xl) * fPtr(xr)) < 0) {
			cnt = 0;
			while ((xr - xl) / 2 > eps) {
				cnt++;
				xi = (xl + xr) / 2;
				if ((fPtr(xl) * fPtr(xi)) > 0) xl = xi;
				else xr = xi;
			}
			if (abs(xi - eps) < eps) { xi = 0; }
			rts.push_back(xi);
		}
	}
	
	return rts;
}

void print(double a, double b, vector <double> d) {
	for (int i = 1; i <= a; i++) { cout << '\n' << fixed << setprecision(0) << i << ") " <<
		setprecision(b) << d[i - 1] << '\n'; }
	cout << endl << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	double xl, xr, c, step;

	xl = xr = 0;

	vector <double> roots;
	vector <double> finals;

	c = abs(log10(eps)) + 1;
	step = 0.1;

	while (true) {
		switch (menu()) {
		case 1: // y = 5*cos(x)
			finals = bisec(cos5, xl, xr, step, roots);
			print(finals.size(), c, finals);
			break;

		case 2: // y = 10*cos(x)
			finals = bisec(cos10, xl, xr, step, roots);
			print(finals.size(), c, finals);
			break;

		case 3: // y = f(x)
			finals = bisec(FuncAny, xl, xr, step, roots);
			print(finals.size(), c, finals);
			break;

		case 4:
			return 0;
			break;

		default:
			cout << "\nНедопустимое действие. Повторите выбор.\n";
			break;
		}
	}

	system("pause");
	return 0;
}
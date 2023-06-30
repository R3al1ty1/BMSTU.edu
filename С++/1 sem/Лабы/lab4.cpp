#define _MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;
double eps = 1e-8;

double AnyFunc(double x) {
	return (tan(x) + cos(x)/2);
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
	cout << "Выберите действие: ";
	cin >> choice;
	while (cin.fail()) {
		cout << "Ошибка ввода. Повторите ввод\n";
		cin.clear();
		cin.ignore(10, '\n');
		cin >> choice;
	}
	return choice;
}

vector < vector <double> > HalfDiv(double (*fPtr)(double), double xl, double xr,
                                   double step, vector<double>* roots, vector<double>* count) {
	double xi = 0;
	vector<double>rts = *roots;
	vector<double>vCount = *count;
	int cnt, RootCnter = 0;

	cout << "\nВведите значения xn, xk" << endl;
	cout << "\nxn = "; cin >> xl; cout << "xk = "; cin >> xr;

	for (double i = xl; i <= xr; i += step) {
		double xl = i;
		double xr = i + step;
		if ((fPtr(xl) * fPtr(xr)) <= 0) {
			cnt = 0;
			while ((xr - xl) / 2 > eps) {
				cnt++;
				xi = (xl + xr) / 2;
				if ((fPtr(xl) * fPtr(xi)) > 0) xl = xi;
				else xr = xi;
			}
			if (abs(xi - eps) < eps) { xi = 0; }
			rts.push_back(xi);
			vCount.push_back(cnt);
			RootCnter++;
		}
	}
	vector < vector <double> > cmb(RootCnter, vector <double>(2));

	for (int i = 0; i < RootCnter; i++) {cmb[i][0] = rts[i];}
	for (int j = 0; j < RootCnter; j++) {cmb[j][1] = vCount[j];}

	return cmb;
}

void print(double a, double b, vector < vector <double> > d) {
	for (int i = 1; i <= a; i++) {
		cout << '\n' << fixed << setprecision(0) << i << ") " << setprecision(b) << d[i - 1][0] << '\n';
	}
	cout << endl << endl;
}

int main() {
	double xl, xr, c, step, size, x;

	xl = xr = 0;

	vector <double> roots;
	vector <double> count;
	vector < vector <double> > finals;

	double(*F)(double);

	c = abs(log10(eps)) + 1;
	step = 0.1;

	while (true) {
		switch (menu()) {
		case 1: // y = 5*cos(x)
			F = cos5;
			finals = HalfDiv(F, xl, xr, step, &roots, &count);
			size = finals.size();
			print(size, c, finals);
			//print(HalfDiv(F, k, xl, xr, step, &roots, &count).size(), c, HalfDiv(F, k, xl, xr, step, &roots, &count));
			break;

		case 2: // y = 10*cos(x)
			F = cos10;
			finals = HalfDiv(F, xl, xr, step, &roots, &count);
			size = finals.size();
			print(size, c, finals);
			break;

		case 3: // y = f(x)
			F = &AnyFunc;
			finals = HalfDiv(*AnyFunc, xl, xr, step, &roots, &count);
			size = finals.size();
			print(size, c, finals);
			break;

		case 4:
			return 0;
			break;

		default:
			cout << "\nНедопустимое действие. Повторите выбор.\n";
			break;
		}
	}
	return 0;
}
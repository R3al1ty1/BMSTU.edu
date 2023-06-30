#include <iostream>
#include <algorithm>
using namespace std;

int cnt1 = 0;
int cnt2 = 0;
int n = 0;

int Menu(){
    cout<<"================СОРТИРОВКА МАССИВОВ===================\n";
    cout<<"\t1 – miniMax: Сортировка по убыванию\n";
    cout<<"\t2 – miniMax: Сортировка по возростания\n";
    cout<<"\t3 - bubble: Сортировка методом пузырькового всплытия\n";
    cout<<"\t4 - Выход\n";
    int choice;
    cout<<"Выберите действие\n";
    cin>>choice;
    while(cin.fail()){
        cout<<"Ошибка ввода. Повторите ввод\n";
        cin.ignore(10,'\n');
        cin>>choice;
    }
    return choice;
}

void miniMax(int *arr, int size, bool (*comparisonFcn)(int, int))
{
    for (int sIndex = 0; sIndex < size; ++sIndex)
    {
        int bIndex = sIndex;
        cnt1++;

        for (int currIndex = sIndex + 1; currIndex < size; ++currIndex)
        {
            if (comparisonFcn(arr[bIndex], arr[currIndex]))
                bIndex = currIndex;
        }
        swap(arr[sIndex], arr[bIndex]);
    }
}
bool ascending(int a, int b)
{
    return a > b;
}
bool descending(int a, int b)
{
    return a < b;
}

void bubble(int *array, int size)
{
	for(int i = 1; i < size; ++i)
	{
		for(int r = 0; r < size - i; r++)
		{
			if(array[r + 1] < array[r])
			{
				int temp = array[r + 1];
				array[r + 1] = array[r];
				array[r] = temp;
                cnt2++;
			}
		}
	}
}
void printArray(int *array, int size)
{
    for (int index = 0; index < size; ++index)
        cout << array[index] << " ";
    cout << endl;
}

int main()
{
    int arr[8] = { 4, 8, 5, 6, 2, 3, 1, 7 };
    int array[8] = { 4, 8, 5, 6, 2, 3, 1, 7 };

    while(true) {
        switch(Menu()){
            case 1:
                miniMax(arr, 8, descending);
                printArray(arr, 8);
                cout << cnt1 - 8 * n << endl;
                n++;
                break;
            case 2:
                miniMax(arr, 8, ascending);
                printArray(arr, 8);
                cout << cnt1 - 8 * n << endl;
                n++;
                break;
            case 3:
                bubble(array, 8);
                printArray(array, 8);
                cout << cnt2 << endl;
                break;
            case 4:
                return 0;
            default: cout<< "Недопустимое действие. Повторите выбор" << endl;
        }
    }
}
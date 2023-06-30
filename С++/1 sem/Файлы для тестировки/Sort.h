#pragma once
template <typename T> void MinMax(T arr[], int n, bool(*cmp)(T obj1, T obj2), int& nCmp, int& nSwp)
{
	nCmp = 0;
	nSwp = 0;
	for (int i = 0; i < n - 1; i++) {
		int max = i;
		for (int j = i + 1; j < n; j++) {
			nCmp++;
			if (cmp(arr[j], arr[max]) == 1)
				max = j;
		}
		if (max != i) {
			std::swap(arr[i], arr[max]);
			nSwp++;
		}
	}
}

template <typename T> void Bubble(T arr[], int n, bool(*cmp)(T obj1, T obj2), int& nCmp, int& nSwp)
{
	int i, j;
	nCmp = 0;
	nSwp = 0;
	int flag = 1;
	for (i = 0; (i < n-1) and (flag==1); i++) {
		flag = 0;
		for (j = n-1; j > i; j--) {
			nCmp++;
			if (cmp(arr[j], arr[j-1])) {
				std::swap(arr[j], arr[j-1]);
				flag = 1;
				nSwp++;
			}
		}
	}
}

#include <iostream>
using namespace std;
int show(int);
int main()
{
    int num=9;
    cout << show(num) << endl;  // 3
}
int show(int arg)
{
    if (arg >0) return arg - show(--arg); // приоритет операций --arg > cout
    return 1;			        // 8 - show(8) -> 7 - show(7) ... -> 0 - show(0)
}

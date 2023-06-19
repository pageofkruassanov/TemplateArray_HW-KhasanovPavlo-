#include "Array.h"

int main()
{
    int* arr = new int[3] {5, 5, 9};
    Array<int> obj(3, 3, arr);
    cout << obj.GetUpperBound();
    cout << endl << obj.GetAt(2);
    obj.SetAt(0, 2);
    cout << endl << obj[0];
    obj.Add(15);
    cout << endl << obj[3];
    int* arr2 = new int[2] {2, 100};
    Array<int> obj2(2, 3, arr2); 
    obj.Append(obj2);
    cout << endl << obj;
    cout << endl << obj.GetData();
    obj.InsertAt(4, 1999);
    cout << endl << obj;
    obj.RemoveAt(3);
    cout << endl << obj;
}
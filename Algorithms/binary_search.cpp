#include <iostream>
using namespace std;
int binary_search(int array[], int size, int item)
{

    int low = 0;
    int high = size;
    int mid = 0;
    //<= is necessary otherwise it may bug out
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (array[mid] == item)
        {

            return mid;
        }
        else if (item > array[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}
int main()
{
    cout << (24 and 1);
    int array[] = {10, 15, 18, 21, 25, 29, 32, 24, 55, 125, 189, 210, 420};
    cout << "Item found at index : " << binary_search(array, 13, 55);
}
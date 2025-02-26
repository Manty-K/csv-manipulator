#include <stdio.h>

int main(int argc, char const *argv[])
{
    int arr[] = {3, 4, 6, 10};

    int length = sizeof(arr) / sizeof(int);

    int target = 10;

    int left = 0;

    int right = length - 1;

    int result = 0;
    int haveToInsert = 0;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            result = mid;
            haveToInsert = 1;
            break;
        }

        if (target > arr[mid])
        {
            result = mid;

            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    printf("Result : %d and %s\n", result, haveToInsert ? "found" : "not found");

    return 0;
}

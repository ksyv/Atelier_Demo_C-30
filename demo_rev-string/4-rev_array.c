#include "main.h"

void reverse_array(int *a, int n)
{
    int *left = a;
    int *right = a + n -1;
    int temp;


    while (left < right)
    {
        temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}
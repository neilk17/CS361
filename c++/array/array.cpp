#include <cstdlib>
#include <iostream>
#include <math.h>
#include <time.h>

void printArray(int A[], int arrLen)
{
    std::cout << "[";
    for(int j = 0;j<arrLen; j++)
    {
        if (j+1 == arrLen)
            std::cout << A[j];
        else
            std::cout << A[j] << ", ";
    }
    std::cout << "]\n";
}

void merge(int A[], int start, int middle, int stop)
{
    int auxLen = stop-start+1;
    int* aux = new int[auxLen];
    for (int i = 0;i < auxLen; i++)
    {
        aux[i] = A[start+i];
    }
    int auxMiddle = middle-start;
    int auxStop = stop-start;
    int i = 0;
    int j = auxMiddle+1;
    for (int k=start; k<stop+1;k++)
    {
        if(i > auxMiddle)
        {
            A[k] = aux[j];
            j++;
        }
        else if(j > auxStop)
        {
            A[k] = aux[i];
            i++;
        }
        else if(aux[j] > aux[i])
        {
            A[k] = aux[i];
            i++;
        }
        else
        {
            A[k] = aux[j];
            j++;
        }
    }
    delete[] aux;
}

void msortSec(int A[], int start, int  stop)
{
    if (start >= stop)
        return;

    int middle = start + floor((stop-start)/2);
    msortSec(A,start,middle);
    msortSec(A,start,middle);
    merge(A,start,middle, stop);
}

void mergeSort(int* A, int size)
{
    msortSec(A, 0, size - 1);
}

int main()
{
    int arrLength = 20;
    int arr1[arrLength];

    srand(time(0));

    for(int i=arrLength;i>0;i--)
    {
        arr1[i] = rand()%arrLength;
    }

    std::cout << "Unsorted Array: ";
    printArray(arr1, arrLength);
    mergeSort(arr1, arrLength);
    std::cout << "Sorted Array: ";
    printArray(arr1, arrLength);
}

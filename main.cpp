/*
Cindy Ramirez
CPSC 350
Assignment 6
December 13, 2019

*/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

void insertionSort(double arr[], int n);
void bubbleSort(double arr[], int n);
void selectionSort(double arr[], int n);
void swap(double *a, double *b);
int partition(double arr[], int low, int high);
void quickSort(double arr[], int low, int high);
void copyArr(double * to, double * from, unsigned int size);
void createTextFile(string filename, unsigned int n);
bool isSorted(double* arr, unsigned int size);

void merge(double* first_half, double* second_half, int first_half_size, int second_half_size, int mergedArraySize);
void mergeSort(double * array, int arraySize);


//=====================main=====================================================

int main(int argc, char** argv)
{
    string firstArg(argv[1]);
    //g++ main.cpp
    // ./a.out CREATEDATA my400RandomDoubles.txt 400
    // ./a.out my400RandomDoubles.txt
    if (firstArg == "CREATEDATA")
    {
        cout << "Got into CREATEDATA" << endl;
        createTextFile(argv[2], stoi(argv[3]));
    }
    else if (argc > 1)
    {
        char *fileName = argv[1];
        ifstream inFile;
        string line = "";
        string outFileName(fileName);
        outFileName += "_REPORT.txt";
        ofstream out(outFileName);
        int n;


        double beginInsertion, endInsertion;
        double beginBubble, endBubble;
        double beginSelection, endSelection;
        double beginQS, endQS;
        double beginMS, endMS;


        inFile.open(fileName);
        inFile >> n;
        double * arr = new double[n];
        int i = 0;
        while (i < n && inFile >> arr[i])
        {
            i++;
        }

        for (int j = n-25; j < n; j++)
        {
            cout << "arr[j] = " << arr[j] << endl;
        }

        bool sorted = false;

        out << "Insertion Sort: " << endl;;
        double * insertArr = new double[n];
        copyArr(insertArr, arr, n);
        beginInsertion = clock();
        insertionSort(insertArr, n);
        endInsertion = clock();
        out << " Start Time: " << (double)(beginInsertion/(double) CLOCKS_PER_SEC) << " - " << " End Time: " << (double) (endInsertion/(double) CLOCKS_PER_SEC) << " seconds " << endl;
        out << " Time Elapsed: " << (double)((endInsertion-beginInsertion)/(double) CLOCKS_PER_SEC) << endl; // 0.002
        out << "\n";

        sorted = isSorted(insertArr,n);
        if (sorted)
        {
            cout << "Verified proper sort" << endl;
        }
        else
        {
            cout << "Incorrect sort detected" << endl;
        }

        out << "Bubble Sort " << endl;
        double * bubbleArr = new double[n];
        copyArr(bubbleArr, arr, n);
        beginBubble = clock();
        bubbleSort(bubbleArr, n);
        endBubble = clock();
        out << " Start Time: " << (double)(beginBubble/(double) CLOCKS_PER_SEC) << " - " << " End Time: " << (double) (endBubble/(double) CLOCKS_PER_SEC) << " seconds " << endl;
        out << " Time Elapsed: " << (double)((endBubble-beginBubble)/(double) CLOCKS_PER_SEC) << endl;
        out << "\n";


        sorted = isSorted(bubbleArr, n);
        if (sorted)
        {
            cout << "Verified proper sort" << endl;
        }
        else
        {
            cout << "Incorrect sort detected" << endl;
        }

        out << "Selection Sort " << endl;
        double * selectionArr = new double[n];
        copyArr(selectionArr, arr, n);
        beginSelection = clock();
        selectionSort(selectionArr, n);
        endSelection = clock();
        out << " Start Time: " << (double)(beginSelection/(double) CLOCKS_PER_SEC) << " - " << " End Time: " << (double) (endSelection/(double) CLOCKS_PER_SEC) << " seconds " << endl;
        out << " Time Elapsed: " << (double)((endSelection-beginSelection)/(double) CLOCKS_PER_SEC) << endl;
        out << "\n";

        sorted = isSorted(selectionArr, n);
        if (sorted)
        {
            cout << "Verified proper sort" << endl;
        }
        else
        {
            cout << "Incorrect sort detected" << endl;
        }

        out << "Quick Sort " << endl;
        double * quickSortArr = new double[n];
        copyArr(quickSortArr, arr, n);
        beginQS = clock();
        cout << "n-1 = " << n-1 << endl;
        quickSort(quickSortArr, 0, n-1);
        endQS =  clock();
        out << " Start Time: " << (double)(beginQS/(double) CLOCKS_PER_SEC) << " - " << " End Time: " << (double) (endQS/(double) CLOCKS_PER_SEC) << " seconds " << endl;
        out << " Time Elapsed: " << (double)((endQS-beginQS)/(double) CLOCKS_PER_SEC) << endl;
        out << "\n";

        sorted = isSorted(quickSortArr, n);
        if (sorted)
        {
            cout << "Verified proper sort" << endl;
        }
        else
        {
            cout << "Incorrect sort detected" << endl;
        }


        out << " Merge Sort " << endl;
        double * MergeSortArr = new double[n];
        copyArr(MergeSortArr, arr, n);
        beginMS = clock();
        mergeSort(MergeSortArr, n);
        endMS =  clock();
        out << " Start Time: " << (double)(beginMS/(double) CLOCKS_PER_SEC) << " - " << " End Time: " << (double) (endMS/(double) CLOCKS_PER_SEC) << " seconds " << endl;
        out << " Time Elapsed: " << (double)((endMS-beginMS)/(double) CLOCKS_PER_SEC) << endl;
        out << "\n";

        sorted = isSorted(MergeSortArr, n);
        if (sorted)
        {
            cout << "Verified proper sort" << endl;
        }
        else
        {
            cout << "Incorrect sort detected" << endl;
        }

        inFile.close();
        out.close();
        //cout << "check text file" << endl;
    }
    else
    {
        cout << " Could not open file.... exiting program " << endl;
    }
    return 0;
}
//====================== end of main ===========================================



//============ insertionSort ================================================
//Function to sort an array using insertion sort
void insertionSort(double arr[], int n)
{

    int key;
    int j = 0;
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        j = i-1;

        //Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position */
        while (j >= 0 && arr[j] > key)
        {
        arr[j+1] = arr[j];
        j = j-1;
        }
        arr[j+1] = key;
    }


}

//============== end of insertionSort()=========================================



//==================== BubbleSort() ===========================================
//Function to sort an array using bubble sort
void bubbleSort(double arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < (n-1); j++)
    {
      if (arr[j] > arr[j+1])
      {
          int temp = arr[j];
          arr[j] = arr[j+1];
          arr[j+1] = temp;
      }
    }
  }
}


//===========end of Bubble Sort()===============================================


//====================== Selection sort()=======================================
//Function to sort an array using selection sort
void selectionSort(double arr[], int n)
{
  for (int i = 0; i < n-1; i++)
  {
    int min = i;
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[min])
      {
         min = j;
      }
    }

      int temp = arr[min];
      arr[min] = arr[i];
      arr[i] = temp;
  }
}

//=========== quick sort algorithms =========================================

void swap(double *a, double *b)
{
  double t = *a;
  *a = *b;
  *b= t;
}

void quickSort(double arr[], int low_index, int high_index)
{
    if ( low_index < high_index )
    {
      double pivot_val = arr[high_index];
      //arr[4999]
      int i = (low_index - 1);

      for (int j = low_index; j <= high_index - 1; j++)
      {
         if (arr[j] <= pivot_val)
         {
           i++;
           swap(&arr[i], &arr[j]);
         }
      }
      //cout << "i+1=" << i+1 << endl;
      //cout << "high_index=" << high_index << endl;
      swap(&arr[i+1], &arr[high_index]);

      quickSort(arr, low_index, i);
      quickSort(arr, i+2, high_index);
    }
}

//=================== end of quick sort algorithms ===========================

void copyArr(double * to, double * from, unsigned int size)
{
    for (int i = 0; i < size; i++)
    {
        to[i] = from[i];
    }
}

void createTextFile(string filename, unsigned int n)
{
    ofstream out(filename);
    out << n << endl;
    srand( (unsigned) time(NULL));
    for (int i = 0; i < n; i++)
    {
        out << ((double) rand() / (double) RAND_MAX);
        out << endl;
    }

}

bool isSorted(double* arr, unsigned int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i+1])
        {
            cout << "Incorrect Values: arr[" << i << "]: " << arr[i] << " and arr[i+1]: " << arr[i+1] << endl;
            return false;
        }
    }
    return true;
}


//================ merge sort algorithms =========================
void merge(double* first_half, double* second_half, int first_half_size, int second_half_size, int mergedArraySize)
{
    double * merged = new double[mergedArraySize];
    int i = 0;
    int first_index = 0;
    int second_index = 0;
    while (i < mergedArraySize)
    {
        if (first_index == first_half_size)
        {
            merged[i] = second_half[second_index];
            i++;
            second_index++;

        }
        else if (second_index == second_half_size)
        {
            merged[i] = first_half[first_index];
            i++;
            first_index++;

        }
        else if (first_half[first_index] < second_half[second_index])
        {
            merged[i] = first_half[first_index];
            i++;
            first_index++;
        }
        else
        {
            merged[i] = second_half[second_index];
            i++;
            second_index++;
        }
    }

    for (int i = 0; i < mergedArraySize; i++)
    {
        first_half[i] = merged[i];
    }
    delete merged;
    return;
}

void mergeSort(double * array, int arraySize)
{
    if (arraySize <= 1)
    {
        return;
    }
    else
    {

        int first_half_size = arraySize / 2;
        int second_half_size = arraySize / 2;
        if (arraySize%2 == 1)
        {
            second_half_size++;
        }
        mergeSort(array,first_half_size); // [0,1]
        double * second_half = array + first_half_size;
        mergeSort(second_half,second_half_size); // [2,3,4]
        merge(array, second_half, first_half_size, second_half_size, arraySize);
    }
}

//================= end of merge sort algorithms ==================

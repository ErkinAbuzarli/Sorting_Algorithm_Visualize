#include <sys/time.h>
#include <time.h>
#include <stdio.h> 
#include <stdlib.h>

void selectionSort(int arr[], int n);
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);

void histogram_for_insertion(int *arr, int n, int red, int green, int key);         // We must write different functions for insertion because
void histogram(int *arr, int n, int red, int green);                                // in insertion we grouped elements.
void delay(int number_of_seconds);
void swap(int *xp, int *yp);


void insertionSort(int arr[], int n) 
{ 
    int i, key, j; 
    for (i = 1; i < n; i++) { 
        key = arr[i]; 
        j = i - 1; 
  
        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && arr[j] > key) { 
            histogram_for_insertion(arr, n , j, i ,key);
            delay(1);
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
} 

void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < n-i-1; j++)  
        if (arr[j] > arr[j+1]){
            histogram(arr, n, j, j+1);
            delay(1);
            swap(&arr[j], &arr[j+1]);  
        }else{
            histogram(arr, n, j, j);
            delay(1);
        }
}
  
void selectionSort(int arr[], int n) 
{ 
    int i, j, min_idx; 
  
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        // Print histogram each changes.
        histogram(arr, n, i, min_idx);
        delay(1);
        // Swap the found minimum element with the first element 
        swap(&arr[min_idx], &arr[i]); 
        printf("\n");
    } 
} 

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds)
    ; 
} 

void histogram(int *arr, int n, int red, int green){

    int w = (54-n)/2;               

    for (int i = 0; i < w; i++)             // With that we print histogram mid of terminal.
        printf("\n");
    
    for(int i = 0; i < n;i++)
    {
        printf("%3d |", arr[i]);            // Print number.

        for( int j = 0; j < arr[i];j++)     // And histogram with *.
        {
            if(red == -1)                   // For print sorted array.
            {
                printf("\033[1;32m*\033[0m");
            } 
            else                            
            {
                if (i == green && i == red) // If no change print blue.
                    printf("\033[1;34m*\033[0m");
                else if(i == red)           
                    printf("\033[1;31m*\033[0m");
                else if (i == green)
                    printf("\033[1;32m*\033[0m");
                else
                    printf("*");
            }
        }
        if (red == -1) delay(0.5);
        printf("\n");
    }

    for (int i = 0; i < w; i++)
        printf("\n");
}

void histogram_for_insertion(int *arr, int n, int red, int green, int key){

    int w = (54-n)/2;

    for (int i = 0; i < w-5; i++)             // With that we print histogram mid of terminal.
        printf("\n");

    printf("Key:\n%3d |", key);

    for (int i = 0; i < key; i++)             // Print Key value as green.
        printf("\033[1;32m*\033[0m");

    printf("\n\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("%3d |", arr[i]);              // Print number

        for( int j = 0; j < arr[i];j++)
        {
            if(i >=red && i < green)          
                printf("\033[1;31m*\033[0m");
            else
                printf("*");
        }
        printf("\n");
    }

    for (int i = 0; i < w; i++)
        printf("\n");
    
}

int main() 
{ 
    int n, ans;

    printf("\e[1;1H\e[2J");                 // This clear terminal
    printf("\n\n%121s\n\n\n", "Sorting Algorithms Visualization");

    printf("Please Full Screen For Best Result\n\n1: Selection Sort\n2: Bubble Sort\n3: Insertion Sort\n\nSelect Algorithm: ");
    scanf("%d", &ans);

    printf("Array size: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n);             

    for(int i = 0 ; i< n; i++){
        *(arr + i) = (rand()%200);          // Write random number for array
    }

    printf("\n\n\n");

    
    switch (ans)                            // Navigate for choosen Sort Algorithm
    {
    case 1:
        selectionSort(arr, n);
        break;
    
    case 2:
        bubbleSort(arr, n);
        break;

    case 3:
        insertionSort(arr, n);
        break;

    default:
        break;
    }
    
    histogram(arr, n, -1, -1);              // Print sorted array.


    free(arr);                              // Free memory.
    return 0; 
} 

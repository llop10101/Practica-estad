#include <vector>
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;
typedef vector<int> Vector;

int partition(vector<int> &vec, int low, int high) {

    // Selecting last element as the pivot
    int pivot = vec[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(vec, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

void merge(vector<int>& vec, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<int> leftVec(n1), rightVec(n2);

    // Copy data to temporary vectors
    for (i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];
    for (j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];

    // Merge the temporary vectors back into vec[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftVec[], if any
    while (i < n1) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightVec[], if any
    while (j < n2) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left..right]
void mergeSort(vector<int>& vec, int left, int right) {
    if (left < right) {
      
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        // Merge the sorted halves
        merge(vec, left, mid, right);
    }
}


void bubbleSort(vector<int>& v) {
    int n = v.size();

    // Outer loop that corresponds to the number of
    // elements to be sorted
    for (int i = 0; i < n - 1; i++) {

        // Last i elements are already
        // in place
        for (int j = 0; j < n - i - 1; j++) {
          
              // Comparing adjacent elements
            if (v[j] > v[j + 1])
              
                  // Swapping if in the wrong order
                swap(v[j], v[j + 1]);
        }
    }
}

void selectionSort(vector<int> &arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {

        // Assume the current position holds
        // the minimum element
        int min_idx = i;

        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {

                // Update min_idx if a smaller
                // element is found
                min_idx = j; 
            }
        }

        // Move minimum element to its
        // correct position
        swap(arr[i], arr[min_idx]);
    }
}

void insertionSort(std::vector<int> &vec) 
{ 
    for (auto it = vec.begin(); it != vec.end(); it++) 
    {         
        // Searching the upper bound, i.e., first  
        // element greater than *it from beginning 
        auto const insertion_point =  
                std::upper_bound(vec.begin(), it, *it); 
          
        // Shifting the unsorted part 
        std::rotate(insertion_point, it, it+1);         
    } 
} 

void llegirFitxer(Vector&vector, int nLinies) {
    cout << "Insert the file path";
    string path;
    cin>>path;
    ifstream file(path);
    if (!file) {
        cerr << "Error: File not found" << endl;
        return;
    }
    int value;
    int readedLines = 0;
    while(file>>value && readedLines <= nLinies) {
        vector.push_back(value);
        readedLines++;
    }
    file.close();
    cout << "Final vector size: " << vector.size() << endl;

}

int main(int argc, char* argv[]) {
    // Crear vector 
    Vector vector;
    
    // Llegir fitxer
    llegirFitxer(vector,atoi(argv[0]));
    
    // Executar els codis
    // Saber quant tarden 
     
    // Guardar les dades de memoria i velocitat
    return 0;
}

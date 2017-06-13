//
//  TRIMMEAN.cpp
//  TRIMMEAN
//
//  Created by Kevin Tan on 6/11/17.
//

#include "TRIMMEAN.h"

///////////////////////////////////////////////////////////////////////////
// Helper Functions
///////////////////////////////////////////////////////////////////////////

/* Partitioning algorithm for QuickSort and QuickSelect */
static int partition(int array[], int low, int high) {

    // Pick the first element to be the pivot.
    int pivotIndex = low;
    int pivot = array[low];
    
    do {
        
        while (low <= high && array[low] <= pivot)
            low++;
        
        while (array[high] > pivot)
            high--;
        
        if (low < high) {
            
            int temp = array[low];
            array[low] = array[high];
            array[high] = temp;
            
        }
        
    } while (low < high);
    
    int temp = array[pivotIndex];
    array[pivotIndex] = array[high];
    array[high] = temp;
    
    pivotIndex = high;
    return pivotIndex;
    
}

/* QuickSort algorithm */
static void quickSort(int array[], int first, int last) {
    
    if (last - first >= 1) {
        
        int pivotIndex = partition(array, first, last);
        
        quickSort(array, first, pivotIndex-1);
        quickSort(array, pivotIndex+1, last);

    }
    
}

/* QuickSelect algorithm */
static int quickSelect(int array[], int first, int last, int k) {
    
    if (last - first >= 1) {
        
        int pivotIndex = partition(array, first, last);
        
        if (pivotIndex == k)
            return array[pivotIndex];
        
        else if (k < pivotIndex)
            return quickSelect(array, first, pivotIndex-1, k);
        
        else
            return quickSelect(array, pivotIndex+1, last, k);
        
    }
    
    return array[first];
    
}

/* Calculate mean given starting and ending array index */
inline
static double mean(int array[], int low, int high) {
    
    int acc = 0;
    
    for (int i = low; i <= high; i++)
        acc += array[i];
    
    return acc / (double)(high - low + 1);
    
}

///////////////////////////////////////////////////////////////////////////
// slowTRIMMEAN Implementation
///////////////////////////////////////////////////////////////////////////

// Given an array of integers, exclude "percent" percent of data points from the top and bottom tails
// of a data set. Calculate and return the mean of the remaining data.
//
// inputArray: data set; array of integers to examine
// n: size of data set
// percent: fractional number of data points to exclude, where 0 <= percent < 1
// errorno (optional): pointer to ErrorNumber enumerated type for additional error information
//
// If any problems are encountered, return NaN. If the errorno argument is defined, additional information
// about the offending error will be provided in the form of an error code.
double slowTRIMMEAN(int inputArray[], int n, double percent, ErrorNumber *errorno) {
    
    /* Error Handling */
    
    double NaN = 0 * (1e308 * 1e308);
    bool enoIsDefined = errorno != nullptr;
    
    if (n <= 0) {
        // size (n) out of range.
        if (enoIsDefined)
            *errorno = EBADN;
        
        return NaN;
        
    }
    
    if (percent < 0 || percent >= 1) {
        // Percent out of range.
        if (enoIsDefined)
            *errorno = EBADPCNT;
        
        return NaN;
        
    }
    
    if (inputArray == nullptr) {
        // inputArray is null.
        if (enoIsDefined)
            *errorno = EBADARR;
        
        return NaN;
        
    }
    
    /* TRIMMEAN */
    
    // Copy inputArray into a local array which we will sort: we don't want to modify the original
    // input array.
    int array[n];
    for (int i = 0; i < n; i++)
        array[i] = inputArray[i];
    
    // Use QuickSort algorithm to sort the array.
    quickSort(array, 0, n-1);
    
    // Calculate the number of elements to exclude and round down to the nearest even number.
    int elementsToExclude = n * percent;
    if (elementsToExclude % 2 != 0)
        elementsToExclude--;
    
    // Using our sorted array, exclude the lowest and highest (elementsToExclude / 2) elements and
    // return the trimmed average.
    int low = elementsToExclude / 2;
    int high = n - (elementsToExclude / 2) - 1;
    
    return mean(array, low, high);
    
}

///////////////////////////////////////////////////////////////////////////
// TRIMMEAN Implementation
///////////////////////////////////////////////////////////////////////////

// Given an array of integers, exclude "percent" percent of data points from the top and bottom tails
// of a data set. Calculate and return the mean of the remaining data.
//
// inputArray: data set; array of integers to examine
// n: size of data set
// percent: fractional number of data points to exclude, where 0 <= percent < 1
// errorno (optional): pointer to ErrorNumber enumerated type for additional error information
//
// If any errors are encountered, return NaN. If the errorno argument is defined, additional information
// about the offending error will be provided in the form of an error code.
double TRIMMEAN(int inputArray[], int n, double percent, ErrorNumber *errorno) {
    
    /* Error Handling */
    
    double NaN = 0 * (1e308 * 1e308);
    bool enoIsDefined = errorno != nullptr;
    
    if (n <= 0) {
        // size (n) out of range.
        if (enoIsDefined)
            *errorno = EBADN;
        
        return NaN;
        
    }
    
    if (percent < 0 || percent >= 1) {
        // Percent out of range.
        if (enoIsDefined)
            *errorno = EBADPCNT;
        
        return NaN;
        
    }
    
    if (inputArray == nullptr) {
        // inputArray is null.
        if (enoIsDefined)
            *errorno = EBADARR;
        
        return NaN;
        
    }
    
    /* fastTRIMMEAN */
    
    // Calculate the number of elements to exclude and round down to the nearest even number.
    int elementsToExclude = n * percent;
    if (elementsToExclude % 2 != 0)
        elementsToExclude--;
    
    // Calculate number of elements trimmed from top/bottom.
    int half = elementsToExclude / 2;
    
    // Use QuickSelect algorithm to find the lowest and highest values we include in our trimmed sum.
    int lowBound = quickSelect(inputArray, 0, n-1, half);
    int highBound = quickSelect(inputArray, 0, n-1, n-half-1);
    
    // Compute weights. If there is only one occurrence of lowBound and highBound in the data set,
    // a == b == c == d == weight1 == weight2 == 1.
    double a, b = 0, c, d = 0, dm = 0, bm = 0;
    double weight1, weight2;
    
    int curr;
    for (int i = 0; i < n; i++) {
        
        curr = inputArray[i];
        if (curr < lowBound)
            bm++;
        else if (curr == lowBound)
            b++;
        
        if (curr < highBound)
            dm++;
        else if (curr == highBound)
            d++;
        
    }
    
    a = b + bm - half;
    c = n - half - dm;
    
    weight1 = a / b;
    weight2 = c / d;
    
    // Compute a trimmed sum.
    double trimmedSum = 0;
    
    for (int i = 0; i < n; i++) {
        
        // Calculate all possible values and and use conditional moves to optimize branch prediction.
        int curr = inputArray[i];
        double weighted1 = weight1 * curr;
        double weighted2 = weight2 * curr;
        
        double toAdd = 0;
    
        if (curr == lowBound)
            toAdd = weighted1;
        else if (curr == highBound)
            toAdd = weighted2;
        else if (lowBound < curr && curr < highBound)
            toAdd = curr;
        
        // if (curr < lowBound || curr > highBound), exclude the element from our trimmed sum; just
        // continue without performing any operations on trimmedSum.
        
        trimmedSum += toAdd;
        
    }
    
    // Return trimmed sum / number of elements in our trimmed sum.
    return trimmedSum / (n - 2*half);
    
}

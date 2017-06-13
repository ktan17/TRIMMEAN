//
//  main.cpp
//  TRIMMEAN
//
//  Created by Kevin Tan on 6/11/17.
//

#include "TRIMMEAN.h"
#include <iostream>
#include <random>
#include <sys/time.h>

// Get time
inline
long long get_time() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

// Returns elapsed time
inline
float elapsed_time(long long start_time, long long end_time) {
    return (float) (end_time - start_time) / (1000 * 1000);
}

// Return a uniformly distributed random int from min to max, inclusive
inline
int randInt(int min, int max)
{
    if (max < min)
        std::swap(max, min);
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

int main() {
    
    /* Sample code that tests performance of slowTRIMMEAN and TRIMMEAN */
    
    int arr[100000];
    
    for (int i = 0; i < 100000; i++)
        arr[i] = randInt(-500, 500);
    
    // Perform TRIMMEAN and fastTRIMMEAN on 100,000 randomly generated integers in the range of [-500,
    // 500].
    long long start = get_time();
    std::cout << "slowTRIMMEAN output: " << slowTRIMMEAN(arr, 100000, 0.2) << std::endl;
    long long end = get_time();
    
    long long start2 = get_time();
    std::cout << "TRIMMEAN output: " << TRIMMEAN(arr, 100000, 0.2) << std::endl << std::endl;
    long long end2 = get_time();
    
    float trimTime = elapsed_time(start, end);
    float fastTrimTime = elapsed_time(start2, end2);
    
    std::cout << "slowTRIMMEAN took " << trimTime << std::endl;
    std::cout << "TRIMMEAN took " << fastTrimTime << std::endl << std::endl;
    
    char tstring[13] = "slowTRIMMEAN";
    char *winner = tstring;
    if (fastTrimTime <= trimTime)
        winner += 4;
    
    std::cout << winner << " performed better." << std::endl << std::endl;
    
}

//
//  TRIMMEAN.h
//  TRIMMEAN
//
//  Created by Kevin Tan on 6/11/17.
//

#ifndef trimmean
#define trimmean

enum ErrorNumber {
    
    EBADN,
    EBADPCNT,
    EBADARR
    
};

double slowTRIMMEAN(int inputArray[], int n, double percent, ErrorNumber *errorno = nullptr);
double TRIMMEAN(int inputArray[],  int n, double percent, ErrorNumber *errorno = nullptr);

#endif /* trimmean defined */

/*
 * @Author: Shengyuan Wang, Kaiyang Yao
 * @Date: 2022-11-19 18:56:40
 * @LastEditors: Shengyuan Wang
 * @LastEditTime: 2022-12-08 12:42:48
 * @FilePath: /445f22/project-team2-shengyuan-kaiyang/OpenMP/APSPtest.c
 * @Description: Test File Generator
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "MatUtil.h"
#include "Floyd_openMP.h"
#include "../utils/getCommandLine.h"
int main(int argc, char **argv)
{
    // Default Setup
    int N = 100;
    int numThreads = 1;
    int verbose = 0;
    int experiment = 0;

    //Get Argument from terminal
    getArguments(argc, argv, &N, &numThreads, &verbose, &experiment);
    if (experiment) {
        verbose = 0;
    }
    omp_set_num_threads(numThreads);

    int *mat = (int*)malloc(sizeof(int)*N*N);
    GenMatrix(mat, N);

    //compute your results
    int *result = (int*)malloc(sizeof(int)*N*N);
    memcpy(result, mat, sizeof(int)*N*N);
    //replace by parallel algorithm
    double st = omp_get_wtime();
    Floyd_Warshall(result, N);
    double runtime = omp_get_wtime() - st;

    //print the output
    if (experiment) {
        printf("%f\t", runtime);
    } else {
        printf("Elapsed time (parallel) = %f s\n", runtime);
    }
    
    if (verbose) {
        for (int i = 0; i < N*N; i++) {
            printf("%4d", result[i]);
            if (i % N == N-1) {
                printf("\n");
            }
        }
    }
}

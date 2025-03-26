#include <stdio.h>

#include <omp.h>

int main()
{
    int num_procs = omp_get_num_procs();
    printf("-> Number of available procs: %d\n", num_procs);
    return 0;
}
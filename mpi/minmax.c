#include <mpi.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
  
#define SIZE 1000  
  
int main(int argc, char *argv[])   
{  
    int rank, size;  
    int num[SIZE];  
    int l_min, l_max, g_min, g_max; //local_min, local_max, global_min,  
global_max  
    int c_size; //chunk sizwee  
  
    MPI_Init(&argc, &argv);  
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
    MPI_Comm_size(MPI_COMM_WORLD, &size);  
  
    c_size = SIZE / size;  
  
    // Process 0 generates the random numbers  
    if (rank == 0)   
    {  
        srand(time(NULL));  
        for (int i = 0; i < SIZE; i++)   
        {  
            num[i] = rand() % 1000;  // Random numbers between 0 and 999  
        }  
    }  
  
    // Scatter the numbers to all processes  
    int *l_num = malloc(c_size * sizeof(int)); // local_numberss  
    MPI_Scatter(num, c_size, MPI_INT, l_num, c_size, MPI_INT, 0,  
MPI_COMM_WORLD);  
  
    // Each process finds its local min and max  
    l_min = l_num[0];  
    l_max = l_num[0];  
    for (int i = 1; i < c_size; i++)   
    {  
        if (l_num[i] < l_min) l_min = l_num[i];  
        if (l_num[i] > l_max) l_max = l_num[i];  
    }  
  
    // Use MPI_Reduce to find global min and max  
    MPI_Reduce(&l_min, &g_min, 1, MPI_INT, MPI_MIN, 0,  
MPI_COMM_WORLD);  
    MPI_Reduce(&l_max, &g_max, 1, MPI_INT, MPI_MAX, 0,  
MPI_COMM_WORLD);  
  
    // Process 0 prints the final min and max  
    if (rank == 0)   
    {  
        printf("Minimum number: %d\n", g_min);  
        printf("Maximum number: %d\n", g_max);  
    }  
  
    // Free memory and finalize MPI  
    free(l_num);  
    MPI_Finalize();  
  
    return 0;  
}
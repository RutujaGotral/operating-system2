#include <mpi.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#define SIZE 1000  
int main(int argc, char *argv[])   
{  
int rank, size;  
int num[SIZE];  
int l_sum = 0, t_sum = 0; //local sum and total sum  
int c_size; //chucnk size  
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
            num[i] = rand() % 100;  
        }  
    }  
    // Scatter the numbers to all processes  
    int *l_num = malloc(c_size * sizeof(int));// local_numbers  
    MPI_Scatter(num, c_size, MPI_INT,l_num, c_size, MPI_INT,0,  
MPI_COMM_WORLD);  
    // Each process computes its local sum  
    for (int i = 0; i < c_size; i++)   
    {  
        l_sum += l_num[i];  
    }  
    // Gather the local sums and add them together  
    MPI_Reduce(&l_sum, &t_sum, 1, MPI_INT, MPI_SUM, 0,  
MPI_COMM_WORLD);  
    // Process 0 prints the final result  
    if (rank == 0)   
    {  
        printf("Total sum of 1000 random numbers: %d\n", t_sum);  
    }  
    // Free memory and finalize MPI  
    free(l_num);  
    MPI_Finalize();  
    return 0;  
} 
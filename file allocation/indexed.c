#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#define MAX_FILES 10  
#define MAX_BLOCKS 100  
  
int *disk;   
int n;   
char directory[MAX_FILES][30]; // Stores file names  
int file_index_block[MAX_FILES]; // Stores index block for each file  
int file_blocks[MAX_FILES][MAX_BLOCKS]; // Stores block addresses for each file  
  
// Initialize disk  
void initializeDisk()   
{  
    for (int i = 0; i < n; i++)   
    {  
        disk[i] = 0; // Free blocks  
    }  
    for (int i = 0; i < MAX_FILES; i++)   
    {  
        directory[i][0] = '\0'; // Empty directory  
        file_index_block[i] = -1; // No index block assigned  
        for (int j = 0; j < MAX_BLOCKS; j++)   
 {  
            file_blocks[i][j] = -1; // No allocated blocks  
        }  
    }  
}  
  
// Display disk bit vector  
void displayBitVector()   
{  
    printf("\nDisk Bit Vector (0 = Free, 1 = Allocated):\n");  
    for (int i = 0; i < n; i++)   
    {  
        printf("%d ", disk[i]);  
    }  
    printf("\n");  
}  
  
// Create file using indexed allocation  
void createFile()   
{  
    char fileName[30];  
    int numBlocks;  
    printf("\nEnter file name: ");  
    scanf("%s", fileName);  
  
    // Check if file exists  
    for (int i = 0; i < MAX_FILES; i++)   
    {  
        if (strcmp(directory[i], fileName) == 0)   
 {  
            printf("File already exists!\n");  
            return;  
        }  
    }  
  
    printf("Enter number of blocks needed: ");  
    scanf("%d", &numBlocks);  
      
    // Find free index block  
    int indexBlock = -1;  
    for (int i = 0; i < n; i++)   
    {  
        if (disk[i] == 0)   
 {  
            indexBlock = i;  
            disk[i] = 1; // Allocate index block  
            break;  
        }  
    }  
    if (indexBlock == -1)   
    {  
        printf("No free index block available!\n");  
        return;  
    }  
  
    // Allocate file blocks  
    int allocated = 0;  
    for (int i = 0; i < n && allocated < numBlocks; i++)   
    {  
        if (disk[i] == 0)   
 {  
            disk[i] = 1;  
            file_blocks[MAX_FILES][allocated] = i;  
            allocated++;  
        }  
    }  
      
    if (allocated < numBlocks)   
    {  
        printf("Not enough free blocks!\n");  
        disk[indexBlock] = 0; // Free index block  
        return;  
    }  
  
    // Store file details in directory  
    for (int i = 0; i < MAX_FILES; i++)   
    {  
        if (directory[i][0] == '\0')   
 {  
            strcpy(directory[i], fileName);  
            file_index_block[i] = indexBlock;  
            printf("File '%s' created with index block at %d.\n", fileName, indexBlock);  
            return;  
        }  
    }  
    printf("Directory full!\n");  
}  
  
// Show directory  
void showDirectory()   
{  
    printf("\nDirectory:\n");  
    for (int i = 0; i < MAX_FILES; i++)   
    {  
        if (directory[i][0] != '\0')   
 {  
            printf("File: %s, Index Block: %d\n", directory[i], file_index_block[i]);  
        }  
    }  
}  
  
// Delete a file  
void deleteFile()   
{  
    char fileName[30];  
    printf("\nEnter file name to delete: ");  
    scanf("%s", fileName);  
  
    for (int i = 0; i < MAX_FILES; i++)   
    {  
        if (strcmp(directory[i], fileName) == 0)   
 {  
            disk[file_index_block[i]] = 0; // Free index block  
            for (int j = 0; file_blocks[i][j] != -1; j++)   
     {  
                disk[file_blocks[i][j]] = 0; // Free file blocks  
            }  
            directory[i][0] = '\0';  
            file_index_block[i] = -1;  
            printf("File '%s' deleted.\n", fileName);  
            return;  
        }  
    }  
    printf("File not found!\n");  
}  
  
// Main function  
int main()   
{  
    int choice;  
    printf("Enter number of disk blocks: ");  
    scanf("%d", &n);  
    disk = (int *)malloc(n * sizeof(int));  
    if (disk == NULL)   
    {  
        printf("Memory allocation failed!\n");  
        return -1;  
    }  
    initializeDisk();  
      
    do {  
        printf("\nMenu:\n");  
        printf("1. Create file\n");  
        printf("2. Show directory\n");  
        printf("3. Delete file\n");  
        printf("4. Show disk bit vector\n");  
        printf("5. Exit\n");  
        printf("Enter your choice: ");  
        scanf("%d", &choice);  
          
        switch (choice)   
 {  
            case 1: createFile(); break;  
            case 2: showDirectory(); break;  
            case 3: deleteFile(); break;  
            case 4: displayBitVector(); break;  
            case 5: printf("Exiting...\n"); break;  
            default: printf("Invalid choice!\n");  
        }  
    } while (choice != 5);  
      
    free(disk);  
    return 0;  
}
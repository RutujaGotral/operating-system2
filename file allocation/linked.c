//linked file allocation
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#define MAX_FILES 10 
int *disk;  // Array to represent the disk blocks 
int n;  // Number of blocks in the disk 
int *next;  // Array to represent the linked list of blocks (next pointers) 
char directory[MAX_FILES][30];  // Directory to store file names 
int file_start[MAX_FILES];  // Starting block of each file 
// Function to initialize the disk and directory 
void initializeDisk() { 
for (int i = 0; i < n; i++) { 
disk[i] = 0; // 0 means the block is free 
next[i] = -1; // No next block initially 
} 
for (int i = 0; i < MAX_FILES; i++) { 
directory[i][0] = '\0';  // Empty directory entries 
file_start[i] = -1;  // No files yet 
} 
} 
// Function to display the bit vector (disk state) 
void displayBitVector() { 
printf("\nDisk Bit Vector (0 = Free, 1 = Allocated):\n"); 
for (int i = 0; i < n; i++) { 
printf("%d ", disk[i]); 
} 
printf("\n"); 
} 
// Function to create a new file 
void createFile() { 
char fileName[30]; 
int numBlocks; 
printf("\nEnter file name: "); 
scanf("%s", fileName); 
// Check if file already exists 
for (int i = 0; i < MAX_FILES; i++) { 
if (strcmp(directory[i], fileName) == 0) { 
printf("File already exists!\n"); 
            return; 
        } 
    } 
 
    printf("Enter number of blocks needed for the file: "); 
    scanf("%d", &numBlocks); 
 
    // Check if there are enough free blocks 
    int freeBlocks = 0; 
    for (int i = 0; i < n; i++) { 
        if (disk[i] == 0) { 
            freeBlocks++; 
        } 
    } 
    if (freeBlocks < numBlocks) { 
        printf("Not enough free blocks available!\n"); 
        return; 
    } 
 
    // Allocate blocks to the file using linked allocation 
    int startBlock = -1; 
    int prevBlock = -1; 
    for (int i = 0; i < n; i++) { 
        if (disk[i] == 0) { 
            if (startBlock == -1) { 
                startBlock = i; // First block of the file 
            } 
            disk[i] = 1; // Mark the block as allocated 
            if (prevBlock != -1) { 
                next[prevBlock] = i;  // Link the previous block to the current block 
            } 
            prevBlock = i; 
            numBlocks--; 
            if (numBlocks == 0) { 
                next[prevBlock] = -1;  // End of file 
                break; 
            } 
        } 
    } 
 
    // Store the file in the directory 
    for (int i = 0; i < MAX_FILES; i++) { 
        if (directory[i][0] == '\0') { 
strcpy(directory[i], fileName); 
file_start[i] = startBlock; 
printf("File '%s' created successfully starting at block %d.\n", fileName, startBlock); 
return; 
} 
} 
} 
// Function to show the directory (file names and their starting blocks) 
void showDirectory() { 
printf("\nDirectory contents:\n"); 
for (int i = 0; i < MAX_FILES; i++) { 
if (directory[i][0] != '\0') { 
printf("File Name: %s, Start Block: %d\n", directory[i], file_start[i]); 
} 
} 
} 
// Function to delete a file 
void deleteFile() { 
char fileName[30]; 
printf("\nEnter the file name to delete: "); 
scanf("%s", fileName); 
int found = 0; 
for (int i = 0; i < MAX_FILES; i++) { 
if (strcmp(directory[i], fileName) == 0) { 
found = 1; 
int currentBlock = file_start[i]; 
while (currentBlock != -1) { 
disk[currentBlock] = 0;  // Mark the block as free 
int nextBlock = next[currentBlock]; // Get the next block 
next[currentBlock] = -1;  // Clear the next pointer 
currentBlock = nextBlock;  // Move to the next block 
} 
// Clear the file entry in the directory 
directory[i][0] = '\0'; 
file_start[i] = -1; 
printf("File '%s' deleted successfully.\n", fileName); 
break; 
} 
} 
if (!found) { 
printf("File not found!\n"); 
} 
} 
// Main function to handle the menu-driven options 
int main() { 
int choice; 
// Take the number of blocks in the disk as input 
printf("Enter the number of blocks in the disk: "); 
scanf("%d", &n); 
// Dynamically allocate memory for disk and next pointers arrays 
disk = (int *)malloc(n * sizeof(int)); 
next = (int *)malloc(n * sizeof(int)); 
if (disk == NULL || next == NULL) { 
printf("Memory allocation failed!\n"); 
return -1; 
} 
initializeDisk(); 
do { 
printf("\nMenu:\n"); 
printf("1. Create new file\n"); 
printf("2. Show directory\n"); 
printf("3. Delete file\n"); 
printf("4. Show disk bit vector\n"); 
printf("5. Exit\n"); 
printf("Enter your choice: "); 
scanf("%d", &choice); 
switch (choice) { 
case 1: 
createFile(); 
break; 
case 2: 
showDirectory(); 
break; 
case 3: 
deleteFile(); 
break; 
case 4: 
displayBitVector(); 
break; 
case 5: 
printf("Exiting...\n"); 
break; 
default: 
printf("Invalid choice! Please try again.\n"); 
} 
} while (choice != 5); 
// Free the dynamically allocated memory 
free(disk); 
free(next); 
return 0; 
}
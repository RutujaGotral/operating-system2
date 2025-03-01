//fcfs algorithm
#include <stdio.h> 
int main() 
{ 
   int hpos, req[20],i,n,mov=0; 
    printf("Enter the Head Position"); 
    scanf("%d",&hpos); 
    printf("Enter the total no request"); 
    scanf("%d",&n); 
    printf("Enter the Request"); 
    for(i=0;i<n;i++) 
     scanf("%d",&req[i]); 
    for(i=0;i<n;i++)  
    { 
        printf("%d->",hpos); 
        mov =mov + (abs(hpos-req[i])); 
        hpos =req[i]; 
         
    } 
    printf("%d\n",hpos); 
    printf("Total Seek Position :%d",mov); 
}
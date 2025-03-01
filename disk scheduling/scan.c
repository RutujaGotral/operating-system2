//SCAN Disk Scheduling algorithm 
 
#include<stdio.h> 
#include<stdlib.h> 
void scan(int req[],int n,int head,int size,int dir) 
{ 
 int seek=0,i,j,temp,bound=size,start; 
 for(i=0;i<n-1;i++) 
 { 
    for(j=i+1;j<n;j++)  
     {    
        if(req[i]>req[j]) 
  { 
   temp=req[i]; 
   req[i]=req[j]; 
   req[j]=temp; 
  } 
     } 
 } 
 for(start=0;start<n;start++) 
     if(req[start]>=head) 
      { 
 
  break; 
      } 
 printf("seek sequence:%d",head); 
 if(dir==1) 
 { 
  for(i=start;i<n;i++) 
  { 
   seek+=abs(req[i]-head); 
   head=req[i]; 
   printf("->%d",head); 
  } 
  seek+= abs(bound - head); 
  head = bound; 
  printf(" ->%d",head); 
  for(i=start-1;i>=0;i--) 
  { 
   seek+=abs(req[i]-head); 
   head=req[i]; 
   printf("->%d",head); 
  } 
 } 
 else 
 { 
  for(i=start-1;i>=0;i--) 
  { 
   seek+=abs(req[i]-head); 
   head=req[i]; 
   printf("->%d",head); 
  } 
  seek+= abs( head -0); 
  head = 0; 
  printf(" ->%d",head);  
  for(i=start;i<n;i++) 
  { 
   seek+=abs(req[i]-head); 
head=req[i]; 
printf("->%d",head); 
} 
} 
printf("\n Total seek time:%d\n",seek); 
} 
int main() 
{ 
 
int n,head,size,dir,i; 
printf("Enter number of requets:"); 
scanf("%d",&n); 
int req[n]; 
printf("Enter request queue:"); 
for(i=0;i<n;i++) 
scanf("%d",&req[i]); 
printf("Enter disk size:"); 
scanf("%d",&size); 
printf("Enter initial head position:"); 
scanf("%d",&head); 
printf("Enter direction (1  for right,0 for left):"); 
scanf("%d",&dir); 
scan(req,n,head,size,dir); 
return 0; 
}
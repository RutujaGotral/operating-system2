//sstf algorithm
#include<stdio.h> 
#include<stdlib.h> 
int main() 
{ 
 int readyq[100],i,n,totalhead=0,initial,count=0; 
 printf("Enter no of requests"); 
 scanf("%d",&n); 
 printf("Enter no of request sequence"); 
 for(i=0;i<n;i++) 
 { 
  scanf("%d",&readyq[i]); 
 } 
  printf("Enter initial head position"); 
  scanf("%d",&initial); 
  while(count!=n) 
  { 
   int min=1000,diff,index; 
   for(i=0;i<n;i++) 
   { 
    diff=abs(readyq[i]-initial); 
    if(min>diff) 
    { 
     min=diff; 
     index=i; 
    } 
   } 
   totalhead=totalhead+min; 
   initial=readyq[index]; 
   readyq[index]=1000; 
   count++; 
} 
printf("total head movements is %d",totalhead); 
}
//Bankers Algorithm Set-B 
#include<stdio.h> 
int n=5,m=3,j,i,cnt; 
int work[5]; 
int max[][3]={{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}}; 
int allo[][3]={{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}}; 
int need[5][3]; 
int ss[5]; 
int finish[5]; 
int avl[3]; 

void print(int x[7][7]) 
{ 
int i,j; 
for(i=0;i<n;i++) 
{ 
for(j=0;j<m;j++) 
printf("%d\t",x[i][j]); 
printf("\n"); 
} 
} 

main() 
{ 
 int i; 
 char ch; 
  
 printf("allocation matrix\n"); 
 //acceptdata(allo); 
 print(allo); 
 printf("\n\n"); 
 printf("max matrix\n"); 
 //acceptdata(max); 
 print(max); 
 printf("need matrix\n"); 
    computeneed(); 
 print(need); 
 printf("work is\n"); 
 for(i=0;i<m;i++) 
 { 
 scanf("%d",&work[i]); 
    avl[i]=work[i]; 
 } 
  
 checkstate(); 
     printf("Do you want to the request for another process(y/n)"); 
     scanf("\n%c",&ch); 
     if(ch=='y') 
       request(); 
     else 
      return; 
      
} 
 
void computeneed() 
{ 
 int i,j; 
 for(i=0;i<n;i++) 
 
  for(j=0;j<m;j++) 
   need[i][j]=max[i][j]-allo[i][j]; 
} 
 
int checkneed(int i) 
{ 
 int j; 
 cnt=0; 
 for(j=0;j<m;j++) 
  if(need[i][j]<=work[j]) 
   cnt++; 
 if(cnt==m) 
  return 1; 
 else  
  return 0; 
} 
void checkstate() 
{ 
 
 int flag=0; 
 int k=0,cnt=0; 
 for(i=0;i<n;i++) 
  finish[i]=0; 
 while(1) 
 {  flag=0; 
 
  for(i=0;i<n;i++) 
         { 
   if(finish[i]==0) 
    if(checkneed(i)==1) 
    { 
     for(j=0;j<m;j++) 
      work[j]=work[j]+allo[i][j]; 
     finish[i]=1; 
     flag=1; 
     ss[k++]=i; 
    } 
         } 
 if(n==k) 
  { 
   cnt=1; 
   break; 
 
  } 
  if(flag==0) 
  { 
   printf("not in safe state"); 
   break; 
  } 
 } 
 if(cnt==1) 
 { 
  printf("safe sequence is\n"); 
  for(i=0;i<n;i++) 
   printf("P%d\t",ss[i]); 
 
 
 } 
  for(i=0;i<m;i++) 
    work[i]=avl[i]; 
} 
 void request() 
{ 
  int i,req[10],p,flag=0; 
  printf("Enter the Process"); 
  scanf("%d",&p); 
  printf("Enter the request"); 
  for(i=0;i<m;i++) 
  scanf("%d",&req[i]); 
  for(i=0;i<m;i++) 
  { 
      if(req[i]<=need[p][i]) 
      { 
         if(req[i]<=work[i]) 
         { 
         flag=1;           
         } 
         else  
         { 
           
         flag=0; 
         break; 
         } 
      } 
      else 
        { 
            flag=0;  
            break; 
        } 
         
    }  
      if(flag==1) 
       { 
        for(i=0;i<m;i++) 
        { 
          allo[p][i]=allo[p][i]+req[i];  
          need[p][i]=need[p][i]-req[i]; 
          work[i]=work[i]-req[i];        
      } 
          checkstate(); 
       } 
} 
#include<stdio.h>
#include<stdlib.h>

void sender(int,int**);
void receiver(int,int*);
int* bitAdd(int,int**);

int main()
{
   int n,i,j;
   printf("\n\n   - - - - C H E C K S U M - - - - \n\n");
   printf("Enter the no of input : ");
   scanf("%d",&n);
   int **value;
   value=(int**)malloc(n);
   for(i=0;i<8;i++)
       value[i]=(int*)malloc(8);
   for(i=0;i<n;i++)
   {
       printf("%d : ",(i+1));
       for(j=0;j<8;j++)
       {
          scanf("%d",&value[i][j]);  
       }
   }
   sender(n,value);
}

void sender(int n , int **value)
{
    int i,j,*v;
    char  option;
    v =(int*)malloc(8);
    
    v = bitAdd(n,value);
    printf("\n\nAdd         : ");
    for(i=0;i<8;i++)
    {
       printf("%d ",v[i]);
    }
    
    printf("\nSented Data : ");
    for(i=0;i<8;i++)
    {
      if(v[i] == 1)
      {
           v[i] = 0;
      }
      else
      {
           v[i] = 1;
      }
      printf("%d ",v[i]);
   }
   receiver(n,v);
}
void receiver(int n,int* value)
{
   printf("\n\n   - - - - Receiver - - - - \n\nR : ");
   int i,j,count;
   int *v;
   v =(int*)malloc(8);
   for(i=0;i<8;i++)
   {
      printf("%d ",value[i]);
      v[i]=value[i];
   }
   printf("\n");
   int **s;
   s=(int**)malloc(n+1);
   for(i=0;i<=n;i++)
       s[i]=(int*)malloc(8);
   for(i=0;i<n;i++)
   {
      printf("%d : ",i+1);
      for(j=0;j<8;j++)
      {
          scanf("%d",&s[i][j]);
      }
   }
   printf("\nR : ");
   for(i=0;i<8;i++)
   {
       printf("%d ",v[i]);
       s[n][i] = v[i];
   }
   v  = bitAdd(n+1,s);
   printf("\nCheckSum Value : ");
   for(i=0;i<8;i++)
   {
       printf("%d ",v[i]);
   }
   count = 0;
   for(i=0;i<8;i++)
   {
      if(v[i] == 1)
         count++;
   }
   if(count == 8)
      printf("\n\nYour Data is Accept\n");
   else
      printf("\n\nYour Data is Wrong\n");
}
int* bitAdd(int n,int** value)
{
    int i,j,sum,carry,sumBit,c;
    carry = 0;
    int *v=(int*)malloc(n);
    for(i=7;i>=0;i--)
    {
       sum = 0;
       c = carry;
       for(j=0;j<n;j++)
       {
          sum  += value[j][i];
       }
       if(sum == 0)
       {
          sumBit = 0;
          carry = 0;
       }
       else if(sum==1)
       {
           sumBit = 1;
           carry = 0;
       }
       else if(sum%2 == 0)
       {
           sumBit = 0;
           carry = 1;   
       }
       else if(sum%2 != 0)
       {
           sumBit = 1;
           carry = 1;
       }
       sumBit = sumBit + c;

       if(sumBit == 2)
       {
           sumBit = 0;
           carry  = 1;
       }
       v[i] = sumBit;
   }
   return v;
}

#include<stdio.h>
#include<stdlib.h>

void bitStuff(int[],int);
void deStuff(int[],int);
void display(int[],int);

void main()
{
   int n,i;
   printf("\n\n  - - - - Bit Stuffing And Destuffing - - - - \n\n");
   printf("Enter the lenght of data :  ");
   scanf("%d",&n);
   int data[30];
   printf("Enter Your Data : ");

   for( i=0;i<n;i++ )
   {
     scanf("%d",&data[i]);
   }
   printf("\n  Original data  :  ");
   display(data,n);
   bitStuff(data,n);
}

//Function
void display(int value[30],int n)
{
  int i;
  for (i=0;i<n;i++)
  {
    printf("%d ",value[i]);
  }
  printf("\n");
}

void bitStuff(int arr[],int n)
{
   int count,i,j,k,l,m,temp,temp1;
   int flag[8]={0,1,1,1,1,1,1,0};
   int a[30];
    
   for(i=0;i<8;i++)  //front flag
   {
        a[i]=flag[i];
   }
   
   j=0;
   for(i=8;i<n+8;i++)  // data 
   {
       a[i]= arr[j];
       j++;
   }
   
   n=n+8;
   for(i=8;i<n;i++)  //data check
   {
      count=0;
      temp=i;
      if( a[temp]==0 )
      {
         i++;
         for(k=i;k<i+5;k++)
         {
            if(a[k]==1)
            {
                count++;
            }
         }
         if(count==5)
         {
            n++;
            i=i+5;
            k=i;
            temp=a[i];
            a[i]=0;
            for(j=n;j>k;j--)
            {
               a[j+1] = a[j];
            }
            a[i+1]=temp;
         }
      }
   }

   j=0;
   for(i=n;i<n+8;i++) //back flag
   {
      a[i]=flag[j];
      j++;
   }

   n=n+8;
   printf("\n  Sented   data  :  ");
   display(a,n);
   deStuff(a,n);
}
void deStuff(int arr[],int n)
{
  printf("\n  - - - Receiver Received - - - \n");
  int count,i,j,k,m,temp;
  int data[30];
  
  j=0;
  for(i=8;i<n-8;i++)  //Remove Frond and back flag
  {
      data[j]=arr[i];
      j++;
  }
  
  n=n-16;
  for(i=0;i<n;i++)  //Check the data
  {
      count=0;
      temp=i;
      if( data[temp]==0 )
      {
          i++;
          for(k=i;k<i+5;k++)
          {
             if(data[k]==1)
             {
                count++;
             }
          }

          if(count==5)
          {
             i=i+5;
             k=i;
             for(j=k+1;j<n;j++)
             {
                 data[j-1] = data[j];
             }
             n--;
          }
      }
  }
  
  printf("\n  received data : ");
  display(data,n);
  printf("\n");  
}

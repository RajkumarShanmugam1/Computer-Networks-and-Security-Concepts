#include<stdio.h>
#include<stdlib.h>

void byteStuff(int[],int);
void deStuff(int[],int);
void display(int[],int);

int main()
{
   int n,i,data[40];
   printf("\n\n    - - - - Byte Stuffing and Destuffing - - - -    \n\n");
   printf(" Enter the lenght of data : ");
   scanf("%d",&n);
   if(n%8 == 0)
   {
      printf(" Enter Your Data : ");
      for( i=0;i<n;i++ )
      {
          scanf("%d",&data[i]);
      }
      printf("\n Original Data :  ");
      display(data,n);
      byteStuff(data,n);
   }
   else
   {
     printf("\n Please Try Again . . . \n Please put lenght in [ 8 ,16 ,32 ,..] \n\n");
   }
}

void display(int data[],int n)
{
   int i,count=0;
   for(i=0;i<n;i++)
   {
       printf("%d ",data[i]);
       count++;
       if(count==8)
       {
           count=0;
           printf("  ");
       }
   }
   printf("\n"); 
}

void byteStuff(int data[],int n)
{
    int count,k,temp,x,m,j,i,temp2;
    x = 0;
    int flag[8]={0,1,1,1,1,1,1,0};
    int escape[8]={0,1,1,1,1,1,0,1};
    int a[80];
  
   
   for(i=0;i<8;i++)  //Frond flag
   {
        a[i]=flag[i];
   }
   j=0;
   for(i=8;i<n+8;i++) //data
   {
       a[i]= data[j];
       j++;
   }
   n=n+8;

   for(i=8;i<n;x++) //Escape check
   {
       count=0;
       temp=i;
       if( a[temp]==0 )
       {
           for(k=i+1;k<i+6;k++)
           {
              if(a[k]==1)
              {
                 count++;
              }
           }
           if(count==5)
           {
               k=i+6;
               if( ( a[k]==0 && a[k+1]==1 ) || ( a[k]==1 && a[k+1]==0 ))
               {
                  for(j=n;j>i-1;j--)
                  {
                      a[j+8]= a[j];
                  }
                  temp2=0;
                  for(j=i;j<i+8;j++)
                  {
                      a[j]=escape[temp2];
                      temp2++;
                  }
		  i=i+8;
		  n=n+8;
                }
           }
       }
       i=i+8;
    }

    j=0;
    for(i=n;i<n+8;i++) //Back flag
    {
       a[i]=flag[j];
       j++;
    }

    n=n+8;
    printf("\n Sented Data  : ");
    display(a,n);
    deStuff(a,n);
}

void deStuff(int arr[],int n)
{
    printf("\n - - - Data Received - - -\n");
    int count,k,temp,m,x,j,i,temp2;
    int data[80];
    x=0;
    j=0;
    for(i=8;i<n-8;i++) //remove front and back flag
    {
        data[j]=arr[i];
        j++;
    }
    n=n-16;
   
   for(i=0;i<n;x++) //Escape sequence process
   {
      count=0;
      temp=i;
      if( data[temp]==0 )
      {   
         for(k=i+1;k<i+6;k++)
         {
            if(data[k]==1)
            {
               count++;
            }
         }
         if(count==5)
         {
	    k=i+6;
            if( data[k]==0 && data[k+1]==1 )
            {
               for(j=i;j<n;j++)
               {
	           data[j]=data[j+8];
               }
               n=n-8;
            }
         }
      }
      i=i+8;
   }
   printf("\n\n Received data : ");
   display(data,n);
   printf("\n\n");
}

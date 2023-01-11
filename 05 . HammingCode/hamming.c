#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int check_parity(int n,int i,int code[])        
{
    int p=0,k,j;
    for(j=i;j<=n;j=k+i)
    {
        for(k=j;k<j+i && k<=n;k++)
        {                    
            if(code[k]==1)
               p++;
        }
    }
    if(p%2==0)
        return 0;        
    else 
        return 1;        
}

void hamming_code(int data[], int num)
{
    int i,r=0,m=0,n,j=1,c,code[50];    
    while((r+num+1)>(pow(2,r)))            
        r++;
    n=num+r;                    
    for(i=1;i<=n;i++)
    {
        if(i==pow(2,m) && m<=r)
        {
            code[i]=0;            
            m++;
        }
        else
        {
            code[i]=data[j];        
            j++;
        }
    }

    m=0;
    for(i=1;i<=n;i++)
    {
        if(i==pow(2,m) && m<=r)            
        {
            c=check_parity(n,i,code);
            code[i]=c;
            m++;
        }
    }

    printf("\n\nHamming  code   : ");
    for(i=n;i>0;i--)
    	printf(" %d",code[i]);
    printf("\n\nEnter Your code : ");
    for(i=n;i>0;i--)
    	scanf(" %d",&code[i]);
    m=j=c=0;
    for(i=1;i<=n;i++)
    {
        if(i==pow(2,m) && m<=r)
        {
            c=c+(pow(2,j)*check_parity(n,i,code));    
            j++;
            m++;
        }
    }
    if(c==0)
        printf("\nNo Error\n");
    else
    {
        printf("\nError in %d position ",(n-c)+1);
	printf("\nCorrected code : ");
        if(code[c]==1)
            code[c]=0;
        else
            code[c]=1;
        for(i=n;i>0;i--)
            printf("%d ",code[i]);
        printf("\n\n");
    }
}

int main()
{
    int data[50], num,i;

    printf("\nEnter no.of.bits : ");
    scanf("%d",&num);
    printf("\nEnter data       : ");
    for(i=num;i>0;i--)
       scanf("%d",&data[i]);
    hamming_code(data, num);
    return 0;
}

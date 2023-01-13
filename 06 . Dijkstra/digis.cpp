#include<iostream>
#include<stdio.h>
using namespace std;
#include<limits.h>
int minDistance(int dist[],bool *visited,int n)
{
  int min_index,min=INT_MAX;
  for(int i=0;i<n;i++)
  {
      if(visited[i]==false && dist[i]<=min)
      {
        min=dist[i];
        min_index=i;
      }
  }
  return min_index;
}
void printPath(int parent[], int j)
{
    if (parent[j] == -1)
        return;
   
    printPath(parent, parent[j]); 
    printf("-%d", j);
}
void display_sortest_distances(int array[],int parent[],int src,int n)
{
    for(int i=0;i<n;i++)
    {
      cout<<"\nMin distance of node"<<(i)<<" : "<<array[i];
      cout<<"\nPath : ";
      cout<<src;
      printPath(parent,i);
      cout<<"\n";
    }
    cout<<"\n";
}
void dijkstra(int **wm,int src,int n)
{
   int max[n];
   int parent[n];
   bool *visited=new bool[n];
   int i;
   parent[src]=-1;
   for(i=0;i<n;i++)
   {
    visited[i]=false; 
    max[i]=INT_MAX;
   }
   max[src]=0;
   for(int count=0;count<n-1;count++)
   {
       int u=minDistance(max,visited,n);
       visited[u]=true;
       for(int v=0;v<n;v++)
       {
           if (!visited[v] && wm[u][v] && max[u] != INT_MAX
                && (max[u] + wm[u][v]) < max[v])
           {
                parent[v]=u;
                max[v] = max[u] + wm[u][v];
           }
       }
   }
   display_sortest_distances(max,parent,src,n);
}
int main()
{
  cout<<"\nEnter No.of.vertices : ";
  int n;
  cin>>n;
  int **matrix=new int*[n];
  int i,j;
  for(i=0;i<n;i++)
  {
   matrix[i]=new int[n];
   for(j=0;j<n;j++)
   {
        matrix[i][j]=0;
   }
  }
  int m,u,v,w;
  cout<<"Enter No.of.edges    : ";
  cin>>m;
  cout<<"\n";
  for(i=0;i<m;i++)
  {
      cout<<"Enter u ,v and w [edge "<<i<<" ]: ";
      cin>>u;
      cin>>v;
      cin>>w;
      matrix[u][v]=w;
      matrix[v][u]=w;
  }
  int src;
  cout<<"Enter Starting Node : ";
  cin>>src;
  cout<<"\n";
  dijkstra(matrix,src,n);
}

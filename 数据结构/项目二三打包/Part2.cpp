#include<stdio.h>
#define MAXN 27
using namespace std;
int a[MAXN];//0 1 2 ---n
int maxv[MAXN];//0 OR 1
int num[MAXN];
int N,M,mincost;
int dfs(int n,int sum)
{
    if (n==N+1)
    {   
       if(sum >= M) 
	   {
	   	
       		if (sum < mincost) 	mincost = sum;
	   }
       return 0;
    }
    for(int i = 0; i <= maxv[n]; i++)
    {
        a[n] = i;
        dfs(n+1,sum + num[n]*a[n]);
        a[n] = 0;
    }
    return 0;
}
 
int main()
{
    scanf("%d%d",&N,&M);//3  20 
    for (int i=1; i<=N; i++)
    	scanf("%d%d",&num[i],&maxv[i]);
    mincost = 0x7FFFFFFF;
    dfs(1,0);
    if (mincost == 0x7FFFFFFF) 
		printf("无法满足最低需求");
    else
		printf("%.2lf\n",mincost*0.01);
    return 0;
}

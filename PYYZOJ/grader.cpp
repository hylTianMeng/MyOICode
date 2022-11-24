#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include<vector>
#include"poison.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;
static int n,m,k,t,p;
static bool flag[25],f[25];
static int calc(int s)
{
	int ans=0;
	while(s)
	{
		if(s&1)ans++;
		s>>=1;
	}
	return ans;
}
void feed(int i,int j)
{
	assert(i>=0&&i<n);
	assert(j>=0&&j<m);
	assert(flag[j]==0);
	if(i==p)f[j]=1;
}
int done()
{
	t--;
	if(t<0)
	{
		printf("Too many queries.\n");
		exit(0);
	}
	int rest=0,s=0;
	for(int i=0;i<m;i++)
	{
		flag[i]|=f[i],f[i]=0;
		if(flag[i]==0)rest++,s|=(1<<i);
	}
	if(rest<k)
	{
		printf("Too many deaths.\n");
		exit(0);
	}
	return s;
}
int main()
{
	assert(scanf("%d%d%d%d",&n,&m,&k,&t)==4);
	p=rand()%n;
	int ans=solve(n,m,k,t);
	if(ans==p)printf("Correct.\n");
	else printf("Wrong Answer.\n");
	return 0;
}

#ifdef __cplusplus
}
#endif

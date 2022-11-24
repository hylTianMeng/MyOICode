#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cassert>
#include"interact.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace std;
static int n,root,a[6],pa[100005],lc[100005],rc[100005],dfn[100005],L[100005],R[100005];
static int ind,tot;
static bool flag[100005];
static bool needoutput;
static void dfs(int node)
{
	if(!node)return;
	L[node]=ind+1;
	dfs(lc[node]);
	dfn[node]=++ind;
	dfs(rc[node]);

	R[node]=ind;
}
bool query(int x,int l,int r)
{
	assert(x>=1&&x<=n);
	assert(l>=1&&l<=n);
	assert(r>=1&&r<=n);
	assert(l<=r);
	++tot;
	if(tot>a[1])
	{
		printf("Error. Too many queries.\n");
		exit(0);
	}
	if(L[x]==l&&R[x]==r)
	{
		if(needoutput)printf("Query (%d, %d, %d), return True.\n",x,l,r);
		return 1;
	}
	else
	{
		if(needoutput)printf("Query (%d, %d, %d), return False.\n",x,l,r);
		return 0;
	}
}
void report(int x,int y)
{
	assert(x>=1&&x<=n);
	assert(y>=1&&y<=n);
	assert(x!=y);
	if(pa[x]!=y)swap(x,y);
	if(x!=root&&pa[x]==y&&!flag[x])
	{
		flag[x]=1;
		if(needoutput)printf("Successfully reported (%d, %d).\n",x,y);
		return;
	}
	if(pa[x]!=y||x==root)
	{
		printf("Error. Edge (%d, %d) doesn't exist.\n",x,y);
		exit(0);
	}
	if(flag[x])
	{
		printf("Error. Edge (%d, %d) has already been reported.\n",x,y);
		exit(0);
	}
}
int main(int argc,char*argv[])
{
	if(argc>1&&strcmp(argv[1],"-s")==0)needoutput=1;
	assert(scanf("%d%d%d%d%d",&a[1],&a[2],&a[3],&a[4],&a[5])==5);
	assert(scanf("%d",&n)==1);
	for(int i=1;i<=n;i++)
	{
		assert(scanf("%d%d",&lc[i],&rc[i])==2);
		flag[lc[i]]=flag[rc[i]]=1;
		pa[lc[i]]=pa[rc[i]]=i;
	}
	root=1;
	while(flag[root])root++;
	dfs(root);
	memset(flag,0,sizeof(flag));
	guess(n);
	for(int i=1;i<=n;i++)
	{
		if(!flag[i]&&i!=root)
		{
			printf("Error. Edge (%d, %d) not reported.\n",i,pa[i]);
			return 0;
		}
	}
	static int ans=0;
	while(ans<5&&tot<=a[ans+1])ans++;
	printf("OK. T=%d, score=%dx\n",tot,ans*2);
	return 0;
}

#ifdef __cplusplus
}
#endif

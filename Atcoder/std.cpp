#include<bits/stdc++.h>
using namespace std;
struct tree
{
	int son[3],ed,tag;bool flag;
}tr[1000005];
int tot,n,p[15],ans[1000005];char s[200005];
void insert(int x)
{
	int u=0,now=x;
	for(int i=1;i<=n;i++)
	{
		int ch=x%3;x/=3;
		if(!tr[u].son[ch])tr[u].son[ch]=++tot;
		u=tr[u].son[ch];
	}
	tr[u].ed=now;tr[u].flag=1;
}
void pushdown(int u)
{
	if(!tr[u].tag)return;
	swap(tr[u].son[1],tr[u].son[2]);
	tr[tr[u].son[0]].tag^=1;
	tr[tr[u].son[1]].tag^=1;
	tr[tr[u].son[2]].tag^=1;
	tr[u].tag=0;
}
void change(int u)
{
	if(tr[u].flag)return;
	pushdown(u);
	swap(tr[u].son[0],tr[u].son[1]);
	swap(tr[u].son[0],tr[u].son[2]);
	change(tr[u].son[0]);
}
void dfs(int u,int val,int dep)
{
	if(tr[u].flag){ans[tr[u].ed]=val;return;}
	pushdown(u);
	dfs(tr[u].son[0],val,dep+1);
	dfs(tr[u].son[1],val+p[dep],dep+1);
	dfs(tr[u].son[2],val+p[dep]*2,dep+1); 
}
int main()
{
    freopen("my.in","r",stdin);
    freopen("std.out","w",stdout);
	scanf("%d",&n);p[0]=1;
	for(int i=1;i<=n;i++)p[i]=p[i-1]*3;
	for(int i=0;i<p[n];i++)insert(i);
	scanf("%s",s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)
	{
		if(s[i]=='S')tr[0].tag^=1;
		else change(0);
	}
	dfs(0,0,0);
	for(int i=0;i<p[n];i++)printf("%d ",ans[i]); 
	return 0;
}
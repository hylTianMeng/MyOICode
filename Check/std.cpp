#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	int y=0;char z[70];
	while(x){
		z[y++]=x%10+48;
		x/=10;
	}
	while(y--) putchar(z[y]);
}
const int N=5e3+5,mod=998244353;
int n,f[N][N],g[N],a[N];
int fac[N<<1],inv[N<<1];
vector<int>G[N];
int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=(res*x)%mod;
		x=(x*x)%mod;
		y>>=1; 
	} 
	return res;
}
int C(int x,int y){
	if(!y) return 0;
	else return ((fac[x]*inv[y])%mod*inv[x-y])%mod;
}
int Catalan(int x){
	if(x<=1) return 1;
	else return C(x<<1,x)-C(x<<1,x+1);
}
int siz[N];
void dfs(int x,int y){
	f[x][1]=g[x]=siz[x]=1;
	for(int u:G[x]){
		if(u==y) continue;
		dfs(u,x);
		memset(a,0,sizeof a);
		for(int i=0;i<=siz[x];i++) a[i]=(f[x][i]*f[u][0])%mod;
		for(int i=1;i<=siz[u];i++) a[i+1]=(a[i+1]+(f[u][i]*g[x])%mod)%mod;
		g[x]=(g[x]*f[u][0])%mod;
		for(int i=1;i<=siz[x];i++){
			for(int j=1;j<=siz[u];j++){
				if((i+j)&1) continue;
				a[0]=(a[0]+((f[x][i]*f[u][j])%mod*Catalan((i+j>>1)-1))%mod)%mod;
			} 
		}
		for(int i=0;i<=n;i++) f[x][i]=(a[i]+mod)%mod;
		siz[x]+=siz[u];
	}
	for(int i=0;i<=siz[x];i++){
		printf("f[%d][%d]=%d\n",x,i,f[x][i]);
	}
}
signed main(){
  freopen("my.in","r",stdin);
  freopen("std.out","w",stdout);
	n=read();
	for(int i=1,x,y;i<n;i++){
		x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=(fac[i-1]*i)%mod;
	inv[n]=ksm(fac[n],mod-2);
	for(int i=n-1;i>=1;i--) inv[i]=(inv[i+1]*(i+1))%mod;
	dfs(1,0);
	printf("%d\n",f[1][0]);
	// write(f[1][0]);
}
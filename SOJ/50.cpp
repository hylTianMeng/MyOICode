#include<bits/stdc++.h>
#define mset(a,b) memset((a),(b),sizeof((a)))
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dec(i,l,r) for(int i=(r);i>=(l);i--)
#define cmax(a,b) (((a)<(b))?(a=b):(a))
#define cmin(a,b) (((a)>(b))?(a=b):(a))
#define Next(k) for(int x=head[k];x;x=li[x].next)
#define vc vector
#define ar array
#define pi pair
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define N 61
#define M number
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;
const int mod=998244353;

template<typename T> inline void read(T &x) {
	x=0; int f=1;
	char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x*=f;
}

int n,m,K,w;
int vis[N][N][N],val[N][N][N];
int ans[N][N][N];
int up[N][N][N],dn[N][N][N];
int mup[N][N],mdn[N][N],sm[N][N];

inline int ksm(int a,int b,int mod){
	int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}
inline void init(){
	rep(i,1,K)rep(j,1,n)rep(k,1,m){
		up[i][j][k]=up[i-1][j][k]+1;
		if(!vis[i][j][k]) up[i][j][k]=0;
	}
	dec(i,1,K)rep(j,1,n)rep(k,1,m){
		dn[i][j][k]=dn[i+1][j][k]+1;
		if(!vis[i][j][k]) dn[i][j][k]=0;
	}
}
inline void solve(){
	int nsum=0;
	rep(i,1,K)rep(j,1,n)rep(k,1,m){
		rep(jj,j-1,n) mup[jj][k-1]=mdn[jj][k-1]=INF;
		rep(kk,k-1,m) mup[j-1][kk]=mdn[j-1][kk]=INF;
		rep(jj,j-1,n)rep(kk,k-1,m) sm[jj][kk]=0;
		rep(jj,j,n)rep(kk,k,m){
			mup[jj][kk]=min(up[i][jj][kk],min(mup[jj-1][kk],mup[jj][kk-1]));
			mdn[jj][kk]=min(dn[i][jj][kk],min(mdn[jj-1][kk],mdn[jj][kk-1]));
		}
		rep(jj,j,n)rep(kk,k,m){
			nsum=(nsum+mup[jj][kk]);
			int now=mup[jj][kk]*mdn[jj][kk];
			if(!now) break;
			sm[j][k]+=now;
			sm[jj+1][kk+1]+=now;
			sm[jj+1][k]-=now;
			sm[j][kk+1]-=now;
		}
		rep(jj,j,n)rep(kk,k,m){
			(sm[jj][kk]+=sm[jj-1][kk]+sm[jj][kk-1]-sm[jj-1][kk-1]);
			(ans[i][jj][kk]+=sm[jj][kk]);
		}
		
	}
	int Ans=0;
	int sum=1ll*n*(n+1)*m*(m+1)*K*(K+1)%mod;
	sum=1ll*sum*inv(8)%mod;
	// printf("sum=%d\n",sum);
	sum=ksm(sum,w,mod);
	sum=inv(sum);
	rep(i,1,K)rep(j,1,n)rep(k,1,m){
		Ans=(Ans+1ll*(ksm(nsum,w,mod)-ksm(nsum-ans[i][j][k],w,mod))%mod*val[i][j][k]%mod*sum%mod)%mod;
		// Ans=(Ans+(ksm(nsum,w,mod)-ksm(nsum-ans[i][j][k],w,mod))%mod*val[i][j][k]%mod)%mod;
	}
	printf("%d\n",(Ans+mod)%mod);
}

signed main(){
	// freopen("my.in","r",stdin);
	// freopen("my.out","w",stdout);
	read(n);read(m);read(K);read(w);
	rep(i,1,n)rep(j,1,m)rep(k,1,K) read(vis[k][i][j]);
	rep(i,1,n)rep(j,1,m)rep(k,1,K) read(val[k][i][j]);
	init();
	solve();
	return 0;
}
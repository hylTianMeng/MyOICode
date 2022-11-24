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
#define N 210
#define M number
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
#define int long long
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,m,K,Q,c[N][N],f[N][N];

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    mset(f,INF);read(n);read(m);read(K);read(Q);
    rep(i,1,m){
        int u,v,w;read(u);read(v);read(w);
        cmin(f[u][v],w);c[u][v]=1;
    }
    rep(i,1,n) f[i][i]=0,c[i][i]=1;
    rep(k,1,n)rep(i,1,n)rep(j,1,n){
        f[i][j]=cmin(f[i][j],f[i][k]+f[k][j]);
        c[i][j]|=(c[i][k]&c[k][j]);
    }
    int ans=0,Ans=0;
    rep(i,1,Q){
        int a,b;read(a);read(b);
        int ans1=0,Ans1=INF;
        bool op=0;
        rep(j,1,K){
            if(c[a][j]&&c[j][b]) op=1;
            cmin(Ans1,f[a][j]+f[j][b]);
        }
        // printf("a=%d b=%d Ans1=%d\n",a,b,Ans1);
        if(op){
            ans++;
            Ans+=Ans1;
        }
    }
    printf("%lld\n%lld\n",ans,Ans);
    return 0;
}
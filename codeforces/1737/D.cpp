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
#define N 510
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

const int INF=1e18;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int f[N][N],n,m,t;
struct edge{
    int u,v,w;
}li[N*N];

signed main(){
    // freopen("my.in","r",stdin);
    read(t);
    while(t--){
        read(n);read(m);
        rep(i,1,n)rep(j,1,n) f[i][j]=INF;
        rep(i,1,n) f[i][i]=0;
        rep(i,1,m){
            read(li[i].u);read(li[i].v);read(li[i].w);
            int u=li[i].u,v=li[i].v;
            f[u][v]=f[v][u]=1;
        }
        rep(k,1,n)rep(i,1,n)rep(j,1,n) cmin(f[i][j],f[i][k]+f[k][j]);
        int Ans=INF;
        rep(i,1,m){
            int now=min(f[li[i].u][1]+f[li[i].v][n],f[li[i].u][n]+f[li[i].v][1]);
            rep(j,1,n){
                cmin(now,min(f[li[i].u][j],f[li[i].v][j])+1+f[j][1]+f[j][n]);
            }
            Ans=min(Ans,(now+1)*li[i].w);
            // printf("i=%d now=%lld\n",i,now);
        }
        printf("%lld\n",Ans);
    }

    return 0;
}
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
#define N 16
#define M 40010
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
//#define int long long
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

int t,n,a[N],f[M][N][N],b[M],sum[M],tot;
vi v[N];
P g[M][N][N];

inline int lowbit(int x){return x&(-x);}
inline void Solve(int i,int j,int k){
    if(!i||!j||!k) return;
    P now=g[i][j][k];
    int T=now.fi^i;rep(o,0,n-1) if(((T>>o)&1)&&o+1!=k){
        v[k].pb(o+1);
        // printf("k=%d i=%d\n",k,o+1);
    }
    Solve(now.fi,j-1,now.se);
}
inline int ID(int x){
    int cnt=0;rep(i,1,x) if(a[i]) cnt++;return cnt;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    rep(i,0,15) b[(1<<i)]=i;
    read(t);
    while(t--){
        read(n);rep(i,1,n) read(a[i]);
        rep(i,0,(1<<n)-1)rep(j,0,n)rep(k,0,n) f[i][j][k]=INF,g[i][j][k]=mp(-1,-1);
        rep(i,0,(1<<n)-1) sum[i]=0;
        rep(i,0,15) v[i].clear();
        f[0][0][0]=0;
        rep(i,0,(1<<n)-1)rep(j,0,n-1) if((i>>j)&1) sum[i]+=a[j+1];
        rep(i,0,(1<<n)-1)rep(j,0,n)rep(k,0,n)if(f[i][j][k]!=INF){
            // printf("i=%d j=%d k=%d\n",i,j,k);
            int S=((1<<n)-1)^i;
            for(int T=S;T;T=S&(T-1)){
                // printf("T=%d\n",T);
                // printf("T>>k=%d\n",(T>>k));
                if(!(T>>k)) continue;
                // printf("T=%d\n",T);
                if(sum[T]<=f[i][j][k]) continue;
                int tt=T>>(k);int posi=b[lowbit(tt)];
                // cmin(f[i|T][j+1][posi+(k)+1],sum[T]);
                if(f[i|T][j+1][posi+k+1]>sum[T]){
                    f[i|T][j+1][posi+k+1]=sum[T];g[i|T][j+1][posi+k+1]=mp(i,k);
                }
                // g[i|T][j+1][posi+k+1]=mp(i,k);
                // printf("f[%d][%d][%d]=%d\n",i|T,j+1,posi+k+1,f[i|T][j+1][posi+k+1]);
            }
        }
        int ans=-1;tot=0;
        bool op=0;
        dec(i,1,n){
            rep(j,1,n) if(f[(1<<n)-1][i][j]!=INF){
                Solve((1<<n)-1,i,j);
                ans=i;op=1;break;
            }
            if(op) break;
        }
        // printf("ans=%d\n",ans);
        printf("%d\n",n-ans);
        rep(i,1,n){
            if(!v[i].size()) continue;
            for(int x:v[i]){
                int nowi=ID(x);int nowj=ID(i);
                printf("%d %d\n",nowi,nowj);a[x]=0;
            }
        }
    }
    return 0;
}
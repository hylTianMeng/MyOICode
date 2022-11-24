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
#define N 121
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

int Q,t,x,y;
int a[N][N];

inline void Calc(int x,int y,int c){
    rep(i,0,min(120ll,x+y)){
        rep(j,0,min(120ll,x+y)){
            a[i][j]=0;
        }
    }
    a[0][0]=c;
    rep(i,0,x+y-1){
        // printf("i=%lld\n",i);
        rep(j,max(i-119ll,0ll),min(119ll,i)){
            int nowx=j,nowy=i-j;
            // printf("a[%lld][%lld]=%lld\n",nowx,nowy,a[nowx][nowy]);
            if(a[nowx][nowy]){
                if(nowx<119) a[nowx+1][nowy]+=a[nowx][nowy]/2;
                if(nowy<119) a[nowx][nowy+1]+=(a[nowx][nowy]+1)/2;
                a[nowx][nowy]=0;
            }
        }
    }
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(Q);
    while(Q--){
        read(t);read(x);read(y);
        if(t<x+y){puts("NO");continue;}
        Calc(x,y,t-x-y);int nowa=a[x][y];
        Calc(x,y,t-x-y+1);int nownowa=a[x][y];
        // printf("nowa=%lld nownowa=%lld\n",nowa,nownowa);
        if(nowa==nownowa){
            puts("NO");
        }
        else puts("YES");
    }
    return 0;
}
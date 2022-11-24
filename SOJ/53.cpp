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
#define N 100010
#define M number
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

int n,m,fa[N][21],dep[N],su[N][21],v[N];
char s[N];
vi e[N];

inline void dfs(int k,int fat){
    dep[k]=dep[fat]+1;
    fa[k][0]=fat;
    rep(i,1,20) fa[k][i]=fa[fa[k][i-1]][i-1];
    su[k][0]=v[k]|v[fat];
    rep(i,1,20){
        su[k][i]=su[k][i-1]|su[fa[k][i-1]][i-1];
    }
    for(int to:e[k])if(to!=fat){
        dfs(to,k);
    }
}
inline int ge(int a,int b){
    int val=v[a]|v[b];
    if(dep[a]<dep[b]) swap(a,b);
    dec(i,0,20) if(dep[fa[a][i]]>=dep[b]){
        val|=su[a][i];a=fa[a][i];
    }
    if(a==b) return val;
    dec(i,0,20){
        if(fa[a][i]!=fa[b][i]){
            val|=su[a][i];val|=su[b][i];
            a=fa[a][i],b=fa[b][i];
        }
    }
    val|=su[a][0];val|=su[b][0];
    return val;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    scanf("%s",s+1);
    rep(i,1,n){
        if(s[i]=='H') v[i]=1;
        else v[i]=2;
    }
    rep(i,1,n-1){
        int u,v;read(u);read(v);e[u].pb(v);e[v].pb(u);
    }
    dfs(1,0);
    rep(i,1,m){
        int a,b;read(a);read(b);
        int val=ge(a,b);
        char c[2];scanf("%s",c);
        int now=0;
        if(c[0]=='H') now=1;
        else now=2;
        if((val&now)!=0) putchar('1');
        else putchar('0');
    }
    return 0;
}
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
#define N 1010
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

int n;
struct Node{
    int id,x;
    inline bool operator < (const Node &b)const{return x>b.x;}
}p[N][N];
int ans[N],L[N],rp[N*N];
bool vis[N];

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n)rep(j,1,n+1) read(p[i][j].x),p[i][j].id=(i-1)*(n+1)+j,rp[(i-1)*(n+1)+j]=p[i][j].x;
    rep(i,1,n) sort(p[i]+1,p[i]+n+2);
    rep(i,1,n) L[i]=2;
    rep(i,1,n){
        int maxx=-1,id=-1;
        rep(j,1,n) if(!vis[j]){
            if(maxx<p[j][L[j]].x) maxx=p[j][L[j]].x,id=j;
        }
        vis[id]=1;ans[id]=L[id];
        rep(j,1,n) if(!vis[j]) L[j]++; 
    }
    rep(i,1,n){
        int u=p[i][ans[i]].id,v=p[i][ans[i]-1].id;
        printf("%d %d ",min(u,v),max(u,v));
    }
    // puts("");
    // rep(i,1,n){
    //     int u=p[i][ans[i]].id,v=p[i][ans[i]-1].id;
    //     printf("%d %d ",rp[min(u,v)],rp[max(u,v)]);
    // }
    return 0;
}
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
#define N 5010
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

int n,m,x[N],p[N],sum,last,minn,maxx;
bool vis[N];


signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    rep(i,1,n){
        read(x[i]);read(p[i]);
    }
    if(x[n]-x[1]>m){puts("-1");return 0;}
    minn=1;maxx=n;
    rep(i,1,n){
        // printf("i=%d\n",i);
        int ans=INF,Ans=-1;
        rep(j,1,n){
            if(vis[j]) continue;
            // printf("j=%d\n",j);
            int nowans=0;
            if(i!=1) nowans=abs(x[j]-x[last]);
            // printf("nowans=%d\n",nowans);
            nowans+=min(x[j]-x[minn],x[maxx]-x[j])+x[maxx]-x[minn];
            // printf("nowans=%d\n",nowans);
            if(nowans+sum<=m){
                if(ans>p[j]){
                    ans=p[j];Ans=j;
                }
            }
        }
        assert(p[Ans]==ans);
        assert(ans<=n);
        ans=Ans;
        // printf("ans=%d\n",ans);
        vis[ans]=1;
        printf("%lld ",p[ans]);
        if(i!=1) sum+=abs(x[last]-x[ans]);
        last=ans;
        while(vis[minn]) minn++;
        while(vis[maxx]) maxx--;
        // printf("sum=%d\n",sum);
    }
    return 0;
}
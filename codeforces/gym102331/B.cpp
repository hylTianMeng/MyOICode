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
#define N 300010
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
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,X,a[N],f[N];

struct Trie{
    struct Node{
        int ch[2],val;
        inline Node(){ch[0]=ch[1]=0;val=0;}
        inline int operator [] (int id){return ch[id];}
    }p[N*60];
    int tot;
    inline Trie(){
        tot=1;
    }
    inline void Insert(int x,int v){
        int now=1;
        dec(i,0,60){
            int k=(x>>i)&1;
            if(!p[now][k]) p[now].ch[k]=++tot;
            p[now].val=(p[now].val+v)%mod;
            now=p[now][k];
        }
        p[now].val=(p[now].val+v)%mod;
    }
    inline int Ask(int x){
        int ans=0,now=1;
        dec(i,0,60){
            if(!now) break;
            int xk=(X>>i)&1;
            int aik=(x>>i)&1;
            if(!xk){
                (ans+=p[p[now][aik^1]].val)%=mod;
                now=p[now][aik];
            }
            else{
                now=p[now][aik^1];
            }
        }
        ans=(ans+p[now].val)%mod;
        return ans;
    }
}tr;

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(X);rep(i,1,n) read(a[i]);
    sort(a+1,a+n+1);
    rep(i,1,n){
        f[i]=(tr.Ask(a[i])+1)%mod;
        tr.Insert(a[i],f[i]);
    }
    int ans=0;
    rep(i,1,n){
        ans=(ans+f[i])%mod;
        // printf("f[%lld]=%lld\n",i,f[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
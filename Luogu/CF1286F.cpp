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
#define N 21
#define M 2000100
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

int n,a[N],f[M],lg[M],b[N],bt,sum[M];

inline vi Get(int nl,int nr){
    vi v;v.clear();
    if(nl==nr){
        if(b[nl]>0){v.pb(-b[nl]);v.pb(b[nl]);}
        else{v.pb(b[nl]);v.pb(-b[nl]);}return v;
    }
    v=Get(nl+1,nr);
    vi v1,v2;v1.clear();v2.clear();
    rep(i,0,(int)v.size()-1) v1.pb(v[i]-b[nl]);
    rep(i,0,(int)v.size()-1) v2.pb(v[i]+b[nl]);
    vi now;now.clear();
    int l=0,r=0;
    while(l<(int)v1.size()&&r<(int)v2.size()){
        if(v1[l]<v2[r]) now.pb(v1[l]),l++;
        else now.pb(v2[r]),r++; 
    }
    // printf("now.size()=%d l=%d r=%d\n",now.size(),l,r);
    while(l<(int)v1.size()) now.pb(v1[l]),l++;
    while(r<(int)v2.size()) now.pb(v2[r]),r++;
    // printf("v1.size()=%d v2.size()=%d\n",v1.size(),v2.size());
    // printf("now.size()=%d\n",now.size());
    return now;
}
inline bool Check(int S){
    if(__builtin_popcount(S)==1){
        if(sum[S]==0) return 1;return 0; 
    }
    int siz=__builtin_popcount(S)-1;
    if((sum[S]-siz)&1) return 0;bt=0;
    rep(i,0,n-1) if((S>>i)&1) b[++bt]=a[i+1];int mid=(1+bt)>>1;
    vi L=Get(1,mid),R=Get(mid+1,bt);
    // printf("mid=%d\n",mid);
    int l=R.size(),r=R.size()-1;
    // puts("L:");for(int x:L) printf("%d ",x);puts("");
    // puts("R:");for(int x:R) printf("%d ",x);puts("");
    int nd=1+(abs(sum[S])<=siz)*2;
    // printf("nd=%d\n",nd);
    for(int i=0;i<L.size();i++){
        while(l&&L[i]+R[l-1]>=-siz) l--;
        while(r>=0&&L[i]+R[r]>siz) r--;
        // printf("l=%d r=%d\n",l,r);
        nd-=min(nd,r-l+1);
        // if(l<=r&&r!=R.size()) return 1;
        // if(r==-1) return 0;
    }
    return (nd==0);
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) read(a[i]),lg[1<<i]=i;
    rep(i,1,n) sum[1<<(i-1)]+=a[i];
    rep(i,0,n-1)rep(j,0,(1<<n)-1) if((j>>i)&1) sum[j]+=sum[j^(1<<i)];
    lg[1]=0;
    // printf("Check(7)=%d\n",Check(7));
    for(int T=0;T<(1<<n);T++){
        if(!f[T]&&Check(T)){
            // puts("Now");
            int t=T^((1<<n)-1);
            for(int S=t;;S=(S-1)&t){
                // printf("T|S=%d T=%d S=%d\n",T|S,T,S);
                cmax(f[T|S],f[S]+1);
                if(!S) break;
            }
        }
        // printf("f[%d]=%d\n",T,f[T]);
    }
    printf("%lld\n",n-f[(1<<n)-1]);
    return 0;
}
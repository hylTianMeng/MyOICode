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
#define int long long
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int pr[N],ta,phi[N],n;
bool no[N];

inline void GetPrime(int n){
    no[1]=1;phi[1]=1;
    rep(i,2,n){
        if(!no[i]) pr[++ta]=i,phi[i]=i-1;
        for(int j=1;j<=ta&&1ll*pr[j]*i<=n;j++){
            no[pr[j]*i]=1;
            if(i%pr[j]==0){
                phi[i*pr[j]]=pr[j]*phi[i];
                break;
            }
            else phi[i*pr[j]]=phi[i]*phi[pr[j]];
        }
    }
}
inline int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
inline int lcm(int a,int b){
    return a*b/gcd(a,b);
}

signed main(){
    read(n);GetPrime(100000);
    int ans=0;
    rep(d,1,n){
        rep(c,2,n/d){
            // if(c*d<=1) continue;
            ans=(ans+lcm(n-c*d,d)*phi[c]%mod)%mod;
            // printf("ans=%d c=%d d=%d\n",ans,c,d);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
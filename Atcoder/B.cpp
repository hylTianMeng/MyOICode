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
#define N number
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

ll n,A,B;

signed main(){
    read(n);read(A);read(B);
    if(n<A) printf("0");
    else if(A<=B) printf("%lld\n",max(0ll,n-(A-1)));
    else{
        n-=(A-1);
        if(n<0){puts("0");}
        int cnt=n/A;    
        int ans=cnt*B;
        n=n%A;
        // printf("ans=%lld\n",ans);
        // printf("n=%lld\n",n);
        if(n<=B) ans+=n;else ans+=B;
        printf("%lld\n",ans);
    }
    return 0;
}
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
#define N 52
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

int n;
struct LinearBasis{
    int p[N];
    inline void Insert(int x){
        dec(i,0,49) if((x>>i)&1){
            if(!p[i]){p[i]=x;return;}
            else x^=p[i];
        }
    }
    inline int Ask(){
        int ans=0;
        dec(i,0,49) if((ans^p[i])>ans) ans^=p[i];
        return ans;
    }
}lb;

signed main(){
    read(n);
    rep(i,1,n){int x;read(x);lb.Insert(x);}
    printf("%lld\n",lb.Ask());
    return 0;
}
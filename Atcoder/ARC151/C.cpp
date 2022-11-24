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
#define pb emplace_back
#define N 200010
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

int n,m,x[N],y[N];
int a,b;

inline int calc(int x){
    if(x==0) return 0;
    if(x&1) return (x-1)/2;
    else return (x-2)/2;
}

signed main(){
    read(n);read(m);
    rep(i,1,m) read(x[i]),read(y[i]);
    a=0;b=0;
    if(m==0){
        if(n&1) puts("Takahashi");
        else puts("Aoki");
        return 0;
    }
    if(x[1]!=1) a++;
    if(x[m]!=n) a++;
    rep(i,1,m-1){
        if(y[i]==y[i+1]){a++;}
        else b++;
    }
    int cnt=0;
    cnt+=calc(x[1]-1);
    cnt+=calc(n-x[m]);
    if(cnt&1) a++;
    if(a&1) puts("Takahashi");
    else puts("Aoki");
    return 0;
}
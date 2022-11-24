#include<bits/stdc++.h>
#define mset(a,b) memset((a),(b),sizeof((a)))
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dec(i,l,r) for(int i=(r);i>=(l);i--)
#define inc(a,b) (((a)+(b))>=mod?(a)+(b)-mod:(a)+(b))
#define sub(a,b) (((a)-(b))<0?(a)-(b)+mod:(a)-(b))
#define mul(a,b) 1ll*(a)*(b)%mod
#define sgn(a) (((a)&1)?(mod-1):1)
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

int t1,t2;
priority_queue<int> ql;
priority_queue<int,vector<int>,greater<int> > qr;

int n,l,r,ans;

signed main(){
    // assert(freopen("my.in","r",stdin));
    // assert(freopen("my.out","w",stdout));
    read(n);read(l);read(r);
    ql.push(r);qr.push(r);
    int lst=r-l;
    rep(i,2,n){
        int l,r;read(l);read(r);
        int now=r-l;
        t1-=lst;t2+=now;
        int L=ql.top()+t1,R=qr.top()+t2;
        // printf("t1=%d t2=%d\n",t1,t2);
        // printf("L=%d R=%d r=%d\n",L,R,r);
        if(L<=r&&r<=R){
            ql.push(r-t1);qr.push(r-t2);
        }
        else if(r<L){
            int k=ql.top()+t1;ql.pop();qr.push(k-t2);ql.push(r-t1);ql.push(r-t1);
            ans+=(L-r);
        }
        else{
            int k=qr.top()+t2;qr.pop();ql.push(k-t1);qr.push(r-t2);qr.push(r-t2);
            ans+=(r-R);
        }
        lst=now;
    }
    printf("%lld\n",ans);
    return 0;
}
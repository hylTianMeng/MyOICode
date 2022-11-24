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
#define M 1000100
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
#define int long long
typedef vector<int> vi;

const int INF=1e18;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,m,K,P,a[N][N],r[M],h[M];
priority_queue<int> q;

signed main(){
    read(n);read(m);read(K);read(P);
    rep(i,1,n)rep(j,1,m) read(a[i][j]);
    rep(i,1,n){
        int sum=0;
        rep(j,1,m) sum+=a[i][j];
        q.push(sum);
    }
    int nowans=0;
    rep(i,1,K){
        int to=q.top();q.pop();
        nowans+=to;
        q.push(to-P*m);
        r[i]=nowans;
    }
    nowans=0;
    while(q.size()) q.pop();
    rep(i,1,m){
        int sum=0;
        rep(j,1,n) sum+=a[j][i];
        q.push(sum);
    }
    nowans=0;
    rep(i,1,K){
        int to=q.top();q.pop();
        nowans+=to;
        q.push(to-P*n);
        h[i]=nowans;
    }
    int ans=-INF;
    rep(i,0,K){
        // printf("h[%d]=%d r[%d]=%d\n",i,h[i],i,r[i]);
        ans=cmax(ans,h[i]+r[K-i]-i*(K-i)*P);
    }
    printf("%lld\n",ans);
    return 0;
}
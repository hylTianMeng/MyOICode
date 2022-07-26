#include<bits/stdc++.h>
#include "poison.h"
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
#define N 10010
#define M 21
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

int lim,nn,nm,nk,nt,tot;
int a[M],b[N][M];
int di[M];

inline void dfs(int k,int num){
    if(num>lim) return;
    if(k==nm){
        rep(i,0,nm-1) b[tot][i]=a[i];tot++;
        return;
    }
    if(tot==nn) return;
    rep(i,0,nt){
        a[k]=i;dfs(k+1,num+(i!=0));
        if(tot==nn) return;
    }
}

int solve(int n,int m,int k,int t){
    nn=n;nm=m;nk=k;nt=t;lim=m-k;
    dfs(0,0);
    // rep(i,0,n-1){
    //     rep(j,0,m-1) printf("%d ",b[i][j]);puts("");
    // }
    rep(i,1,t){
        rep(j,0,n-1)rep(o,0,m-1)if(b[j][o]==i&&!di[o]){
            feed(j,o);
        }
        int ans=done();
        rep(j,0,m-1){
            if(di[j]) continue;
            if(!((ans>>j)&1)){
                di[j]=i;
            }
        }
    }
    // rep(i,0,m-1) printf("di[%d]=%d\n",i,di[i]);
    rep(i,0,n-1){
        bool op=1;
        rep(j,0,m-1) if(di[j]!=b[i][j]) op=0;
        if(op){
            // printf("MyAns=%d\n",i);
            return i; 
        }
    }
    assert(0);
}
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
#define N 1000100
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

int n,K,l,a[N],cnt[N][2],f[N],g[N],Ans,maxx,maxxid;
string s;

//最大化 id
inline bool DP(int id,int mid){
    // printf("id=%d mid=%d\n",id,mid);
    rep(i,1,n) f[i]=0,g[i]=0;
    maxx=-INF;
    rep(i,0,l-1) f[i]=cnt[i][id];
    cmax(maxx,f[0]-cnt[0][id^1]);
    maxxid=0;
    rep(i,l,n){
        f[i]=cnt[i-l][id]+maxx-mid+l;
        g[i]=maxxid+1;
        // cmax(maxx,f[i-l+1]-cnt[i-l+1][id^1]);
        if(maxx<f[i-l+1]-cnt[i-l+1][id]){
            maxx=f[i-l+1]-cnt[i-l+1][id];
            maxxid=g[i-l+1];
        }
    }
    // rep(i,0,n){
        // printf("f[%d]=%d g[%d]=%d\n",i,f[i],i,g[i]);
    // }
    maxx=-INF;maxxid=-1;
    rep(i,0,n){
        if(maxx<f[i]+cnt[n][id]-cnt[i][id]){
            maxx=f[i]+cnt[n][id]-cnt[i][id];maxxid=g[i];
        }
    }
    // printf("maxx=%d maxxid=%d\n",maxx,maxxid);
    return maxxid<=K;
}
inline void Solve(int id){
    int L=0,R=n;
    while(L<R){
        int mid=(L+R)>>1;
        if(DP(id,mid)) R=mid;else L=mid+1;
    }
    DP(id,L);cmax(Ans,maxx+L*K);
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(K);read(l);cin>>s;int lens=s.length()-1;
    rep(i,0,lens) if(s[i]>='a'&&s[i]<='z') a[i+1]=0;else a[i+1]=1;
    if(K*l>=n){
        puts("0");return 0;
    }
    rep(i,1,n){
        cnt[i][0]=cnt[i-1][0];cnt[i][1]=cnt[i-1][1];
        cnt[i][a[i]]++;
    }
    Solve(0);
    // printf("Ans=%d\n",Ans);
    Solve(1);
    // printf("Ans=%d\n",Ans);
    printf("%lld\n",n-Ans);
    return 0;
}


/*
+ 统计答案出错
+ 应为 L*K 而非 L*maxxid
+ 预处理出错
+ 忘开 long long
*/
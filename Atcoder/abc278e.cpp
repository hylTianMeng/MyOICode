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
#define N 310
#define M number
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

int H,W,n,h,w;
int a[N][N],cnt[N],ans;

inline void add(int x){
    if(!cnt[x]) ans++;cnt[x]++;
}
inline void del(int x){
    cnt[x]--;if(!cnt[x]) ans--;
}

int main(){
    read(H);read(W);read(n);read(h);read(w);
    rep(i,1,H)rep(j,1,W) read(a[i][j]),add(a[i][j]);
    // printf("ans=%d\n",ans);
    rep(i,1,H-h+1){
        rep(j,i,i+h-1)rep(k,1,w){
            del(a[j][k]);
        }
        // puts("");rep(i,1,30) printf("%d ",cnt[i]);puts("fdass");puts("");
        printf("%d ",ans);
        rep(k,w+1,W){
            rep(j,i,i+h-1) del(a[j][k]);
            rep(j,i,i+h-1) add(a[j][k-w]);
            printf("%d ",ans);
            // rep(o,1,5) printf("%d ",cnt[o]);puts("NOOO");
        }
        puts("");
        ans=0;mset(cnt,0);
        rep(j,1,H)rep(k,1,W) add(a[j][k]);
    }
    return 0;
}
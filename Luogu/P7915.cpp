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
#define N 1000010
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

int t,a[N],n,st,b[N];
P p[N];
char s[N];

inline bool Check(int l,int r,int z,int y){
    // puts("Here");
    int cnt=1;
    rep(i,1,2*n) b[i]=0;
    b[z]=2*n;
    while(y-z+1<n){
        // printf("l=%d r=%d\n",l,r);
        // printf("p[a[l]].se=%d\n",p[a[l]].se);
        while(!b[l]&&(p[a[l]].se==z-1||p[a[l]].se==y+1)&&y-z+1<n){
            cnt++;
            if(p[a[l]].se==z-1) z--,b[z]=2*n-cnt+1;else y++,b[y]=2*n-cnt+1;
            s[++st]='L';l++;
            // puts("L");
        }
        if(y-z+1>=n) break;
        if(!b[r]&&(p[a[r]].fi==z-1||p[a[r]].fi==y+1)){
            cnt++;
            if(p[a[r]].fi==z-1) z--,b[z]=2*n-cnt+1;else y++,b[y]=2*n-cnt+1;
            s[++st]='R';r--;
            // puts("R");
        }
        else return 0;
    }
    // rep(i,1,2*n) printf("%d ",b[i]);
    int now=n+1;
    while(z<=y){
        if(b[z]==now) s[++st]='L',z++;
        else if(b[y]==now) s[++st]='R',y--;
        else assert(0);
        now++;
    }
    return 1;
}
inline void Print(){
    rep(i,1,st) putchar(s[i]);puts("");
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        read(n);
        rep(i,1,2*n) read(a[i]);
        rep(i,1,2*n) p[a[i]]=mp(-1,-1);
        rep(i,1,2*n){
            if(p[a[i]].fi==-1){p[a[i]].fi=i;}else p[a[i]].se=i;
        }
        bool op=0;
        st=0;s[++st]='L';
        if(Check(2,2*n,p[a[1]].se,p[a[1]].se)){op=1;Print();continue;}
        st=0;s[++st]='R';
        if(Check(1,2*n-1,p[a[2*n]].fi,p[a[2*n]].fi)){op=1;Print();continue;}
        if(!op){puts("-1");}
    }
}
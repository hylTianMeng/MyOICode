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
#define N 510
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

int t,n,k,r,c,a[N];;
char s[N][N],s2[N][N];

inline int Calc(){
    int cnt=0;
    rep(i,1,n)rep(j,1,n) if(s[i][j]=='X') cnt++;return cnt;
}
inline int Calc2(){
    int cnt=0;
    rep(i,1,n)rep(j,1,n) if(s2[i][j]=='X') cnt++;return cnt;
}

int main(){
    read(t);
    while(t--){
        read(n);read(k);read(r);read(c);
        rep(i,1,n)rep(j,1,n) s[i][j]='.';
        s[r][c]='X';int now=c;a[r]=now;
        dec(i,1,r-1){
            now--;if(now==0) now=n;
            s[i][now]='X';a[i]=now;
        }
        now=c;
        rep(i,r+1,n){
            now++;if(now==n+1) now=1;
            s[i][now]='X';a[i]=now;
        }
        rep(i,1,n){
            for(int j=a[i];j>0;j-=k) s[i][j]='X';
            for(int j=a[i];j<=n;j+=k) s[i][j]='X';
        }
        rep(i,1,n)rep(j,1,n) s2[i][j]='.';
        s2[r][c]='X';now=c;a[r]=now;
        rep(i,1,n){
            rep(j,1,n) putchar(s[i][j]);puts("");
            a[i]=0;
        }
    }
}
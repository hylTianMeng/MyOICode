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
#define N 10010
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

char s[N],t[N];
int lens,lent,f[N][N];
vi v[N];

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    scanf("%s",s+1);scanf("%s",t+1);int lens=strlen(s+1),lent=strlen(t+1);
    int cnt=0;
    rep(i,1,lens){
        cnt=0;
        rep(j,i,lens){
            if(s[j]=='.') cnt--;else cnt++;if(cnt<0) break;
            if(cnt==0) {v[i].pb(j);break;}
        }
    }
    mset(f,INF);
    f[0][0]=0;
    rep(i,0,lens)rep(j,0,lent)if(f[i][j]!=INF){
        if(s[i+1]==t[j+1]) cmin(f[i+1][j+1],f[i][j]);
        cmin(f[i+1][j],f[i][j]+1);
        for(int x:v[i+1]) cmin(f[x][j],f[i][j]);
    }
    // rep(i,0,lens)rep(j,0,lent)printf("f[%d][%d]=%d\n",i,j,f[i][j]);
    printf("%d\n",f[lens][lent]);
    return 0;
}
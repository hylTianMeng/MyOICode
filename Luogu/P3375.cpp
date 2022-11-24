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
int n,m,nxt[N],f[N];

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    scanf("%s",s+1);scanf("%s",t+1);n=strlen(s+1);m=strlen(t+1);
    nxt[1]=0;
    for(int i=2,j=0;i<=m;i++){
        while(j&&t[i]!=t[j+1]) j=nxt[j];
        if(t[i]==t[j+1]) j++;
        nxt[i]=j;
    }
    for(int i=1,j=0;i<=n;i++){
        while((j&&s[i]!=t[j+1])||j==m) j=nxt[j];
        if(s[i]==t[j+1]) j++;
        f[i]=j;
    }
    rep(i,1,n) if(f[i]==m) printf("%d\n",i-m+1);
    rep(i,1,m) printf("%d ",nxt[i]);
}

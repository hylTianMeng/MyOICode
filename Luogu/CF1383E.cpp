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
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,a[N],at,f[N],sta[N],top,sum[N];
char s[N];

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    scanf("%s",s+1);int len=strlen(s+1);
    int l=1;while(s[l]=='0'&&l<len) l++;
    int r=len;while(s[r]=='0'&&l<=r) r--;
    // printf("l=%d r=%d\n",l,r);
    if(l>r){
        printf("%lld\n",len);return 0;
    }
    if(l==r){
        l=l-1;r=len-r;
        printf("%lld\n",(l+1)*(r+1)%mod);return 0;
    }
    int nl=l;
    while(nl<r){
        int cnt=0;nl++;while(s[nl]!='1') cnt++,nl++;
        a[++at]=cnt;
    }
    l=l-1;r=len-r;
    // printf("nowl=%lld nowr=%lld\n",l,r);
    n=at;
    f[1]=a[1]+1;sum[1]=a[1]+2;sum[0]=1;f[0]=1;
    sta[++top]=1;
    // rep(i,1,n) printf("a[%lld]=%lld\n",i,a[i]);
    // printf("n=%d\n",n);
    rep(i,2,n){
        int l=top;
        rep(j,0,a[i]){
            while(l&&a[sta[l]]<j) l--;
            // printf("j=%d l=%d\n",j,l);
            f[i]=(f[i]+sum[i-1]-(l==0?0:sum[sta[l]-1]))%mod;
        }
        sum[i]=(sum[i-1]+f[i])%mod;
        while(top&&a[sta[top]]<=a[i]) top--;sta[++top]=i;
    }
    // rep(i,1,n) printf("f[%d]=%lld\n",i,f[i]);
    int Ans=0;
    rep(i,1,n) Ans=(Ans+f[i])%mod;Ans++;
    printf("%lld\n",(Ans*(l+1)%mod*(r+1)%mod+mod)%mod);
    return 0;
}
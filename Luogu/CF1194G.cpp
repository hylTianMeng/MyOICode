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
#define N 110
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
const int mod=998244353;

template<typename T> inline void read(T &x){
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int c[N],n,f[N][21][21][4][4][4][4][2][2],a,b;
string s;

inline int cm(int i,int j,int co){
    if(i<j) return 0;
    else if(i>j) return 1;
    else return co;
}
inline int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

inline int dfs(int posi,int axj,int bxj,int s1,int s2,int s3,int s4,int lim1,int lim2){
    if(posi==n+1){
        if(!axj&&!bxj&&!lim1&&!lim2&&(s1==3||s2==3||s3==3||s4==3)) return 1;return 0;
    }
    int &now=f[posi][axj][bxj][s1][s2][s3][s4][lim1][lim2];
    if(now!=-1) return now;
    int ans=0;
    rep(i,0,9){
        int nowa=(i*a+axj)%10;
        int nowaxj=(i*a+axj)/10;
        int nowb=(i*b+bxj)%10;
        int nowbxj=(i*b+bxj)/10;
        int nows1=s1|((nowa==a)<<1)|(nowb==b);
        int nows2=s2|((nowa==a*2)<<1)|(nowb==b*2);
        int nows3=s3|((nowa==a*3)<<1)|(nowb==b*3);
        int nows4=s4|((nowa==a*4)<<1)|(nowb==b*4);
        ans=(ans+dfs(posi+1,nowaxj,nowbxj,nows1,nows2,nows3,nows4,cm(nowa,c[posi],lim1),cm(nowb,c[posi],lim2)))%mod;
    }
    now=ans;
    return ans;
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    cin>>s;int len=s.length()-1;
    dec(i,0,len) c[len-i]=s[i]-'0';n=len;
    int ans=0;
    int now=1;
    rep(i,0,n){
        ans=(ans+c[i]*now%mod)%mod;now=now*10%mod;
    }
    // printf("ans=%d\n",ans);
    rep(i,1,9)rep(j,i+1,9){
        if(gcd(i,j)!=1) continue;
        mset(f,-1);
        a=i;
        b=j;
        // ans=(ans+dfs(0,0,0,0,0,0,0,0,0))%mod;
        int nowans=dfs(0,0,0,0,0,0,0,0,0);
        // printf("a=%d b=%d ans=%d\n",a,b,nowans);
        ans=(ans+nowans*2%mod)%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
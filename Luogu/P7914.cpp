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
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int f[N][N],g[N][N][2],h[N][N],n,K;
char s[N];

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(K);scanf("%s",s+1);
    rep(i,1,n-1){
        if((s[i]=='('||s[i]=='?')&&(s[i+1]==')'||s[i+1]=='?')){
            f[i][i+1]=h[i][i+1]=1;
        }
    }
    rep(i,3,n){
        rep(j,1,n-i+1){
            int l=j,r=j+i-1;
            // rep(k,1,K){
            //     if(s[l+k-1]!='*'&&s[l+k-1]!='?') break;
            //     if(l+k-1>=r-1) break;
            //     g[l][r][0]=(g[l][r][0]+h[l+k][r])%mod;
            // }
            rep(k,1,K){
                if(s[r-k+1]!='*'&&s[r-k+1]!='?') break;
                if(l+1>=r-k+1) break;
                g[l][r][1]=(g[l][r][1]+h[l][r-k])%mod;
            }
            if(s[l]!='*'&&s[l]!=')'&&s[r]!='*'&&s[r]!='('){
                int L=l+1,R=r-1;
                bool op=1;
                rep(k,L,R) if(s[k]!='*'&&s[k]!='?'){op=0;break;}
                if(R-L+1<=K&&op) h[l][r]++;
                h[l][r]=(h[l][r]+f[L][R])%mod;
                rep(k,L,R-1){
                    if(s[k]!='*'&&s[k]!='?') break;
                    if(k-L+1>K) break;
                    h[l][r]=(h[l][r]+f[k+1][R])%mod;
                }
                dec(k,L+1,R){
                    if(s[k]!='*'&&s[k]!='?') break;
                    if(R-k+1>K) break;
                    h[l][r]=(h[l][r]+f[L][k-1])%mod;
                }
            }
            else h[l][r]=0;
            rep(k,l,r-1){
                f[l][r]=(f[l][r]+1ll*g[l][k][1]*f[k+1][r]%mod)%mod;
                f[l][r]=(f[l][r]+1ll*h[l][k]*f[k+1][r]%mod)%mod;
            }
            f[l][r]=(f[l][r]+h[l][r])%mod;
            // printf("g[l][r][1]=%d h[l][r]=%d f[l][r]=%d l=%d r=%d\n",g[l][r][1],h[l][r],f[l][r],l,r);
        }
    }
    printf("%d\n",f[1][n]);
    return 0;
}
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
//#define int long long
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;
const int base=1001;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int f[N][2010],n,x,y,z,a[N],b[N];

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    mset(f,INF);
    read(n);read(x);read(y);read(z);
    rep(i,1,n){
        read(a[i]);read(b[i]);
    }
    f[0][base]=0;
    rep(i,0,n-1){
        rep(j,0,base*2) if(f[i][j]!=INF){
            if(a[i+1]>b[i+1]){
                int cha=a[i+1]-b[i+1];
                rep(k,0,a[i+1]-b[i+1]){
                    int sum=0;
                    if(j+k>2*base) continue;
                    rep(o,j+1,j+k){
                        if(o>base) sum-=z*(i+1);
                        else sum+=z*(i+1);
                    }
                    sum+=(cha-k)*y;
                    cmin(f[i+1][j+k],f[i][j]+sum);
                }
            }
            else{
                int cha=b[i+1]-a[i+1];
                rep(k,0,b[i+1]-a[i+1]){
                    int sum=0;
                    if(j-k<0) continue;
                    dec(o,j-k,j-1){
                        if(o>=base) sum+=z*(i+1);
                        else sum-=z*(i+1);
                    }
                    sum+=(cha-k)*x;
                    cmin(f[i+1][j-k],f[i][j]+sum);
                }
            }
            // printf("f[%d][%d]=%d\n",i,j-base,f[i][j]);
        }
    }
    int ans=f[n][base];
    printf("%d\n",ans);
    return 0;
}
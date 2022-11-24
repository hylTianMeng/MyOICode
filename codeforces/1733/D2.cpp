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
#define N 5010
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

const int INF=1e18;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int t,n,x,y;
string s,ss;
int a[N],b[N],c[N];
int f[N][N];

namespace Subtask1{
    inline void Solve(){
        int cnt=0;
        rep(i,1,n) if(c[i]) cnt++;
        if(cnt==0){
            puts("0");return;
        }
        if(cnt&1){
            puts("-1");return;
        }
        int ans=0;
        if(cnt>2){
            ans=cnt/2*y;
            printf("%lld\n",ans);
            return;
        }
        else{
            int i1=-1,j1=-1;
            rep(i,1,n)if(c[i]){
                if(i1==-1) i1=i;
                else j1=i;
            }
            if(i1+1!=j1){
                ans=y;
                printf("%lld\n",ans);
                return;
            }
            else{
                if(y*2<=x){
                    ans=y*2;
                }
                else ans=x;
                printf("%lld\n",ans);
                return;
            }
        }
    }
}

namespace Subtask2{
    inline void Solve(){
        int cnt=0;
        rep(i,1,n) if(c[i]) cnt++;
        if(cnt==0){
            puts("0");return;
        }
        if(cnt&1){
            puts("-1");return;
        }
        int ans=0;
        rep(i,0,n)rep(j,0,n) f[i][j]=INF;
        f[0][0]=0;
        vi v;v.clear();v.pb(0);
        rep(i,1,n) if(c[i]) v.pb(i);
        int len=(int)v.size()-1;
        rep(i,0,len-1){
            rep(j,0,n-1) f[i+1][j+1]=cmin(f[i+1][j+1],f[i][j]);
            if(i+2<=len){
                rep(j,0,n-1) if(f[i][j]!=INF){
                    f[i+2][j]=cmin(f[i+2][j],f[i][j]+(v[i+2]-v[i+1])*x);
                }
            }
            rep(j,1,n) if(f[i][j]!=INF){
                f[i+1][j-1]=cmin(f[i+1][j-1],f[i][j]+y);
            }
        }
        ans=f[len][0];
        printf("%lld\n",ans);
    }
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        read(n);read(x);read(y);
        cin>>s>>ss;
        rep(i,0,n-1) a[i+1]=s[i]-'0';
        rep(i,0,n-1) b[i+1]=ss[i]-'0';
        rep(i,1,n) c[i]=0;
        rep(i,1,n) if(a[i]==b[i]) c[i]=0;else c[i]=1;
        if(x>=y) Subtask1::Solve();
        else Subtask2::Solve();
    }
    return 0;
}
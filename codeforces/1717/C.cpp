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
#define N 200010
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

int t,n,a[N],b[N];
bool vis[N];

int main(){
//     freopen("my.in","r",stdin);
    read(t);
    while(t--){
        read(n);rep(i,1,n) read(a[i]);
        rep(i,1,n) vis[i]=0;rep(i,1,n) read(b[i]);
        rep(i,1,n) if(a[i]==b[i]) vis[i]=1;
        bool oo=1;
        rep(i,1,n) if(b[i]<a[i]){oo=0;break;}
        if(!oo){puts("No");continue;}
        int l=-1;
        rep(i,1,n) if(vis[i]){l=i;break;}
        if(l!=-1){
            int now=l;l--;if(l==0) l=n;
            bool op=1;
            while(l!=now){
                if(vis[l]){l--;if(l==0) l=n;continue;}
                int last=l+1;if(last==n+1) last=1;
                if(b[l]>b[last]&&b[l]!=b[last]+1){op=0;break;}
                l--;if(l==0) l=n;
            }
            if(!op){puts("No");}else puts("Yes");
        }
        else{
            bool op=1;
            rep(i,1,n-1) if(b[i]>b[i+1]&&b[i]!=b[i+1]+1){op=0;break;}
            if(b[n]>b[1]&&b[n]!=b[1]+1){op=0;}
            if(op){puts("Yes");}else puts("No");
        }
    }
}
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
#define N 100010
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
vc<P> ans;

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        ans.clear();
        read(n);rep(i,1,n) read(a[i]);
        rep(i,1,n) b[i]=-1;
        rep(i,1,n) b[i]=(a[i]&1);
        int fin=-1;
        rep(i,2,n) if(b[i]==b[1]) fin=i;
        if(fin!=-1){
            dec(i,1,fin-1) if(b[i]==b[1]){
                ans.pb(mp(i,fin));
            }
        }
        rep(i,2,n) if(b[i]!=b[1]){
            ans.pb(mp(1,i));
        }
        printf("%d\n",(int)ans.size());
        for(P now:ans){
            printf("%d %d\n",now.fi,now.se);
        }
    }
    return 0;
}
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

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int t,n,a[N],b[N];
vi va,vb;
multiset<int> s;

inline int f(int x){
    int c=0;while(x){x/=10;c++;}return c;
}

int main(){
    // freopen("my.in","r",stdin);
    read(t);
    while(t--){
        read(n);s.clear();va.clear();vb.clear();
        rep(i,1,n){
            int x;read(x);s.insert(x);
        }
        rep(i,1,n){
            int x;read(x);if(s.find(x)!=s.end()){
                s.erase(s.find(x));
            }
            else vb.pb(x);
        }
        for(int x:s) va.pb(x);
        int ans=0;s.clear();
        for(int i=0;i<va.size();i++){
            if(va[i]>=10) va[i]=f(va[i]),ans++;
            s.insert(va[i]);
        }
        for(int i=0;i<vb.size();i++){
            if(vb[i]>=10) vb[i]=f(vb[i]),ans++;
            if(s.find(vb[i])!=s.end()){
                s.erase(s.find(vb[i]));
            }
            else if(vb[i]!=1) ans++;
        }
        for(int x:s) if(x!=1) ans++;
        printf("%d\n",ans);
    }
}
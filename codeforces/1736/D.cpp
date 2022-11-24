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
#define pb emplace_back
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

int t,n,a[N];
string s;
vi ans;

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        read(n);
        n*=2;
        cin>>s;
        rep(i,1,n) a[i]=s[i-1]-'0';
        ans.clear();
        int cnt=0;
        rep(i,1,n) if(a[i]) cnt++;
        if(cnt&1){
            puts("-1");continue;
        }
        for(int i=1;i<=n;i+=2){
            if(a[i]==a[i+1]) continue;
            else{
                int len=ans.size();
                int op=-1;
                if(len&1) op=1;
                else op=0;
                if(a[i]==op) ans.pb(i);
                else ans.pb(i+1);
            }
        }
        printf("%d ",(int)ans.size());for(int x:ans) printf("%d ",x);puts("");
        for(int i=1;i<=n;i+=2) printf("%d ",i);puts("");
    }
}
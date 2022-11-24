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

int main(){
    // freopen("my.in","r",stdin);
    read(t);
    while(t--){
        read(n);
        rep(i,1,n) read(a[i]);rep(i,1,n) read(b[i]);
        bool op=1;
        rep(i,1,n) if(a[i]!=b[i]) op=0;
        if(op){
            puts("0");continue;
        }
        int cnt=0;
        rep(i,1,n) if(a[i]!=b[i]) cnt++;
        sort(a+1,a+n+1);sort(b+1,b+n+1);
        int i1=0,i2=0;
        rep(i,1,n) if(a[i]==0) i1=i;
        rep(i,1,n) if(b[i]==0) i2=i;
        int now=abs(i1-i2);
        if(cnt>now) printf("%d\n",now+1);
        else printf("%d\n",now);
    }
    return 0;
}
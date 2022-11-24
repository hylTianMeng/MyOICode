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
#define N number
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

int a,b;

inline P nxt(int a,int b){
    b++;if(b==60) a++,b=0;
    if(a==24) a=0;
    return mp(a,b);
}
inline bool chk(int a,int b){
    int B=a%10;
    int c=b/10;
    if(a/10*10+c<24&&B*10+b%10<60) return 1;
    return 0;
}

int main(){
    read(a);read(b);
    while(1){
        if(chk(a,b)){
            printf("%d %d\n",a,b);
            break;
        }
        P now=nxt(a,b);
        a=now.fi;b=now.se;
    }
}
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

int n;
char s[N],t[N],u[N];

int main(){
    read(n);
    scanf("%s",s+1);
    scanf("%s",t+1);
    vi v;v.clear();
    rep(i,1,n) if(s[i]==t[i]) u[i]='0';
    else v.pb(i);
    if(v.size()&1){
        puts("-1");return 0;
    }
    int cha=0;
    rep(i,0,(int)v.size()-1){
        int sheng=v.size()-i;
        if(abs(cha)==sheng){
            if(cha>0) u[v[i]]=t[v[i]],cha--;
            else u[v[i]]=s[v[i]],cha++;
        }
        else{
            if(s[v[i]]=='0') u[v[i]]='0',cha++;
            else u[v[i]]='0',cha--;
        }
    }
    rep(i,1,n) putchar(u[i]);
    return 0;
}
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
#define N 100
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
char s[N];

inline bool Check(int p){
    bool op1=1,op2=1;
    dec(i,1,p-1) if(s[i]!='W'){if(s[i]=='B') op1=0;break;}
    rep(i,p+1,n) if(s[i]!='W'){if(s[i]=='B') op2=0;break;}
    if(!op1&&!op2) return 0;return 1;
}
inline int Calc(int p){
    int Ans=0;
    int ans=0;
    bool op1=0;
    if(s[p-1]=='B'){
        dec(i,1,p-1) if(s[i]=='B') ans++;else if(s[i]=='W') op1=1;else break;
    }
    if(!op1) ans=0;
    cmax(Ans,ans);
    bool op2=0;
    if(s[p+1]=='B'){
        rep(i,p+1,n) if(s[i]=='B') ans++;else if(s[i]=='W') op2=1;else break;
    }
    if(!op2) ans=0;
    return max(Ans,ans);
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);
    scanf("%s",s+1);
    int Ans=0;
    rep(i,1,n){
        if(s[i]!='.') continue;
        if(!Check(i)) continue;
        // printf("i=%d\n",i);
        int ans=Calc(i);
        Ans=max(Ans,ans);
    }
    printf("%d\n",Ans);
    return 0;
}
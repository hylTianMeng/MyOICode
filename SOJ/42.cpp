#include<bits/stdc++.h>
#include "interact.h"
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

inline P solve(int n,int l,int lst_l){
    int now=l;
    while(now<=n){
        int pre=now;
        if(!query(now,l,now)){
            P ans=solve(n,now+1,l);
            report(now,ans.fi);
            now=ans.se;
        }
        printf("l=%d now=%d\n",l,now);
        if(l!=1&&query(l-1,lst_l,now)){
            printf("l=%d lst_l=%d pre=%d now=%d\n",l,lst_l,pre,now);
            return mp(pre,now);
        }
        now++;
        if(now<=n) report(pre,now);
    }
    return mp(-INF,-INF);
}

void guess(int n){
    solve(n,1,0);
}
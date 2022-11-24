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
#define N 400010
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

set<int> s[N];
map<int,int> id;
int n,m,tot;

int main(){
    read(n);read(m);
    rep(i,1,m){
        int op,a,b;read(op);read(a);read(b);
        if(id.find(a)==id.end()) id[a]=++tot;
        if(id.find(b)==id.end()) id[b]=++tot;
        a=id[a];
        b=id[b];
        if(op==1&&s[a].find(b)==s[a].end()) s[a].insert(b);
        if(op==2&&s[a].find(b)!=s[a].end()) s[a].erase(b);
        if(op==3){
            if(s[a].find(b)!=s[a].end()&&s[b].find(a)!=s[b].end()){
                puts("Yes");
            }
            else puts("No");
        }
    }
}
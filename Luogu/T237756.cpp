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

int n,m,a[N],b[N],c[N],d[N],p[N];
ll ans;
struct Node{
    int id,c;
    ll v;
    inline Node(){}
    inline Node(int id,int c,ll v) : id(id),c(c),v(v) {}
    inline bool operator < (const Node &b)const{return v>b.v;}
};
priority_queue<Node> q;
inline ll Calc(int id,int j){
    return 1ll*a[id]*j*j+1ll*b[id]*j+1ll*c[id];
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);rep(i,1,n) read(a[i]),read(b[i]),read(c[i]);
    rep(i,1,n) d[i]=1,ans+=Calc(i,1);
    rep(i,1,n) q.push(Node(i,2,Calc(i,2)));
    rep(i,1,2*m-n){
        Node now;
        while(1){
            now=q.top();q.pop();if(now.c!=m+1) break;
        }
        ans+=now.v;d[now.id]++;q.push(Node(now.id,now.c+1,Calc(now.id,now.c+1)));
    }
    // rep(i,1,n) printf("d[%d]=%d\n",i,d[i]);
    printf("%lld\n",ans);
    rep(i,1,n) p[i]=i;sort(p+1,p+n+1,[&](int i,int j){return d[i]>d[j];});
    int l=1;while(d[p[l+1]]>1) l++;
    rep(i,1,m){
        printf("%d %d\n",1,1);
    }
    
    return 0;
}
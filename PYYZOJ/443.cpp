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

int n;
struct BIT{
    int p[N];
    inline int lowbit(int x){return x&(-x);}
    inline void Add(int w,int x){
        for(int i=w;i<=n;i+=lowbit(i)) p[i]+=x;
    }
    inline int Ask(int w){
        int res=0;for(int i=w;i;i-=lowbit(i)) res+=p[i];return res;
    }
}bit;
struct LCT{
    struct Node{
        int s[2],val,tc,tr,fa;
    }p[N];
    int tot=0;
    #define ls(k) (p[(k)].s[0])
    #define rs(k) (p[(k)].s[1])
    #define fa(k) (p[(k)].fa)
    inline void R(int k){
        swap(ls(k),rs(k));p[k].tr^=1;
    }
    inline void C(int k,int x){p[k].val=x;p[k].tc=x;}
    inline void PushDown(int k){
        if(p[k].tr) R(ls(k)),R(rs(k)),p[k].tr^=1;
        if(p[k].tc) C(ls(k),p[k].tc),C(rs(k),p[k].tc),p[k].tc=0;
    }
    inline bool Root(int k){return ls(fa(k))!=k&&rs(fa(k))!=k;}
    inline void Update(int k){
        if(!Root(k)) Update(fa(k));PushDown(k);
    }
    inline bool which(int k){return rs(fa(k))==k;}
    inline void PushUp(int k){}
    inline void rotate(int k){
        if(Root(k)) return;
        int y=fa(k),z=fa(y),x=which(k);
        p[y].s[x]=p[k].s[x^1];p[k].s[x^1]=y;
        fa(p[y].s[x])=y;if(!Root(y)) p[z].s[which(y)]=k;
        fa(k)=z;fa(y)=k;Update(y);Update(k);
    }
    inline void Splay(int k){
        Update(k);
        for(int f=fa(k);!Root(k);rotate(k)){
            if(Root(k)) rotate((which(fa(k))==which(k))?f:k);
        }
    }
    inline int Access(int k){
        int y=0;
        for(;k;y=k,k=fa(k)){
            Splay(k);rs(k)=0;PushUp(k);
        }
        return y;
    }
    inline void MakeRoot(int k){
        k=Access(k);R(k);
    }
    inline int NewNode(int val){
        ++tot;p[tot].val=val;return tot;
    }
    inline int Find(int k){
        MakeRoot(k);Splay(k);PushDown(k);while(ls(k)) k=ls(k),PushDown(k);Splay(k);return k;
    }
    inline void Link(int a,int b){
        MakeRoot(a);if(Find(b)==a) return;Splay(b);fa(a)=b;
    }
    inline void Init(){
        
    }
};

int main(){

}
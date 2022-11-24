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
#define N 100010
#define M 1000100
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
//#define int long long
typedef pair<int,int> P;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;
const int mod=1e9+7;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int n,m,tot,ID[M],IID[500];
struct edge{
    int to,next,w;
    inline void Init(int to_,int ne_,int w_){
        to=to_;next=ne_;w=w_;
    }
}li[N<<1];
int head[N],tail,f[N][376];
#define LinearBasis LB
struct LinearBasis{
    int p[5];
    inline bool Insert(int x){
        if(x==0) return 1;
        dec(i,0,4) if((x>>i)&1){
            if(p[i]){x^=p[i];}
            else{
                p[i]=x;
                rep(j,0,i-1) if(p[j]&&((p[i]>>j)&1)) p[i]^=p[j];
                rep(j,i+1,4) if(p[j]&&((p[j]>>i)&1)) p[j]^=p[i];return 1;
            }
        }
        return 0;
    }
    inline int Hash(){return p[0]|(p[1]<<1)|(p[2]<<3)|(p[3]<<6)|(p[4]<<10);}
    inline void IHash(int x){
        int now=1;
        rep(i,0,4){
            p[i]=x&((1<<now)-1);
            x>>=now;now++;
        }
    }
}A,lb[N];
bool tag[N],vis[N],vi[N],ok[N];
int W[N];
int d[N],ow[N];
map<P,int> Map;

inline void Add(int from,int to,int w){
    li[++tail].Init(to,head[from],w);head[from]=tail; 
}
inline void dfs(int k){
    LB now=A;
    if(k==32){
        if(ID[A.Hash()]) return;ID[A.Hash()]=++tot;IID[tot]=A.Hash();return;
    }
    dfs(k+1);A=now;if(A.Insert(k)) dfs(k+1);A=now;
}
inline void Dfs(int k,int fa,int xo,int id){
    // printf("k=%d\n",k);
    vis[k]=1;d[k]=xo;Next(k){
        int to=li[x].to,w=li[x].w;
        if(to==fa) continue;
        if(tag[to]&&tag[k]){vi[k]=1;vi[to]=1;ow[k]=to;ow[to]=k;Map[mp(to,k)]=Map[mp(k,to)]=w;continue;}
        if(!vis[to]) Dfs(to,k,xo^w,id);
        else{
            // printf("k=%d to=%d\n",k,to);
            if(k<to) continue;
            // printf("Insert %d\n",d[to]^xo^w);printf("d[%d]=%d xo=%d w=%d\n",to,d[to],xo,w);
            if(!lb[id].Insert(d[to]^xo^w)||!(d[to]^xo^w)){ok[id]=0;}
        }
    }
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);dfs(1);
    //tot=374
    rep(i,1,m){
        int u,v,w;read(u);read(v);read(w);Add(u,v,w);Add(v,u,w);
    }
    Next(1){
        int to=li[x].to;tag[to]=1;ok[to]=1;W[to]=li[x].w;
    }
    Next(1){
        int to=li[x].to;Dfs(to,1,li[x].w,to);
        // printf("ok[%d]=%d\n",to,ok[to]);
    }
    int last=0;mset(f,0);f[0][1]=1;
    for(int x=head[1];x;x=li[x].next){
        int to=li[x].to;
        if(!vi[to]){
            rep(j,1,374) f[to][j]=(f[to][j]+f[last][j])%mod;
            if(ok[to])rep(j,1,374)if(f[last][j]){
                LB now;now.IHash(IID[j]);
                bool op=1;
                rep(k,0,4) if(!now.Insert(lb[to].p[k])){op=0;break;}
                if(!op) continue;
                f[to][ID[now.Hash()]]=(f[to][ID[now.Hash()]]+f[last][j])%mod;
            }
        }
        else{
            if(ow[to]<to) continue;
            // printf("to=%d\n",to);
            int a=to,b=ow[to],w=Map[mp(a,b)];
            rep(j,1,374) f[a][j]=(f[a][j]+f[last][j])%mod;
            LB now=lb[a];
            bool op=1;
            rep(j,0,4) if(!now.Insert(lb[b].p[j])){op=0;break;}
            if(op&&ok[a]&&ok[b])rep(j,1,374)if(f[last][j]){
                LB nowj;nowj.IHash(IID[j]);
                bool op2=1;
                rep(k,0,4) if(!nowj.Insert(now.p[k])){op2=0;break;}
                if(!op2) continue;
                f[a][ID[nowj.Hash()]]=(f[a][ID[nowj.Hash()]]+1ll*f[last][j]*2%mod)%mod;
            }
            op&=now.Insert(W[a]^W[b]^w);op&=(W[a]^W[b]^w);
            // printf("op=%d w=%d W[%d]=%d W[%d]=%d\n",op,w,a,W[a],b,W[b]);
            if(op&&ok[a]&&ok[b])rep(j,1,374)if(f[last][j]){
                LB nowj;nowj.IHash(IID[j]);
                bool op2=1;
                rep(k,0,4) if(!nowj.Insert(now.p[k])){op2=0;break;}
                if(!op2) continue;
                f[a][ID[nowj.Hash()]]=(f[a][ID[nowj.Hash()]]+f[last][j])%mod;
            }
        }
        last=to;
        // rep(j,1,374) printf("f[%d][%d]=%d\n",last,j,f[last][j]);
    }
    int ans=0;
    rep(i,1,374) ans=(ans+f[last][i])%mod;
    printf("%d\n",ans);
    return 0;
}
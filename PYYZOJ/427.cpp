#include<bits/stdc++.h>
#define mset(a,b) memset((a),(b),sizeof((a)))
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define dec(i,l,r) for(int i=(r);i>=(l);i--)
#define inc(a,b) (((a)+(b))>=mod?(a)+(b)-mod:(a)+(b))
#define sub(a,b) (((a)-(b))<0?(a)-(b)+mod:(a)-(b))
#define mul(a,b) 1ll*(a)*(b)%mod
#define sgn(a) (((a)&1)?(mod-1):1)
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
#define N 1000010
#define M number
using namespace std;

typedef double dd;
typedef long double ld;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
#define int long long
typedef pair<int,int> P;
typedef vector<int> vi;

const int INF=0x3f3f3f3f;
const dd eps=1e-9;
const int mod=998244353;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int dfn[N],low[N],sta[N],top,rt,ctot,tot,n,m,f[N],Pow[N],InvPow[N],inv2,ans[N];
vi dcc[N],e[N],E[N];

inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int a){return ksm(a,mod-2,mod);}
inline void Tarjan(int k){
    dfn[k]=low[k]=++tot;
    if(rt==k&&e[k].size()==0){ctot++;dcc[ctot].pb(k);}sta[++top]=k;
    for(int to:e[k]){
        if(!dfn[to]){
            Tarjan(to);low[k]=min(low[k],low[to]);
            if(low[to]>=dfn[k]){
                ctot++;int x;do{x=sta[top--];dcc[ctot].pb(x);}while(x!=to);dcc[ctot].pb(k);
            }
        }
        else low[k]=min(low[k],dfn[to]);
    }
}
inline void Build(){
    // printf("ctot=%d\n",ctot);
    // rep(i,1,ctot){for(int x:dcc[i]) printf("%d ",x);puts("");}
    rep(i,1,ctot){
        int now=i+n;
        for(int x:dcc[i]){
            E[now].pb(x),E[x].pb(now);
            // printf("Add %d %d\n",now,x);
        }
    }
}
inline void DP(int k,int fa){
    vi v;v.clear();f[k]++;
    // printf("k=%d\n",k);
    for(int to:E[k]) if(to!=fa){
        // puts("here");
        v.clear();
        for(int x:E[to]) v.pb(x);
        int id=-1;
        rep(i,0,(int)v.size()-1) if(v[i]==k) id=i;
        rep(i,0,(int)v.size()-1) if(i!=id){
            // printf("fa=%d to=%d\n",fa,to);
            // printf("k=%d v[i]=%d\n",k,v[i]);
            DP(v[i],to);
        }
        dec(i,0,id-1){
            int L=InvPow[id-i],R=InvPow[v.size()-id+i];
            if(v.size()!=2) f[k]=(f[k]+1ll*((L+R-InvPow[v.size()])%mod)*f[v[i]]%mod)%mod;
            else f[k]=(f[k]+inv2*f[v[i]]%mod)%mod;
        }
        // printf("k=%d f[k]*Pow[m]=%d\n",k,f[k]*Pow[m]%mod);
        rep(i,id+1,(int)v.size()-1){
            int L=InvPow[i-id],R=InvPow[v.size()+id-i];
            if(v.size()!=2) f[k]=(f[k]+1ll*((L+R-InvPow[v.size()])%mod)*f[v[i]]%mod)%mod;
            else f[k]=(f[k]+inv2*f[v[i]]%mod)%mod;
        }
    }
    // printf("k=%d\n",k);
    // printf("f[k]*Pow[m]=%d\n",f[k]*Pow[m]%mod);
}
inline void ChRt(int k,int fa){
    ans[k]=f[k];vi v;
    for(int to:E[k]) if(to!=fa){
        v.clear();
        for(int x:E[to]) v.pb(x);
        //Delete Begin
        int id=-1;
        rep(i,0,(int)v.size()-1) if(v[i]==k) id=i;
        dec(i,0,id-1){
            int L=InvPow[id-i],R=InvPow[v.size()-id+i];
            if(v.size()!=2) f[k]=(f[k]-1ll*((L+R-InvPow[v.size()])%mod)*f[v[i]]%mod)%mod;
            else f[k]=(f[k]-inv2*f[v[i]]%mod)%mod;
        }
        rep(i,id+1,(int)v.size()-1){
            int L=InvPow[i-id],R=InvPow[v.size()+id-i];
            if(v.size()!=2) f[k]=(f[k]-1ll*((L+R-InvPow[v.size()])%mod)*f[v[i]]%mod)%mod;
            else f[k]=(f[k]-inv2*f[v[i]]%mod)%mod;
        }
        f[k]=(f[k]+mod)%mod;
        //Delete Over
        // rep(i,1,3) printf("i=%d f[i]*Pow[m]=%d\n",i,f[i]*Pow[m]);
        int sum1=0,sum2=0,sum=0,len=E[to].size();
        if(len!=2){
            rep(i,0,v.size()-1){
                sum=(sum+f[v[i]])%mod;
                sum1=(sum1+1ll*f[v[i]]*InvPow[i]%mod)%mod;
                sum2=(sum2+1ll*f[v[i]]*InvPow[len-i]%mod)%mod;
            }
            rep(i,0,v.size()-1){
                sum1=(sum1-1ll*f[v[i]]*InvPow[i]%mod)%mod;
                sum2=(sum2-1ll*f[v[i]]*InvPow[len-i]%mod)%mod;
                sum1=(sum1+1ll*f[v[i]]*InvPow[len+i]%mod)%mod;
                sum2=(sum2+1ll*f[v[i]]*Pow[i]%mod)%mod;
                if(v[i]==k) continue;
                int LastF=f[v[i]];f[v[i]]=(sum1*Pow[i]%mod+sum2*InvPow[i]%mod-sum*InvPow[len]%mod)%mod;
                f[v[i]]=(f[v[i]]+mod)%mod;
                ChRt(v[i],to);
                f[v[i]]=LastF;
            }
        }
        else{
            rep(i,0,v.size()-1){
                if(v[i]==k) continue;int LastF=f[v[i]];f[v[i]]=(f[v[i]]+f[k]*inv2%mod)%mod;
                ChRt(v[i],to);f[v[i]]=LastF;
            }
        }

        //Add Begin
        dec(i,0,id-1){
            int L=InvPow[id-i],R=InvPow[v.size()-id+i];
            if(v.size()!=2) f[k]=(f[k]+1ll*((L+R-InvPow[v.size()])%mod)*f[v[i]]%mod)%mod;
            else f[k]=(f[k]+inv2*f[v[i]]%mod)%mod;
        }
        rep(i,id+1,(int)v.size()-1){
            int L=InvPow[i-id],R=InvPow[v.size()+id-i];
            if(v.size()!=2) f[k]=(f[k]+1ll*((L+R-InvPow[v.size()])%mod)*f[v[i]]%mod)%mod;
            else f[k]=(f[k]+inv2*f[v[i]]%mod)%mod;
        }
        //Add Over
        // rep(i,1,3) printf("i=%d f[i]*Pow[m]=%d\n",i,f[i]*Pow[m]%mod);
    }
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(m);
    inv2=inv(2);Pow[0]=1;rep(i,1,n<<1) Pow[i]=1ll*Pow[i-1]*2%mod;
    InvPow[0]=1;rep(i,1,n<<1) InvPow[i]=1ll*InvPow[i-1]*inv2%mod;
    rep(i,1,m){
        int u,v;read(u);read(v);e[u].pb(v);e[v].pb(u);
    }
    Tarjan(1);Build();
    // exit(0);
    DP(1,0);ChRt(1,0);
    rep(i,1,n) printf("%d\n",ans[i]*Pow[m]%mod);
    return 0;
}
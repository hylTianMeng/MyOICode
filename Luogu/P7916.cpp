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
#define N 2010
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

const int INF=0x3f3f3f3f3f3f3f3f;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

vc<P> e[N*N];
int c[N][N],r[N][N],n,m,T,d[N*N],f[N][N],xu[N*N],cnt[N*N],w[N][N];
bool vis[N*N];
vi v;
P id[N<<2];
struct Point{
    int w,id,co;
    inline bool operator < (const Point &b)const{return id<b.id;}
}p[N*N];

inline int ID(int a,int b){
    return (a-1)*(m-1)+b;
}
struct Node{
    int id,v;
    inline bool operator < (const Node &b)const{return v>b.v;}
};
priority_queue<Node> q;
inline void dij(int id,int s){
    fill(d+1,d+1000*1000+1,INF);q.push({s,0});d[s]=0;mset(vis,0);
    while(q.size()){
        Node top=q.top();q.pop();
        if(vis[top.id]) continue;
        vis[top.id]=1;
        for(P to:e[top.id]){
            if(vis[to.fi]||d[to.fi]<=d[top.id]+to.se) continue;
            d[to.fi]=d[top.id]+to.se;
            q.push({to.fi,d[to.fi]});
        }
    }
    for(int i=0;i<(int)v.size();i++){
        // printf("w[%d][%d=%d\n",i,id,d[v[i]]);
        w[id][i]=w[i][id]=d[v[i]];
    }
}
inline void Print(int a,int b,int c){
    // printf("from=%lld to=%lld w=%lld\n",a,b,c);
    cnt[a]++;cnt[b]++;
    assert(cnt[a]<=e[a].size());
    assert(cnt[b]<=e[b].size());
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout); 
    read(n);read(m);read(T);
    rep(i,1,n-1)rep(j,1,m){
        read(c[i][j]);
    }
    rep(i,1,n)rep(j,1,m-1){
        read(r[i][j]);
    }
    rep(i,1,n-2)rep(j,1,m-1){
        // Print(ID(i,j),ID(i+1,j),r[i+1][j]);
        e[ID(i,j)].pb(mp(ID(i+1,j),r[i+1][j]));
        e[ID(i+1,j)].pb(mp(ID(i,j),r[i+1][j]));
    }
    // puts("Finish colu");
    rep(i,1,n-1)rep(j,1,m-2){
        // Print(ID(i,j),ID(i,j+1),c[i][j+1]);
        e[ID(i,j)].pb(mp(ID(i,j+1),c[i][j+1]));
        e[ID(i,j+1)].pb(mp(ID(i,j),c[i][j+1]));
    }
    rep(i,1,m-1) id[i]=mp(1,i);id[m]=mp(-1,-1);rep(i,m+1,m+n-1) id[i]=mp(i-m,m-1);id[m+n]=mp(-1,-1);
    rep(i,m+n+1,2*m+n-1) id[i]=mp(n-1,2*m+n-i);id[2*m+n]=mp(-1,-1);
    rep(i,2*m+n+1,2*m+2*n-1) id[i]=mp(2*m+2*n-i,1);id[2*m+2*n]=mp(-1,-1);
    // puts("Finish");
    //矩形内部建边。
    while(T--){
        // printf("T=%d\n",T);
        int pc;read(pc);
        if(pc==1){puts("0");continue;}
        rep(i,1,pc){
            int w,id,co;read(w);read(id);read(co);
            p[i].w=w;p[i].id=id;p[i].co=co;
        }
        sort(p+1,p+pc+1);
        int tot=ID(n-1,m-1);
        v.clear();
        rep(i,2,pc){
            // printf("i=%lld\n",i);
            ++tot;
            rep(j,p[i-1].id,p[i].id-1){
                if(id[j]==mp(-1ll,-1ll)) continue;
                int w=-1;
                if(j<=m){w=r[id[j].fi][id[j].se];}
                else if(j<=m+n){w=c[id[j].fi][id[j].se+1];}
                else if(j<=2*m+n){w=r[id[j].fi+1][id[j].se];}
                else if(j<=2*m+2*n){w=c[id[j].fi][id[j].se];}
                e[tot].pb(mp(ID(id[j].fi,id[j].se),w));
                e[ID(id[j].fi,id[j].se)].pb(mp(tot,w));
                Print(tot,ID(id[j].fi,id[j].se),w);
            }
            if(i!=2){
                e[tot].pb(mp(tot-1,p[i-1].w));
                e[tot-1].pb(mp(tot,p[i-1].w));
                Print(tot,tot-1,p[i-1].w);
            }
            if(p[i].co!=p[i-1].co) v.pb(tot);
        }
        ++tot;
        e[tot-1].pb(mp(tot,p[pc].w));
        e[tot].pb(mp(tot-1,p[pc].w));
        Print(tot-1,tot,p[pc].w);
        rep(j,p[pc].id,2*m+2*n){
            if(id[j]==mp(-1ll,-1ll)) continue; 
            int w=-1;
            if(j<=m){w=r[id[j].fi][id[j].se];}
            else if(j<=m+n){w=c[id[j].fi][id[j].se+1];}
            else if(j<=2*m+n){w=r[id[j].fi+1][id[j].se];}
            else if(j<=2*m+2*n){w=c[id[j].fi][id[j].se];}
            // printf("id[%lld].fi=%lld if[%lld].se=%lld w=%lld\n",j,id[j].fi,j,id[j].se,w);
            e[tot].pb(mp(ID(id[j].fi,id[j].se),w));
            e[ID(id[j].fi,id[j].se)].pb(mp(tot,w));
            Print(tot,ID(id[j].fi,id[j].se),w);
        }
    // exit(0);
        rep(j,1,p[1].id-1){
            if(id[j]==mp(-1ll,-1ll)) continue;
            int w=-1;
            if(j<=m){w=r[id[j].fi][id[j].se];}
            else if(j<=m+n){w=c[id[j].fi][id[j].se+1];}
            else if(j<=2*m+n){w=r[id[j].fi+1][id[j].se];}
            else if(j<=2*m+2*n){w=c[id[j].fi][id[j].se];}
            e[tot].pb(mp(ID(id[j].fi,id[j].se),w));
            e[ID(id[j].fi,id[j].se)].pb(mp(tot,w));
            Print(tot,ID(id[j].fi,id[j].se),w);
        }
    // exit(0);
        if(p[1].co!=p[pc].co) v.pb(tot);
        e[tot].pb(mp(ID(n-1,m-1)+1,p[1].w));
        e[ID(n-1,m-1)+1].pb(mp(tot,p[1].w));
        Print(tot,ID(n-1,m-1)+1,p[1].w);
        if(v.empty()){
            puts("0");rep(i,1,tot){
                while(cnt[i]) e[i].pop_back(),cnt[i]--;
            }continue;
        }
        //初始化完成
        for(int i=0;i<(int)v.size()-1;i++) dij(i,v[i]);
        //最短路
        rep(i,0,(int)v.size()-1) xu[i+1]=i;rep(i,v.size()+1,2*v.size()) xu[i]=xu[i-v.size()];
        int len=2*v.size();
        // rep(i,1,len/2)rep(j,1,len/2) printf("w[%lld][%lld]=%lld\n",xu[i],xu[j],w[xu[i]][xu[j]]);
        rep(i,1,len-1) f[i][i+1]=w[xu[i]][xu[i+1]];
        for(int i=4;i<=len;i+=2){
            rep(j,1,len-i+1){
                int l=j,r=j+i-1;
                f[l][r]=f[l+1][r-1]+w[xu[l]][xu[r]];
                rep(k,l,r-1){
                    if((k-l+1)&1) continue;
                    f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
                }
                // printf("f[%d][%d]=%d\n",l,r,f[l][r]);
            }
        }
        // printf("e[9307].size()=%d\n",e[9307].size());
        int ans=INF;
        rep(i,1,len/2+1) ans=min(ans,f[i][i+len/2-1]);
        printf("%lld\n",ans);
        rep(i,1,len) xu[i]=0;
        rep(i,1,tot){
            // assert(cnt[i]>=0);
            while(cnt[i]>0){
                if(e[i].empty()) assert(0);
                e[i].pop_back();
                cnt[i]--;
            }
        }
        // exit(0);
    }
}

/*
+ 建边时下标弄错。
*/
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
#define N 4000100
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

int n,ans[N];
char s[N];
vi e[N];int L[N],R[N],itot;

struct BIT{
    int p[N];
    inline int lowbit(int x){return x&(-x);}
    inline void Add(int w,int x){
        // printf("Add w=%d x=%d\n",w,x);
        for(int i=w;i<=itot;i+=lowbit(i)) p[i]+=x;
    }
    inline int Ask(int w){
        // printf("Ask w=%d\n",w);
        int res=0;for(int i=w;i;i-=lowbit(i)) res+=p[i];return res;
    }
}bit;
struct Ques{
    int op,k,x;
    inline Ques(){}
    inline Ques(int op,int k,int x) : op(op),k(k),x(x) {}
};
vc<Ques> qu[N];
struct SAM{
    int Link[N<<1],tot,Len[N<<1],ch[N<<1][10],cnt[N<<1],last,Ans;
    inline SAM(){tot=1;Link[1]=-1;Len[1]=0;last=1;Ans=0;}
    inline void Insert(int c,int id){
        // printf("first Ans=%d\n",Ans);
        vc<P> v;v.clear();
        int now=++tot;Len[now]=Len[last]+1;int p=last;
        while(p!=-1&&!ch[p][c]){
            ch[p][c]=now;cnt[p]++;
            if(cnt[p]==1&&p!=1) Ans--,v.pb(mp(p,-1));
            else if(cnt[p]==2&&p!=1) Ans++,v.pb(mp(p,1));
            p=Link[p];
        }
        // printf("Ans=%d\n",Ans);
        if(p==-1){Link[now]=1;}
        else{
            int q=ch[p][c];if(Len[q]==Len[p]+1){Link[now]=q;}
            else{
                int clone=++tot;Link[clone]=Link[q];rep(i,0,9) ch[clone][i]=ch[q][i];cnt[clone]=cnt[q];
                if(cnt[clone]>=2) Ans++;else if(cnt[clone]==1) v.pb(mp(clone,-1));Len[clone]=Len[p]+1;
                Link[q]=clone;Link[now]=clone;while(p!=-1&&ch[p][c]==q) ch[p][c]=clone,p=Link[p];
            }
        }
        last=now;Ans++;v.pb(mp(now,-1));qu[id].pb(Ques(1,now,-1));
        dec(i,0,(int)v.size()-1) qu[id].pb(Ques(2,v[i].fi,v[i].se));
    }
    inline void dfs(int k,int fa){
        L[k]=++itot;if(cnt[k]==1) qu[n+1].pb(Ques(2,k,1));
        for(int to:e[k])if(to!=fa){dfs(to,k);}
        R[k]=itot;
    }
    inline void Build(){
        rep(i,1,tot) if(Link[i]!=-1){
            e[Link[i]].pb(i);
            // printf("Add %d %d\n",Link[i],i);
        }dfs(1,0);
    }
}sam;

inline void Solve(){
    // rep(i,1,n) printf("%d ",ans[i]);puts("");
    dec(i,1,n+1){
        for(Ques now:qu[i]) if(now.op==1) ans[i]+=bit.Ask(L[now.k]);
        else{
            if(now.k==1) continue;
            // printf("Ope Add %d %d\n",now.k,now.x);
            bit.Add(L[now.k],now.x);bit.Add(R[now.k]+1,now.x*(-1));
        }
    }
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);scanf("%s",s+1);
    rep(i,1,n) sam.Insert(s[i]-'0',i),ans[i]=sam.Ans;sam.Build();
    Solve();rep(i,1,n) printf("%d ",ans[i]);
    return 0;
}
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
#define N 300010
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

vi e[N];
int vis[N];

//表示 i 一定要比 j 排名靠前。
inline void Add(int i,int j){e[i+1].pb(j+1);}
inline void Clear(){
    rep(i,1,26) vis[i]=0,e[i].clear();
}
inline void Print(){
    rep(i,1,26){
        for(int to:e[i]){
            printf("edge u -> v %d %d\n",i,to);
        }
    }
}

struct Trie{
    struct Node{
        int ch[26],End;
        inline int& operator [] (const int a){return ch[a];}
    }p[N];
    int tot;
    inline Trie(){tot=0;}
    inline void Insert(string s){
        int len=s.length();
        int now=0;
        rep(i,0,len-1){
            if(!p[now][s[i]-'a']) p[now][s[i]-'a']=++tot;
            now=p[now][s[i]-'a'];
        }
        p[now].End++;
    }
    inline bool Build(string s){
        bool op=1;
        int now=0;
        int len=s.length();
        rep(i,0,len-1){
            int x=s[i]-'a';
            rep(j,0,25){
                if(j==x) continue;
                if(!p[now][j]) continue;
                Add(x,j);
            }
            now=p[now][x];
            if(p[now].End&&i!=len-1){
                op=0;break;
            }
        }
        return op;
    }
}st;

int n;
string s[N];
vc<string> ans;

inline bool dfs(int k,int cnt){
    vis[k]=cnt;
    for(int to:e[k]){
        if(vis[to]==cnt) return 1;
        if(vis[to]) continue;
        if(dfs(to,cnt)) return 1;
    }
    vis[k]=-1;
    return 0;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);rep(i,1,n) cin>>s[i];
    rep(i,1,n){
        st.Insert(s[i]);
    }
    rep(i,1,n){
        Clear();
        bool op=st.Build(s[i]);
        if(!op) continue;
        // puts("Here");
        // Print();puts("");
        op=1;
        rep(i,1,26){
            if(!vis[i]){
                if(dfs(i,i)){
                    op=0;
                    break;
                }
            }
        }

        if(op) ans.pb(s[i]);
    }
    printf("%d\n",(int)ans.size());
    for(string ss:ans) cout<<ss<<'\n';
    return 0;
}
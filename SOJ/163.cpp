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
#define N 100010
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

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int s[4],n,a[N][4],ans;
set<int> v[4];
struct Node{
    int val,id;
    inline Node(){}
    inline Node(int val,int id) : val(val),id(id) {}
    inline bool operator < (const Node &b)const{
        return (val!=b.val)?(val<b.val):id<b.id;
    }
};
priority_queue<Node> q,q1,q2;

inline void endpro(){
    printf("%lld\n",ans);exit(0);
}
inline void chk(){
    int sum=0;
    for(int i:v[1]){
        sum+=a[i][1];
    }
    for(int i:v[2]){
        sum+=a[i][2];
    }
    for(int i:v[3]){
        sum+=a[i][3];
    }
    if(sum==ans){}
    else puts("NOOOOOOO");
}
inline void chk2(){
    if(v[1].size()==s[1]&&v[2].size()==s[2]&&v[3].size()==s[3]&&s[1]+s[2]+s[3]==n){
        // puts("YES2");
    }
    else{
        printf("v[1].size()=%lld v[2].size()=%lld v[3].size()=%lld\n",(int)v[1].size(),(int)v[2].size(),(int)v[3].size());
    }
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    rep(i,1,3) read(s[i]);
    n=s[1]+s[2]+s[3];
    rep(i,1,n){
        rep(j,1,3) read(a[i][j]);
        if(a[i][1]>=a[i][2]&&a[i][1]>=a[i][3]) v[1].insert(i),ans+=a[i][1];
        else if(a[i][2]>=a[i][1]&&a[i][2]>=a[i][3]) v[2].insert(i),ans+=a[i][2];
        else v[3].insert(i),ans+=a[i][3];
    }
    int i1=-1;
    rep(i,1,3){
        if(v[i].size()>s[i]){i1=i;break;}
    }
    if(i1==-1) endpro();
    for(int id:v[i1]){
        // printf("i1=%lld id=%lld\n",i1,id);
        int maxx=-INF;
        rep(j,1,3) if(j!=i1){
            maxx=max(maxx,-a[id][i1]+a[id][j]);
        }
        // printf("maxx=%lld id=%lld\n",maxx,id);
        q.push({maxx,id});
    }
    while(v[i1].size()>s[i1]){
        // printf("siz=%lld\n",(int)v[i1].size());
        assert(q.size());
        Node top=q.top();q.pop();
        assert(v[i1].find(top.id)!=v[i1].end());
        v[i1].erase(top.id);
        int nowi=-1;
        rep(j,1,3) if(j!=i1){
            if(top.val==-a[top.id][i1]+a[top.id][j]){nowi=j;break;}
        }
        // printf("top.id=%lld top.val=%lld\n",top.id,top.val);
        // printf("nowi=%lld\n",nowi);
        ans+=top.val;
        v[nowi].insert(top.id);
    }
    // exit(0);
    int i2=-1;
    rep(j,1,3) if(v[j].size()>s[j]){i2=j;break;}
    if(i2==-1) endpro();
    int i3=-1;
    rep(j,1,3) if(j!=i1&&j!=i2) i3=j;
    while(q.size()) q.pop();
    for(int x:v[i2]){
        q.push({-a[x][i2]+a[x][i1],x});
    }
    for(int x:v[i1]){
        q1.push({-a[x][i1]+a[x][i3],x});
    }
    for(int x:v[i2]){
        q2.push({-a[x][i2]+a[x][i3],x});
    }
    while(v[i2].size()>s[i2]){
        Node t2=q2.top();
        Node t1=q1.top();
        Node t=q.top();
        if(t2.val>=t1.val+t.val){
            q2.pop();ans+=t2.val;
            v[i2].erase(t2.id);
            v[i3].insert(t2.id);
        }
        else{
            q1.pop();q.pop();
            v[i2].erase(t.id);
            v[i1].erase(t1.id);
            ans+=t1.val+t.val;
            v[i3].insert(t1.id);
            v[i1].insert(t.id);
            q1.push({-a[t.id][i1]+a[t.id][i3],t.id});
        }
    }
    chk();
    chk2();
    endpro();
    return 0;
}


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

int t,n;
P p[10];
map<int,int> cnt;

inline bool chk(int id){
    bool op=1;
    rep(i,0,2){
        if(id==i) continue;
        if(p[id].fi==p[i].fi||p[id].se==p[i].se) continue;
        op=0;
    }
    return op;
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(t);
    while(t--){
        read(n);
        int r1,c1,r2,c2,r3,c3;
        int x,y;
        read(r1);read(c1);read(r2);read(c2);read(r3);read(c3);
        read(x);read(y);
        p[0].fi=r1;p[0].se=c1;p[1].fi=r2;p[1].se=c2;p[2].fi=r3;p[2].se=c3;
        bool op=0;
        rep(i,0,2){
            // if(p[i].fi==1&&p[i].se==1){ op=0; break; }
            // if(p[i].fi==1&&p[i].se==n){ op=0; break; }
            // if(p[i].fi==n&&p[i].se==1){ op=0; break; }
            // if(p[i].fi==n&&p[i].se==n){ op=0; break; }
            if(p[i].fi!=1&&p[i].fi!=n&&p[i].se!=1&&p[i].se!=n){op=1;break;}
        }
        sort(p,p+3);
        if(!op){
            P now(-1,-1);
            rep(i,0,2) if(chk(i)) now=p[i];
            if(x!=now.fi&&y!=now.se){
                puts("NO");
            }
            else puts("YES");
            continue;
        }
        else{
            int id=-1;
            rep(i,0,2) if(chk(i)) id=i;
            sort(p,p+3);
            P now(-1,-1);
            if(id==0){
                now=mp(p[0].fi+1,p[0].se+1);
            }
            else if(id==2){
                now=mp(p[2].fi-1,p[2].se-1);
            }
            else if(id==1){
                // puts("Here");
                if(p[0].fi==p[1].fi) now=mp(p[1].fi+1,p[1].se-1);
                else now=mp(p[1].fi-1,p[1].se+1);
            }
            // printf("now.fi==%d now.se==%d\n",now.fi,now.se);
            if((x-now.fi)%2==0&&(y-now.se)%2==0){
                puts("NO");
            }
            else puts("YES");
        }
    }
}
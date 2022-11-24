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
#define N 2000100
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
const int Len=1e6;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

inline int lowbit(int x){return x&(-x);}

int f[N],n,m,len;
struct SegmentTree{
    #define ls(k) k<<1
    #define rs(k) k<<1|1
    struct Node{
        int t1,t2,sum,len,op;
        inline void Print(){
            printf("t1=%lld t2=%lld sum=%lld len=%lld\n",t1,t2,sum,len);
        }
    }p[N<<2];
    inline void A(int k,int x,int len){
        p[k].sum+=x*len;p[k].t1+=x;
    }
    inline void B(int k,int x){
        p[k].sum+=x*p[k].len;p[k].t2+=x;
    }
    inline void PushDown(int k){
        if(p[k].t1){
            A(ls(k),p[k].t1,f[p[ls(k)].len]);
            A(rs(k),p[k].t1,f[p[k].len]-f[p[ls(k)].len]-p[k].len);
            if(p[k].op){
                B(ls(k),p[k].t1);B(rs(k),p[k].t1);
            }
            p[k].t1=0;
        }
        if(p[k].t2){
            B(ls(k),p[k].t2);
            B(rs(k),p[k].t2);
            p[k].t2=0;
        }
    }
    inline void PushUp(int k){
        p[k].sum=p[ls(k)].sum+p[rs(k)].sum;
    }
    inline void Change(int k,int l,int r,int z,int y,int x){
        // printf("k=%lld l=%lld r=%lld z=%lld y=%lld x=%lld\n",k,l,r,z,y,x);
        if(z<=l&&r<=y){
            if(r-lowbit(r)+1==l){
                A(k,x,f[p[k].len]);
                return;
            }
            int mid=(l+r)>>1;PushDown(k);
            Change(ls(k),l,mid,z,y,x);
            Change(rs(k),mid+1,r,z,y,x);
            PushUp(k);
            return;
        }
        int mid=(l+r)>>1;
        PushDown(k);
        if(z<=mid) Change(ls(k),l,mid,z,y,x);
        if(mid<y) Change(rs(k),mid+1,r,z,y,x);
        PushUp(k);
    }
    inline int Ask(int k,int l,int r,int z,int y){
        if(z<=l&&r<=y){
            return p[k].sum;
        }
        int mid=(l+r)>>1,ans=0;
        PushDown(k);
        if(z<=mid) ans=ans+Ask(ls(k),l,mid,z,y);
        if(mid<y) ans=ans+Ask(rs(k),mid+1,r,z,y);
        PushUp(k);
        return ans;
    }
    inline void Build(int k,int l,int r){
        p[k].len=r-l+1;
        if(r-lowbit(r)+1==l) p[k].op=1;else p[k].op=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        Build(ls(k),l,mid);
        Build(rs(k),mid+1,r);
    }
}st;
signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    f[1]=1;
    for(int i=2;i<=Len;i<<=1){
        f[i]=2*(f[i/2])+(i/2);
        // printf("f[%lld]=%lld\n",i,f[i]);
    }
    read(n);read(m);
    int len=1;
    while(len<n) len<<=1;
    st.Build(1,1,len);
    rep(i,1,m){
        // printf("i=%lld\n",i);
        int op,l,r,v;
        read(op);read(l);read(r);
        if(op==1){
            read(v);
            st.Change(1,1,len,1,r,v);
            if(l!=1) st.Change(1,1,len,1,l-1,-v);
        }
        else{
            int ans=st.Ask(1,1,len,l,r);
            printf("%lld\n",ans);
        }
        // printf("p[9]:\n");st.p[9].Print();
        // printf("p[4]:\n");st.p[4].Print();
        // printf("p[18]:\n");st.p[18].Print();
        // printf("p[19]:\n");st.p[19].Print();
    }
    return 0;
}

/*

9 8
1 3 5 3
2 2 4
2 4 9
1 1 9 1
2 5 5
2 2 4
1 8 9 1
2 1 9

12
6
6
20
48
*/

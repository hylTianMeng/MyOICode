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
#define N 600010
#define M 1000100
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
const int mod=1004535809;
const int g=3;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

struct FastIO
{
    #define MB (1<<20)
    char ib[MB+100],*p,*q;
    char ob[MB+100],*r,stk[128];
    int tp;

    FastIO(){p=q=ib,r=ob,tp=0;}
    ~FastIO(){fwrite(ob,1,r-ob,stdout);}

    char read_char()
    {
        if(p==q)
        {
            p=ib,q=ib+fread(ib,1,MB,stdin);
            if(p==q)return 0;
        }
        return *p++;
    }
    template<typename T>
    void read_int(T& x)
    {
        char c=read_char(),l=0;
        for(x=0;!isdigit(c);c=read_char())l=c;
        for(;isdigit(c);c=read_char())x=x*10-'0'+c;
        if(l=='-')x=-x;
    }

    void write_char(char c)
    {
        if(r-ob==MB)r=ob,fwrite(ob,1,MB,stdout);
        *r++=c;
    }
    template<typename T>
    void write_int(T x) 
    {
        if(x<0)write_char('-'),x=-x;
        do stk[++tp]=x%10+'0';
        while(x/=10);
        while(tp)write_char(stk[tp--]);
    }
}IO;

int n,m,a[N],posi[N],Len,cnt[N],b[N];
int tr[N];
int A[N];

struct Ope{
    int l,r,L;
}q[M];

inline int gel(int id){return (id-1)*Len+1;}
inline int ger(int id){return min(n,id*Len);}
inline void Gettr(int len){
    rep(i,0,len-1) tr[i]=(tr[i>>1]>>1)|((i&1)?(len>>1):0);
}
inline int ksm(int a,int b,int mod){
    int res=1;while(b){if(b&1){res=1ll*res*a%mod;}a=1ll*a*a%mod;b>>=1;}return res;
}
inline int inv(int x){return ksm(x,mod-2,mod);}
inline void NTT(int *f,int n,int op){
    rep(i,0,n-1) if(i<tr[i]) swap(f[i],f[tr[i]]);
    for(int i=2;i<=n;i<<=1){
        int tg=ksm(g,(mod-1)/i,mod);
        if(op==-1) tg=inv(tg);
        for(int j=0;j<n;j+=i){
            int now=1;
            for(int k=j;k<j+i/2;k++){
                int tt=now*f[k+i/2]%mod;
                f[k+i/2]=(f[k]-tt+mod)%mod;
                f[k]=(f[k]+tt)%mod;
                now=now*tg%mod;
            }
        }
    }
    if(op==-1){
        int invn=inv(n);
        rep(i,0,n-1) f[i]=f[i]*invn%mod;
    }
}

signed main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    IO.read_int(n);rep(i,1,n) IO.read_int(a[i]);
    IO.read_int(m);
    rep(i,1,m){
        // read(q[i].l);read(q[i].r);read(q[i].L);
        IO.read_int(q[i].l);IO.read_int(q[i].r);IO.read_int(q[i].L);
    }
    Len=ceil(sqrt(log2(n)*n)*2.0);
    rep(i,1,n){
        posi[i]=(i-1)/Len+1;
    }
    rep(i,1,posi[n]){
        int l=gel(i),r=ger(i);
    }
    rep(j,1,m){
        int bl=q[j].L,br=min(n,q[j].L+q[j].r-q[j].l);
        int blid=posi[bl];
        int brid=posi[br];
        if(blid==brid){
            rep(i,bl,br){
                b[i]+=a[i-q[j].L+q[j].l];
            }
        }
        else{
            rep(i,bl,ger(blid)){
                b[i]+=a[i-q[j].L+q[j].l];
            }
            rep(i,gel(brid),br){
                b[i]+=a[i-q[j].L+q[j].l];
            }
        }
    }
    int len=1;
    while(len<(n+1)*2) len<<=1;
    Gettr(len);
    NTT(a,len,1);
    rep(i,1,posi[n]){
        int l=gel(i),r=ger(i);
        mset(cnt,0);
        rep(j,1,m){
            int bl=q[j].L,br=min(n,q[j].L+q[j].r-q[j].l);
            int blid=posi[bl];
            int brid=posi[br];
            if(blid<i&&i<brid){
                int len=l-bl+1;
                cnt[q[j].l+len-1]++;
            }
        }
        reverse(cnt+1,cnt+n+1);
        NTT(cnt,len,1);
        rep(j,0,len) cnt[j]=cnt[j]*a[j]%mod;
        NTT(cnt,len,-1);
        rep(j,l,r){
            int val=cnt[n+1+(j-l)];
            b[j]=(b[j]+val)%mod;
        }
    }
    // rep(i,1,n) printf("%lld\n",b[i]);
    rep(i,1,n){
        // printf("b[i]=%d\n",b[i]);
        IO.write_int(b[i]);
        IO.write_char('\n');
    }
    return 0;
}
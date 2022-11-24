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
#define N 66000
#define M 66000
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

int n,k,a[N],sum,b[N];
//change!
bitset<2001> f[N];
priority_queue<P > q;

inline void ge(int s,int x){
    if(!s) return;
    if(x*k<=2000&&f[s][x*k]==1){
        rep(i,0,n-1) if((s>>i)&1) b[i+1]++; 
        ge(s,x*k);return;
    }
    rep(i,1,n) if(((s>>(i-1))&1)&&x>=a[i]){
        if(f[s^(1<<(i-1))][x-a[i]]){ge(s^(1<<(i-1)),x-a[i]);return;}
    }
}

int main(){
    // freopen("my.in","r",stdin);
    // freopen("my.out","w",stdout);
    read(n);read(k);rep(i,1,n) read(a[i]);f[0][0]=1;
    rep(i,1,n) sum+=a[i];
    for(int i=0;i<(1<<n);i++){
        rep(j,1,n) if((i>>(j-1))&1){
            // puts("Here");
            // cout<<f[i^(1<<(j-1))]<<endl;
            // printf("a[j]=%d\n",a[j]);
            f[i]|=(f[i^(1<<(j-1))]<<a[j]);
        }
        dec(j,1,sum/k){
            // f[i][j]=f[i][j*k];
            if(f[i][j*k]){
                // printf("j=%d\n",j);
                f[i][j]=1;
            }
        }
        // printf("i=%d:\n",i);
        // cout<<f[i]<<endl;
    }
    if(!f[(1<<n)-1][1]){puts("NO");return 0;}
    else{
        puts("YES");
        ge((1<<n)-1,1);
        // rep(i,1,n) printf("b[%d]=%d\n",i,b[i]);
        rep(i,1,n) q.push({b[i],a[i]});
        while(q.size()>1){
            P n1=q.top();q.pop();
            P n2=q.top();q.pop();
            printf("%d %d\n",n1.se,n2.se);
            n1.se+=n2.se;
            while(n1.se%k==0){
                n1.se/=k;n1.fi--;
            }
            q.push(n1);
        }
    }
    return 0;
}
/*
+ DP 数组第二种转移赋值出现错误。
+ 递归没有设点结束条件
*/
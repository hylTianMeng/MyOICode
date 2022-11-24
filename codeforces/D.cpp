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

const int INF=1e9;
const dd eps=1e-9;

template<typename T> inline void read(T &x) {
    x=0; int f=1;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c == '-') f=-f;
    for(;isdigit(c);c=getchar()) x=x*10+c-'0';
    x*=f;
}

int t,n,a[N],k,b[N];

inline bool Check(int mid){
    int Ans=INF,cnt=0,nowans=0;
    rep(i,1,n) if(a[i]<(mid+1)/2) cnt++;
    rep(i,1,n-1){
        nowans=cnt;
        if(a[i]>=(mid+1)/2&&a[i]<mid) nowans++;
        if(a[i+1]>=(mid+1)/2&&a[i+1]<mid) nowans++;
        cmin(Ans,nowans);
    }
    return Ans<=k;
}

int main(){
    // freopen("my.in","r",stdin);
    read(t);
    rep(T,1,t){
        read(n);read(k);rep(i,1,n) read(a[i]);
        // if(t==10000){
        //     if(T!=193) continue;
        //     printf("%d %d\n",n,k);
        //     rep(i,1,n) printf("%d ",a[i]);
        //     exit(0);
        // }
        // else{
            int l=1,r=INF;
            // printf("Check(4)=%d\n",Check(4));

            while(l<r){
                int mid=(l+r+1)>>1;
                if(Check(mid)) l=mid;
                else r=mid-1;
            }
            printf("%d\n",l);
        // }
    }
    return 0;
}
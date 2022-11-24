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

int t,n,a[N];

int main(){
    // freopen("my.in","r",stdin);
    read(t);
    while(t--){
        read(n);rep(i,1,n) read(a[i]);
        if(n==1){
            printf("0\n");continue;
        }
        else if(n==2){
            printf("%d\n",max(a[1],a[2])-min(a[1],a[2]));continue;
        }
        int maxx=-INF,maxid=-1;
        rep(i,1,n){
            if(maxx<a[i]){maxx=a[i];maxid=i;}
        }
        int minn=INF,minid=-1;
        int ans=-INF;
        rep(i,1,n){
            if(minn>a[i]){minn=a[i];maxid=i;}
        }
        cmax(ans,maxx-a[1]);
        // printf("%d\n",ans);
        cmax(ans,a[n]-minn);
        rep(i,1,n){
            if(a[i]==maxx){
                int ne=i+1;if(ne==n+1) ne=1;
                cmax(ans,maxx-a[ne]);
            }
        }
        rep(i,1,n){
            if(a[i]==minn){
                int ne=i-1;if(ne==0) ne=n;
                cmax(ans,a[ne]-minn);
            }
        }
        rep(i,1,n){
            int ne=i-1;if(ne==0) ne=n;
            cmax(ans,a[ne]-a[i]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
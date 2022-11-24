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
#define N 11000100
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

int Len[N<<1],maxright,mid,n;
char a[N],b[N<<1];

inline void Manacher(){
    mid=0;maxright=0;
    rep(i,1,n){
        if(i<maxright) Len[i]=min(Len[(mid<<1)-i],maxright-i);else Len[i]=1;
        while(i+Len[i]<=n&&i-Len[i]&&b[i+Len[i]]==b[i-Len[i]]) Len[i]++;
        if(i+Len[i]>maxright) maxright=i+Len[i],mid=i;
    }
}

int main(){
    scanf("%s",a+1);int len=strlen(a+1);
    rep(i,1,len){
        b[i*2-1]='#';b[i*2]=a[i];
    }
    b[2*len+1]='#';n=2*len+1;
    Manacher();
    int ans=1;
    rep(i,1,n){
        if(b[i]=='#') cmax(ans,Len[i]-1);
        else cmax(ans,Len[i]-1);
    }
    printf("%d\n",ans);
    return 0;
}
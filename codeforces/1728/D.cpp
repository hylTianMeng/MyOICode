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
#define N 2100
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

string s;
int t,f[N][N];

//0 first win
//1 draw
//2 second win
inline int dfs(int l,int r){
    if(r-l+1==2){
        if(s[l]!=s[r]) return 0;
        else return 1;
    }
    // printf("f[l][r]=%d\n",f[l][r]);
    if(f[l][r]!=-1) return f[l][r];
    bool op1=1,op2=1;
    //first use s[l]
    int ans=3;
    if(s[l]>s[l+1]||s[l]>s[r]) op1=0;
    else{
        // puts("Here");
        int ans1=-1,ans2=-1;
        if(s[l]==s[l+1]) ans1=dfs(l+2,r);
        if(s[l]==s[r]) ans2=dfs(l+1,r-1);
        // printf("ans1=%d ans2=%d\n",ans1,ans2);
        if(ans1!=-1||ans2!=-1) cmin(ans,max(ans1,ans2));
        else return 0;
    }
    if(s[r]>s[r-1]||s[r]>s[l]) op2=0;
    else{
        // puts("Here");
        int ans1=-1,ans2=-1;
        if(s[r]==s[r-1]) ans1=dfs(l,r-2);
        if(s[l]==s[r]) ans2=dfs(l+1,r-1);
        // printf("ans1=%d ans2=%d\n",ans1,ans2);
        if(ans1!=-1||ans2!=-1) cmin(ans,max(ans1,ans2));
        else return 0;
    }
    // printf("ans=%d\n",ans);
    if(!op1&&!op2) return 2;
    assert(ans<=2);
    return ans;
}

int main(){
    freopen("my.in","r",stdin);
    freopen("my.out","w",stdout);
    read(t);
    while(t--){
        cin>>s;int n=s.length();
        rep(i,0,n)rep(j,0,n) f[i][j]=-1;
        int ans=dfs(0,n-1);
        if(ans==0) puts("Alice");
        else if(ans==1) puts("Draw");
        else puts("Bob");
    }
}
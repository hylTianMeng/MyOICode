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
#define N 200010
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

char s[N];
int len;

int main(){
    read(len);
    scanf("%s",s+1);
    if(len&1){
        if(s[1]!='A'||s[len]!='B') puts("Yes");
        else puts("No");
    }
    else{
        if(s[1]=='A'&&s[len]=='B') puts("No");
        else{
            int l=1,r=len;
            while(l<r-1){
                if(s[l]==s[r]) l++,r--;
                else if(s[l]=='A') l++,r--;
                else{l++;r--;s[l]='B';}
            }
            if(s[l]==s[r]) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
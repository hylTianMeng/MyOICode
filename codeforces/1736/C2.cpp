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
#define N 200010
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

int a[N],b[N],n,m,f[N],pre[N],suf[N];

struct SegmentTree{
	#define ls(k) k<<1
	#define rs(k) k<<1|1
	int val[N<<2];
	inline void push_up(int k){
		val[k]=min(val[ls(k)],val[rs(k)]);
	}
	inline void build(int k,int l,int r){
		if(l==r){
			val[k]=b[l];return;
		}
		int mid=(l+r)>>1;
		build(ls(k),l,mid);build(rs(k),mid+1,r);
		push_up(k);
	}
	inline int ask_min(int k,int l,int r,int z,int y){
		if(z<=l&&r<=y){
			return val[k];
		}int mid=(l+r)>>1,ans=INF;
		if(z<=mid) ans=min(ans,ask_min(ls(k),l,mid,z,y));
		if(mid<y) ans=min(ans,ask_min(rs(k),mid+1,r,z,y));
		return ans;
	}
}st;

signed main(){
	// freopen("my.in","r",stdin);
	// freopen("my.out","w",stdout);
	read(n);rep(i,1,n) read(a[i]);
	rep(i,1,n) b[i]=a[i]-i;
	b[n+1]=-INF;
	st.build(1,1,n+1);
	rep(i,1,n) f[i]=min(f[i-1]+1,a[i]);
	rep(i,1,n+1) pre[i]=pre[i-1]+f[i];
	suf[n]=a[n];
	// printf("spe=%lld\n",st.ask_min(1,1,n+1,4,4));
	dec(i,1,n-1){
		// printf("i=%d\n",i);
		int l=i+1,r=n+1;
		while(l<r){
			int mid=(l+r)>>1;
			if(st.ask_min(1,1,n+1,i+1,mid)<=a[i]-i) r=mid;
			else l=mid+1;
		}
		int q=l;
		// printf("q=%d\n",q);
		suf[i]=suf[q]+(1+q-i)*(q-i)/2+(a[i]-1)*(q-i);
		// printf("suf[i]=%d\n",suf[i]);
	}
	// rep(i,1,n) printf("%lld ",f[i]);puts("");
	read(m);
	rep(i,1,m){
		int p,x;read(p);read(x);
		int upt=min(f[p-1]+1,x);
		if(p==n){
			printf("%lld\n",pre[n-1]+upt);
			continue;
		}
		int l=p+1,r=n+1;
		while(l<r){
			int mid=(l+r)>>1;
			if(st.ask_min(1,1,n+1,p+1,mid)<=upt-p) r=mid;
			else l=mid+1;
		}
		int q=l;
		// printf("q=%lld\n",q);
		int ans=pre[p-1]+suf[q];
		// printf("ans=%lld\n",ans);
		ans=ans+(1+q-p)*(q-p)/2+(upt-1)*(q-p);
		printf("%lld\n",ans);
	}
	return 0;
}
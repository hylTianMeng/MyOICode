#include<bits/stdc++.h> 
#define N 100010
#define ll long long
#define fi first
#define int long long
#define se second
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

typedef pair<int,int> P;

template<typename T> inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) f*=(-1);
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x*=f;
}

int n,a[N],b[N],ans=0;

signed main(){
	freopen("my.in","r",stdin);
	freopen("my.out","w",stdout);
	read(n);
	rep(i,1,n) read(a[i]);
	rep(i,1,n) if(a[i]==0) b[i]=1;
	rep(i,1,n){
		ans+=a[i]/2;
		if(a[i]&1) a[i]=1;
		else a[i]=0;
	}
	for(int i=1,j;i<=n&&j<=n;i=j+1){
		j=i;while(!b[j]&&j<=n) j++;
		int cnt=0;
		rep(k,i,j-1) if(a[k]==1) cnt++;
		ans+=cnt/2;
	}
	// for(int i=1,j=0;i<=n&&j<=n;i=j+1){
	// 	j=i;while(a[j]&&j<=n) j++;
	// 	int sum=0;
	// 	rep(k,i,j-1) sum+=a[k];
	// 	ans+=sum/2;
	// }
	printf("%lld\n",ans);
	return 0;
}
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define int long long
#define N 41
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

typedef pair<int,int> P;

const int INF=0x3f3f3f3f;

template<typename T> inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=f*-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x*=f;
}

ll n,K,f[20][32][20][14][12][2][2],pw2[N],pw3[N],pw5[N],pw7[N],w,p[N];


inline ll calc(int j1,int j2,int j3,int j4){
	if(j1==100) return 0;
	return pw2[j1]*pw3[j2]*pw5[j3]*pw7[j4];
}
inline ll dfs(int pos,int j1,int j2,int j3,int j4,int lim,int pre){
	if(f[pos][j1][j2][j3][j4][lim][pre]!=-1) return f[pos][j1][j2][j3][j4][lim][pre];
	int &ans=f[pos][j1][j2][j3][j4][lim][pre];
	ans=0;
	if(pos==w+1){
		ans=1;	
//		printf("pos=%lld j1=%lld j2=%lld j3=%lld j4=%lld lim=%lld pre=%lld ans=%lld\n",pos,j1,j2,j3,j4,lim,pre,ans);
		return 1;
	}
	int up=(lim==1)?p[pos]:9;
	rep(i,0,up){
		int now=calc(j1,j2,j3,j4);
		if(now==0){
			ans=(ans+dfs(pos+1,100,0,0,0,lim&&(i==up),pre&&(i==0)));
			continue;
		}
			if(i==0){
				printf("pos=%d j1=%d j2=%d j3=%d j4=%d lim=%d pre=%d ans=%d\n",pos,j1,j2,j3,j4,lim,pre,ans);
				printf("ans=%d\n",ans);
				if(pre) ans=(ans+dfs(pos+1,j1,j2,j3,j4,lim&&(i==up),pre&&(i==0)));
				else ans=(ans+dfs(pos+1,100,0,0,0,lim&&(i==up),pre&&(i==0)));
				printf("ans=%d\n",ans);
				printf("pos=%d j1=%d j2=%d j3=%d j4=%d lim=%d pre=%d ans=%d\n",pos,j1,j2,j3,j4,lim,pre,ans);
			}
			else if(i==1){
				ans=(ans+dfs(pos+1,j1,j2,j3,j4,lim&&(i==up),0));
				puts("1");	
			}
			else if(i==2){
				ans=(ans+dfs(pos+1,j1+1,j2,j3,j4,lim&&(i==up),0));
//				puts("2");
			}
			else if(i==3){
				ans=(ans+dfs(pos+1,j1,j2+1,j3,j4,lim&&(i==up),0));
			}
			else if(i==4){
				ans=(ans+dfs(pos+1,j1+2,j2,j3,j4,lim&&(i==up),0));
			}
			else if(i==5){
				ans=(ans+dfs(pos+1,j1,j2,j3+1,j4,lim&&(i==up),0));
			}
			else if(i==6){
				ans=(ans+dfs(pos+1,j1+1,j2+1,j3,j4,lim&&(i==up),0));
			}
			else if(i==7){
				ans=(ans+dfs(pos+1,j1,j2,j3,j4+1,lim&&(i==up),0));
			}
			else if(i==8){
				ans=(ans+dfs(pos+1,j1+3,j2,j3,j4,lim&&(i==up),0));
			}
			else if(i==9){
				ans=(ans+dfs(pos+1,j1,j2+2,j3,j4,lim&&(i==up),0));
			}
	}
	printf("pos=%lld j1=%lld j2=%lld j3=%lld j4=%lld lim=%lld pre=%lld ans=%lld\n",pos,j1,j2,j3,j4,lim,pre,ans);
	return ans;
}
inline ll solve(int x){
	while(x){
		p[++w]=x%10;x/=10;
	}
	reverse(p+1,p+w+1);
//	exit(0);
	return dfs(1,0,0,0,0,1,1);
}

signed main(){
	freopen("my.in","r",stdin);
	freopen("my.out","w",stdout);
	read(n);read(K);
//	exit(0);
	pw2[0]=pw3[0]=pw5[0]=pw7[0]=1;
	rep(i,1,40){
		if(i<=30) pw2[i]=pw2[i-1]*2;
		if(i<=19) pw3[i]=pw3[i-1]*3;
		if(i<=13) pw5[i]=pw5[i-1]*5;
		if(i<=11) pw7[i]=pw7[i-1]*7;
	}
	memset(f,-1,sizeof(f));
	int ans=solve(n);
	printf("%lld\n",ans-1);
	return 0;
}
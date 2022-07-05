#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=5.4e5,maxm=12+5;
int m,n=1,t,p,b[maxm][maxm],phip;
struct cp{
	int a,b;
	cp operator +(cp x){
		return {(a+x.a)%p,(b+x.b)%p};
	}
	cp operator *(cp x){
		return {(int)((1ll*a*x.b%p+1ll*b*x.a%p-1ll*a*x.a%p+p)%p),(int)((1ll*b*x.b%p-1ll*a*x.a%p+p)%p)};
	}
	cp operator *(ll x){
		return {(int)(1ll*a*x%p),(int)(1ll*b*x%p)};
	}
    inline void Print(){
        printf("x=%d y=%d\n",a,b);
    }
}f[maxn],g[maxn];
cp ksm(cp a,int b){
	cp ans={0,1};
	while(b){
		if(b%2==1) ans=ans*a;
		a=a*a;
		b/=2;
	}
	return ans;
}
int phi(int n){
	int res=n;
	for(int i=2;i*i<=n;i++) if(n%i==0){
		res=1ll*res*(i-1)/i;
		while(n%i==0) n/=i;
	}
	if(n>1) res=1ll*res*(n-1)/n;
	return res;
}
int ksm(int a,int b){
	int ans=1;
	while(b){
		if(b%2==1) ans=1ll*ans*a%p;
		a=1ll*a*a%p;
		b/=2;
	}
	return ans;
}
void FWT(cp* f,int n,bool flag){
	for(int i=1;i<n;i*=3) for(int j=0;j<n;j+=i*3) for(int k=j;k<j+i;k++){
		cp t0=f[k],t1=f[k+i],t2=f[k+i*2];
		if(flag){
			f[k]=t0+t1+t2;
			f[k+i]=t0+t1*(cp){1,0}+t2*(cp){p-1,p-1};
			f[k+i*2]=t0+t1*(cp){p-1,p-1}+t2*(cp){1,0};
		}
		else{
			f[k]=t0+t1+t2;
			f[k+i]=t0+t1*(cp){p-1,p-1}+t2*(cp){1,0};
			f[k+i*2]=t0+t1*(cp){1,0}+t2*(cp){p-1,p-1};
            // int invn=ksm(n,phip-1);
            // f[k]=f[k]*invn;
            // f[k+i]=f[k+i]*invn;
            // f[k+i*2]=f[k+i*2]*invn;
		}
	}
	if(!flag){
		int invn=ksm(n,phip-1);
        printf("inv3=%d\n",invn);
		for(int i=0;i<n;i++) f[i]=f[i]*invn;
	}
}
int main(){
	freopen("my.in","r",stdin);
	freopen("std.out","w",stdout);
	m=readint();
	for(int i=0;i<m;i++) n*=3;
	t=readint();
	p=readint();
	for(int i=0;i<n;i++) f[i].b=readint();
	for(int i=0;i<=m;i++) for(int j=0;j<=m-i;j++) b[i][j]=readint();
	for(int i=0;i<n;i++){
		int x=i,cnt1=0,cnt2=0;
		for(int j=0;j<m;j++){
			if(x%3==1) cnt1++;
			else if(x%3==2) cnt2++;
			x/=3;
		}
		g[i].b=b[cnt1][cnt2];
	}
	phip=phi(p);
	FWT(f,n,1);
	FWT(g,n,1);
    for(int i=0;i<n;i++) ksm(g[i],t).Print();
	for(int i=0;i<n;i++) f[i]=f[i]*ksm(g[i],t);
    for(int i=0;i<n;i++) f[i].Print();
	FWT(f,n,0);
	for(int i=0;i<n;i++) printf("%d\n",f[i].b);
	#ifdef LOCAL
	fprintf(stderr,"%f\n",1.0*clock()/CLOCKS_PER_SEC);
	#endif
	return 0;
}
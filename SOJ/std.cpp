#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+ch-'0';
		ch=getchar();
	}
	return x*f;
} 
inline void write(int x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
unordered_map<int,int>f[2][2][21];
int n,k,a[21];
inline int dfs(bool flag,bool ok,int x,int y){
	if(!x){
		if(y<=k) return 1;
		else return 0;
	}
	if(f[flag][ok][x].count(y)) return f[flag][ok][x][y];
	int ans=0;
	for(int i=0;i<=(ok?a[x]:9);i++){
		if(flag)
			ans+=(i==0)?dfs(flag,ok&&i==a[x],x-1,y):dfs(0,ok&&i==a[x],x-1,i);
		else
			ans+=dfs(flag,ok&&i==a[x],x-1,y*i);
	}
	return f[flag][ok][x][y]=ans;
}
inline void solve(){
	n=read(),k=read();
	int tot=0;
	while(n){
		a[++tot]=n%10;
		n/=10;
	}
	write(dfs(1,1,tot,0)-1);
	return ;
}
signed main(){
	// freopen("my.in","r",stdin);
	// freopen("std.out","w",stdout);
	solve();
	return 0;
}
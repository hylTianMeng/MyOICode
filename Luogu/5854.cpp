#include<iostream>
#include<cstdio>
#include<stack>
#define NUM 10000010
// #define int int
using namespace std;

int n;
struct dian{
	int fa,lc,rc;
	int zhi;
};
dian a[NUM];
stack <int> st;

inline int read(){
    int x = 0,f = 1;
	char ch = getchar();
    while( !isdigit(ch) ){
		if(ch=='-') f=-1;ch=getchar();
	}
    while( isdigit(ch) ){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
    return x*f;
}


signed main(){
	// n = read();
	// for( int i = 1;i <= n;i++ ){
	// 	a[i].zhi = read();
	// 	while( !st.empty() && a[st.top()].zhi > a[i].zhi ){
	// 		a[i].lc = st.top();
	// 		st.pop();
	// 	}
	// 	if( !st.empty() ){
	// 		a[st.top()].rc = i;
	// 	}
	// 	st.push( i );
	// }
	// long long lans = 0,rans = 0;
	// for( int i = 1;i <= n;i++ ){
	// 	lans ^= 1ll * i * ( a[i].lc + 1 );
	// 	rans ^= 1ll * i * ( a[i].rc + 1 );
	// }
	// printf( "%lld %lld",lans,rans );
	
	return 0;
}
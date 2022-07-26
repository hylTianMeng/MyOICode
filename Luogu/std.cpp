#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int INF = 1e18;
double DINF = 1e18;
vector<vector<int> > Data;
int ans = INF;
vector<int> dp, sz;
int n;
struct Line{double k; double b; double l; double r;};
vector<Line> cht;
int ask(int x){
    int L = 0, R = cht.size();
    double cp = x;
    while (R-L>1){
        int M = (L+R)/2;
        if (cht[M].r >= cp) L = M;
        else R = M;
    }
    int K = cht[L].k, B = cht[L].b;
    return K*x+B;
}
double intersect(Line &a, Line &b){
    if (a.k == b.k) return -DINF;
    double db = a.b - b.b;
    double dk = b.k - a.k;
    return db/dk;
}
void add(double k, double b){
    Line nl = {k, b, -DINF, DINF};
    while (cht.size()){
        double inter = intersect(nl, cht.back());
        if (inter <= cht.back().l){
            cht.pop_back();
        }
        else{
            cht.back().r = inter;
            nl.l = inter;
            cht.push_back(nl);
            break;
        }
    }
    if (!cht.size()) cht.push_back(nl);
}
void calc(int vertex, int last){
    vector<pair<int, int> > children;
    int cur=0;
    for (int i=0; i < Data[vertex].size(); i++){
        int to = Data[vertex][i];
        if (to == last) continue;
        children.push_back({sz[to], dp[to]});
        cur++;
    }
    if (cur==1) return;
    sort(children.begin(), children.end(), greater<pair<int, int> > ());
    for (int i=0; i < children.size(); i++){
        int SZ = children[i].first, DP = children[i].second;
        if (i > 0){
            int res = ask(SZ);
            ans = min(ans, res + DP + n*n + SZ*SZ - 2*n*SZ);
        }
        int K = 2*SZ;
        int B = DP+SZ*SZ-2*n*SZ;
        add(K, B);
    }
}
void dfs(int vertex, int last){
    sz[vertex] = 1;
    for (int i=0; i < Data[vertex].size(); i++){
        int to = Data[vertex][i];
        if (to == last) continue;
        dfs(to, vertex);
        sz[vertex] += sz[to];
    }
    if (sz[vertex] == 1) dp[vertex] = 1;
    else{
        dp[vertex] = INF;
        for (int i=0; i < Data[vertex].size(); i++){
            int to = Data[vertex][i];
            if (to == last) continue;
            dp[vertex] = min(dp[vertex], dp[to] + (sz[vertex] - sz[to]) * (sz[vertex] - sz[to]));
        }
    }
    calc(vertex, last);
}
signed main() {
	freopen("my.in","r",stdin);
	freopen("std.out","w",stdout);
    ios_base::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    Data.resize(n, {});
    dp.resize(n, -1);
    sz.resize(n, -1);
    for (int i=0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        Data[u-1].push_back(v-1), Data[v-1].push_back(u-1);
    }
    if (n==2){
        cout << 2;
        return 0;
    }
    int father = -1;
    for (int i=0; i < n; i++){
        if (Data[i].size() > 1) father = i;
    }
    dfs(father, -1);
    int res = 2*n*(n-1) - (ans - n);
    cout << res/2;
    return 0;
}
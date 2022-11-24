#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>

#define Heriko return
#define Deltana 0
#define Romanno 1
#define S signed
#define LL long long
#define DB double
#define R register
#define I inline
#define CI const int
#define CL const long long
#define mkp(a,b) make_pair(a,b)
#define mst(a,b) memset(a,b,sizeof(a))
#define ON std::ios::sync_with_stdio(false);cin.tie(0)
#define Files() freopen("my.in","r",stdin);freopen("my.out","w",stdout)

using namespace std;

template<typename J>
I void fr(J &x) {
    short f(1);
    x=0;
    char c(getchar());

    while(c<'0' or c>'9') {
        if(c=='-')
            f=-1;

        c=getchar();
    }

    while(c>='0' and c<='9') {
        x=(x<<3)+(x<<1)+(c^=48);
        c=getchar();
    }

    x*=f;
}

template<typename J>
I void fw(J x,bool k) {
    if(x<0)
        x=-x,putchar('-');

    static short stak[35];
    short top(0);

    do {
        stak[top++]=x%10;
        x/=10;
    }
    while(x);

    while(top)
        putchar(stak[--top]+'0');

    k?puts(""):putchar(' ');
}

CI MXX(5e4+5),MOD(201314);

struct Edge {
    int nex,to;
}

r[MXX<<1];

int head[MXX],rcnt;

I void Add(int x,int y) {
    r[++rcnt]=(Edge){head[x],y},head[x]=rcnt;
    r[++rcnt]=(Edge){head[y],x},head[y]=rcnt;
}

int dep[MXX],fa[MXX],sz[MXX],son[MXX];

void DFS1(int x,int fath) {
    dep[x]=dep[fath]+1,sz[x]=1,fa[x]=fath;

    for(int i(head[x]);i;i=r[i].nex) {
        int y(r[i].to);

        if(y==fath)
            continue;

        DFS1(y,x);
        sz[x]+=sz[y];

        if(sz[y]>sz[son[x]])
            son[x]=y;
    }
}

int idcnt,id[MXX],antid[MXX],top[MXX];

void DFS2(int x,int tp) {
    top[x]=tp,id[x]=++idcnt,antid[idcnt]=x;
    
    if(son[x])
        DFS2(son[x],tp);

    for(int i(head[x]);i;i=r[i].nex) {
        int y(r[i].to);

        if(y==fa[x] or y==son[x])
            continue;

        DFS2(y,y);
    }
}

struct Node {
    int l,r,v,tg;
}

t[MXX<<2];

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)

I void Pushup(int x) {
    t[x].v=(t[lc(x)].v+t[rc(x)].v)%MOD;
}

I void Pushdown(int x) {
    if(t[x].tg) {
        int mid((t[x].l+t[x].r)>>1);
        t[lc(x)].v+=t[x].tg*(mid-t[x].l+1);
        t[rc(x)].v+=t[x].tg*(t[x].r-mid);
        t[lc(x)].tg+=t[x].tg;
        t[rc(x)].tg+=t[x].tg;
        t[x].tg=0;
    }
}

void Build(int x,int l,int r) {
    t[x].l=l,t[x].r=r,t[x].tg=t[x].v=0;

    if(l==r)
        Heriko;

    int mid((l+r)>>1);
    Build(lc(x),l,mid);
    Build(rc(x),mid+1,r);
}

void Modify(int x,int lx,int rx) {
    if(lx<=t[x].l and t[x].r<=rx) {
        (t[x].tg+=1)%=MOD;
        (t[x].v+=(t[x].r-t[x].l+1))%=MOD;

        Heriko;
    }

    Pushdown(x);
    int mid((t[x].l+t[x].r)>>1);

    if(lx<=mid)
        Modify(lc(x),lx,rx);

    if(rx>mid)
        Modify(rc(x),lx,rx);

    Pushup(x);
}

int Query(int x,int lx,int rx) {
    if(lx<=t[x].l and t[x].r<=rx)
        Heriko t[x].v%MOD;

    Pushdown(x);
    int mid((t[x].l+t[x].r)>>1),res(0);

    if(lx<=mid)
        res+=Query(lc(x),lx,rx);

    if(rx>mid)
        res+=Query(rc(x),lx,rx);

    Heriko res%MOD;
}

I void MTree(int x,int y) {
    while(top[x]!=top[y]) {
        if(dep[x]<dep[y])
            swap(x,y);

        Modify(1,id[top[x]],id[x]);
        x=fa[top[x]];
    }

    if(dep[x]>dep[y])
        swap(x,y);

    Modify(1,id[x],id[y]);
}

I int QTree(int x,int y) {
    int res(0);

    while(top[x]!=top[y]) {
        if(dep[x]<dep[y])
            swap(x,y);

        (res+=Query(1,id[top[x]],id[x]))%=MOD;
        x=fa[top[x]];
    }

    if(dep[x]>dep[y])
        swap(x,y);

    (res+=Query(1,id[x],id[y]))%=MOD;

    Heriko res%MOD;
}

struct QList {
    int ans1,ans2;

    QList() {
        ans1=ans2=0;
    }

    I int ANS() {
        Heriko (ans1+MOD-ans2)%MOD;
    }
}

ans[MXX];

struct QueryQue {
    int id,pos,v,flg;

    QueryQue() {
        id=pos=v=flg=0;
    }

    QueryQue(int x,int y,int z,int w) {
        id=x,pos=y,v=z,flg=w;
    }

    I bool operator < (const QueryQue &x) const {
        Heriko pos<x.pos;
    }

    I bool operator > (const QueryQue &x) const {
        Heriko pos>x.pos;
    }
}

Q[MXX<<1];

int n,m,qn;

S main() {
    // Files();

    // fr(n),fr(m);

    for(int i(2);i<=n;++i) {
        int knd;
        // fr(knd);
        Add(knd+1,i);
    }

    for(int i(1);i<=m;++i) {
        int l,r,x;
        // fr(l),fr(r),fr(x);
        Q[++qn]=QueryQue(i,l,x+1,0);
        Q[++qn]=QueryQue(i,r+1,x+1,1);
    }

    DFS1(1,0);
    DFS2(1,1);
    Build(1,1,n);
    sort(Q+1,Q+1+qn);

    // for(int i(1);i<=n;++i)
    //     cout<<dep[i]<<endl;

    int nw(0);

    for(int i(1);i<=qn;++i) {
        while(nw<Q[i].pos)
            MTree(1,++nw);

        int knd(Q[i].id);

        if(Q[i].flg)
            ans[knd].ans1=QTree(1,Q[i].v);
        else
            ans[knd].ans2=QTree(1,Q[i].v);
    }

    // cout<<QTree(1,n)<<endl;

    for(int i(1);i<=m;++i)
        fw(ans[i].ANS(),1);

    Heriko Deltana;
}
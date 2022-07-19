#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <string>

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
#define Files() freopen("RNMTQ.in","r",stdin);freopen("RNMTQ.out","w",stdout)

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

CI MXX(2022),WXX(1005);

string s1,s2;

int a[MXX],tg[MXX],n1,n2,cnt,n;

map<string,int> id;
map<int,string> antid;
bool space[WXX],co[MXX];
pair<int,int> wrd[WXX];
set<int> s[WXX];

I void Split() {
    int l(0),r(0),lst(0);
    string nw;

    while(l<n1) {
        while(('a'<=s1[r] and s1[r]<='z') or ('A'<=s1[r] and s1[r]<='Z'))
            ++r;

        nw=s1.substr(l,r-l);

        if(!id[nw])
            id[nw]=++cnt,antid[cnt]=nw;

        if(s1[r]==' ')
            space[id[nw]]=1;

        if(space[lst])
            s[lst].insert(id[nw]);

        lst=id[nw];

        while(!(('a'<=s1[r] and s1[r]<='z') or ('A'<=s1[r] and s1[r]<='Z')))
            ++r;

        l=r;
    }

    l=r=0;
    int tmp(cnt);

    while(l<n2) {
        while(('a'<=s2[r] and s2[r]<='z') or ('A'<=s2[r] and s2[r]<='Z'))
            ++r;

        nw=s2.substr(l,r-l);

        if(!id[nw])
            id[nw]=++cnt,antid[cnt]=nw;

        a[++n]=id[nw];
        wrd[n]=mkp(l,r-1);

        if(id[nw]<=tmp and space[id[nw]])
            co[n]=1;

        while(!(('a'<=s2[r] and s2[r]<='z') or ('A'<=s2[r] and s2[r]<='Z')))
            ++r;

        l=r;
    }
}

I void TagMaker() {
    for(int i(1);i<=n;++i)
        if(co[i] and !co[i-1] and !co[i+1])
            co[i]=0;

    // for(int i(1);i<=n;++i)
    //     fw((int)co[i],0);

    // puts("");

    int lst(0),nw(0);

    for(int i(1);i<n;++i) {
        if(co[i] and co[i+1]) {
            if(!s[a[i]].count(a[i+1]))
                co[i]=0;
            else
                nw=1;
        }
        else
            nw=0;

        if(lst)
            co[i]=1;

        lst=nw;
    }

    // for(int i(1);i<=n;++i)
    //    fw((int)co[i],0);

    // puts("");

    int fst(1),l(1);

    for(int i(1);i<=n;++i)
        if(co[i]) {
            fst=l=i;

            break;
        }

    for(int i(fst);i<=n;++i) {
        if(!co[i]) {
            int r(i-1);
            tg[wrd[l].first]=1,tg[wrd[r].second]=2;

            while(!co[i]) {
                ++i;

                if(i==n)
                    break;
            }

            l=i;
        }
    }

    for(int i(0);i<n2;++i) {
        if(tg[i]==1)
            cout<<"<b>";

        cout<<s2[i];

        if(tg[i]==2)
            cout<<"</b>";
    }

}

I void Tolower() {
    for(int i(0);i<n1;++i)
        s1[i]=tolower(s1[i]);

    for(int i(0);i<n2;++i)
        s2[i]=tolower(s2[i]);
}

S main() {
    // Files();

    getline(cin,s1),getline(cin,s2);
    n1=s1.size(),n2=s2.size();
    Tolower();Split();TagMaker();

    Heriko Deltana;
}

}
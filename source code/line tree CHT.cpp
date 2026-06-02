#include "bits/stdc++.h"
using namespace std;
#define pb push_back
#define int long long
using ll = long long;
#define sz(x) (int)((x).size())
const int maxn = 3e5+69;
vector<int> g[maxn];
int a[maxn],b[maxn],res[maxn];
int pre[maxn],suf[maxn],st[maxn],en[maxn];
int timer = 0;
vector<pair<int,int>> que[maxn];
int n,q;
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    static const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
}nig[maxn],pref,suff;
int par[maxn][22];
int diz[maxn];
int tour[maxn];
void dfs(int node,int pa){
    timer++;
    st[node] = timer;
    tour[timer] = node;
    for(auto x : g[node]){
        if(x != pa){
            diz[x] = diz[node] + 1;
            par[x][0] = node;
            for(int i = 1; i <= 19 ; i++) par[x][i] = par[par[x][i-1]][i-1];
            dfs(x,node);
        }
    }
    en[node] = timer;
}
int jump(int node,int dizz){
    if(dizz < 0) return node;
    for(int i = 0 ; (1<<i) <= dizz ; i++){
        if((dizz>>i)&1) node = par[node][i];
    }
    return node;
}
void dfs_que(int u, int pre = -1){
    for(int v : g[u]){
        if(v == pre)
            continue;
        dfs_que(v, u);
        if(sz(nig[v]) > sz(nig[u]))
            swap(nig[u],nig[v]);
        for(Line x : nig[v]) nig[u].add(x.k, x.m);
        nig[v].clear();
    }
    nig[u].add(a[u], b[u]);
    for(auto [id, x] : que[u])
        res[id] = max(res[id], nig[u].query(x));
}
struct type{
    int val,num,id;
};
vector<type> off[maxn];
int ban[maxn];
signed main(){
    cin >> n >> q;
    for(int i = 1; i <= n ; i++) cin >> a[i];
    for(int i = 1; i <= n ; i++) cin >> b[i];
    for(int i = 1; i <= n-1 ; i++){
        int u,v; cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs(1,0);
    int root = 1;
    for(int i = 1;  i <= q ; i++){
        int T; cin >> T;
        if(T == 1){
            ban[i] = 1;
            cin >> root;
        }
        else{
            int u,x; cin >> u >> x;
            if(st[u] < st[root] && en[root] <= en[u]){
                //cout << i << "check\n";
                int upper = jump(root,diz[root] - diz[u] - 1);
                off[st[upper]-1].pb({x,1,i});
                off[en[upper]+1].pb({x,2,i});
            }
            else if(u == root){
                off[n].pb({x,1,i});
            }
            else que[u].pb({i,x});
        }
    }
    for(int i = 1; i <= n ;i++){
        pref.add(a[tour[i]],b[tour[i]]);
        for(auto X : off[i]){
            if(X.num == 1){
                res[X.id] = max(res[X.id],pref.query(X.val));
            }
        }
    }
    for(int i = n; i >= 1 ;i--){
        suff.add(a[tour[i]],b[tour[i]]);
        for(auto X : off[i]){
            if(X.num == 2){
                res[X.id] = max(res[X.id],suff.query(X.val));
            }
        }
    }
    dfs_que(1);
    for(int i = 1; i <= q ; i++) if(!ban[i]) cout << res[i] << '\n';
}
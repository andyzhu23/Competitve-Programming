/*
 * Author: Andy Zhu
 * 
 * just a noob, what is coding?
 *
 * “Do we run the trails, or the trails run us? Get revenge on the trails that ran u like that” 
 * I pray the cows
 * My Dream School:
 * South Harmon Institute of Technology
 * The meaning of life is:
 * #define int long long
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <memory>
#include <string>
#include <algorithm>
#include <bitset>
#include <iterator>
#include <deque>
#include <random>
#define endl "\n"
#define l_b lower_bound
#define u_b upper_bound
#define ins insert
#define fir first
#define sec second
#define lc (rt << 1)
#define rc (rt << 1 | 1)
#define pb push_back
#define pf push_front
#define mp make_pair
#define random(a, b) rand() % (b - a + 1) + a
#define log(a, b) log(a) / log(b)
using ll = long long;
using lb = long double;
using namespace std;
typedef pair<int, int> PI;
typedef pair<ll, ll> PLL;
typedef pair<string, string> PS;
typedef vector<int> VI;
typedef vector<PI> VPI;
typedef vector<ll> VLL;
typedef vector<PLL> VPLL;
typedef queue<int> QI;
typedef stack<int> STKI;
typedef deque<int> DQI;
typedef set<int> SI;
typedef set<ll> SLL;
typedef set<string> SS;
typedef unordered_set<int> USI;
typedef unordered_set<ll> USLL;
typedef unordered_set<string> USS;
typedef map<int, int> MI;
typedef map<ll, ll> MLL;
typedef map<string, string> MS;
typedef unordered_map<int, int> UMI;
typedef unordered_map<ll, ll> UMLL;
typedef unordered_map<string, string> UMS;
const int INF = 1e9;
const int MOD = 1e9 + 7;

inline void copy(int a[], int b[], int sz){
    for(int i = 0;i<=sz;i++)
        a[i] = b[i];
}

inline int gcd(int a, int b){
    if(a == 0) return b;
    if(b == 0) return a;
    return gcd(b, a % b);
}

inline int lcm(int a, int b){
    return a * b / gcd(a, b);
}

inline int getMid(int l, int r){
    return (l + r) >> 1;
}

inline ll fast_pow(ll a, ll b){
    if(b == 1) return a;
    ll tmp = fast_pow(a, b / 2);
    if(b % 2 == 1) return tmp * tmp * a;
    else return tmp * tmp;
}

inline bool is_prime(ll x){
    for(ll i = 2; i * i <= x;i++){
        if(x % i == 0) return false;
    }
    return true;
}

const int N = 1e5 + 10;
int n, m, a[N], dep[N], f[N][30], cnt[N];
VI e[N], query[N];
UMI res[N];

inline void dfs(int u, int fa, int d){
    dep[u] = d;
    f[u][0] = fa;
    for(int i = 1;i<=20;i++){
        f[u][i] = f[f[u][i - 1]][i - 1];
    }
    for(int i = 0;i<e[u].size();i++){
        int v = e[u][i];
        if(v == fa) continue;
        dfs(v, u, d + 1);
    }
}

inline int LCA(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 20;i>=0;i--){
        if(dep[f[x][i]] >= dep[y]) x = f[x][i];
        if(x == y) return x; 
    }
    for(int i = 20;i>=0;i--){
        if(f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

inline void dfs2(int u, int fa){
    cnt[a[u]] ++;
    if(!query[u].empty()){
        for(int i = 0;i<query[u].size();i++){
            int c = query[u][i];
            res[u][c] = cnt[c];
        }
    }

    for(int i = 0;i<e[u].size();i++){
        int v = e[u][i];
        if(v == fa) continue;
        dfs2(v, u);
    }
    cnt[a[u]]--;
}

struct q{
    int a, b, c, lca;
} qs[N];

inline void file(){
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
}

int main(){
    srand(time(0));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    file();
    cin>>n>>m;
    for(int i = 1;i<=n;i++) cin>>a[i];
    for(int i = 1;i<n;i++){
        int a, b;
        cin>>a>>b;
        e[a].pb(b);
        e[b].pb(a);
    }
    dfs(1, 0, 1);
    for(int i = 1;i<=m;i++){
        int a, b, c;
        cin>>a>>b>>c;
        query[a].pb(c);
        query[b].pb(c);
        int lca = LCA(a, b);
        query[lca].pb(c);
        qs[i].a = a;
        qs[i].b = b;
        qs[i].c = c;
        qs[i].lca = lca;
    }
    dfs2(1, 0);
    for(int i = 1;i<=m;i++){
        int A = qs[i].a;
        int b = qs[i].b;
        int c = qs[i].c;
        int lca = qs[i].lca;
        int Sum = res[A][c] + res[b][c] - 2 * res[lca][c] + (a[lca] == c);
        cout<<((Sum > 0) ? 1 : 0);
    }
    cout<<endl;
    return 0;
}

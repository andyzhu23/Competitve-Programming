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
#include <memory.h>
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
#define UM unordered_map;
#define US unordered_set;
#define V vector;
#define all(v) v.begin(), v.end()
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
const int dir[8][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}, {-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
inline int lowbit(int x){return x & (- x);}
inline bool CMP(int a, int b){return a > b;}
inline void copy(int a[], int b[], int sz){for(int i = 0;i<=sz;i++) a[i] = b[i];}
inline int gcd(int a, int b){if(a == 0) return b; if(b == 0) return a; return gcd(b, a % b);}
inline int lcm(int a, int b){return a / gcd(a, b) * b;}
inline int getMid(int l, int r){return (l + r) >> 1;}
inline ll fast_pow(ll a, ll b){if(b == 1) return a;ll tmp = fast_pow(a, b / 2);if(b % 2 == 1) return tmp * tmp * a;else return tmp * tmp;}
inline bool is_prime(ll x){for(ll i = 2; i * i <= x;i++) if(x % i == 0) return false; return true;}

const int N = 1e6 + 10;
int n, q, a[N], v[N], st[N << 2];
UMI Map;

VI lft;

inline void build(int rt, int l, int r){
    if(l == r){
        st[rt] = v[l];
        return;
    }
    int mid = getMid(l, r);
    build(lc, l, mid);
    build(rc, mid + 1, r);
    st[rt] = max(st[lc], st[rc]);
}

inline int query(int rt, int l, int r, int x, int y){
    if(x == l && y == r){
        return st[rt];
    }
    int mid = getMid(l, r);
    if(y <= mid) return query(lc, l, mid, x, y);
    else if(x > mid) return query(rc, mid + 1, r, x, y);
    else return max(query(lc, l, mid, x, mid), query(rc, mid + 1, r, mid + 1, y));
}

int main(){
    srand(time(0));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    int l = 1;
    for(int i = 1;i<=n;i++){
        cin>>a[i];
        Map[a[i]]++;
        while(Map[a[i]] > 1)
            Map[a[l++]]--;
        v[i] = i - l + 1;
        lft.pb(l);
    }
    lft.pb(n + 1);
    build(1, 1, n);
    int ans = 0;
    while(q--){
        int l, r;
        cin>>l>>r;
        l ^= ans;
        r ^= ans;
        ans = query(1, 1, n, r, u_b(all(lft), l) - lft.begin());
        cout<<ans<<endl;
    }

    return 0;
}

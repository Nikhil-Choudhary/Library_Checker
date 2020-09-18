// https://judge.yosupo.jp/problem/range_affine_range_sum
// (range update range query)
// update ->(l,r) arr[i] = a*arr[i] + b for every i in (l, r)
// query -> (l,r) sum of arr[i] for every i in (l,r)
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
#define ordered_set tree<int,null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 
#define ordered_set_pair tree<pair<int,int>,null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update> 
#define ordered_set_mutiset tree<int,null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
typedef long long int ll;
typedef long double ld;
typedef unsigned long long int ull;
typedef pair<int,int> pi; 
#define PI 3.1415926535897932384
#define FOR(i,vv,n) for(int i=vv;i<n;i++)
#define FORR(i,n,vv) for(int i=n-1;i>=vv;i--)
#define ve vector 
#define maxind(v) (max_element(v.begin(),v.end())-v.begin())
#define minind(v) (min_element(v.begin(),v.end())-v.begin())
#define maxe(v) *max_element(v.begin(),v.end())
#define mine(v) *min_element(v.begin(),v.end())
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define eb emplace_back
#define FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mp make_pair
#define M 1000000007ll
#define INF 1000000000000000000ll
#define PRECISE cout.precision(18);
#define BS(v,n) binary_search(v.begin(),v.end(),n)
#define srt(v) sort(v.begin(),v.end())
#define rsrt(v) sort(v.begin(),v.end(),greater <ll>())
#define uni(v) v.resize(unique(v.begin(),v.end())-v.begin())
#define c first
#define d second
#define GET(i,p) get<p>(i)

ll m=998244353; // mod with

ll const maxn=500000+5; // max length of arr

ll segtree[4*maxn]; // main segtree array
pair<ll,ll> lazy[4*maxn]; // lazy segtree array

// function to perform a common opration at a vertex 
void fun(ll st, ll c2, ll d2, ll l, ll r){
	segtree[st] = (segtree[st]*c2%m + d2*(r-l+1)%m) % m;
	lazy[st].c = lazy[st].c*c2%m;
	lazy[st].d = (lazy[st].d*c2%m + d2) % m;
}


void push(ll st, ll l, ll r){
	if(lazy[st].c != 1 || lazy[st].d != 0){  // to check is upadate is req. saves a lot of time
		ll mid = (l + r) >> 1;
		fun((st<<1), lazy[st].c, lazy[st].d, l, mid);
		fun((st<<1)+1, lazy[st].c, lazy[st].d, mid+1, r);
		lazy[st].c = 1;
		lazy[st].d = 0;
	}
}

// st to keep track of current  pos in segarray, sl,sr is the current range of node
// l,r current range of query , a,b is for specific query
void update(ll st, ll sl, ll sr, ll l, ll r,ll a, ll b){
	if(l > r){
		return;
	}
	if(sl == l && sr == r){
		fun(st, a, b, sl, sr);
		return;
	}
	push(st, sl, sr);
	ll mid = (sl + sr) >> 1;
	update((st<<1), sl, mid, l, min(r, mid), a, b); // we want common seg bw (l,r) and (sl,sr)
	update((st<<1) + 1, mid + 1, sr, max(mid+1, l), r, a, b); // l >=sl and r <= sr, 
	segtree[st] = (segtree[(st<<1)] + segtree[(st<<1)+1]) % m;
}

ll query(ll st, ll sl, ll sr, ll l, ll r){
	if(l > r){
		return 0;
	}
	if(sl == l && sr == r){
		return segtree[st];
	}
	push(st, sl, sr);
	ll mid = (sl + sr) >> 1;
	return (query((st<<1), sl, mid, l, min(r, mid)) + query((st<<1)+1, mid + 1, sr, max(l, mid+1), r)) % m; 
}

int main(){
ll n, q;
cin>>n>>q;
FOR(i, 0, n){
	ll x;
	cin>>x;
	update(1, 0, n-1, i, i, 0, x);
}


FOR(i1, 0, q){
	ll ty;
	cin>>ty;
	if(ty == 0){
		ll l, r, b, c; // queries are l,r -> (l,r-1)
		cin>>l>>r>>b>>c;
		update(1, 0, n-1, l, r-1, b, c);
	}
	else{
		ll l, r;
		cin>>l>>r;
		cout<<query(1, 0, n-1, l, r-1)<<"\n";

	}
}
return 0;
}


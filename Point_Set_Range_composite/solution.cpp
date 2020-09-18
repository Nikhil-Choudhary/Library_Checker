// https://judge.yosupo.jp/problem/point_set_range_composite
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
#define F first
#define S second
#define GET(i,p) get<p>(i)

ll m=998244353;

struct nik{
ll c=0 , d=0 ;
};

const ll maxn= 5e5+5 ;
nik segarr[4*maxn];

void update(ll st, ll sl, ll sr, ll ind, ll &a, ll &b){

if(sl == sr){
segarr[st].c = a;
segarr[st].d = b;
return ;
}

ll mid = (sl + sr) / 2;

if(ind > mid)
	update(2*st+1, mid+1, sr, ind, a, b);
else
	update(2*st, sl, mid, ind, a, b);

ll c1 = segarr[2*st].c;
ll c2 = segarr[2*st+1].c;
ll d1 = segarr[2*st].d;
ll d2 = segarr[2*st+1].d;
segarr[st].c = c1*c2%m;
segarr[st].d = c2*d1%m + d2%m;

}

void query(ll st, ll sl, ll sr, ll l ,ll r, ll &ans){

if(l > r)
	return;

if(l == sl && r == sr){
	ans = (segarr[st].c*ans%m + segarr[st].d) % m;
	return;
}

ll mid = (sl + sr) / 2;

query(2*st, sl, mid, l, min(r, mid), ans);
query(2*st+1, mid+1, sr, max(mid+1, l), r, ans);

}


int main(){

	// #ifndef ONLINE_JUDGE
 //    // for getting input from input.txt	
 //    freopen("input.txt", "r", stdin);
 //    // for writing output to output.txt
 //    freopen("output.txt", "w", stdout);
	//  #endif
    FAST
//	PRECISE

ll n, q;
cin>>n>>q;
FOR(i, 0, n){
	ll x, y;
	cin>>x>>y;
	update(1, 0, n-1, i, x, y);
}

FOR(i1, 0, q){
	ll a, b, c, d;
	cin>>a>>b>>c>>d;
	if(a == 0){
		update(1, 0, n-1, b, c, d);	
	}
	else{
		ll ans=d;
		query(1, 0, n-1, b, c-1, ans);
		cout<<ans<<"\n";
	}
}



return 0;
 }


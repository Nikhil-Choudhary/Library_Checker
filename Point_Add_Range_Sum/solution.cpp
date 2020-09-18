// https://judge.yosupo.jp/problem/point_add_range_sum

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


ll bit[500000+5];
ll n;
void add(ll ind,ll val){
	for(ll i=ind;i<=n;i+=(i&-i))
		bit[i]+=val;
}

ll sum(ll ind){
	ll ans=0;
	for(ll i=ind;i>0;i-=(i&-i))
		ans+=bit[i];
	return ans;
}

ll query(ll ind1,ll ind2){
return sum(ind2)-sum(ind1-1);
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


ll q;
cin>>n>>q;
FOR(i,0,n){
	ll x;
	cin>>x;
	add(i+1,x);
}

FOR(i1,0,q){
	ll t,l,r;
	cin>>t>>l>>r;
	if(t==1)
		cout<<query(l+1,r)<<"\n";
	else
		add(l+1,r);
}


return 0;
 }


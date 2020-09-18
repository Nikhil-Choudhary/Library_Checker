// https://judge.yosupo.jp/problem/unionfind
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
#define FOR(i,vv,n) for(ll i=vv;i<n;i++)
#define FORR(i,n,vv) for(ll i=n-1;i>=vv;i--)
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
#define all(v) v.begin(),v.end()
#define BS(v,n) binary_search(all(v),n)
#define srt(v) sort(v.begin(),v.end())
#define rsrt(v) sort(all(v),greater <ll>())
#define uni(v) v.resize(unique(all(v))-v.begin())
#define F first
#define S second
#define GET(i,p) get<p>(i)

ll root(ll u,ve <ll>&vec){
	if(vec[u]==u)return u;
	else return vec[u]=root(vec[u],vec);
}

void combine(ll u,ll v,ve <ll> &vec,ve <ll> &rank){
ll z1=root(u,vec);
ll z2=root(v,vec);
if(rank[z1]<rank[z2])
	swap(z1,z2);
vec[z2]=z1;
if(rank[z1]==rank[z2])	
rank[z1]++;
}



int main(){

	// #ifndef ONLINE_JUDGE
 //    // for getting input from input.txt	
 //    freopen("input.txt", "r", stdin);
 //    // for writing output to output.txt
 //    freopen("output.txt", "w", stdout);
	//  #endif

    FAST
	//PRECISE

ll n,q;
cin>>n>>q;
ve <ll> vec(n),rank(n);
FOR(i,0,n)
vec[i]=i;
FOR(i,0,q){
	ll t,x,y;
	cin>>t>>x>>y;
	if(t==0){
		combine(x,y,vec,rank);
	}
	else{
		ll x1=root(x,vec);
		ll x2=root(y,vec);
		if(x1==x2)cout<<1;
		else cout<<0;
		cout<<"\n";
	}
}



return 0;
 }


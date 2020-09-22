// SEGMENT TREE BEATS/ TREE OF 2ND MAX
// https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
/* learning resource:-
1). https://codeforces.com/blog/entry/57319
2). https://www.youtube.com/watch?v=wFqKgrW1IMQ
3). search on google and will get a lot other good sources 
*/ 
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
#define BS(v,n) binary_search(v.begin(),v.end(),n)
#define srt(v) sort(v.begin(),v.end())
#define rsrt(v) sort(v.begin(),v.end(),greater <ll>())
#define uni(v) v.resize(unique(v.begin(),v.end())-v.begin())
#define F first
#define S second
#define GET(i,p) get<p>(i)


//O(nlogn+qlogn)*logn, actual performance better than this
typedef pair<ll,ll>  p2;
typedef pair<p2,ll> p3;

const ll maxn = (1<<18);


ll upmi[2*maxn],upma[2*maxn],upadd[2*maxn];  // array to know the updates to be made
p3 curma[2*maxn]; // tuples storing, 1st max, strictly 2nd max and count of max.
p3 curmi[2*maxn]; // tuples storing, 1st min, strictly 2nd min and count of min.
ll cursum[2*maxn]; // stores current sum


// used to transfer curretn update value to child notes to avoid any conflicts bw max and min updates
// which are present in chil already

void chmin(ll & x1, ll  x2){  
if(x1>x2)
	x1=x2;
}

void chmax(ll & x1, ll  x2){
if(x1<x2)
	x1=x2;
}


// just initializing the values
// we are smartly using, INF and -INF to avoid special cases when complete range consist of 1 element
void ini(ll st, ll sl, ll sr){
	upmi[st]=INF;upma[st]=-INF;
	curma[st] = {{0,-INF},(sr-sl+1)};
	curmi[st] = {{0,INF},sr-sl+1};
	if(sl == sr){
		return ;
	}
	ll mid = (sl+sr)/2;
	ini(2*st,sl,mid);
	ini(2*st+1,mid+1,sr);
}

// most trick part
// at first sight we can think that operations are not commutative, therefore we have to process carefully
// we are assuming that curadd value will be always added and we will try do other 2 ops according to it

void pushdown(ll st, ll sl, ll sr){
	auto fun1 = [](ll &x1,ll x2,ll x3){if(x1==x2)x1=x3;};
	auto fun4 = [](ll &z, ll b){	if(z!=INF&&z!=-INF)	z+=b;};

	if(upmi[st]!=INF){ // tag is set
		if(upmi[st]<curma[st].F.F){ // required to update
			cursum[st] += (-curma[st].F.F + upmi[st])*curma[st].S; // correcting cursum
			fun1(curmi[st].F.F,curma[st].F.F,upmi[st]); // correcting curmi
			fun1(curmi[st].F.S,curma[st].F.F,upmi[st]); // correcting curmi
			curma[st].F.F = upmi[st]; // correcting curma
			if(sl!=sr){
				FOR(j,0,2){
					// below ordering solves the conflict of clashing min and max updates in child
					chmin(upmi[2*st+j],upmi[st]-upadd[2*st+j]); // passing update value to child
					chmin(upma[2*st+j],upmi[2*st+j]); 
				}
			}
		}
		upmi[st]=INF;
	}

	if(upma[st]!=-INF){
		if(upma[st]>curmi[st].F.F){
			cursum[st] += (-curmi[st].F.F + upma[st])*curmi[st].S; // correcting cursum
			fun1(curma[st].F.F,curmi[st].F.F,upma[st]); // correcting curma
			fun1(curma[st].F.S,curmi[st].F.F,upma[st]); // correcting curma
			curmi[st].F.F = upma[st]; // correcting curmi
			if(sl!=sr){
				FOR(j,0,2){
					chmax(upma[2*st+j],upma[st]-upadd[2*st+j]); // passing values to child
					chmax(upmi[2*st+j],upma[2*st+j]);
				}
			}
		}
		upma[st]=-INF;
	}

	if(upadd[st]!=0){
		cursum[st]+= (sr-sl+1)*(upadd[st]);
		// correcting curmi,curma,curadd
		fun4(curmi[st].F.F,upadd[st]); 
		fun4(curmi[st].F.S,upadd[st]);
		fun4(curma[st].F.F,upadd[st]);
		fun4(curma[st].F.S,upadd[st]);
		if(sl!=sr){
			FOR(j,0,2){
				upadd[2*st+j]+=upadd[st]; // passing values to child
			}
		}
		upadd[st]=0;
	}

}


ll query(ll st,ll sl, ll sr, ll l, ll r){ // normal query like we do in a segment tree
	pushdown(st, sl, sr);
	if(sr<l||sl>r){
		return 0;
	}
	if(sr==r && sl == l){
		return cursum[st];
	}
	ll mid=(sl+sr)/2;
	return query(2*st,sl,mid,l,min(mid,r)) + query(2*st+1,mid+1,sr,max(mid+1,l),r);
}

p3 combmax(p3 a, p3 b){ // helper function
if(a>b)
	swap(a,b);
if(a.F.F==b.F.F){
	return {{a.F.F,max(a.F.S,b.F.S)},a.S+b.S};
}
return {{b.F.F,max(a.F.F,b.F.S)},b.S};
}

p3 combmin(p3 a,p3 b){ // helper function
if(a<b)
	swap(a,b);
if(a.F.F==b.F.F){
	return {{a.F.F,min(a.F.S,b.F.S)},a.S+b.S};
}
return {{b.F.F,min(a.F.F,b.F.S)},b.S};
}

void pull(ll st){
	cursum[st]=cursum[2*st]+cursum[2*st+1]; // correcting cursum
	curma[st]=combmax(curma[2*st],curma[2*st+1]); // correcting curma
	curmi[st]=combmin(curmi[2*st],curmi[2*st+1]); // correcting curmi
}

// break conditions makes complexity stronger but tag conditions degrades complexity
// In this verision if we have a tag at a node then that node value is yet to be evaluated
void update(ll st,ll sl, ll sr, ll t, ll l, ll r, ll b){
	pushdown(st,sl,sr); // necessary
	if(sr<l||sl>r){ // normal break condition
		return;
	}

	// these 2 additional break condition makes code efficient
	// additional brak conditions
	if(t == 0){ 
		if(curma[st].F.F <=b){return;}}
	if(t==1){
		if(curmi[st].F.F >=b){return;}}

	if(sr<=r&&sl>=l){
		if(t == 0){
			if(curma[st].F.F <=b){return;}  // could be done here but is little slow
			else if(curma[st].F.S<b){ // loosen tag condition, which add additional logn factor
				upmi[st] = b;
				pushdown(st,sl,sr); //necessary, so that we can have appropriate value while calling pull
				return;
			}
		}
		if(t==1){
			if(curmi[st].F.F >=b){return;}
			else if(curmi[st].F.S>b){   // here we are not going inside when it becomes equal
				upma[st] = b;			// this saves us from writing different logic for condition
				pushdown(st,sl,sr);		// when segment values becones all equal
				return;
			}	
		}
		if(t==2){
			upadd[st] = b;
			pushdown(st,sl,sr);
			return;
		}
	}
	ll mid=(sl+sr)/2;
	update(2*st,sl,mid,t,l,min(r,mid),b);
	update(2*st+1,mid+1,sr,t,max(l,mid+1),r,b);
	pull(st); // combing child nodes
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

//queries and updates are in range
// t==0, ai=min(ai,b)
// t==1, ai=max(ai,b)
// t==2, ai=ai+b
// t==3, output sum from l to r

ll n,q;
cin>>n>>q;
ini(1,0,n-1);
ve <ll> v(n);
FOR(i,0,n){
	cin>>v[i];
	update(1,0,n-1,2,i,i,v[i]);
}

FOR(i1,0,q){
	ll t;
	cin>>t;
	if(t==3){
		ll l,r;
		cin>>l>>r;
		cout<<query(1,0,n-1,l,r-1)<<"\n";
	}
	else{
		ll l,r,b;
		cin>>l>>r>>b;
		r--; // to adjust with input
		update(1,0,n-1,t,l,r,b);
	}
}

return 0;
 }

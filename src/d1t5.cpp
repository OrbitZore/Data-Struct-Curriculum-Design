#include <bits/stdc++.h>
using namespace std;
using INT=int;
using ll=long long;
#define pb push_back
#define eb emplace_back
#define all(a) (a).begin(),(a).end()
bool MULTIDATA=true;
struct solution{
	ll n,m;
	void scan(){
		if (!(cin>>n>>m)) exit(0);
	}
	int f(int n,int m){
		if (m==1) return n;
		if (n==1) return 1;
		if (n<=m) return (f(n-1,m)+m-1)%n+1;
		int w=n%m,e=n-n/m,l=n/m*m;
		int a=f(e,m);
		if (a<=w) return a+l;
		a-=w;a+=(a-1)/(m-1);
		return a;
	}
	void solve(){
		cout << f(n,m) << endl;
	} 
};


INT main(){
	cin.tie(0);ios::sync_with_stdio(false);
	int T=0x3f3f3f3f;
	while (T--){
		auto a=unique_ptr<solution>(new solution());
		a->scan();
		a->solve();
		if (!cin.good()) break;
	}
	return 0;
}
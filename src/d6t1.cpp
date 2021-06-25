#include <bits/stdc++.h>
using namespace std;
using INT=int;
//#define int long long
#define pb push_back
#define eb emplace_back
#define all(a) (a).begin(),(a).end()
template<class T>
using refT=reference_wrapper<T>;
template<class T>
using crefT=reference_wrapper<const T>;
auto &_=std::ignore;
using ll=long long;
template<class T>
using vec=vector<T>;
template<bool B,class T=void>
using enableif_t=typename enable_if<B,T>::type;

#define DEF_COULD(name,exp) \
template<class U> \
struct name{\
	template<class T>\
	constexpr static auto is(int i)->decltype(exp,true){return true;}\
	template<class T>\
	constexpr static bool is(...){return false;}\
	static const bool value=is<U>(1);\
};
#define DEF_CAN(name,exp) DEF_COULD(can##name,exp)
#define ENABLE(T,name) enableif_t<can##name<T>::value>(1)
#define ENABLEN(T,name) enableif_t<!can##name<T>::value>(1)
#define FOR_TUPLE enableif_t<i!=tuple_size<T>::value>(1)
#define END_TUPLE enableif_t<i==tuple_size<T>::value>(1)

#define DEF_INF(name,exp)\
constexpr struct{\
	template<class T>\
	constexpr operator T()const {return numeric_limits<T>::exp();}\
} name;

DEF_CAN(Out,(cout<<*(T*)(0))) DEF_CAN(For,begin(*(T*)(0)))
DEF_INF(INF,max) DEF_INF(MINF,min)

template<size_t i,class T>
auto operator>>(istream& is,T &r)->decltype(END_TUPLE,is){
	return is;
}
template<size_t i=0,class T>
auto operator>>(istream& is,T &r)->decltype(FOR_TUPLE,is){
	is>>get<i>(r);
	return operator>> <i+1>(is,r);
}
template<class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLE(T,Out),c+1){
	os << cv;
	while (*c!='}') c++;
	return c+1;
}
template<size_t i,class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,For),END_TUPLE,c+1){
	return c;
}
template<size_t i=0,class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,For),FOR_TUPLE,c+1){
	while (*c!='{') os << *c++;
	c=__format(os,c,get<i>(cv));
	return __format<i+1>(os,c,cv);
}
template<class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,Out),ENABLE(T,For),c+1){
	const char *ct=c+1;
	if (cv.size()==0){
		while (*ct!='}') ct++;
		ct++;
		while (*ct!='}') ct++;
	}else{
		for (auto &i:cv){
			const char *cc=c+1;
			while (*cc!='{') os << *cc++;
			cc=__format(os,cc,i);
			while (*cc!='}') os << *cc++;
			ct=cc;
		}
	}
	return ct+1;
}
void _format(ostream &os,const char *c){
	while (*c!='{'&&*c!='\0') os<< *c++;
}
template<class T,class ...Args>
void _format(ostream &os,const char *c,const T &a,Args&& ...rest){
	while (*c!='{'&&*c!='\0') os<< *c++;
	if (*c=='{') c=__format(os,c,a);
	_format(os,c,forward<Args>(rest)...);
}
template<class ...Args>
string format(const char *c,Args&& ...rest){
	ostringstream os;
	_format(os,c,forward<Args>(rest)...);
	return os.str();
}
template<class ...Args>
ostream& print(const char *c,Args&& ...rest){return _format(cout,c,forward<Args>(rest)...),cout;}

#ifdef LOCAL
#define debug(...) cerr<<format(__VA_ARGS__)
#else
#define debug(...) cerr
#endif
template<class T,class ...Args>
struct Rtar{
	T& a;tuple<Args...> n;
	Rtar(T& a,tuple<Args...> n):a(a),n(n){}
};
template<class T,class ...Args>
Rtar<T,Args&...> rtar(T &a,Args&... rest){
	return Rtar<T,Args&...>(a,tie(rest...));
}
template<size_t i,class U,class ...Args,class T=tuple<Args&...>>
auto operator>>(istream& is,Rtar<U,Args&...> r)->decltype(END_TUPLE,is){
	return is>>r.a;
}
template<size_t i=0,class U,class ...Args,class T=tuple<Args&...>>
auto operator>>(istream& is,Rtar<U,Args&...> r)->decltype(FOR_TUPLE,is){
	r.a=typename decay<U>::type(get<i>(r.n));
	for (auto &w:r.a)
		operator>> <i+1>(is,Rtar<decltype(w),Args&...>(w,r.n));
	return is;
}
template<class T1,class T2>
bool cmin(T1 &a,const T2 b){return a>b?a=b,1:0;}
template<class T1,class T2>
bool cmax(T1 &a,const T2 b){return a<b?a=b,1:0;}
template<class T1,class T2,class ...T3>
bool cmin(T1 &a,const T2 b,const T3 ...rest){return cmin(a,b)|cmin(a,rest...);}
template<class T1,class T2,class ...T3>
bool cmax(T1 &a,const T2 b,const T3 ...rest){return cmax(a,b)|cmax(a,rest...);}
bool MULTIDATA=false;
template <class vT>
struct wedge{int u,v;vT w;};
template <class vT>
struct sedge{int u,v;const constexpr static vT w=1;};
template <class vT>
bool operator<(const wedge<vT> &a,const wedge<vT> &b){return a.w<b.w;}
template <template <class vT> class etT,class vT>
struct graph:public vector<vector<etT<vT>>>{
	using eT=etT<vT>;
	using esT=vector<eT>;
	using GT=vector<esT>;
	using vector<vector<etT<vT>>>::vector;
	void addEdge(const eT &a){GT::operator[](a.u).push_back(a);}
	void add2Edge(eT a){addEdge(a);swap(a.u,a.v);addEdge(a);}
};
struct mfset:protected vector<int>{
	mfset(){}
	mfset(int size){resize(size);}
	void resize(int size){
		vector<int>::resize(size);
		iota(this->begin(),this->end(),0);
	}
	int find(int a){
		int &b=this->operator[](a);
		return a==b?a:b=find(b);
	}
	bool merge(int a,int b){
		int aa=find(a),bb=find(b);
		if (aa!=bb){
			this->operator[](bb)=aa;
			return true;
		}
		return false;
	}
};
struct solution{
	int n,m;
	mfset s;
	vec<wedge<int>> l;
	void scan(){
		cin>>n>>m;
		if (!cin.good()) exit(0);
		s.resize(n+1);
		for (int i=0;i<m;i++){
			int u,v,w;
			cin>>u>>v>>w;
			l.pb({u,v,w});
		}
	}
	
	void solve(){
		sort(all(l));
		ll sum=0;
		for (auto &e:l)
			if (s.merge(e.u,e.v))
				sum+=e.w;
		cout << sum << endl;
	} 
};


INT main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int T=INF;
	if (MULTIDATA) cin>>(T);
	while (T--){
		auto a=unique_ptr<solution>(new solution());
		a->scan();
		a->solve();
		if (!cin.good()) break;
	}
	return 0;
}
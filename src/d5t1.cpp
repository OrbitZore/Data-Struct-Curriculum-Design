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
#define op_array(x) \
template<class T,size_t d> \
array<T,d>& operator x##=(array<T,d>& a,const array<T,d>& b){for (size_t i=0;i<d;i++) a[i] x##=b[i];return a;}\
template<class T,class U,size_t d>\
auto operator x##=(array<T,d>& a,const U& b)->decltype(T(declval<U>()),a){for (size_t i=0;i<d;i++) a[i] x##=b;return a;}\
template<class T,size_t d>\
array<T,d> operator x (const array<T,d>& a,const array<T,d>& b){array<T,d> k(a);k x##=b;return k;}
op_array(+) op_array(-) op_array(*) op_array(/)
template<class T>
using vec2=array<T,2>;
template<class T>
using vec3=array<T,3>;
template<class T,size_t d>
T dot(const array<T,d>& a,const array<T,d>& b){
	T ans=0;
	for (size_t i=0;i<d;i++) ans+=a[i]*b[i];
	return ans;
}
template<class T,size_t d>
T abs(const array<T,d>& a){return sqrt(dot(a,a));}
template<class T>
T crs(const vec2<T> &a,const vec2<T> &b){return a[0]*b[1]-a[1]*b[0];}
template<class T>
vec3<T> crs(const vec3<T> &a,const vec3<T> &b){return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};}
template<class T,size_t d>
istream& operator>>(istream& is,array<T,d> &p){
	for (size_t i=0;i<d;i++) is>>p[i];
	return is;
}
struct status{
	vec2<int> player,box;
	bool operator<(const status &s)const{
		if (player<s.player) return true;
		if (s.player<player) return false;
		if (box<s.box) return true;
		return false;
	}
};
const array<vec2<int>,4> direct{
	0,-1,
	0,1,
	-1,0,
	1,0
};
struct solution{
	int n,m;
	vec<vec<char>> G;
	set<status> s;
	vec2<int> dest;
	status ini;
	void scan(){
		cin>>n>>m>>rtar(G,n,m);
	}
	const char at(const vec2<int>& p)const {return G[p[0]][p[1]];}
	bool vaild(const vec2<int>& p)const {return 0<=p[0]&&p[0]<n&&0<=p[1]&&p[1]<m&&at(p)!='#';}
	int bfs(){
		set<status> s;
		queue<status> q,Q;
		int step=0;
		auto insert=[&](status t){s.insert(t);Q.push(t);return t.box==dest;};
		auto notin=[&](status t){return s.find(t)==s.end();};
		if (insert(ini)) return step;
		do{
			while (q.size()){
				status t=q.front();q.pop();
				for (auto i:direct){
					status nt{t.player+i,t.box};
					if (nt.player==nt.box) nt.box+=i;
					if (vaild(nt.player)&&vaild(nt.box)){
						if (notin(nt)) {
							if (insert(nt))
								return step;
						}
					}
				}
			}
			swap(q,Q);
			step++;
		}while (q.size());
		return -1;
	}
	void solve(){
		for (int i=0;i<n;i++) for (int j=0;j<m;j++)
			if (G[i][j]=='X') ini.player={i,j};
			else if (G[i][j]=='*') ini.box={i,j};
			else if (G[i][j]=='@') dest={i,j};
		print("{}\n",bfs());
	} 
};


INT main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int T=1;
	if (MULTIDATA) cin>>(T);
	while (T--){
		auto a=unique_ptr<solution>(new solution());
		a->scan();
		a->solve();
		if (!cin.good()) break;
	}
	return 0;
}
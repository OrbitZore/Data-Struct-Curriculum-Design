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
bool MULTIDATA=true;
map<string,function<double(double,double)>> funcmap={
	{"+",plus<double>()},
	{"-",minus<double>()},
	{"*",multiplies<double>()},
	{"/",divides<double>()}
};
using namespace std::placeholders;
struct tree{
	string a;
	shared_ptr<tree> ch[2];
	tree(){}
	tree(string a):a(a){}
	tree(int a):a(to_string(a)){}
	double calc(const function<double(string)>& func){
		if ((!ch[0])&&(!ch[1]))
			return func(a);
		return funcmap[a](ch[0]->calc(func),ch[1]->calc(func));
	}
	ostream& print(const function<string(string)>& func){
		bool f=(!ch[0])&&(!ch[1]);
		if (!f) cout << "(";
		if (ch[0]) ch[0]->print(func);
		cout << func(a);
		if (ch[1]) ch[1]->print(func);
		if (!f) cout << ")";
		return cout;
	}
};

#define op_array(x) \
template<class T,size_t d> \
array<T,d>& operator x##=(array<T,d>& a,const array<T,d>& b){for (size_t i=0;i<d;i++) a[i] x##=b[i];return a;}\
template<class T,class U,size_t d>\
auto operator x##=(array<T,d>& a,const U& b)->decltype(T(declval<U>()),a){for (size_t i=0;i<d;i++) a[i] x##=b;return a;}\
template<class T,size_t d,class U>\
auto operator x (const array<T,d>& a,const U& b)->decltype(T(declval<U>()),array<T,d>()){array<T,d> k(a);k x##=b;return k;}
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

struct solution{
	array<int,4> a;
	int n;
	void scan(){
		cin >> a;
		if (!cin.good()) exit(0);
	}
	template<class U>
	static vec<set<int>> choosePart(U op,U ed,int count){
		if (count==0) return {{}};
		vec<set<int>> ans;
		auto ied=next(ed,1-count);
		for (auto i=op;i!=ied;i++){
			auto xs=choosePart(next(i),ed,count-1);
			for (auto x:xs){
				x.insert(*i);
				ans.eb(move(x));
			}
		}
		return ans;
	}
	template<class U>
	static vec<pair<set<int>,set<int>>> choose(U op,U ed,int count){
		auto xs=choosePart(op,ed,count);
		vec<pair<set<int>,set<int>>> y;
		for (auto a:xs){
			set<int> b(op,ed);
			for (auto i:a) b.erase(i);
			y.eb(make_pair(move(a),move(b)));
		}
		return y;
	}
	static vec<shared_ptr<tree>> make(set<int> v={0,1,2,3}){
		vec<shared_ptr<tree>> ans;
		if (v.size()==1){
			ans.eb(shared_ptr<tree>(new tree(*v.begin())));
		}else{
			for (int i=1;i<v.size();i++)
				for (auto str:{"+","-","*","/"}){
					for (auto& pair:choose(all(v),i)){
						auto &a=pair.first,&b=pair.second;
						auto lsons=make(a),rsons=make(b);
						for (auto &l:lsons){
							for (auto &r:rsons){
								auto t=shared_ptr<tree>(new tree(str));
								t->ch[0]=l;
								t->ch[1]=r;
								ans.eb(t);
							}
						}
					}
				}
		}
		return ans;
	}
	static vec<shared_ptr<tree>> after;
	void solve(){
		for (auto& tree_ptr:after){
			auto w=tree_ptr->calc([&](const string& i)->double{
				return a[stoi(i)];
			});
			if (fabs(w-24)<=1e-6){
				tree_ptr->print([&](const string& i){
					if (isdigit(i[0])) return to_string(a[stoi(i)]);
					return i;
				});
				print("=24\n");
				return ;
			}
		}
		print("NO\n");
	} 
};

vec<shared_ptr<tree>> solution::after=solution::make();
INT main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int T=INF;
//	if (MULTIDATA) cin>>(T);
	while (T--){
		auto a=unique_ptr<solution>(new solution());
		a->scan();
		a->solve();
		if (!cin.good()) break;
	}
	return 0;
}
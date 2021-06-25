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
template<class T>
struct tree{
	T str;int i;
	unique_ptr<tree> ch[2];
	int size;
	tree(T&& str,int i):str(str),i(i){}
	tree(const T& str,int i):str(str),i(i),size(1){}
	void maintain(){size=1+(ch[0]?ch[0]->size:0)+(ch[1]?ch[1]->size:0);}
	static void insert(unique_ptr<tree>& t,const T& a,int i){
		if (!t) {t.reset(new tree(a,i));return ;}
		if (a<t->str)  insert(t->ch[0],a,i);
		else insert(t->ch[1],a,i);
		t->maintain();
	}
	static tree* search(unique_ptr<tree>& t,const T& a){
		if (!t) return nullptr;
		if (t->str==a) return t.get();
		if (a<t->str) return search(t->ch[0],a);
		return search(t->ch[1],a);
	}
	static void back_search(unique_ptr<tree>& t){
		if (!t) return ;
		back_search(t->ch[0]);
		back_search(t->ch[1]);
		print("{} ",t->str);
	}
};
using tr=tree<string>;
struct solution{
	unique_ptr<tr> t;
	void scan(){
		string a;int i=0;
		while (getline(cin,a),a!="#") tr::insert(t,a,i++);
		tr::back_search(t);
		cout << endl;
	}
	vec<pair<int,tr*>> find(const string &a){
		vec<pair<int,tr*>> vs;
		auto inserter=[&](const string &a){
			auto x=tr::search(t,a);
			if (x) vs.pb(make_pair(x->i,x));
		};
		for (int i=0;i<=a.size();i++){
			for (char c='a';c<='z';c++){
				string tmp;tmp.reserve(a.size()+1);
				tmp+=a.substr(0,i);
				tmp+=c;
				tmp+=a.substr(i,a.size()-i);
				inserter(tmp);
			}
			if (i!=a.size()){
				string tmp;tmp.reserve(a.size()-1);
				tmp+=a.substr(0,i);
				tmp+=a.substr(i+1,a.size()-i-1);
				inserter(tmp);
				
				tmp=a;
				for (char c='a';c<='z';c++){
					tmp[i]=c;
					inserter(tmp);
				}
			}
		}
		sort(all(vs),[](const pair<int,tr*> &a,
						const pair<int,tr*> &b){
			return a.first<b.first;
		});
		vs.resize(unique(all(vs))-vs.begin());
		return vs;
	}
	void solve(){
		string a;
		while (getline(cin,a),a!="#"){
			if (tr::search(t,a)){
				print("{} is correct\n",a);
			}else{
				print("{}:",a);
				for (auto &x:find(a))
					print(" {}",x.second->str);
				cout << endl;
			}
			cout.flush();
		}
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
#define plane map<int,int>
typedef long long LL;
struct hull{
	plane t;
	LL area;
	inline hull(){
		t.clear();
		area=0;
	}
	inline plane::iterator pre( plane::iterator x){
		return x==t.begin() ? x : --x;
	}
	inline plane::iterator next( plane::iterator x){
		return x==t.end() ? x : ++x;
	}
	inline LL traparea(LL x1,LL y1,LL x2,LL y2){
		return (x2-x1)*(y1+y2);
	}
	inline LL traparea(plane::iterator p0,plane::iterator p1){
		return traparea(p0->first,p0->second,p1->first,p1->second);
	}
	inline LL triarea(plane::iterator x){
		LL res=0;
		if (x!=t.begin()) res+=traparea(pre(x),x);
		if (next(x)!=t.end()) res+=traparea(x,next(x));
		if (x!=t.begin() && next(x)!=t.end()) res+=traparea(next(x),pre(x));
		return res;
	}
	inline int check(plane::iterator x){
		if (t.size()<3 || x==t.begin() || next(x)==t.end()) return 0;
		return triarea(x)<=0;
	}
	void insert(int x,int y){
		if (t.find(x)!=t.end()){
			if (y<=t[x]) return;
			area-=triarea(t.lower_bound(x));
			t.erase(x);
		}
		plane::iterator it=t.insert(make_pair(x,y)).first;
		if (check(it)){
			t.erase(it);
			return;
		}
		area+=triarea(it);
		while (check(pre(it))){
			area-=triarea(pre(it));
			t.erase(pre(it));
		}
		while (check(next(it))){
			area-=triarea(next(it));
			t.erase(next(it));
		}
	}
	inline int contain(int x,int y){
		plane :: iterator S=t.begin() , T=pre(t.end()) ;
		if (x<S->first || x>T->first) return 0;
		if (x==S->first) return y<=S->second;
		if (x==T->first) return y<=T->second;
		plane::iterator it=t.lower_bound(x) , p=pre(it);
		int x1=p->first , y1=p->second , x2=it->first , y2=it->second;
		return (LL)(y-y1)*(x2-x1) <= (LL)(y2-y1)*(x-x1);
	}
} upper,lower;


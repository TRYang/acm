#include <stdio.h>
#include <map>
#define plant map<int,int>

using namespace std;

typedef long long LL;

struct hull{
	plant t;
	LL area;
	inline hull(){
		t.clear();
		area=0;
	}
	inline plant :: iterator pre( plant :: iterator x){
		return x==t.begin() ? x : --x;
	}
	inline plant :: iterator next( plant :: iterator x){
		return x==t.end() ? x : ++x;
	}
	inline LL traparea(LL x1,LL y1,LL x2,LL y2){
		return (x2-x1)*(y1+y2);
	}
	inline LL traparea(plant :: iterator p0,plant :: iterator p1){
		return traparea(p0->first,p0->second,p1->first,p1->second);
	}
	inline LL triarea(plant :: iterator x){
		LL res=0;
		if (x!=t.begin()) res+=traparea(pre(x),x);
		if (next(x)!=t.end()) res+=traparea(x,next(x));
		if (x!=t.begin() && next(x)!=t.end()) res+=traparea(next(x),pre(x));
		return res;
	}
	inline int check(plant :: iterator x){
		if (t.size()<3 || x==t.begin() || next(x)==t.end()) return 0;
		return triarea(x)<=0;
	}
	void insert(int x,int y){
		if (t.find(x)!=t.end()){
			if (y<=t[x]) return;
			area-=triarea(t.lower_bound(x));
			t.erase(x);
		}
		plant :: iterator it=t.insert(make_pair(x,y)).first;
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
} upper,lower;
void AddPoint(){
	int x,y;
	scanf("%d %d",&x,&y);
	upper.insert(x,y);
	lower.insert(x,-y);
}
inline LL aabs(LL x){return x>0?x:-x;}
int main(){
	int i,j,k;
	int qn;
	for (i=0;i<3;i++) AddPoint();
	for (scanf("%d",&qn);qn>0;qn--){
		AddPoint();
		printf("%I64d\n",aabs(upper.area+lower.area));
	}
	return 0;
}

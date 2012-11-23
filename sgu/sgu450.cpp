#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#define maxn 110

using namespace std;

//available empty seat for the customers
struct block{
	int len,x,y;
	friend bool operator < (const block &a,const block &b){
		if (a.len!=b.len) return a.len>b.len;
		return a.x<b.x || (a.x==b.x && a.y<b.y);
	}
};

struct customer{
	int T,P,W,E;
	void read(){
		scanf("%d%d%d%d",&T,&P,&W,&E);
	}
};

multiset< int > all_seat;
set< block > seat;
set< int > whole_empty_counter;
set< block > half_empty_counter;
int shop_map[maxn][maxn];		//record the state of the whole shop
queue< customer > Q;
int C[maxn];					//size of the counters 
int n,m,T;

void init(){
	seat.clear();
	whole_empty_counter.clear();
	for (int i=0;i<n;i++) whole_empty_counter.insert(i);
	half_empty_counter.clear();
	all_seat.clear();
	for (int i=0;i<n;i++) all_seat.insert(C[i]);
	while (!Q.empty()) Q.pop();
}

int last(multiset<int> &t){
	set<int>::iterator it=t.end();
	--it;
	return *it;
}

int check(int p){
	if (all_seat.size()==0) return 0;
	if (last(all_seat)<p) return 0;
	return 1;
}

int main(){
	scanf("%d%d%d",&n,&m,&T);
	for (int i=0;i<n;i++) scanf("%d",C+i);
	init();
	for (int i=0;i<m;i++){
		customer tmp;
		tmp.read();
		Q.push(tmp);
	}
	while (!Q.empty()){
	}
	return 0;
}

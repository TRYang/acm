#include <stdio.h>
#include <string.h>
#include <map>
#include <algorithm>
#define maxn 250010

using namespace std;

map< pair<int,int> , int> s;
int type[maxn],L[maxn],R[maxn];
int x[maxn<<1],xn;
int n,m;
int check(pair<int,int> a,pair<int,int> b){
	return a.first<=b.first && a.second>=b.second;
}
int main(){
	xn=m=0;
	char cmd[20];
	while (scanf("%s",cmd)!=EOF){
		if (cmd[0]=='+') type[m]=0;else type[m]=1;
		scanf("%d%d",L+m,R+m);
		if (type[m]==0){
			x[xn++]=L[m];
			x[xn++]=R[m];
		}
		m++;
	}
	sort(x,x+xn);
	xn=unique(x,x+xn)-x;
	s.clear();
	n=0;
	for (int t=0;t<m;t++){
		pair<int,int> d=make_pair(L[t],R[t]);
		if (type[t]==0){
			if (s.find(d)==s.end())
				s.insert(make_pair(d,0));
			s[d]++;
			int ans=0;
			for (map< pair<int,int> ,int>::iterator it=s.begin();it!=s.end();it++)
				if (check(d,it->first)) ans+=it->second;
			printf("%d\n",ans-1);
			++n;
		}else{
			if (s.find(d)==s.end() || s[d]==0) continue;
			s[d]--;
			if (s[d]==0) s.erase(d);
			--n;
		}
	}
	return 0;
}
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <bitset>
#define maxn 110

using namespace std;

bitset<maxn> s[maxn];
bitset<maxn> a[maxn];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) s[i].reset();
	for (int i=0;i<m;i++){
		int k,v;
		a[i].reset();
		for (scanf("%d",&k);k;k--){
			scanf("%d",&v);
			v--;
			a[i].set(v);
		}
	}
	for (int i=0;i<m;i++){
		int tag=1;
		for (int j=0;j<i;j++)
			if (a[j]==a[i]) tag=0;
		if (tag){
			for (int j=0;j<n;j++)
				if (a[i][j]) s[j].set(i);
		}
	}
	int ans=0;
	for (int i=0;i<n;i++)
		if (s[i].count()>0){
			int tag=1;
			for (int j=0;j<i;j++)
				if (s[j]==s[i]) tag=0;
			if (tag) ++ans;
		}
	printf("%d\n",ans);
	return 0;
}

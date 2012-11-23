#include <stdio.h>
#include <string.h>
#include <set>
#define maxn 110

using namespace std;

set<int> s;
int b[maxn];
int d[maxn],dn;
int n,m;
int check(int x){
	for (int i=0;i<dn;i++)
		if (s.find(b[x]^d[i])==s.end()) return 0;
	return 1;
}
int main(){
	scanf("%d",&m);
	for (int i=0;i<m;i++) scanf("%d",b+i);
	if (m==1){
		printf("0 %d\n",b[0]);
		return 0;
	}
	n=2;
	while (n*(n-1)/2<m) ++n;
	dn=1;
	d[0]=b[0];
	s.clear();
	for (int i=1;i<m;i++) s.insert(b[i]);
	for (int i=1;i<m;i++)
		if (check(i)){
			d[dn++]=b[i];
			s.erase(b[i]);
		}
	printf("0");
	for (int i=0;i<dn;i++) printf(" %d",d[i]);
	puts("");
	return 0;
}
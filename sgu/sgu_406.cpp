#include <stdio.h>
#include <string.h>
#include <bitset>
#include <algorithm>

using namespace std;

bitset<120> s[11];
int a[11][11],an[11];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		scanf("%d",&an[i]);
		for (int j=0;j<an[i];j++) scanf("%d",&a[i][j]);
		s[i].reset();
		for (int j=0;j<an[i];j++) s[i].set(a[i][j]);
	}
	for (int t=0;t<m;t++){
		bitset<120> p,q;
		p.reset();
		q.reset();
		int dn;
		for (scanf("%d",&dn);dn;dn--){
			int x;
			scanf("%d",&x);
			if (x>0) p.set(x);else q.set(-x);
		}
		int tot=0;
		for (int i=0;i<n;i++)
			if ((s[i]&p)==p && (s[i]&q).count()==0) ++tot;
		printf("%d\n",tot);
		for (int i=0;i<n;i++)
			if ((s[i]&p)==p && (s[i]&q).count()==0){
				printf("%d",an[i]);
				for (int j=0;j<an[i];j++) printf(" %d",a[i][j]);
				puts("");
			}
	}
	return 0;
}
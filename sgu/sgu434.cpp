#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#define maxn 21

using namespace std;

int a[maxn],b[maxn];
vector<int> c,d;
set<int> dmask[21010];
int f[1<<maxn];
int cn,dn;
int n;
int bitcount(int x){
	int ret=0;
	for (;x;ret+=(x&1),x>>=1);
	return ret;
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",a+i);
	for (int i=0;i<n;i++) scanf("%d",b+i);
	c.clear();
	d.clear();
	for (int i=0;i<n;i++)
		if (a[i]>b[i]){
			c.push_back(a[i]-b[i]);
		}else
		if (a[i]<b[i]){
			d.push_back(b[i]-a[i]);
		}
	if (c.size()>d.size()) swap(c,d);
	cn=c.size();
	dn=d.size();
	int value[1<<cn];
	for (int mask=0;mask<(1<<cn);mask++){
		value[mask]=0;
		for (int i=0;i<cn;i++)
			if ((mask&(1<<i))>0) value[mask]+=c[i];
	}
	int dvalue[1<<dn];
	for (int mask=0;mask<(1<<dn);mask++){
		int sum=0;
		for (int i=0;i<dn;i++)
			if ((mask&(1<<i))>0) sum+=d[i];
		dvalue[mask]=sum;
		dmask[sum].insert(mask);
	}
//	for (int i=0;i<cn;i++) printf("%d ",c[i]);puts("");
//	for (int i=0;i<dn;i++) printf("%d ",d[i]);puts("");
	f[0]=0;
	for (int mask=1;mask<(1<<cn+dn);mask++){
		int s1=(mask>>dn),s2=(mask&((1<<dn)-1));
		f[mask]=1000;
		if (s1==0 || s2==0) continue;
		if (value[s1]!=dvalue[s2]) continue;
		f[mask]=bitcount(mask)-1;
		set<int>::iterator it;
		int tot;
		for (int subset=(s1&(s1-1));subset;subset=((subset-1)&s1)){
			tot=value[subset];
			for (it=dmask[tot].begin();it!=dmask[tot].end();it++)
				f[mask]=min(f[mask],f[((s1^subset)<<dn)|(s2^(*it))]+bitcount((subset<<dn)|(*it))-1);
		}
	}
	int ans;
	if (f[(1<<cn+dn)-1]==1000) ans=-1;else ans=f[(1<<cn+dn)-1];
	printf("%d\n",ans);
	return 0;
}

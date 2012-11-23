#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 50010

using namespace std;

int idx[maxn*21];
int stt[maxn*21],ent[maxn*21];
int st[maxn],en[maxn];
int ansp[maxn];
int n,m;
bool cmp(int x,int y){
	return ent[x]<ent[y];
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d%d",st+i,en+i);
	m=0;
	for (int i=0;i<n;i++)
		for (int j=-10;j<=10;j++){
			idx[m]=m;
			stt[m]=st[i]+j;
			ent[m]=en[i]+j;
			m++;
		}
	sort(idx,idx+m,cmp);
	int ans=0;
	int T=-1000000;
	for (int i=0;i<m;i++){
		int p=idx[i];
		if (stt[p]>=T){
			T=ent[p];
			ansp[ans++]=p;
		}
	}
	printf("%d\n",ans);
	for (int i=0;i<ans;i++) printf("%d %d\n",ansp[i]/21,ansp[i]%21-10);
	return 0;
}
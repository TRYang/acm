#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
#define maxn 110

using namespace std;

int t[maxn],a[maxn];
queue<int> q[maxn];
int ans[maxn],anst[maxn];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++) scanf("%d%d",a+i,t+i);
	for (int i=0;i<m;i++)
		while (!q[i].empty()) q[i].pop();
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++)
			while (!q[j].empty() && anst[q[j].front()]<=a[i]){
				int T=anst[q[j].front()];
				q[j].pop();
				if (!q[j].empty()){
					int k=q[j].front();
					anst[k]=T+t[k];
				}
			}
		int p=-1;
		for (int j=0;j<m;j++)
			if (p==-1 || q[j].size()<q[p].size()) p=j;
		ans[i]=p+1;
		if (q[p].empty()) anst[i]=a[i]+t[i];
		q[p].push(i);
	}
	for (int j=0;j<m;j++)
		while (!q[j].empty()){
			int T=anst[q[j].front()];
			q[j].pop();
			if (!q[j].empty()){
				int k=q[j].front();
				anst[k]=T+t[k];
			}
		}
	for (int i=0;i<n;i++) printf("%d %d\n",ans[i],anst[i]);
	return 0;
}
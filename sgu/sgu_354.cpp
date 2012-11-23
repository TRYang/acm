#include <stdio.h>
#include <string.h>
#include <vector>
#define maxn 610

using namespace std;

int st[maxn*maxn],aim[maxn*maxn*4],nxt[maxn*maxn*4],ln;
int a[maxn][maxn],b[maxn][maxn];
int q[maxn*maxn];
int tag[maxn*maxn];
int deg[maxn*maxn];
int n;
void in_edge(int x,int y){
	// printf("%d %d\n",x,y);
	deg[y]++;
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int check(){
	memset(st,-1,sizeof(st));
	memset(deg,0,sizeof(deg));
	ln=0;
	for (int j=0;j<n;j++){
		for (int i=0;i<n;i++) q[i]=-1;
		for (int i=n-1;i>=0;i--){
			int p=n-1;
			while (p>=0 && q[p]!=-1) --p;
			if (p<0) return 0;
			while (a[i][j]>0 && p>=0){
				--a[i][j];
				for (--p;p>=0 && q[p]!=-1;--p);
			}
			if (a[i][j]>0 || p<0) return 0;
			q[p]=n*i+j;
		}
		for (int i=0;i<n-1;i++) in_edge(q[i+1],q[i]);
	}
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++) q[j]=-1;
		for (int j=n-1;j>=0;j--){
			int p=n-1;
			while (p>=0 && q[p]!=-1) --p;
			if (p<0) return 0;
			while (b[i][j]>0 && p>=0){
				--b[i][j];
				for (--p;p>=0 && q[p]!=-1;--p);
			}
			if (b[i][j]>0 || p<0) return 0;
			q[p]=i*n+j;
		}
		for (int i=0;i<n-1;i++) in_edge(q[i+1],q[i]);
	}
	int qn=0;
	int num=n*n;
	for (int i=0;i<n*n;i++)
		if (deg[i]==0){
			tag[i]=num--;
			q[qn++]=i;
		}
	for (int p=0;p<qn;p++){
		int u=q[p];
		for (int i=st[u];i!=-1;i=nxt[i]){
			--deg[aim[i]];
			if (deg[aim[i]]==0){
				tag[aim[i]]=num--;
				q[qn++]=aim[i];
			}
		}
	}
	return qn==n*n;
}
int main(){
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) scanf("%d",&a[i][j]);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) scanf("%d",&b[i][j]);
	if (check()){
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				printf("%d",tag[i*n+j]);
				if (j==n-1) puts("");else printf(" ");
			}
		}
	}else puts("0");
	return 0;
}
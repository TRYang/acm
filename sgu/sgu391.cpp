#include <stdio.h>
#include <string.h>
#include <algorithm>
#define maxn 100010

using namespace std;

int cx[maxn],cy[maxn];
int n,m;
int check(){
	int xn=0,yn=0;
	for (int i=1;i<=n;i++)
		if (cx[i]) ++xn;
	for (int i=1;i<=m;i++)
		if (cy[i]) ++yn;
	for (int i=1;i<=n;i++)
		if (cx[i] && cx[i]!=yn) return 0;
	for (int i=1;i<=m;i++)
		if (cy[i] && cy[i]!=xn) return 0;
	return 1;
}
int Z[maxn];
int check2(int *a,int n){
	Z[0]=0;
	for (int i=1,p=0;i<=n;i++){
		int len=(p+Z[p]<=i?0:min(p+Z[p]-i,Z[2*p-i]));
		while (i-len>0 && i+len+1<=n && a[i-len]==a[i+len+1]) ++len;
		Z[i]=len;
		if (i+Z[i]>p+Z[p]) p=i;
	}
	int rn=0;
	for (int i=1;i<=n;i++)
		if (a[i]) ++rn;
	int s=0,t=n;
	int l=s+1,r=t-1;
	while (rn>1){
		int flag=0;
//		printf("[%d,%d] (%d,%d)\n",s,t,l,r);
		int rn1=0;
		while (l<t){
			if (a[l]) ++rn1;
			if (l-Z[l]<=s){
				s=l++;
				rn-=rn1;
				flag=1;
				break;
			}
			++l;
		}
//		printf("[%d,%d] (%d,%d)\n",s,t,l,r);
		rn1=0;
		while (r>s){
			if (a[r+1]) ++rn1;
			if (r+Z[r]>=t){
				t=r--;
				flag=1;
				rn-=rn1;
				break;
			}
			--r;
		}
		if (!flag) return 0;
	}
	return 1;
}
int main(){
	int N;
	scanf("%d%d%d",&n,&m,&N);
	for (int i=0;i<N;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		cx[x]++;
		cy[y]++;
	}
	if (check() && check2(cx,n) && check2(cy,m)) puts("YES");else puts("NO");
	return 0;
}

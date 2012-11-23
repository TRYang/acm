#include <stdio.h>
#include <string.h>
#define maxn 100010
#define maxm 110
int f[maxm][maxn];
char s[maxn];
char st[maxm];
int n,m;
long long ans;
inline int max(int x,int y){return x>y?x:y;}
int main(){
	scanf("%s",s);
	scanf("%s",st);
	n=strlen(s);
	m=strlen(st);
	for (int i=0;i<n;i++){
		if (i==0) f[0][i]=-1;else f[0][i]=f[0][i-1];
		if (st[0]==s[i]) f[0][i]=i;
	}
	for (int j=1;j<m;j++)
		for (int i=0;i<n;i++){
			if (i==0) f[j][i]=-1;else f[j][i]=f[j][i-1];
			if (st[j]==s[i] && i>0 && f[j-1][i-1]>-1) f[j][i]=max(f[j][i],f[j-1][i-1]);
		}
	ans=0;
	for (int i=0;i<n;i++) ans+=f[m-1][i]+1;
	printf("%I64d\n",ans);
	return 0;
}
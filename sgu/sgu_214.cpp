#include <stdio.h>
#include <string.h>
#define maxn 2010
#define maxm 310
int f[maxn][maxn];
char st[maxm];
int m;
int a[maxn],b[maxn];
int w[maxm][maxm];
int m1[maxm],m2[maxm];
int s1[maxm],s2[maxm];
int map[300];
int a1[maxn<<1],a2[maxn<<1];
char s[maxn];
int len;
int n;
void Read(int *c){
	int i,j;
	scanf("%s",s);
	n=strlen(s);
	for (i=0;i<n;i++) c[i]=map[s[i]];
}
int min(int x,int y){return x<y?x:y;}
void find(int i,int j,int p){
	if (i==n && j==n){
		len=p;
		return;
	}
	if (i==n){
		a1[p]=s2[b[j]];
		a2[p]=b[j];
		find(i,j+1,p+1);
		return;
	}
	if (j==n){
		a1[p]=a[i];
		a2[p]=s1[a[i]];
		find(i+1,j,p+1);
		return;
	}
	if (f[i+1][j+1]+w[a[i]][b[j]]==f[i][j]){
		a1[p]=a[i];
		a2[p]=b[j];
		find(i+1,j+1,p+1);
		return;
	}
	if (f[i][j+1]+m2[b[j]]==f[i][j]){
		a1[p]=s2[b[j]];
		a2[p]=b[j];
		find(i,j+1,p+1);
		return;		
	}
	if (f[i+1][j]+m1[a[i]]==f[i][j]){
		a1[p]=a[i];
		a2[p]=s1[a[i]];
		find(i+1,j,p+1);
		return;		
	}
}
int main(){
	int i,j,k;
	scanf("%s",st);
	m=strlen(st);
	for (i=0;i<m;i++) map[st[i]]=i;
	Read(a);
	Read(b);
	for (i=0;i<m;i++)
		for (j=0;j<m;j++) scanf("%d",&w[i][j]);
	for (i=0;i<m;i++){
		m1[i]=w[i][0];s1[i]=0;
		m2[i]=w[0][i];s2[i]=0;
		for (j=1;j<m;j++){
			if (w[i][j]<m1[i]) m1[i]=w[i][j],s1[i]=j;
			if (w[j][i]<m2[i]) m2[i]=w[j][i],s2[i]=j;
		}
	}
	f[n][n]=0;
	for (i=n-1;i>=0;i--) f[n][i]=f[n][i+1]+m2[b[i]];	
	for (i=n-1;i>=0;i--){
		f[i][n]=f[i+1][n]+m1[a[i]];
		for (j=n-1;j>=0;j--) f[i][j]=min(f[i+1][j+1]+w[a[i]][b[j]],min(f[i+1][j]+m1[a[i]],f[i][j+1]+m2[b[j]]));
	}
	printf("%d\n",f[0][0]);
	find(0,0,0);
	for (i=0;i<len;i++) printf("%c",st[a1[i]]);printf("\n");
	for (i=0;i<len;i++) printf("%c",st[a2[i]]);printf("\n");
	return 0;
}

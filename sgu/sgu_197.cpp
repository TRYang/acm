#include <stdio.h>
#include <string.h>
#define maxn 5
int m,q,M;
struct matrix{
	int v[1<<maxn][1<<maxn];
	friend matrix operator * (const matrix &x,const matrix &y){
		matrix res;
		int i,j,k;
		for (i=0;i<M;i++)
			for (j=0;j<M;j++){
				res.v[i][j]=0;
				for (k=0;k<M;k++) res.v[i][j]=(res.v[i][j]+(x.v[i][k]*y.v[k][j])%q)%q;
			}
		return res;
	}
} a,ans,f[2];
char s[120];
int len;
int b[420],c[420],n;
int check(int x,int y){
	for (int i=0;i<m-1;i++){
		if ((x&3)==3 && (y&3)==3) return 0;
		if ((x&3)==0 && (y&3)==0) return 0;
		x>>=1;
		y>>=1;
	}
	return 1;
}
void Init(){
	int i,j;
	memset(a.v,0,sizeof(a.v));
	for (i=0;i<M;i++)
		for (j=0;j<M;j++)
			if (check(i,j)) a.v[i][j]=1;
}
int main(){
	int i,j,k;
	scanf("%s %d %d",s,&m,&q);
	len=strlen(s);
	for (i=1;i<=len;i++) b[len-i]=s[i-1]-'0';
	for (i=0;i<len;i++)
		if (b[i]>0){
			b[i]--;
			if (i==len-1 && b[i]==0) len--;
			break;
		}else b[i]=9;
	n=0;
	while (len>0){
		c[n++]=b[0]%2;
		for (i=len-1;i>=0;i--){
			if (i>0 && (b[i]&1)==1) b[i-1]+=10;
			b[i]>>=1;
		}
		while (len>0 && b[len-1]==0) len--;
	}
	M=1<<m;
	Init();
	memset(ans.v,0,sizeof(ans.v));
	for (i=0;i<M;i++) ans.v[i][i]=1;
	k=0;f[0]=a;
	for (i=0;i<n;i++){
		if (c[i]==1) ans=ans*f[k];
		f[k^1]=f[k]*f[k];
		k^=1;
	}
	k=0;
	for (i=0;i<M;i++)
		for (j=0;j<M;j++) k=(k+ans.v[i][j])%q;
	printf("%d\n",k);
	return 0;
}

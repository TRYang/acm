#include <stdio.h>
#include <string.h>
#define maxm 70
#define maxn 7
int g[maxm][maxn];
char s[maxn];
int n,m;
int f[2][1<<14];
int a[2][2200],an[2];
int now,next;
int ans;
int rv(int x,int p){
	return (x&(((1<<(n<<1))-1)^(3<<p)));
}
int ins(int x,int p){
	return x|p;
}
void updata(int p,int x){
	if (f[next][p]==-1){
		f[next][p]=x;
		a[next][an[next]++]=p;
	}else
	if (x<f[next][p]) f[next][p]=x;
}
int check(int x){
	for (int i=0;i<n;i++){
		if ((x&3)==1) return 0;
		x>>=2;
	}
	return 1;
}
int main(){
	int i,j,k,st,tv,p1,p2;
	scanf("%d %d",&m,&n);
	for (i=0;i<m;i++){
		scanf("%s",s);
		for (j=0;j<n;j++)
			if (s[j]=='.') g[i][j]=1;else g[i][j]=0;
	}
	memset(f,-1,sizeof(f));
	now=0;
	an[0]=1;a[0][0]=0;
	for (i=0;i<n;i++) a[0][0]|=2<<(i<<1);
	f[0][a[0][0]]=0;
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			next=now^1;
			for (k=0;k<an[now];k++){
				st=a[now][k];
				tv=f[now][st];
				f[now][st]=-1;
				if (j>0) p1=((st>>((j-1)<<1))&3);else p1=2;
				p2=((st>>(j<<1))&3);
				if (g[i][j]){
					if (p2==1){
						updata(ins(rv(st,j<<1),2<<(j<<1)),tv);
					}else{
						if (p1==1) updata(ins(rv(rv(st,j<<1),(j-1)<<1),10<<((j-1)<<1)),tv);
						if (p2>0 && p1>0) updata(rv(st,j<<1),tv);
						updata(ins(rv(st,j<<1),1<<(j<<1)),tv+1);
					}
				}else{
					if (p2==1) continue;
					updata(ins(rv(st,j<<1),2<<(j<<1)),tv);
				}
			}
			an[now]=0;
			now=next;
		}
	}
	ans=100000;
	for (i=0;i<an[now];i++)
		if (check(a[now][i]))
			if (f[now][a[now][i]]<ans) ans=f[now][a[now][i]];
	printf("%d\n",ans);
	return 0;
}

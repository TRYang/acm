#include <stdio.h>
#include <string.h>
#define maxn 16
int a[maxn][maxn],s[maxn][maxn];
int f[16][maxn][maxn][226][4];
int t[maxn][maxn];
int n,m,p;
int ans;
int max(int x,int y){return x>y?x:y;}
void work(int i,int j,int k,int p,int z){
	if (p==0) return;
	int ii,jj,d;
	d=p-(k-j+1);
	if (z==0){
		for (ii=j;ii<=k;ii++) t[i][ii]=1;
		for (ii=j;ii<=k;ii++)
			for (jj=ii;jj<=k;jj++)
				if (f[i-1][ii][jj][d][0]+s[i][k]-s[i][j-1]==f[i][j][k][p][z]){
					work(i-1,ii,jj,d,0);
					return;
				}
	}else
	if (z==1){
		if (f[i][j][k][p][0]==f[i][j][k][p][z]){
			work(i,j,k,p,0);
			return;
		}
		for (ii=j;ii<=k;ii++) t[i][ii]=1;
		for (ii=1;ii<=j;ii++)
			for (jj=j;jj<=k;jj++)
				if (f[i-1][ii][jj][d][1]+s[i][k]-s[i][j-1]==f[i][j][k][p][z]){
					work(i-1,ii,jj,d,1);
					return;
				}
	}else
	if (z==2){
		if (f[i][j][k][p][0]==f[i][j][k][p][z]){
			work(i,j,k,p,0);
			return;
		}
		for (ii=j;ii<=k;ii++) t[i][ii]=1;
		for (ii=j;ii<=k;ii++)
			for (jj=k;jj<=m;jj++)
				if (f[i-1][ii][jj][d][2]+s[i][k]-s[i][j-1]==f[i][j][k][p][z]){
					work(i-1,ii,jj,d,2);
					return;
				}
	}else{
		for (ii=0;ii<3;ii++)
			if (f[i][j][k][p][ii]==f[i][j][k][p][z]){
				work(i,j,k,p,ii);
				return;
			}
		for (ii=j;ii<=k;ii++) t[i][ii]=1;
		for (ii=1;ii<=j;ii++)
			for (jj=k;jj<=m;jj++)
				if (f[i-1][ii][jj][d][3]+s[i][k]-s[i][j-1]==f[i][j][k][p][z]){
					work(i-1,ii,jj,d,3);
					return;
				}
	}
}
int main(){
	int i,j,k,l,c;
	scanf("%d %d %d",&n,&m,&p);
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++) scanf("%d",&a[i][j]);
	if (p==0){
		printf("Oil : 0\n");
		return 0;
	}
	for (i=1;i<=n;i++){
		s[i][0]=0;
		for (j=1;j<=m;j++) s[i][j]=s[i][j-1]+a[i][j];
	}
	for (k=0;k<4;k++)
		for (i=1;i<=m;i++)
			for (j=i;j<=m;j++){
				f[0][i][j][0][k]=0;
				for (l=1;l<=p;l++) f[0][i][j][l][k]=-10000000;
			}
	int jj,kk,d;
	for (i=1;i<=n;i++){
		for (j=1;j<=m;j++)
			for (k=j;k<=m;k++)
				for (c=0;c<4;c++){
					f[i][j][k][0][c]=0;
					for (l=1;l<=p;l++) f[i][j][k][l][c]=-10000000;
				}
		for (c=1;c<=p;c++)
			for (j=1;j<=m;j++)
				for (k=j;k<=m;k++)
					if (c>=k-j+1){
						d=c-(k-j+1);
						f[i][j][k][c][0]=-10000000;
						for (jj=j;jj<=k;jj++)
							for (kk=jj;kk<=k;kk++) f[i][j][k][c][0]=max(f[i][j][k][c][0],f[i-1][jj][kk][d][0]);
						f[i][j][k][c][0]+=s[i][k]-s[i][j-1];
						f[i][j][k][c][1]=-10000000;
						for (jj=1;jj<=j;jj++)
							for (kk=j;kk<=k;kk++) f[i][j][k][c][1]=max(f[i][j][k][c][1],f[i-1][jj][kk][d][1]);
						f[i][j][k][c][1]+=s[i][k]-s[i][j-1];
						f[i][j][k][c][1]=max(f[i][j][k][c][1],f[i][j][k][c][0]);
						f[i][j][k][c][2]=-10000000;
						for (jj=j;jj<=k;jj++)
							for (kk=k;kk<=m;kk++) f[i][j][k][c][2]=max(f[i][j][k][c][2],f[i-1][jj][kk][d][2]);
						f[i][j][k][c][2]+=s[i][k]-s[i][j-1];
						f[i][j][k][c][2]=max(f[i][j][k][c][2],f[i][j][k][c][0]);
						f[i][j][k][c][3]=-10000000;
						for (jj=1;jj<=j;jj++)
							for (kk=k;kk<=m;kk++) f[i][j][k][c][3]=max(f[i][j][k][c][3],f[i-1][jj][kk][d][3]);
						f[i][j][k][c][3]+=s[i][k]-s[i][j-1];
						for (int x=0;x<3;x++) f[i][j][k][c][3]=max(f[i][j][k][c][3],f[i][j][k][c][x]);
					}
	}
	ans=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			for (k=j;k<=m;k++) ans=max(ans,f[i][j][k][p][3]);
	printf("Oil : %d\n",ans);
	int tag=1;
	memset(t,0,sizeof(t));
	for (i=1;i<=n && tag;i++)
		for (j=1;j<=m && tag;j++)
			for (k=j;k<=m && tag;k++)
				if (f[i][j][k][p][3]==ans){
					work(i,j,k,p,3);
					tag=0;
				}
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++)
			if (t[i][j]) printf("%d %d\n",i,j);
	return 0;
}

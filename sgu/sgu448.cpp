#include <stdio.h>
#include <string.h>
#define maxn 16
long long f[17][(1<<maxn)+10][maxn];
int q[17][(1<<maxn)*maxn],qn[17];
int count[20];
int a[maxn][maxn];
int n,m,N;
int cal_height(int x){
	return count[x-1];
}
int max(int x,int y){return x>y?x:y;}
void updata(int x,int y,int z,long long value){
	if (f[x][y][z]==0) q[x][qn[x]++]=(y<<4)|z;
	f[x][y][z]+=value;
}
int main(){
	count[0]=0;
	for (int i=1;i<20;i++) count[i]=count[i>>1]+1;
	scanf("%d%d",&n,&m);
	m--;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++) scanf("%d",&a[i][j]);
	memset(f,0,sizeof(f));
	qn[1]=0;
	for (int j=0;j<n;j++){
		q[1][qn[1]++]=((1<<j)<<4)|j;
		f[1][1<<j][j]=1;
	}
	for (int d=2;d<=n;d++){
		qn[d]=0;
		for (int lt=1;lt<d && d-lt>=lt;lt++)
			if (max(cal_height(lt),cal_height(d-lt))+1==cal_height(d)){
				int rt=d-lt;
				for (int p=0;p<qn[lt];p++){
					int mask1=q[lt][p]>>4,x=(q[lt][p]&15);
					for (int c=0;c<qn[rt];c++){
						int mask2=q[rt][c]>>4,y=(q[rt][c]&15);
						if ((mask1&mask2)>0) continue;
						if (lt==rt && a[x][y]==0) continue;
						updata(d,mask1|mask2,a[x][y]?x:y,f[lt][mask1][x]*f[rt][mask2][y]);
					}
				}
			}
	}
	printf("%lld\n",f[n][(1<<n)-1][m]);
	return 0;
}

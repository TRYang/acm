#include <stdio.h>
#include <string.h>
#define maxn 1010
int f[maxn][4][4];
char s[maxn];
int n;
int get(char c){
	if (c=='N') return -1;
	if (c=='L') return 0;
	if (c=='D') return 1;
	if (c=='R') return 2;
	return 3;
}
inline void updata(int &x,int value){
	if (x==-1 || value<x) x=value;
}
void op1(int i,int j,int k){
	if (s[i]=='N'){
		updata(f[i+1][j][k],f[i][j][k]);
	}
}
void op2(int i,int j,int k){
	if (get(s[i])==j || get(s[i])==k){
		updata(f[i+1][j][k],f[i][j][k]+1);
	}
}
void op3(int i,int j,int k){
	int c=get(s[i]);
	if (c!=2 || k!=0){
		updata(f[i+1][c][k],f[i][j][k]+3);
	}
	if (j!=2 || c!=0){
		updata(f[i+1][j][c],f[i][j][k]+3);
	}
}
void op4(int i,int j,int k){
	if (i==n-1) return;
	int c=get(s[i+1]);
	if (get(s[i])==j && (c!=2 || k!=0)){
		updata(f[i+2][c][k],f[i][j][k]+9);
	}
	if (get(s[i])==k && (j!=2 || c!=0)){
		updata(f[i+2][j][c],f[i][j][k]+9);
	}
}
void op5(int i,int j,int k){
	if (i==n-1) return;
	int c=get(s[i]),d=get(s[i+1]);
	if (c!=2 || d!=0){
		updata(f[i+2][c][d],f[i][j][k]+10);
	}
	if (d!=2 || c!=0){
		updata(f[i+2][d][c],f[i][j][k]+10);
	}
}
int main(){
	scanf("%d",&n);
	scanf("%s",s);
	memset(f,-1,sizeof(f));
	f[0][0][2]=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<4;j++)
			for (int k=0;k<4;k++)
				if (f[i][j][k]>-1){
					op1(i,j,k);
					op2(i,j,k);
					op3(i,j,k);
					op4(i,j,k);
					op5(i,j,k);
				}
	int ans=-1;
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			if (f[n][i][j]>-1) updata(ans,f[n][i][j]);
	printf("%d\n",ans);
	return 0;
}
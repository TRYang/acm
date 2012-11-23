#include <stdio.h>
#include <string.h>
int a[25][25];
char b[410][410];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++) a[i/n][i%n]=1;
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			for (int x=0;x<n;x++)
				for (int y=0;y<n;y++){
					int sx=i*n,sy=j*n;
					sx+=x;
					sy+=y;
					if (a[(x+j)%n][(y+i)%n]) b[sx][sy]='*';else b[sx][sy]='.';
				}
		}
	}
	for (int i=0;i<n*n;i++){
		for (int j=0;j<n*n;j++) printf("%c",b[i][j]);
		puts("");
	}
	return 0;
}

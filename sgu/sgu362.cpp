#include <stdio.h>
#include <string.h>
#include <string>
#define maxn 15
using namespace std;
const int mx[]={1,0,-1,0};
const int my[]={0,-1,0,1};
const string s="DLUR";
int tag[maxn][maxn];
int n,m;
int check(int x,int y,int k){
	x+=mx[k];
	y+=my[k];
	return x>0 && x<=n && y>0 && y<=m && !tag[x][y];
}
int main(){
	scanf("%d%d",&n,&m);
	int x,y;
	scanf("%d%d",&x,&y);
	memset(tag,0,sizeof(tag));
	while (1){
		int flag=0;
		tag[x][y]=1;
		for (int i=0;i<4;i++)
			if (check(x,y,i)){
				flag=1;
				x+=mx[i];
				y+=my[i];
				printf("%c",s[i]);
				break;
			}
		if (!flag) break;
	}
	return 0;
}

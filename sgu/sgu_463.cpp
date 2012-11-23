#include <stdio.h>
#include <string.h>
#define maxn 110
const int mx[]={0,-1,0,1};
const int my[]={1,0,-1,0};
int tag[maxn][maxn];
int n,m;
char s[maxn];
int w[maxn][maxn];
int len;
int ans;
void updata(int x,int y){
	if (!tag[x][y]) ans+=w[x][y];else ans+=w[x][y]>>1;
	tag[x][y]=1;
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<n;i++){
		char st[maxn];
		scanf("%s",st);
		for (int j=0;j<m;j++) w[i][j]=st[j]-'0';
	}
	scanf("%s",s);
	len=strlen(s);
	int d=0,x=0,y=0;
	memset(tag,0,sizeof(tag));
	ans=0;
	for (int p=0;p<len;p++){
		if (s[p]=='L'){
			d=(d+1)%4;
		}else
		if (s[p]=='R'){
			d=(d+3)%4;
		}else{
			if (d==0){
				if (x<n) updata(x,y);
				if (x>0) updata(x-1,y);
			}else
			if (d==1){
				if (y>0) updata(x-1,y-1);
				if (y<m) updata(x-1,y);
			}else
			if (d==2){
				if (x>0) updata(x-1,y-1);
				if (x<n) updata(x,y-1);
			}else{
				if (y>0) updata(x,y-1);
				if (y<m) updata(x,y);
			}
			x+=mx[d];
			y+=my[d];
		}
	}
	printf("%d\n",ans);
	return 0;
}

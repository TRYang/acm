#include <stdio.h>
#include <string.h>
#define maxn 5010
int num[maxn];
int father[maxn<<1],size[maxn<<1];
int stack[maxn<<1],stn;
int n,m;
char s[2][maxn];
int ans;
int Find(int x){return father[x] = father[x]==x ? x : Find(father[x]);}
int main(){
	while (scanf("%d%d",&n,&m)!=EOF){
		memset(num,-1,sizeof(num));
		stn=0;
		for (int i=0;i<10000;i++) stack[stn++]=i;
		ans=0;
		for (int i=0;i<m;i++) s[1][i]='?';
		for (int i=0;i<n;i++){
			scanf("%s",s[i&1]);
			for (int j=0;j<m;j++){
				if (s[i&1][j]=='*'){
					if (j && num[j-1]>-1 && num[j]>-1){
						int fx=Find(num[j-1]),fy=Find(num[j]);
						if (fx!=fy){
							father[fx]=fy;
							--ans;
						}
					}else
					if (num[j]>-1){
					}else
					if (j && num[j-1]>-1){
						num[j]=Find(num[j-1]);
						size[num[j]]++;
					}else{
						int tmp=stack[--stn];
						num[j]=tmp;
						father[tmp]=tmp;
						size[tmp]=1;
						++ans;
					}
				}else{
					if (s[(i+1)&1][j]=='*'){
						int k=num[j];
						--size[k];
						if (size[k]==0) stack[stn++]=k;
						num[j]=-1;
					}
				}
			}
			// printf("%d : %d\n",i,ans);
		}
		printf("%d\n",ans);
	}
	return 0;
}
#include <stdio.h>
#include <string.h>
#define maxn 110
#define maxt 10010
int g[maxt],suf[maxt];
int trie[maxt][26],tn;
int value[maxt];
int q[maxt],qn;
char Set[30];
char s[10000];
int f[maxn][maxt];
int fp[maxn][maxt];
int st[maxn];
int n,m,K;
inline void Clear(int p){
	g[p]=0;
	memset(trie[p],0,sizeof(trie[p]));
}
void pr(int x,int y){
	if (x==0) return;
	pr(x-1,fp[x][y]);
	printf("%c",Set[value[y]]);
}
int main(){
	while (scanf("%d%d%d",&n,&K,&m)!=EOF){
		scanf("%s",Set);
		Clear(0);
		tn=1;
		for (int t=0;t<m;t++){
			int fv;
			scanf("%s%d",s,&fv);
			int len=strlen(s);
			if (len>n) continue;
			for (int i=0;i<len;i++)
				for (int j=0;j<K;j++)
					if (Set[j]==s[i]) st[i]=j;
			int p=0;
			for (int i=0;i<len;p=trie[p][st[i++]])
				if (trie[p][st[i]]==0){
					Clear(tn);
					value[tn]=st[i];
					trie[p][st[i]]=tn++;
				}
			g[p]+=fv;
		}
		qn=0;
		for (int i=0;i<K;i++)
			if (trie[0][i]){
				int k=trie[0][i];
				suf[k]=0;
				q[qn++]=k;
			}
		for (int p=0;p<qn;p++){
			int u=q[p];
			for (int i=0;i<K;i++)
				if (trie[u][i]){
					int v=trie[u][i];
					suf[v]=trie[suf[u]][i];
					g[v]+=g[suf[v]];
					q[qn++]=v;
				}else trie[u][i]=trie[suf[u]][i];
		}
		memset(f,-1,sizeof(f));
		f[0][0]=0;
		for (int i=0;i<n;i++)
			for (int j=0;j<tn;j++)
				if (f[i][j]>-1){
					for (int c=0;c<K;c++)
						if (trie[j][c]){
							int np=trie[j][c];
							if (f[i][j]+g[np]>f[i+1][np]){
								f[i+1][np]=f[i][j]+g[np];
								fp[i+1][np]=j;
							}
						}
				}
		int ans=0,ansp;
		for (int i=1;i<tn;i++)
			if (f[n][i]>ans){
				ans=f[n][i];
				ansp=i;
			}
		printf("%d\n",ans);
		pr(n,ansp);
	}
	return 0;
}
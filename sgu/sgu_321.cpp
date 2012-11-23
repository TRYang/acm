#include <stdio.h>
#include <string.h>
#define maxn 200010
char s[20];
int st[maxn],aim[maxn],link[maxn],ln;
int e[maxn],c[maxn],f[maxn];
int next[maxn],stack[maxn];
int ans[maxn],ansp;
int n;

void in_edge(int x,int y){
	aim[ln]=y;
	link[ln]=st[x];
	st[x]=ln++;
}

int max(int x,int y){return x>y?x:y;}

void dfs(){
	int i,k,stn,level,tot;
	stack[stn=1]=1;
	next[1]=st[1];
	level=tot=0;
	while (stn>0){
		k=stack[stn];
		for (i=next[k];i!=-1;i=link[i]){
			next[k]=link[i];
			next[aim[i]]=st[aim[i]];
			level++;
			tot+=c[aim[i]];
			if (tot<(level+1)>>1) f[aim[i]]=((level+1)>>1)-tot;else f[aim[i]]=0;
			stack[++stn]=aim[i];
			break;
		}
		if (i==-1){
			level--;
			tot-=c[k];
			stn--;
			if (stn>0) f[stack[stn]]=max(f[stack[stn]],f[k]);
		}
	}
}

void dfs2(){
	int i,k,stn,tot=0,level=0;
	stack[stn=1]=1;
	next[1]=st[1];
	while (stn>0){
		k=stack[stn];
		for (i=next[k];i!=-1;i=link[i]){
			next[k]=link[i];
			next[aim[i]]=st[aim[i]];
			level++;
			if (!c[aim[i]] && tot<f[aim[i]]){
				ansp++;
				tot++;
				c[aim[i]]=2;
				ans[e[aim[i]]]=1;
			}
			stack[++stn]=aim[i];
			break;
		}
		if (i==-1){
			stn--;
			level--;
			tot-=(c[k]==2);
		}
	}
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	memset(st,-1,sizeof(st));
	ln=0;
	for (i=1;i<n;i++){
		scanf("%d %d %s",&j,&k,s);
		in_edge(k,j);
		e[j]=i;
		if (s[0]=='a'){
			c[j]=0;
			scanf("%s",s);
		}else c[j]=1;
	}
	dfs();
	memset(ans,0,sizeof(ans));
	ansp=0;
	dfs2();
	printf("%d\n",ansp);
	for (i=1;i<n;i++)
		if (ans[i]) printf("%d ",i);
	printf("\n");
	return 0;
}

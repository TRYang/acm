#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 1010
bool a[maxn][maxn];
int next[maxn],pre[maxn];
int tag[maxn],deg[maxn];
int n;
char s[5000],c;

int find(int x){
	if (deg[x]==0) return 0;
	for (int i=1;i<=n;i++)
		if (a[x][i] && !tag[i]) return i;
	return 0;
}

void Cir(int &h,int &t){
	if (a[h][t]){
		pre[h]=t;
		next[t]=h;
		return;
	}
	int i,j,k,tmp,f;
	for (i=next[h];i!=t;i=f)
		if (a[t][i] && a[h][next[i]]){
			k=next[i];
			next[t]=i;
			next[i]=pre[i];
			pre[i]=t;
			next[h]=k;
			pre[k]=h;
			return;
		}else{
			f=next[i];
			tmp=pre[i];
			next[i]=tmp;
			pre[tmp]=i;
		}
}

void Add(int x){
	if (deg[x]==1) return;
	for (int i=1;i<=n;i++)
		if (a[i][x]) deg[i]--;
}

int find2(int &x){
	int i=x,j;
	do{
		if (deg[i]>0){
			x=i;
			for (j=1;j<=n;j++)
				if (!tag[j] && a[i][j]) return j;
		}
		i=next[i];
	}while (i!=x);
}

void work(){
	int head,tail,L=1;
	int i,j,k;
	memset(tag,0,sizeof(tag));
	k=(rand()%n)+1;
	head=tail=k;
	tag[k]=1;
	Add(k);
	while (L<n){
		while (k=find(head),k){
			pre[head]=k;
			next[k]=head;
			head=k;
			tag[k]=1;
			L++;
			Add(k);
		}
		while (k=find(tail),k){
			next[tail]=k;
			pre[k]=tail;
			tail=k;
			tag[k]=1;
			L++;
			Add(k);
		}
		Cir(head,tail);
		if (L<n){
			k=find2(head);
			tag[k]=1;
			Add(k);
			tail=pre[head];
			next[tail]=0;
			pre[head]=k;
			next[k]=head;
			head=k;
		}
	}
}

int main(){
	int i,j,k,l,pp;
	srand(178934);
	scanf("%d",&n);
	memset(deg,0,sizeof(deg));
	while (scanf("%c",&c),c!='\n');
	for (i=1;i<=n;i++){
		gets(s);
		l=strlen(s);
		for (j=0;j<l;)
			if (s[j]==' ') j++;else{
				pp=s[j]-'0';
				for (k=j;k<l-1 && s[k+1]!=' ';k++) pp=(pp*10)+s[k+1]-'0';
				a[i][pp]=1;
				deg[i]++;
				j=k+1;
			}
	}
	/*for (i=1;i<=n;i++){
		for (j=1;j<=n;j++) printf("%d ",a[i][j]);
		printf("\n");
	}*/
	work();
	i=1;
	do{
		printf("%d ",i);
		i=next[i];
	}while (i!=1);
	printf("1\n");
	return 0;
}

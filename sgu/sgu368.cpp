#include <stdio.h>
#include <string.h>
#define maxn 110
int score[maxn];
int a[maxn],an;
char s[maxn],st[maxn];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) scanf("%d",score+i);
	int tot=0;
	for (int p=0;p<n;p++){
		gets(s);
		gets(s);
		int sum=0;
		scanf("%d",&an);
		for (int i=0;i<an;i++) scanf("%d",a+i);
		for (int i=0;i<an;i++){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			if (score[a[i]]<x) sum+=2;else
			if (score[a[i]]<y) sum+=3;else
			if (score[a[i]]<z) sum+=4;else sum+=5;
		}
		int k;
		for (scanf("%d",&k);k;k--){
			gets(st);
			gets(st);
			int d;
			scanf("%d",&d);
			if (sum>=d){
				printf("%s %s\n",s,st);
				tot++;
			}
		}
	}
	if (tot==0) puts("Army");
	return 0;
}

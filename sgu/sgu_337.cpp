#include <stdio.h>
#include <string.h>
#define maxn 2010
char s[maxn<<1];
int p[maxn<<1];
int n,m,len;
int ans;

int check(int L){
	int i,j,k;
	for (i=0;i+L<len;i++) p[i]= (s[i]!=s[i+L]);
	for (i=k=0;i<L;i++) k+=p[i];
	for (i=0;i<n;i++){
		if (k<=m) return 1;
		k-=p[i];
		if (i+L<len) k+=p[i+L];
	}
	return 0;
}

int cmp(int x,int y,int L){
	for (int i=0;i<L;i++){
		if (s[x+i]<s[y+i]) return 1;
		if (s[x+i]>s[y+i]) return 0;
	}
	return 1;
}

void find_ans(int L){
	int i,k=0,st=-1;
	for (i=0;i<L;i++) k+=p[i];
	for (i=0;i<n;i++){
		if (k<=m){
			if (st==-1 || cmp(i,st,L<<1)) st=i;
		}
		k-=p[i];
		if (i+L<len) k+=p[i+L];
	}
	for (i=0;i<L<<1;i++) printf("%c",s[st+i]);
	printf("\n");
}

int main(){
	int i,j,k;
	scanf("%d",&m);
	scanf("%s",s);
	n=strlen(s);
	len=n<<1;
	for (i=n;i<len;i++) s[i]=s[i-n];
	for (ans=n>>1;ans>0;ans--)
		if (check(ans)){
			find_ans(ans);
			break;
		}
	if (ans==0) printf("\n");
	return 0;
}

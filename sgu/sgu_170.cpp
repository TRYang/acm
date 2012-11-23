#include <stdio.h>
#include <string.h>
#define maxn 5010
char s1[maxn],s2[maxn];
int n,m;
int ans;
int check(){
	int i,j,k;
	n=strlen(s1);
	m=strlen(s2);
	if (n!=m) return 0;
	j=k=0;
	for (i=0;i<n;i++){
		if (s1[i]=='+') j++;
		if (s2[i]=='+') k++;
	}
	return j==k;
}
int abs(int x){return x>0?x:-x;}
int main(){
	int i,j,k;
	scanf("%s",s1);
	scanf("%s",s2);
	if (check()){
		ans=0;
		for (i=j=0;i<n;i++)
			if (s1[i]=='+'){
				while (j<n && s2[j]!='+') j++;
				ans+=abs(j-i);
				//printf("%d %d\n",i,j);
				j++;
			}
		printf("%d\n",ans);
	}else printf("-1\n");
	return 0;
}

#include <stdio.h>
#include <string.h>
char s[10010];
char st[10010];
int stack[10010],stn;
int n,len;
char UP(char c){
	return c>='A' && c<='Z' ? c : 'A'+c-'a';
}
char DOWN(char c){
	return c>='a' && c<='z' ? c : 'a'+c-'A';
}
int main(){
	int i,j,k;
	stn=0;
	scanf("%s",s);
	len=strlen(s);
	n=0;
	for (i=0;i<len;i=j+1)
		if (s[i]=='<'){
			for (j=i;s[j]!='>';j++);
			if (s[i+1]=='/'){
				stn--;
			}else{
				if (s[i+1]=='U') stack[++stn]=1;else stack[++stn]=2;
			}
		}else{
			j=i;
			if (stn==0) st[n++]=s[i];else
			if (stack[stn]==1) st[n++]=UP(s[i]);else st[n++]=DOWN(s[i]);
		}
	for (i=0;i<n;i++) printf("%c",st[i]);
	printf("\n");
	return 0;
}

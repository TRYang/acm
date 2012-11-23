#include <stdio.h>
#include <string.h>
#define maxn 2010
char s[maxn];
int a[maxn];
int len;
void Div2(){
	for (int i=len-1;i>=0;i--){
			if (i>0 && (a[i]&1)==1) a[i-1]+=10;
			a[i]>>=1;
		}
	if (a[len-1]==0) len--;
}
void Dec(){
	for (int i=0;i<len;i++)
		if (a[i]>0){
			a[i]--;
			if (a[i]==0 && i==len-1) len--;
			break;
		}else a[i]=9;
}
void pr(){
	for (int i=len-1;i>=0;i--) printf("%d",a[i]);printf("\n");
}
int main(){
	int i,j,k;
	scanf("%s",s);
	len=strlen(s);
	for (i=0;i<len;i++) a[i]=s[len-i-1]-'0';
	if (a[0]%2==0){
		Div2();
		if (a[0]%2==0){
			Dec();
			pr();
		}else{
			Dec();
			Dec();
			pr();
		}
	}else{
		Div2();
		pr();
	}
	return 0;
}

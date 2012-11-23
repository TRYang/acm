#include <stdio.h>
#include <string.h>
int a[8];
int main(){
	for (int i=1;i<8;i++) scanf("%d",a+i);
	char s[10];
	scanf("%s",s);
	int ans=0;
	if (s[0]=='R'){
		ans+=7;
		ans+=8*a[1];
		for (int i=2;i<8;i++) ans+=i;
	}else
	if (s[0]=='C'){
		ans+=8*a[1];
		for (int i=2;i<8;i++) ans+=i*a[i];
	}else{
		ans+=8*a[1];
		for (int i=2;i<8;i++) ans+=i*a[i];
	}
	printf("%d\n",ans);
	return 0;
}

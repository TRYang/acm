#include <stdio.h>
#include <string.h>
#include <ctype.h>
int *a[4];
int main(){
	int n;
	for (int i=0;i<4;i++) a[i]=new int(0);
	char buf[100];
	for (scanf("%d",&n);n;n--){
		scanf("%s",buf);
		if (buf[0]=='w'){
			//writeln(a^);
			printf("%d\n",*a[buf[8]-'a']);
		}else
		if (buf[1]==':'){
			//a:=b;
			a[buf[0]-'a']=a[buf[3]-'a'];
		}else
		if (isdigit(buf[4])){
			//a^:=const
			int number=0,len=strlen(buf)-1;
			for (int i=4;i<len;i++) number=number*10+buf[i]-'0';
			*a[buf[0]-'a']=number;
		}else{
			//a^:=b^
			*a[buf[0]-'a']=*a[buf[4]-'a'];
		}
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
int n;
int main(){
	char s[1010];
	for (scanf("%d",&n);n;n--){
		scanf("%s",s);
		int len=strlen(s);
		if (s[len-1]=='y'){
			s[len-1]='i';
			s[len]='e';
			s[len+1]='s';
			len+=2;
		}else
		if (s[len-1]=='f' || (len>1 && s[len-2]=='f' && s[len-1]=='e')){
			if (s[len-1]=='f') ++len;
			s[len-2]='v';
			s[len-1]='e';
			s[len]='s';
			++len;
		}else
		if (s[len-1]=='x' || s[len-1]=='s' || s[len-1]=='o' || (len>1 && s[len-2]=='c' && s[len-1]=='h')){
			s[len]='e';
			s[len+1]='s';
			len+=2;
		}else{
			s[len]='s';
			len++;
		}
		for (int i=0;i<len;i++) printf("%c",s[i]);
		puts("");
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

int check_letter(char c){
	return islower(c) || isupper(c);
}
int check_sym(char c){
	if (islower(c)) return 1;
	if (isupper(c)) return 1;
	if (isdigit(c)) return 1;
	return c=='_' || c=='-';
}
int check_word(string s){
	if (s.empty()) return 0;
	for (int i=0;i<s.length();i++)
		if (!check_sym(s[i])) return 0;
	return 1;
}
int check_pre(string s){
	if (s.empty()) return 0;
	int i;
	for (i=s.length()-1;i>=0;i--)
		if (s[i]=='.'){
			return check_pre(s.substr(0,i)) && check_word(s.substr(i+1));
		}
	return check_word(s);
}
int check_domain(string s){
	if (s.length()==2 || s.length()==3){
		for (int i=0;i<s.length();i++)
			if (!check_letter(s[i])) return 0;
		return 1;
	}else return 0;
}
int check_suf(string s){
	if (s.empty()) return 0;
	int i,j,k=-1;
	for (i=s.length()-1;i>=0;i--)
		if (s[i]=='.') return check_pre(s.substr(0,i)) && check_domain(s.substr(i+1));
	return 0;
}
int check_add(string s){
	if (s.empty()) return 0;
	int i,j,k=-1;
	for (i=0;i<s.length();i++)
		if (s[i]=='@')
			if (k==-1){
				k=i;
			}else return 0;
	if (k==-1) return 0;
	return check_pre(s.substr(0,k)) && check_suf(s.substr(k+1));
}
int main(){
	int n;
	scanf("%d",&n);
	char st[200];
	gets(st);
	for (;n>0;n--){
		string s;
		s.clear();
		gets(st);
		for (int i=0;i<strlen(st);i++) s+=st[i];
		if (check_add(s)) printf("YES\n");else printf("NO\n");
	}
	return 0;
}

#include <stdio.h>
#include <algorithm>
#define maxn 510
using namespace std;
int tag[maxn];
int f[maxn];
int s[10];
int n;
void work(int x){
	int n=0;
	while (x){
		s[n++]=(x&1);
		x>>=1;
	}
	reverse(s,s+n);
	for (int i=0;i<n;i++){
		int tmp=0;
		for (int j=0;j<n;j++) tmp=(tmp<<1)+s[(i+j)%n];
		tag[tmp]=1;
	}
}
int main(){
	int p=0;
	for (int i=1;i<=100;i++){
		work(i);
		while (tag[p+1]){
			++p;
			f[p]=i;
		}
	}
	for (int i=1;i<=100;i++) printf("%d ",f[i]);puts("");
	return 0;
}
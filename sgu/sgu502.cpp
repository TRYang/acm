#include <stdio.h>
#include <string.h>
char s[20];
int q[(1<<17)*17+10][2];
long long f[(1<<17)+10][17];
int qn;
long long ans;
int n;
int main(){
	scanf("%s",s);
	n=strlen(s);
	memset(f,-1,sizeof(f));
	qn=0;
	for (int i=0;i<n;i++)
		if (s[i]!='0'){
			q[qn][0]=1<<i;
			q[qn++][1]=s[i]-'0';
			f[1<<i][s[i]-'0']=s[i]-'0';
		}
	ans=-1;
	for (int p=0;p<qn;p++){
		int mask=q[p][0],k=q[p][1];
		if (mask==(1<<n)-1){
			if (k==0) ans=f[mask][k];
			continue;
		}
		for (int i=0;i<n;i++)
			if ((mask&(1<<i))==0){
				int tmask=(mask|(1<<i)),c=(k*10+s[i]-'0')%17;
				if (f[tmask][c]==-1){
					f[tmask][c]=f[mask][k]*10+s[i]-'0';
					q[qn][0]=tmask;
					q[qn++][1]=c;
				}
			}
	}
	printf("%lld\n",ans);
	return 0;
}

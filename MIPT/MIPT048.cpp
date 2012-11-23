#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#define maxn 65
#define mp(x,y) ((x<<3)|y)
#define state(x,y,z) ((z<<12)|(x<<6)|y)
#define inside(x,y) (x>=0 && y>=0 && x<8 && y<8 && (x!=2 || y!=2))
#define kill(x,y) (max(abs((x>>3)-(y>>3)),abs((x&7)-(y&7)))<2)

using namespace std;

const int mx[]={0,-1,-1,-1,0,1,1,1};
const int my[]={1,1,0,-1,-1,-1,0,1};

int deg[maxn*maxn*2];
int st[maxn*maxn*2],aim[500000],nxt[500000],ln;
int f[maxn*maxn*2];
int q[maxn*maxn*2],qn;
int att[maxn][maxn];
int stp,enp;
int n=8;
void in_edge(int x,int y){
	deg[y]++;
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
int main(){
	char s[5];
	scanf("%s",s);
	stp=mp(s[0]-'a',s[1]-'1');
	scanf("%s",s);
	enp=mp(s[0]-'a',s[1]-'1');
	for (int i=0;i<64;i++)
		for (int j=0;j<8;j++){
			int x=(i>>3)+mx[j],y=(i&7)+my[j];
			while (inside(x,y)){
				att[i][mp(x,y)]=1;
				x+=mx[j];
				y+=my[j];
			}
		}
	memset(f,-1,sizeof(f));
	memset(st,-1,sizeof(st));
	ln=0;
	qn=0;
	for (int i=0;i<64;i++)
		for (int j=0;j<64;j++){
			if (i==j) continue;
			if (i==18 || j==18) continue;
			if (att[i][j] || kill(18,j)){
				f[state(i,j,0)]=0;
				q[qn++]=state(i,j,0);
			}else
			for (int k=0;k<64;k++)
				if (k!=i && k!=j && k!=18 && att[i][k] && (!kill(k,j) || kill(18,k)))
					in_edge(state(k,j,1),state(i,j,0));
			
			if (!kill(i,j) || kill(18,i)){
				for (int k=0;k<8;k++){
					int sx=(j>>3)+mx[k],sy=(j&7)+my[k];
					if (inside(sx,sy) && mp(sx,sy)!=i) in_edge(state(i,mp(sx,sy),0),state(i,j,1));
				}
			}
		}
	int anst=state(stp,enp,0);
	for (int p=0;p<qn;p++){
		int d=(q[p]>>12),u=q[p];
		// printf("%d\n",f[u]);
		if (u==anst){
			printf("%d\n",f[u]);
			break;
		}
		for (int i=st[u];i!=-1;i=nxt[i]){
			int v=aim[i];
			if (d==0){
				deg[v]--;
				if (deg[v]==0 && (f[u]!=0 || att[(v>>6)&63][v&63])){
					f[v]=f[u]+1;
					q[qn++]=v;
				}
			}else{
				if (f[v]==-1){
					f[v]=f[u];
					q[qn++]=v;
				}
			}
		}
	}
	return 0;
}
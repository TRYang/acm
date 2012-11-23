#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <string>
#define maxn 100010

using namespace std;

string ip[maxn],ipx[maxn];
int x[maxn],xn;
int m;
int track_id[maxn],score[maxn],T[maxn];
int last[maxn];
int tree[maxn<<2];
int value[maxn];
bool type[maxn];
int qn;
inline void push_up(int p){
	tree[p]=(value[tree[p<<1]]>=value[tree[(p<<1)+1]]?tree[p<<1]:tree[(p<<1)+1]);
}
void init(int p,int tl,int tr){
	if (tl==tr){
		tree[p]=tl;
		return;
	}
	int m=(tl+tr)>>1;
	init(p<<1,tl,m);
	init((p<<1)+1,m+1,tr);
	push_up(p);
}
void ins(int p,int tl,int tr,int k){
	if (tl==tr) return;
	int m=(tl+tr)>>1;
	if (k<=m) ins(p<<1,tl,m,k);else ins((p<<1)+1,m+1,tr,k);
	push_up(p);
}
int main(){
	qn=0;
	char buffer[50];
	m=xn=0;
	while (1){
		scanf("%s",buffer);
		if (buffer[0]=='E') break;
		if (buffer[0]=='V'){
			type[qn]=false;
			char ip_stream[100];
			scanf("%s%d%d%d",ip_stream,track_id+qn,score+qn,T+qn);
			ip[qn]=ip_stream;
			ipx[m++]=ip[qn];
			x[xn++]=track_id[qn];
		}else
		if (buffer[0]=='G'){
			type[qn]=true;
		}
		qn++;
	}
	sort(ipx,ipx+m);
	m=unique(ipx,ipx+m)-ipx;
	sort(x,x+xn);
	xn=unique(x,x+xn)-x;
	init(1,1,xn);
	memset(last,-1,sizeof(last));
	int pt=1;
	while (1){
		int k=lower_bound(x,x+xn,pt)-x;
		if (k==xn || x[k]!=pt) break;
		++pt;
	}
	for (int t=0;t<qn;t++){
		if (type[t]==false){
			int k=lower_bound(ipx,ipx+m,ip[t])-ipx;
			int p=upper_bound(x,x+xn,track_id[t])-x;
			if (last[k]==-1 || T[t]-last[k]>=600){
				value[p]+=score[t];
				ins(1,1,xn,p);
				last[k]=T[t];
			}
			printf("%d\n",value[p]);
		}else{
			int p=tree[1];
			if (value[p]<0 || (value[p]==0 && pt<x[p-1])){
				printf("%d 0\n",pt++);
				while (1){
					int k=lower_bound(x,x+xn,pt)-x;
					if (k==xn || x[k]!=pt) break;
					++pt;
				}
			}else{
				printf("%d %d\n",x[p-1],value[p]);
				value[p]=-1;
				ins(1,1,xn,p);
			}
		}
	}
	puts("OK");
	return 0;
}
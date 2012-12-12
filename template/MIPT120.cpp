/*
	描述:
		平面插入点,删除点,询问一个矩形内的点数
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define maxn 100010

using namespace std;

struct node{
	int x,y;
	void read(){
		scanf("%d%d",&x,&y);
	}
} q1[maxn],q2[maxn];
int st[maxn],aim[maxn],nxt[maxn],ln;
int type[maxn];
int x[maxn],xn;
int y[maxn],yn;
vector<int> yc[maxn<<2];
vector<int> ta[maxn<<2];
int qn;
int n;
void in_edge(int x,int y){
	aim[ln]=y;
	nxt[ln]=st[x];
	st[x]=ln++;
}
void Build(int p,int tl,int tr){
	if (tl==tr){
		yn=0;
		for (int i=st[tl];i!=-1;i=nxt[i]) y[yn++]=aim[i];
		sort(y,y+yn);
		yn=unique(y,y+yn)-y;
		yc[p].resize(yn);
		for (int i=0;i<yn;i++) yc[p][i]=y[i];
		ta[p].resize(yn+1);
		for (int i=1;i<=yn;i++) ta[p][i]=0;
		return;
	}
	int m=(tl+tr)>>1;
	Build(p<<1,tl,m);
	Build((p<<1)+1,m+1,tr);
	
	int lp=0,rp=0;
	yc[p].clear();
	int v;
	while (lp<yc[p<<1].size() && rp<yc[(p<<1)+1].size()){
		if (yc[p<<1][lp]<yc[(p<<1)+1][rp]) v=yc[p<<1][lp];else v=yc[(p<<1)+1][rp];
		yc[p].push_back(v);
		while (lp<yc[p<<1].size() && yc[p<<1][lp]==v) lp++;
		while (rp<yc[(p<<1)+1].size() && yc[(p<<1)+1][rp]==v) rp++;
	}
	while (lp<yc[p<<1].size()) yc[p].push_back(yc[p<<1][lp++]);
	while (rp<yc[(p<<1)+1].size()) yc[p].push_back(yc[(p<<1)+1][rp++]);
	ta[p].resize(yc[p].size()+1);
	for (int i=0;i<=yc[p].size();i++) ta[p][i]=0;
}
int ask(int d,int p){
	int ret=0;
	for (;p;p-=(p&(p^(p-1)))) ret+=ta[d][p];
	return ret;
}
void ins(int d,int p,int v){
	for (;p<=yc[d].size();p+=(p&(p^(p-1)))) ta[d][p]+=v;
}
int Add(int p,int tl,int tr,int x,int y){
	if (tl==tr){
		int pos=upper_bound(yc[p].begin(),yc[p].end(),y)-yc[p].begin();
		if (ask(p,pos)-ask(p,pos-1)>0) return 0;
		ins(p,pos,1);
		return 1;
	}
	int m=(tl+tr)>>1;
	int flag;
	if (x<=m) flag=Add(p<<1,tl,m,x,y);else flag=Add((p<<1)+1,m+1,tr,x,y);
	if (flag){
		int pos=upper_bound(yc[p].begin(),yc[p].end(),y)-yc[p].begin();
		ins(p,pos,1);
	}
	return flag;
}
int Del(int p,int tl,int tr,int x,int y){
	if (tl==tr){
		int pos=upper_bound(yc[p].begin(),yc[p].end(),y)-yc[p].begin();
		if (pos==0 || yc[p][pos-1]!=y) return 0;
		if (ask(p,pos)-ask(p,pos-1)==0) return 0;
		ins(p,pos,-1);
		return 1;
	}
	int m=(tl+tr)>>1;
	int flag;
	if (x<=m) flag=Del(p<<1,tl,m,x,y);else flag=Del((p<<1)+1,m+1,tr,x,y);
	if (flag){
		int pos=upper_bound(yc[p].begin(),yc[p].end(),y)-yc[p].begin();
		ins(p,pos,-1);
	}
	return flag;
}
int ly,ry;
int Find(int p,int tl,int tr,int l,int r){
	if (l>r || l>tr || r<tl) return 0;
	if (tl==l && tr==r){
		int ret=0;
		int L=lower_bound(yc[p].begin(),yc[p].end(),ly)-yc[p].begin();
		if (L<yc[p].size() && yc[p][L]<ly) ++L;
		int R=lower_bound(yc[p].begin(),yc[p].end(),ry)-yc[p].begin();
		if (R==yc[p].size() || yc[p][R]>ry) --R;
		if (L<=R) ret+=ask(p,R+1)-ask(p,L);
		return ret;
	}
	int m=(tl+tr)>>1;
	if (l<=m){
		if (r>m){
			return Find(p<<1,tl,m,l,m)+Find((p<<1)+1,m+1,tr,m+1,r);
		}else return Find(p<<1,tl,m,l,r);
	}else return Find((p<<1)+1,m+1,tr,l,r);
}
int main(){
	char buffer[100];
	qn=xn=yn=0;
	while (scanf("%s",buffer)!=EOF){
		if (buffer[0]=='A'){
			type[qn]=0;
			q1[qn].read();
			x[xn++]=q1[qn].x;
		}else
		if (buffer[0]=='D'){
			type[qn]=1;
			q1[qn].read();
		}else{
			type[qn]=2;
			q1[qn].read();
			q2[qn].read();
		}
		++qn;
	}
	
	sort(x,x+xn);
	xn=unique(x,x+xn)-x;
	
	if (xn==0){
		for (int i=0;i<qn;i++)
			if (type[i]==1) puts("NOT FOUND");else puts("0");
		return 0;
	}
	
	memset(st,-1,sizeof(st));
	ln=0;
	for (int i=0;i<qn;i++)
		if (type[i]==0){
			q1[i].x=upper_bound(x,x+xn,q1[i].x)-x;
			in_edge(q1[i].x,q1[i].y);
		}
		
	Build(1,1,xn);
	
	for (int t=0;t<qn;t++){
		if (type[t]==0){
			puts(Add(1,1,xn,q1[t].x,q1[t].y) ? "ADDED" : "ALREADY EXISTS");
		}else
		if (type[t]==1){
			int p=upper_bound(x,x+xn,q1[t].x)-x;
			if (p>0 && x[p-1]==q1[t].x){
				puts(Del(1,1,xn,p,q1[t].y) ? "DELETED" : "NOT FOUND");
			}else puts("NOT FOUND");
		}else{
			int l=lower_bound(x,x+xn,q1[t].x)-x;
			if (l<xn && x[l]<q1[t].x) ++l;
			int r=lower_bound(x,x+xn,q2[t].x)-x;
			if (r==xn || x[r]>q2[t].x) --r;
			ly=q1[t].y;
			ry=q2[t].y;
			printf("%d\n",Find(1,1,xn,l+1,r+1));
		}
	}
	return 0;
}
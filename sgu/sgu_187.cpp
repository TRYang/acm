#include <stdio.h>
#include <string.h>
#define maxn 130010
int ch[maxn][2];
int father[maxn];
int flip[maxn];
int sz[maxn],value[maxn];
int root,tn;
int n,m;
void swap(int &x,int &y){
	int tmp;
	tmp=x;x=y;y=tmp;
}
void push_down(int x){
	if (flip[x]>0){
		swap(ch[x][0],ch[x][1]);
		if (ch[x][0]>0) flip[ch[x][0]]^=1;
		if (ch[x][1]>0) flip[ch[x][1]]^=1;
		flip[x]=0;
	}
}
void push_up(int x){
	sz[x]=1;
	if (ch[x][0]>0) sz[x]+=sz[ch[x][0]];
	if (ch[x][1]>0) sz[x]+=sz[ch[x][1]];
}
void NewNode(int x){
	sz[x]=1;
	father[x]=ch[x][0]=ch[x][1]=0;
}
void Rotate(int x,int f){
	int y=father[x];
	push_down(y);
	push_down(x);
	father[x]=father[y];
	if (father[x]>0) ch[father[y]][ch[father[y]][1]==y]=x;
	ch[y][f]=ch[x][!f];
	father[ch[y][f]]=y;
	ch[x][!f]=y;
	father[y]=x;
	push_up(y);
}
void Splay(int x,int goal){
	push_down(x);
	while (father[x]!=goal){
		if (father[father[x]]==goal){
			Rotate(x,ch[father[x]][1]==x);
		}else{
			int y=father[x],z=father[y];
			int f=(ch[z][1]==y);
			if (ch[y][f]==x){
				Rotate(y,f);
				Rotate(x,f);
			}else{
				Rotate(x,!f);
				Rotate(x,f);
			}
		}
	}
	push_up(x);
	if (goal==0) root=x;
}
void MakeTree(int &p,int l,int r){
	if (l>r) return;
	int m=(l+r)>>1;
	tn++;
	NewNode(tn);
	p=tn;
	value[p]=m;
	MakeTree(ch[p][0],l,m-1);
	if (ch[p][0]>0) father[ch[p][0]]=p;
	MakeTree(ch[p][1],m+1,r);
	if (ch[p][1]>0) father[ch[p][1]]=p;
	push_up(p);
}
int find(int rank){
	int p=root;
	//printf("%d\n",rank);
	while (1){
		push_down(p);
		if (sz[ch[p][0]]+1==rank){
			Splay(p,0);
			return p;
		}
		if (rank>sz[ch[p][0]]+1){
			rank-=sz[ch[p][0]]+1;
			p=ch[p][1];
		}else p=ch[p][0];
	}
}
void pr(int x){
	push_down(x);
	if (ch[x][0]>0) pr(ch[x][0]);
	if (value[x]>0 && value[x]<=n) printf("%d ",value[x]);
	if (ch[x][1]>0) pr(ch[x][1]);
}
int main(){
	int i,j,k;
	scanf("%d %d",&n,&m);
	tn=0;
	sz[0]=0;
	MakeTree(root,0,n+1);
	for (;m>0;m--){
		scanf("%d %d",&i,&j);
		i=find(i);
		j=find(j+2);
		Splay(i,j);
		k=ch[i][1];
		flip[k]^=1;
	/*pr(root);
	printf("\n");*/
	}
	//for (i=1;i<=n+2;i++) printf("%d %d %d %d\n",value[i],ch[i][0],ch[i][1],flip[i]);
	pr(root);
	printf("\n");
	return 0;
}

int LinkNum[maxn],Tlink,LinkHead[maxn];	//cut the tree into serveal link
int father[maxn];						//father node of each node
int tot[maxn];							//size of each sub-tree
int level[maxn];						//level of each node

void dfs(int x){
	int maxp=-1;
	tot[x]=1;
	for (int i=st[x];i!=-1;i=nxt[i])
		if (aim[i]!=father[x]){
			int v=aim[i];
			father[v]=x;
			level[v]=level[x]+1;
			dfs(v);
			tot[x]+=tot[v];
			if (maxp==-1 || tot[v]>tot[maxp]) maxp=v;
		}
	if (maxp==-1){		//x is a leaf
		LinkHead[Tlink]=x;
		LinkNum[x]=Tlink++;
		return;
	}
	LinkNum[x]=LinkNum[maxp];
	LinkHead[LinkNum[x]]=x;
}
void Prepare_LCA(int root){		//the root of a tree
	Tlink=0;		//total number of Link
	memset(father,-1,sizeof(father));
	level[root]=0;
	dfs(root);
}
int lca(int x,int y){
	while (LinkNum[x]!=LinkNum[y]){
		if (level[LinkHead[LinkNum[x]]]>=level[LinkHead[LinkNum[y]]])
			x=father[LinkHead[LinkNum[x]]];
		else
			y=father[LinkHead[LinkNum[y]]];
	}
	return level[x]<level[y]?x:y;
}

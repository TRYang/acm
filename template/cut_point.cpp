int Time,low[maxn];
int is_cut[maxn];
void dfs(int fx,int x){
	int mint;
	mint=low[x]=++Time;
	for (int i=st[x];i!=-1;i=link[i])
		if (aim[i]!=fx){
			if (low[aim[i]]==-1){
				dfs(x, aim[i]);
				if (low[aim[i]]<mint) mint=low[aim[i]];
				if (low[aim[i]]>=low[x]) is_cut[x]=1;
			}
			if (low[aim[i]]<mint) mint=low[aim[i]];
		}
	low[x]=mint;
}
void find_cut(int x){
	int i,j,k;
	k=0;
	memset(low,-1,sizeof(low));
	Time=low[x]=1;
	memset(is_cut,0,sizeof(is_cut));
	for (i=st[x];i!=-1;i=link[i])
		if (low[aim[i]]==-1){
			dfs(x,aim[i]);
			k++;
		}
	if (k>1) is_cut[x]=1;
}
int w[maxn][maxn];//边权
int match[maxn];//与y匹配的点
int sx[maxn],sy[maxn];//标记x和y有没遍历到
int lx[maxn],ly[maxn];//x和y的km标号

int dfs(int x){
	sx[x]=1;
	for (int i=0;i<n;i++)
		if (!sy[i] && lx[x]+ly[i]==w[x][i]){
			sy[i]=1;
			if (match[i]==-1 || dfs(match[i])){
				match[i]=x;
				return 1;
			}
		}
	return 0;
}

int KM(int n){
	int i,j,k,d;
	for (i=0;i<n;i++){
		lx[i]=-1000000;
		ly[i]=0;
		for (j=0;j<n;j++)
			if (w[i][j]>lx[i]) lx[i]=w[i][j];
	}
	memset(match,-1,sizeof(match));
	for (i=0;i<n;i++)
		while (1){
			memset(sx,0,sizeof(sx));
			memset(sy,0,sizeof(sy));
			if (dfs(i)) break;
			d=10000000;
			for (j=0;j<n;j++)
				if (sx[j])
					for (k=0;k<n;k++)
						if (!sy[k] && lx[j]+ly[k]-w[j][k]<d) d=lx[j]+ly[k]-w[j][k];
			for (j=0;j<n;j++){
				if (sx[j]) lx[j]-=d;
				if (sy[j]) ly[j]+=d;
			}
		}
	k=0;
	for (i=0;i<n;i++) k+=lx[i]+ly[i];
	return k;
}

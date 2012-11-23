import java.util.*;
import java.math.*;

public class sgu407{
	public static void main(String [] arg){
		Scanner in=new Scanner(System.in);
		int n=in.nextInt(),m=in.nextInt();
		BigInteger [][] f=new BigInteger[2][2];
		f[0][0]=BigInteger.ONE;
		f[0][1]=BigInteger.ZERO;
		int now=0,next=1;
		for (int i=1;i<=m;i++){
			next=(now^1);
			f[next][0]=f[now][1].multiply(BigInteger.valueOf(n));
			f[next][1]=f[now][0].add(f[now][1].multiply(BigInteger.valueOf(2)));
			now=next;
		}
		System.out.println(f[now][0]);
	}
}

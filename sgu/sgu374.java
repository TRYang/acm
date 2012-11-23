import java.util.*;
import java.math.BigInteger; 

public class sgu374{
	public static void main(String [] arg){
		Scanner In=new Scanner(System.in);
		int a=In.nextInt(),b=In.nextInt(),k=In.nextInt();
		BigInteger ans=BigInteger.ZERO;
		BigInteger [][] c=new BigInteger[25][25]; 
		for (int i=1;i<=k;i++){
			c[i][0]=c[i][i]=BigInteger.ONE;
			for (int j=1;j<i;j++) c[i][j]=c[i-1][j-1].add(c[i-1][j]);
		}
		for (int i=0;i<=k;i++){
			BigInteger A=BigInteger.ONE;
			BigInteger B=BigInteger.ONE;
			for (int j=0;j<k-i;j++)
				A=A.multiply(BigInteger.valueOf(a));
			for (int j=0;j<i;j++)
				B=B.multiply(BigInteger.valueOf(b));
			A=A.multiply(B);
			A=A.multiply(c[k][i]);
			ans=ans.add(A);
//			System.out.println(ans);
		}
		System.out.println(ans);
	}
}

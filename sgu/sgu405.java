import java.util.*;
import java.math.*;

public class sgu405{
	public static void main(String [] arg){
		Scanner in=new Scanner(System.in);
		int n=in.nextInt(),m=in.nextInt();
		int [] score=new int[n];
		for (int i=0;i<n;i++) score[i]=0;
		for (int i=0;i<m;i++){
			int x=in.nextInt(),y=in.nextInt();
			for (int j=0;j<n;j++){
				int c=in.nextInt(),d=in.nextInt();
				int det=0;
				if (x>y && c>d) det+=2;
				if (x<y && c<d) det+=2;
				if (x==y && c==d) det+=2;
				if (x-y==c-d) det+=3;
				if (x==c) det+=1;
				if (y==d) det+=1;
				score[j]+=det;
			}
		}
		for (int i=0;i<n;i++) System.out.print(score[i]+" ");
		System.out.println();
	}
}

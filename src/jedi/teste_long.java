/*
 * Compile assim: javac teste_long.java -target 1.2 -source 1.2
 */
public class teste_long{
	public static void main(String args[]){
		long a=1;
		long teste1=1000000,teste2=2000000;
		/*l2d*/
		double b=(double)a;
		/*l2f*/
		float c=(float)a;
		/*l2i*/
		int d=(int)a;
		teste1=teste2/teste1;
		teste1+=teste1;
		teste1*=teste2;
		teste1-=teste2;
		teste1=teste1%teste2;
	}	
}
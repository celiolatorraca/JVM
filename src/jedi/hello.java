/*
 * Compile assim: javac hello.java -target 1.2 -source 1.2
 */
public class hello{
	public static void main(String args[]){
		int d = -1;
		double e = 3.0;
		double f = -5.0;
		long x = -1;
		long y = 1;
		char aux[] = "fdas";
		
		System.out.println("Hello!\n");	
		System.out.println(d);	
		System.out.println(e);
		System.out.println(f);		
		System.out.println(x);
		System.out.println(y);
		System.out.println(x+y);
		System.out.println(x-y);
	}	
}

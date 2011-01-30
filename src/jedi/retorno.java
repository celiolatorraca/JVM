/*
 * Compile assim: javac retorno.java -target 1.2 -source 1.2
 3
 100100000
 14441.9
 14413.08
 
 */
public class retorno{
	static int soma(int a,int b){
		return a+b;
	}
	static float soma(float a,float b){
		return a+b;
	}
	static double soma(double a,double b){
		return a+b;
	}
	static long soma(long a,long b){
		return a+b;
	}
	public static void main(String args[]){
		int inta,intb;
		long longa,longb;
		float floata,floatb;
		double doublea,doubleb;
		
		inta=1;intb=2;
		longa=100000;longb=100000000;
		floata=1000.0f;floatb=13441.90f;
		doublea=1000.0;doubleb=13413.08;
		
		inta=soma(inta,intb);
		System.out.println(inta);
		
		longa=soma(longa,longb);
		System.out.println(longa);
		
		floata=soma(floata,floatb);
		System.out.println(floata);
		
		doublea=soma(doublea,doubleb);
		System.out.println(doublea);
	}
}
/*
 * Compile assim: javac lookupwitch.java -target 1.2 -source 1.2
 */
public class lookupswitch{
	public static int chooseFar(int i) {
		switch (i) {
			case -100:  return -1;
			case 0:  return 0;
			case 100:  return 1;
			default: return 200;
		}
	}
	public lookupswitch(){
		System.out.println("Ops!");
	}
	public static void main(String args[]){
		System.out.println(lookupswitch.chooseFar(-1));
		System.out.println(lookupswitch.chooseFar(-100));
		System.out.println(lookupswitch.chooseFar(0));
		System.out.println(lookupswitch.chooseFar(100));
		System.out.println(lookupswitch.chooseFar(10000));
	}
}

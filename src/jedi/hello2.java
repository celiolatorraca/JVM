public class hello2 extends hello{
	
	static private int a = 2;
	private double b;
	
	public hello2(){
		System.out.println("ops!");
	}
	
	public hello2(int c){
		System.out.println(c);
	}
	
	
	public static void main(String args[]){
		int e[] = new int[5];
		System.out.println(args[0]);
		String teste = new String();
		teste obj = new teste();
		for (int i = 0; i < 10; i++){
			a++;
		}
		(new hello2()).d = 2;
		(new hello2()).b = 3;
		e[0] = 1 + e[0];
	}	
}

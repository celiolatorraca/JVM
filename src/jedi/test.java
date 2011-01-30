public class test{
	private int campo_test;
	public int add(int d, String x[])
	{
		int a,b,c;
		a = 2;
		b = 3;
		c = a + b;
		return c;
	}
	public static void main(String args[]){
		int a,b,c;
		test d = new test();
		c = 2;
		c += d.add(c,args);
	}
}

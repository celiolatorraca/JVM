class interface_test{
	public static void main(String argv[]){
		soma_certo certo = new soma_certo();
		soma_errado errado = new soma_errado();
		Somar ref;
		ref = certo;
		System.out.println(ref.somar(2,2));
		ref = errado;
		System.out.println(ref.somar(2,2));
		System.out.println(Somar.pi);
	}
}

interface Somar{
	public static double pi = 3.1415;
	public int somar(int a, int b);
}

class soma_certo implements Somar{
	public int somar(int a, int b){
		return a+b;
	}
}

class soma_errado implements Somar{
	public int somar(int a, int b){
		return a-b;
	}
}

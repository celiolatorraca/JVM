
public class Operacoes_long {

	public static void main(String[] args) {
		
		long a = 1, b = 2 , c = 3 , d = 4;
		long soma = 0, divisao = 0, multiplicacao = 0;
		long aux = 0;
		
		soma = a + b; // 3
		divisao = d / b; //2 
		multiplicacao = c * d; //12
		
		aux = a;
		
		a = d; //4
		
		d = aux; //1
		
		aux = b;
		
		b = c; //3

		c = aux; //2
		
		soma = a + b; //7
		divisao = (long) d / b; //0
		multiplicacao = c * d; //2
		
		
	}
	
}

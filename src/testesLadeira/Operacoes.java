
public class Operacoes {

	public static void main(String[] args) {
		
		int a = 1, b = 2 , c = 3 , d = 4;
		int soma = 0, divisao = 0, multiplicacao = 0;
		int aux = 0;
		
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
		divisao = (int) d / b; //0
		multiplicacao = c * d; //2
		
		
	}
	
}

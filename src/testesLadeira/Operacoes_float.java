
public class Operacoes_float {

	public static void main(String[] args) {
		
		float a = 1, b = 2 , c = 3 , d = 4;
		float soma = 0, divisao = 0, multiplicacao = 0;
		float aux = 0;
		
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
		divisao = (float) d / b; //0
		multiplicacao = c * d; //2
		
		
	}
	
}

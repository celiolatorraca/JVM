/*
 *	Teste para 'lookupswitch'.
 *	Descricao: Valores de cases nao ordenados, case negativo, cases bem espacados, mais de uma instrucao em alguns cases.
 *	Saida esperada: Valor -701.
 */
 
public class lookupswitch_basic2 {

	public static void main(String[] args) {
		
		int value = -701;
		int a, b, c;
		a = 0;
		b = 0;
		c = 0;
		
		switch(value){
		case 400:
			a = 1;
			System.out.println("Valor 400.");
			break;
		case 20:
			System.out.println("Valor 20.");
			break;
		case 1:
			b = 2;
			c = a + b;
			System.out.println("Valor 1.");
			break;
		case 100:
			a = 3;
			b = 5;
			c = 6;
			System.out.println("Valor 100.");
			break;
		case 12:
			System.out.println("Valor 12.");
			break;
		case -701:
			c = 12;
			b = a + c;
			System.out.println("Valor -701.");
			break;
		default:
			System.out.println("Valor default.");
			break;
		}
	}

}

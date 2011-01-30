/*
 *	Teste para 'tableswitch'.
 *	Descricao: Valores de cases nao ordenados, case negativo, case 12 e 6 nao existentes, mais de uma instrucao em alguns cases.
 *	Saida esperada: Valor 14.
 */
 
public class switch_basic3 {

	public static void main(String[] args) {
		
		int valor = 14;
		int a,b,c;
		a = 0;
		b = 0;
		c = 0;
		
		switch(valor){
		case 1:
			b = 34;
			c = 33;
			System.out.println("Valor 1.");
			break;
		case 4:
			System.out.println("Valor 4.");
			break;
		case 3:
			System.out.println("Valor 3.");
			break;
		case 5:
			System.out.println("Valor 5.");
			break;
		case 2:
			System.out.println("Valor 2.");
			break;
		case 8:
			System.out.println("Valor 8.");
			break;
		case 9:
			System.out.println("Valor 9.");
			break;
		case 10:
			System.out.println("Valor 10.");
			break;
		case 7:
			System.out.println("Valor 7.");
			break;
		case -2:
			a = -3;
			b = 5;
			c = a + b;
			System.out.println("Valor 11.");
			break;
		case 11:
			a = 3;
			System.out.println("Valor 11.");
			break;
		case 13:
			System.out.println("Valor 13.");
			break;
		case 14:
			System.out.println("Valor 14.");
			break;
		case 15:
			System.out.println("Valor 15.");
			break;
		case 16:
			a = 5;
			b = 10;
			c = 12;
			c = c + a + b;
			System.out.println("Valor 16.");
			break;
		default:
			System.out.println("Valor default.");
			break;
		}
		
	}

}

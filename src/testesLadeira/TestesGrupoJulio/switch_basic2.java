/*
 *	Teste para 'tableswitch'.
 *	Descricao: Valores de cases nao ordenados, case negativo, case 12 nao existente.
 *	Saida esperada: Valor default.
 */
 
public class switch_basic2 {

	public static void main(String[] args) {
		
		int valor = 12;
		
		switch(valor){
		case 1:
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
		case 6:
			System.out.println("Valor 6.");
			break;
		case 10:
			System.out.println("Valor 10.");
			break;
		case 7:
			System.out.println("Valor 7.");
			break;
		case -2:
			System.out.println("Valor 7.");
			break;
		case 11:
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
			System.out.println("Valor 16.");
			break;
		default:
			System.out.println("Valor default.");
			break;
		}
	}

}

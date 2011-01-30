/*
 *	Teste para 'tableswitch'.
 *	Descricao: Valores de cases nao ordenados, case negativo.
 *	Saida esperada: Valor -4
 */

public class switch_basic1 {
	
	public static void main(String[] args) {
		
		int valor = -4;
		
		switch(valor){
		case -1:
			System.out.println("Valor -1.");
			break;
		case 0:
			System.out.println("Valor 0.");
			break;
		case 1:
			System.out.println("Valor 1.");
			break;
		case 4:
			System.out.println("Valor 4.");
			break;
		case -2:
			System.out.println("Valor -2.");
			break;
		case 3:
			System.out.println("Valor 3.");
			break;
		case -3:
			System.out.println("Valor -3.");
			break;
		case 2:
			System.out.println("Valor 2.");
			break;
		case -4:
			System.out.println("Valor -4.");
			break;
		case -5:
			System.out.println("Valor -5.");
			break;
		default:
			System.out.println("Valor default.");
			break;
		}
		
	}

}

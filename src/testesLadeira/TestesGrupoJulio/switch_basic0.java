/*
 *	Teste para 'tableswitch'.
 *	Descricao: Valores de cases ordenados.
 *	Saida esperada: Valor 3.
 */

public class switch_basic0 {

	public static void main(String[] args) {

		int valor = 3;
		
		switch(valor){
		case 0:
			System.out.println("Valor 0.");
			break;
		case 1:
			System.out.println("Valor 1.");
			break;
		case 2:
			System.out.println("Valor 2.");
			break;
		case 3:
			System.out.println("Valor 3.");
			break;
		case 4:
			System.out.println("Valor 4.");
			break;
		default:
			System.out.println("Valor default.");
			break;
		}
		
	}

}

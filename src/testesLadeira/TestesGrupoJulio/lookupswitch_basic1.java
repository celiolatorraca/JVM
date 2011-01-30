/*
 *	Teste para 'lookupswitch'.
 *	Descricao: Valores de cases ordenados, case negativo, cases bem espacados.
 *	Saida esperada: Valor default.
 */
 
public class lookupswitch_basic1 {

	public static void main(String[] args) {
		
		int value = 4;
		
		switch(value){
		case 1:
			System.out.println("Valor 1.");
			break;
		case 20:
			System.out.println("Valor 20.");
			break;
		case 100:
			System.out.println("Valor 100.");
			break;
		case -900:
			System.out.println("Valor -900.");
			break;
		default:
			System.out.println("Valor default.");
			break;
		}
		
	}

}

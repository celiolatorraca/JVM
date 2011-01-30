/*
 *	Teste para 'tableswitch'.
 *	Descricao: Valores de cases nao ordenados, case negativo, case -7 e 0 nao existente.
 *	Saida esperada: Case default.
 *					Case -3.
 *					Case 1.
 *					Case default.
 */
 
public class switch_basic4 {

	public static void main(String[] args) {
		
		int i;
		
		for( i=-7 ; i<7 ; i++, i++, i++, i++ ){
		
			switch(i){
			case -8:
				System.out.println("Case -8.");
				break;
			case -2:
				System.out.println("Case -2.");
				break;
			case -9:
				System.out.println("Case -9.");
				break;
			case -6:
				System.out.println("Case -6.");
				break;
			case -4:
				System.out.println("Case -4.");
				break;
			case -5:
				System.out.println("Case -5.");
				break;
			case -3:
				System.out.println("Case -3.");
				break;
			case 1:
				System.out.println("Case 1.");
				break;
			case 2:
				System.out.println("Case 2.");
				break;
			default:
				System.out.println("Case default.");
				break;
			}
			
		}
		
	}

}

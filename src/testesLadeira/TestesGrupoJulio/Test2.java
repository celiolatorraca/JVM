/*
RESPOSTA ESPERADA:

Case -2.
-222

Case 1.
1234567890longA
1987654320
10356306186048299

Valor 0.
0lala
1

Case Default.
doubleA: 1987654328.000000

Case 2.
Class instanciada!
890765.000000
float = 6780.000000
i = 4
soma 6784.000000

Case Default.
doubleA: 3975308648.000000

Case 3.
1234567890

Fim! =)
*/


public class Test2 {
	
	public static void main(String[] args) {
		
		int i;
		int[] arr= { -2, 1, 0, 4, 2, 7, 3};
		long longA, longB, longC;
		double doubleA;
		float floatA = 890765;
		boolean validade;
		longA = 1;
		longB = 1234;
		doubleA = 8;
		
		validade = false;
		
		for( i=0 ; i<arr.length ; i++ ){
		
			switch(arr[i]){
			case 0:
				System.out.println("Valor 0. ");
				System.out.print(validade + "lala\n");
				validade = true;
				System.out.println(validade);
				System.out.println();
				break;
			case 1:
				System.out.println("Case 1.");
				longA = 1234567890;
				longB = 1987654320;
				System.out.println(longA + "longA");
				System.out.println(longB);
				longC = (longA << 23) | (longB >> 4);
				System.out.println(longC);
				System.out.println();
				break;
			case 2:
				System.out.println("Case 2.");
				/*instancia classe e chama metodo do objeto*/
				Test2_a inst = new Test2_a(floatA);
				System.out.println("Class instanciada!");
				System.out.println(floatA);
				floatA = 6780;
				System.out.println("float = " + floatA);
				System.out.println("i = " + i);
				floatA = inst.metodo(i, floatA);
				System.out.println("soma " + floatA);
				System.out.println();
				break;
			case -2:
				System.out.println("Case -2.");
				longB = -222;
				System.out.println(longB);
				System.out.println();
				break;
			case 3:
				System.out.println("Case 3.");
				if( longA<10 ){
					System.out.println("longA < 10");
				} else {
					while( longA<=10 )
						longA++;
					System.out.println(longA);
				}
				System.out.println();
				break;
			default:
				System.out.println("Case Default.");
				doubleA += (double)longB;
				System.out.println("doubleA: " + doubleA);
				System.out.println();
				break;
			}
			
			
		}
		
		System.out.println("Fim! =)");
		
	}

}

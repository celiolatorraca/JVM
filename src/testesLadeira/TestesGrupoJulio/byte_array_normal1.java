/*
 *	Teste para 'baload', 'bastore', 'i2b'.
 *	Descricao: Testa conversão de bytes (um estoura o valor de byte), arrays uni e multidimensionais.
 *	Saida esperada: 90
 *					-46
 *					unidimensional array
 *					-12
 *					34
 *					0
 *					-56
 *					78
 *					multidimensional array
 *					1 2 
 *					-63 0 
 *					5 3 
 *					-45 2
 */

public class byte_array_normal1 {

	public static void main(String[] args) {

		int intA, intB, i, j, k;
		byte byteA, byteB;
		byte[] arr1_b1 = {-12 , 34, 0, -56, 78};
		byte[][][] arr3_b1 = { { { 1 , 2 } , { -63 , 0 } } , { { 5 , 3 } , { -45 , 2 } } };
		
		intA = 90;
		intB = 1234;			/*valor estoura para byte*/
		
		byteA = (byte)intA;
		byteB = (byte)intB;
		
		System.out.println(byteA);
		System.out.println(byteB);

		System.out.println("unidimensional array");
		for( i=0 ; i<5 ; i++){
			System.out.println(arr1_b1[i]);
		}
		
		System.out.println("multidimensional array");
		for( i=0 ; i<2 ; i++){
			for( j=0 ; j<2 ; j++){
				for( k=0 ; k<2 ; k++){
					System.out.print(arr3_b1[i][j][k]);
					System.out.print(" ");
				}
				System.out.println();
			}
		}
		
	}

}

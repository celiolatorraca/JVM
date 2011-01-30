/*
 *	Teste para 'iadd', 'isub', 'imul', 'idiv', 'irem', 'ishl', 'ishr', 'ior', 'iand'.
 *	Descricao: Teste para todas operacoes com int.
 *	Saida esperada: Soma
 *					257
 *					Subtracao
 *					276
 *					Mul
 *					470
 *					Div
 *					-1
 *					mod
 *					-39
 *					Shift left e right
 *					120
 */

public class int_basic1 {

	public static void main(String[] args) {
		
		int intA, intB, intC, intD;
		int res;
		
		intA = 2;
		intB = 235;
		intC = -274;
		intD = 22;

		System.out.println("Soma");
		res = intD + intB;
		System.out.println(res);

		System.out.println("Subtracao");
		res = intA - intC;
		System.out.println(res);

		System.out.println("Mul");
		res = intA * intB;
		System.out.println(res);

		System.out.println("Div");
		res = intC/intB;
		System.out.println(res);

		System.out.println("mod");
		res = intC%intB;
		System.out.println(res);

		System.out.println("Shift left e right");
		res = ( (intA << 4 | 9 >> intB) | (6 >> intC | intD << 2) );
		System.out.println(res);
		
	}

}

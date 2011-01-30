/*
 * Compile assim: javac aconst_null.java -target 1.2 -source 1.2
 */
public class aconst_null{
	public static void main(String args[]){
		Object i=null;
		if(i==null){
			System.out.println("Objeto Nulo");
		}else{
			if(i!=null){
				System.out.println("Obejto nao nulo");	
			}
			
		}
	}	
}
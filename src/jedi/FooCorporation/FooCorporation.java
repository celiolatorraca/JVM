
public class FooCorporation {
	private float salarioTotal = 0.0f;
	private Empregado empregados[] = new Empregado[6];
	public FooCorporation(){
			Gerente joao = new Gerente("Joao","Silva",120.0f,45,1);
			Gerente melissa = new Gerente("Melissa","Oliveira",255.5f,55,2);
			Engenheiro edson = new Engenheiro("Edson","Pereira",220.0f,70,3);
			Engenheiro felipe = new Engenheiro("Felipe","Brito",124.5f,42,4);
			Engenheiro adam = new Engenheiro("Adam","Silva",248.0f,38,5);
			Engenheiro sofia = new Engenheiro("Sofia","Albuquerque",320.0f,44,6);
			
			System.out.println(sofia.baseSalarial);
			System.out.println(adam.baseSalarial);
			System.out.println(sofia.nome);
			System.out.println(adam.nome);
			joao.addHorasGolfe(10);
			melissa.addHorasGolfe(5);
			
			edson.horasTrafegadas(8);
			felipe.horasTrafegadas(12);
			adam.horasTrafegadas(5);
			sofia.horasTrafegadas(7);
			
			empregados[0] = joao;
			empregados[1] = melissa;
			empregados[2] = edson;
			empregados[3] = felipe;
			empregados[4] = adam;
			empregados[5] = sofia;
			for(int i=0;i<6;i++){
				salarioTotal+= empregados[i].pagamentoSemanal();
			}
	}
	
	public float getSalario(){
		return(salarioTotal);
	}
	
	public static void main(String[] args){
		FooCorporation empresa = new FooCorporation();
		System.out.println("O salario calculado foi de:");
		System.out.println(empresa.getSalario());
	}
}

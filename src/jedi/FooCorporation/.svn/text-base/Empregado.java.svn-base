
public class Empregado {
	String nome = "";
	String sobrenome = "";
	int id = 0;
	float baseSalarial = 0.0f;
	int nroHoras;
	float salario;
	
	public Empregado(String name,String lastName,float baseSalary,
			int numberOfHours,int identification){
		id = identification;
		nome = name;
		sobrenome = lastName;
		baseSalarial = baseSalary;
		nroHoras = numberOfHours;
	}
	public float pagamentoSemanal(){
		salario = 0.0f;
		float temp=0.0f;
		if(baseSalarial<8.0){
			System.out.println("Base salarial menor que 8, o salário" +
					"não foi computado.");
			salario = 0.0f;
		}
		else if(nroHoras>60 || nroHoras<0){
			System.out.println("Erro: o empregado: "+nome+" trabalhou" +
					" mais de 60 horas (ou menos que 0), seu salario nao foi computado");
			salario = 0.0f;
		}
		else if(nroHoras>44){
			temp = nroHoras-44;
			temp *= baseSalarial*1.5;
			temp+= 44*baseSalarial;
			salario = temp;
		}
		else{
			salario = nroHoras*baseSalarial;
		}
	return(salario);
	}
}

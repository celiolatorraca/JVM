/* Universidade de Brasilia - UnB
 * Instituto de Ciencias Exatas - IE
 * Departamento de Ciencia da Computacao
 * Linguagens de Programacao - 2/2008
 * Trabalho 1 - Conceitos de OO
 *
 * Autor: George Bezerra Silva
 * Matricula: 06/85054
 */

/*
 * Classe com a funcao main() para realizar os testes
 * com as outras classes.
 */ 
public class Dogs {
  public static void main(String[] args) {
    System.out.println("Criando um cachorro vira-lata!\n");

    Cachorro viralata = new Cachorro();

    viralata.locomover(); //Metodo sobrescrito
    viralata.comer(); //Metodo sobrescrito
    viralata.latir(); //Metodo da classe Cachorro

    System.out.println("\nOk, criando um cachorro de estimacao!\n");

    CaoDomestico rex = new CaoDomestico("Rex");

    rex.locomover(); //Metodo herdado e nao modificado
    rex.comer(); //Metodo sobrescrito
    rex.latir(); //Metodo herdado e nao modificado
    rex.brincar(); //Implementacao normal do metodo
    rex.brincar("frisbee"); //Testes com a versao polimorfica do metodo
    rex.brincar("bola");
    rex.brincar("boneco");

    //Recebendo o valor do atributo nome via metodo
    System.out.println(rex.getNome());
    System.out.println(", pode voltar pra sua casinha!");
  }
}

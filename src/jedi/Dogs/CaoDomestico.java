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
 * Esta classe representa um cao domestico, que eh tanto um cachorro
 * quanto um animal de estimacao. Por isso herda da classe Cachorro
 * e implementa a classe Pet.
 */ 
public class CaoDomestico extends Cachorro implements Pet {
  //Atributo exclusivo do cao domestico, definido como private
  //para respeitar o encapsulamento
  private String nome;

  //Construtor padrao de CaoDomestico apenas chama o construtor
  //da classe pai, ou seja, da classe Cachorro
  public CaoDomestico() {
    super();
  }

  //Polimorfismo do construtor, podendo definir o nome do CaoDomestico
  //na sua construcao
  public CaoDomestico(String nome) {
    this.setNome(nome);
  }

  //Metodo para definir o nome, respeitando o encapsulamento
  public void setNome(String nome) {
    this.nome = nome;
  }

  //Metodo para descobrir o nome, respeitando o encapsulamento
  public String getNome() {
    return this.nome;
  }

  //Implemetando o metodo definido em Pet
  public void brincar() {
    System.out.println("O cachorro esta brincando com o dono.");
  }

  //Polimorfismo do metodo brincar, pois nao necessariamente
  //precisamos de um brinquedo para brincar com o cachorro.
  //Caso tenhamos um brinquedo, chamamos essa funcao passando
  //o brinquedo como parametro.
  public void brincar(String brinquedo) {
    if(brinquedo.equals("frisbee")) {
      System.out.println("O cachorro pegou o frisbee no ar!");
    }

    else if(brinquedo.equals("bola")) {
      System.out.println("O cachorro correu atras da bola.");
    }

    else {
      System.out.println("O cachorro mordeu o(a) ");
      System.out.println(brinquedo);
    }
  }

  //Reescrita do metodo comer() da classe Cachorro, pois caes
  //domesticos nao saem pra cacar
  public void comer() {
    System.out.println("O cachorro esta comendo a racao.");
  }

  //Note que os metodos latir() e locomover() foram herdados de Cachorro
  //sem serem modificados
}

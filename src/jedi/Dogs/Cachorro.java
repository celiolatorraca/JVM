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
 * Esta classe define um cachorro, que por ser um animal herda da
 * classe Animal.
 * Cachorros podem ser instanciados pelo programa.
 */ 
public class Cachorro extends Animal {
  //Note que houve heranca do atributo "patas" da classe Animal.
  public Cachorro() {
    this.setPatas(4);
  }

  //Sobrescrita de metodo da classe Animal
  public void locomover() {
    System.out.println("O cachorro esta andando.");
  }

  //Sobrescrita de metodo da classe Animal
  public void comer() {
    System.out.println("O cachorro esta cacando sua comida.");
    System.out.println("A presa foi pega pelo cachorro!");
    System.out.println("O cachorro comeu sua presa.");
  }

  public void latir() {
    System.out.println("AU AU!");
  }
}

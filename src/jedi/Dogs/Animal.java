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
 * Esta classe representa um animal generico. Como nao existe um animal
 * generico que nao seja de especie alguma, esta classe eh abstrata.
 */ 
public abstract class Animal {
  //Atributo da classe definido como private para manter encapsulamento
  private int patas;

  //Nao existe uma forma padrao de se locomover entre os animais
  public void locomover() {
  }

  //Nao existe uma forma padrao de comer, entre os animais
  public void comer() {
  }

  //Segundo o encapsulamento, somente metodos definidos podem acessar
  //atributos.
  public void setPatas(int patas) {
    this.patas = patas;
  }
}

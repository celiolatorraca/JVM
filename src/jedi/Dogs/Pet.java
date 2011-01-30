/* Universidade de Brasilia - UnB
 * Instituto de Ciencias Exatas - IE
 * Departamento de Ciencia da Computacao
 * Linguagens de Programacao - 2/2008
 * Trabalho 1 - Conceitos de OO
 *
 * Autor: George Bezerra Silva
 * Matricula: 06/85054
 */

/* Esta interface define um animal de estimacao.
 * Todo animal de estimacao deve saber brincar de alguma forma (neste
 * exemplo), e deve haver uma forma de botar um nome nele e de saber
 * seu nome.
 */
interface Pet {
  public void brincar();
  public void setNome(String nome);
  public String getNome();
}

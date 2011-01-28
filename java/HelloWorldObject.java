/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package teste;

/**
 *
 * @author Yuri Maia
 */

public class HelloWorldObject implements HelloWorldInterface {

  static int field = 10;
  float field2 = 1.0f;
  double field3 = -666.999111333;
  long field4 = 5000000000000111l;
  boolean field5 = true;
  char field6 = 'a';
  byte field7 = 1;
  char field8 = 'A';
	
  String field11 = new String();

  private long field9;
  protected byte[] field10;

  HelloWorldObject(){
  }
  HelloWorldObject(int field) {
    this.field = field;
  }
  public void executeMethod() {
    System.out.println("HelloWorld\n");
  }
  private int privateMethod(){
	int methodField = 11;
    this.field = 10;
	executeMethod();
    return this.field;
  }

}

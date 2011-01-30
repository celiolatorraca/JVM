/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package javaTeste;

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
  public void executeMethod(int a, float b, long c) {
    a += a;
    b *= b;
    c /= c;
  }
  private int privateMethod(){
	int methodField = 11;
    this.field = 10;
    return this.field;
  }

}

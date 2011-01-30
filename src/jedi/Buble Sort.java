class BubbleSort {

  public static void main(String args[]) {
  
   int[] n;
   n = new int[10];
   Random myRand = new Random();
   
   // initialize the array
   for (int i = 0; i < 10; i++) {
     n[i] = myRand.nextInt();
   }
   
   // print the array's initial order
   System.out.println("Before sorting:"); 
   for (int i = 0; i < 10; i++) {
	   
	   System.out.println("n[");
	   System.out.println(i);
	   System.out.println("] = ");
	   System.out.println(n[i]);
   }
   
   boolean sorted = false;
   // sort the array
   while (!sorted) {
     sorted = true;
     for (int i=0; i < 9; i++) {
       if (n[i] > n[i+1]) {
         int temp = n[i];
         n[i] = n[i+1];
         n[i+1] = temp;
         sorted = false;
       }   
     }
   }

  // print the sorted array
  System.out.println();
  System.out.println("After sorting:");  
	  for (int i = 0; i < 10; i++) {
		  System.out.println("n[");
		  System.out.println(i);
		  System.out.println("] = ");
		  System.out.println(n[i]); 
	  }
  
  }

}
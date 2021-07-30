/* Do Comments Work? */
/*

+++ +++
[>++++ ++++<-]
>+.[-]<[-]

*/
// +#[-] 
/* If comments do not work, will print out a '1' or an '11' */

/* Does scratch memory work? */
+++ +++ >
+++ +++ 
{
  ++ > +<	
}
>>[-]<<<
[>>>+<<<-]
>>>[
  <<[<+>>+<-]
  >[<+>-]
  >-]
<[-]<[-]<.[-]

/* expected output:
	0
   expected output if scratch memory does not work:
   	5
*/


/*
/* Does return-to-0 operator work? */
/* Expected output:
	0
   Expected output if operator does not work:
   	1
*/

++++++[>++++++++<-]>[<+>>+<-]>[<+>-]<+^.
[-]>[-]<

/* Call Breakpoints-Extended.include.b */
/* First we check if the include grabs the right values from the calling file */
[-]+>++++++++++++++++++++++++++++++++++++++++++++++++<
@Breakpoints-Extended.include.b@
/* Check that the correct values were returned */

#[-]>#[-] /* Should print out a one then a two. */

/* Raises Cell 1 to the power of Cell 2 */
>> // temp0
[-] 
<< // Cell 1 (x)
[>>+<<-]
+
> // Cell 2 (y)
[
	>>[-] // temp1
	>[-] // temp2
	^[~+^-] // x[temp2+x-]
	~[
		<<[<<+>>>+<-]
		>[<+>-]
		>-
	]
^>-
]
^[>+<-]+!

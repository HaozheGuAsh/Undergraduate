.data

num1:
	.space 4
	.space 4

num2:
	.space 4
	.space 4


.text

.globl _start

_start :
	movl $num1,%ecx
	movl $num2,%edx
	addl $4,%ecx		#lower num1 ptr
	addl $4,%edx		#lower num2 ptr

	movl (%ecx),%eax	#eax=lower num1 val
	movl (%edx),%ebx	#ebx=lower num2 val

	subl $4,%ecx		#upper num1 ptr
	subl $4,%edx		#upper num2 ptr
	
	movl (%ecx),%ecx	
	movl (%edx),%edx
	addl %ecx, %edx    
	addl %ebx,%eax
	jc carry

done:
	movl %eax,%eax
	movl %edx,%edx

	
carry:

	inc %edx
	jmp done
	



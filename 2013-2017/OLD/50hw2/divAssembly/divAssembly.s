.data


dividend:
	.space 4

divisor:
	.space 4

.text

.globl _start

_start :
	movl $0,%eax			# quotient  = 0   eax
	movl $0,%edx			# remainder = 0	  edx	
	movl $dividend,%ebx	
	movl (%ebx),%ebx		# ebx = dividend
	movl $divisor,%esi		
	movl (%esi),%esi		# esi = divisor
	mov $31,%cl			# cl = counter of bit
	jmp shift

done: 
	movl %eax,%eax
	movl %edx,%edx
	
shift:
	movl $dividend,%ebx	
	movl (%ebx),%ebx		# ebx = dividend

	shll $1,%edx			# remainder= remainder <<1
	
	shrl %cl,%ebx			# devidend >> cl(bit)
	andl $1,%ebx			# devidend &1
	cmpl $0,%ebx  			# bit of devidend compare with 0
	jz bitzero				# if equal 0 thus bit is 0
	jmp bitone				# otherwise bit is 1

bitzero:
	movl $1,%edi
	notl %edi				# edi = 11111111...0
	andl %edi,%edx			# edx = remainder &= ~1  set LSB=0
	jmp calc				# go to calc				

bitone:
	orl $1,%edx			# edx = remainder |=1  set LSB=1
	jmp calc				# go to calc

calc:
	cmpl %esi,%edx			# if remainder >= divisor
	jb final				# jump to final if remainder < divisor
	subl %esi,%edx			# remainder -= divisor
	movl $1,%edi			
	shll %cl,%edi			# edi have 1 in current bit position
	orl %edi,%eax			# quotient |= (1 << bit) <- did above
	jmp final				# after calc  go to final

final:
	dec %cl				# decrease bit counter
	jge shift				# do for loop if counter >=0
	jmp	done				# finish


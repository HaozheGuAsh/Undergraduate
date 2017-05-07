.data

string1:
	.space 100

string2:
	.space 100

oldary:
	.space 1000

curary:
	.space 1000

strlen1:
	.space 4

strlen2:
	.space 4

min:
	.space 4

cur1:
	.space 4
cur2:
	.space 4

.text

.globl _start

_start :
	movl $string1,%edi      # edi is the adress of string1
	xorb %al, %al			# process
	movl $-1, %ecx			# to find 
	repne scasb				# strlen of 
	subl $string1, %edi		# string1 
	decl %edi				# and stored in dl
	movl %edi,%edx			# dl equal the length of string1
	movl %edx,strlen1

	movl $string2,%edi		# edi is the adress of string2
	xorb %al, %al			# process
	movl $-1, %ecx			# to find 
	repne scasb				# strlen of 
	subl $string2, %edi		# string1 
	decl %edi				# and stored in dh
	movl %edi,%eax
	movl %eax,strlen2
	movb %al,%dh			# dh equal the length of string1

	movl $oldary,%eax		# eax have the adress of old ary
	movl $curary,%ebx		# ebx have the adress of cur ary

	movl $0,%ecx			# set ecx=0 is cur pos
	#movb %dl,%cl			# cl=dl=length of string1
	call setoldarray

	movl $0,%ecx			# set ecx=0 is cur pos
	#movb %dl,%cl			# cl=dh=length of string2
	call setcurarray

	movl $1,%ecx			# ecx is the counter of i = 1
	
							# eax is adress of oldarray ebx is the adress of curarray
fori:
	cmpl strlen1,%ecx
	jg endfori				# go to endfori if i>strlen1
	movl %ecx,(%ebx)		# curDist[0] = i
	movl $1,%edx			# edx is the counter of j = 1

forj:
	cmpl strlen2,%edx
	jg	endforj				# go to endforj if j>strlen2

	movl %eax,cur1
	movl %ebx,cur2

	movl %ecx,%esi
	decl %esi				# esi = i-1
	addl $string1,%esi		# access string1[i-1]
	movl %esi,%eax
	movb (%eax),%al			# char1 = value of string1[i-1]


	movl %edx,%edi
	decl %edi				# edi = j-1
	addl $string2,%edi		# access string2[j-1]
	movl %edi,%ebx
	movb (%ebx),%bl		# char2 = value of string2[j-1]

	cmpb %bl,%al			# if word1[i-1] == word2[j-1]
	jz equalword			# if 
	jmp notequalword		# else

afterif:
	incl %edx				# j++
	jmp forj				# next j iteration

endforj:
	movl %eax,%esi			# esi = oldary
	movl %ebx,%eax			# oldary = curary
	movl %esi,%ebx			# curary = oldary

	incl %ecx				# i++ at end of forj
	jmp fori				# go to next fori

endfori:
	# after fori we now compute distance
	
	movl strlen2,%edi		# edi = word2len
	movl (%eax,%edi,4),%esi	#esi = oldary[word2len]
	movl %esi,%eax			# eax contain distance

done:
	movl %eax,%eax


findmin:
	cmpl min,%esi			# compare current min with new value
	jl	resetmin			# reset min if new value -min <0
	ret						# return to notequalword

resetmin:
	movl %esi,min			# set min = new value
	jmp findmin				# though do findmin again but cmpl give 0 so will ret 

notequalword:
	movl cur1,%eax
	movl cur2,%ebx

	movl (%eax,%edx,4),%esi # esi = oldDist[j]
	movl %esi,min			# min = oldDist[j]

	movl %edx,%edi
	decl %edi				# edi = j-1
	movl (%ebx,%edi,4),%esi # esi = curDist[j-1]
	call findmin			# min(oldDist[j],curDist[j-1])

	movl %edx,%edi
	decl %edi				# edi = j-1
	movl (%eax,%edi,4),%esi # esi = oldDist[j-1]
	call findmin			# min(cur min,oldDist[j-1])

	movl %edx,%edi			# edi = j
	incl min				# min++
	movl min,%esi			# esi = final min
	movl %esi,(%ebx,%edi,4)	# curDist[j] = final min

	jmp afterif

equalword:
	movl cur1,%eax
	movl cur2,%ebx

	movl %edx,%edi
	decl %edi				# edi = j-1
	# curDist[j] = oldDist[j - 1];

	movl (%eax,%edi,4),%esi # %esi = oldary[j-1]

	movl %edx,%edi
	# edi = j
	movl %esi,(%ebx,%edi,4) # curary[j] = %esi
	jmp afterif

setoldarray:
	movl %ecx,(%eax,%ecx,4) # setting old ary
	incl %ecx				# i++
	cmpb %cl,%dh			# compare curpos with length
	jge setoldarray			# continue if curpos >= length
	ret

setcurarray:
	movl %ecx,(%ebx,%ecx,4) # setting cur ary
	incl %ecx				# i++
	cmpb %cl,%dh			# compare curpos with length
	jge setcurarray			# continue if curpos >= length
	ret


	
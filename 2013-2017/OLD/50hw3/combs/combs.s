.global get_combs
.equ wordsize, 4

.text

get_combs:

	#int** get_combs(int* items, int k, int len)

	#syntax
	# call num_combs to get number  
	#initialize 2d array [total][k] holding combs
	#recursive call setcomb

	movl wordsize(%esp),%esi				# esi is the item array
	movl 2*wordsize(%esp),%edx				# edx is the k
	movl 3*wordsize(%esp),%ecx				# ecx is the len of item array

	#call num_combs
	# num_item, k
	push %edx								# push k
	push %ecx								# push num_item
	call num_combs							# get total in eax
	addl $(2*wordsize),%esp					# clear stack
	jmp initialize

	initialize:
	# malloc  
	push %eax								# eax is total    

	movl $wordsize,%ebx						# size of int
	mull %ebx								# eax = 4* total
	push %eax								# argument for malloc
	call malloc								# eax has address int** ary
	addl $wordsize,%esp						# clean up argument next item is total

	pop  %ecx								# ecx = total
	movl %eax,%edi							# edi = ary[0][0]
	movl 2*wordsize(%esp),%edx				# edx is the k
	movl %edx,%eax							# eax = k
	mull %ebx								# eax = 4 *k
	movl %eax,%ebx							# ebx has 4*k
	movl $0,%edx							# edx=i=0
	movl %edi,%esi							# esi = ary[0][0]
	call for_in_initi
	movl %ecx,%ebx								# ebx = total
	
	#create row array
	movl $wordsize,%ebx						# size of int
	movl %ebx,%eax
	movl 2*wordsize(%esp),%edx				# edx is the k 
	mull %edx								# eax = 4 * k
	push %eax								# push 4*k
	call malloc
	addl $wordsize,%esp

											# eax is row array
											# ebx = total
											# edi = ary[0][0] 
	movl 1*wordsize(%esp),%esi				# esi is the item array
	movl 2*wordsize(%esp),%edx				# edx is the k
	movl 3*wordsize(%esp),%ecx				# ecx is the len of item array
	
	#int comb(int* items, int** ass, int* row, int start, int n, int k, int maxk, int count)
	push %edi
	movl $0,%ebx
	push %ebx								# count
	push %edx								# maxk
	push %ebx								# curk
	push %ecx								# n
	push %ebx								# start
	push %eax								# row ary
	push %edi								# ary
	push %esi								# item ary
	call combination
	addl $(8*wordsize),%esp					# clear stack
	pop %edi
	movl %edi,%eax							# return ary
	ret

	for_in_initi:
		push %ecx
		push %edx
		push %ebx								# push argument 4*k
		call malloc
		addl $wordsize,%esp						#clean up argument
		pop %edx
		pop %ecx
		movl %eax,(%esi)						# ary[i] = malloc(4*k)
		addl $4,%esi							# move to ary[i+1]
		incl %edx								# i++

		cmpl %edx,%ecx							# total - i
		jg for_in_initi							# for loop total -i >0       equal i<total
		ret

	combination:
		#int* items  2, int** ass 3 , int* row  4, int start  5, int n  6, int k  7, int maxk  8, int count 9  care to add wordsize for the ret address
		#prologue
			push %ebp
			movl %esp, %ebp 

		movl 7*wordsize(%ebp),%eax				# eax = curk
		incl %eax								# eax ++
		movl 8*wordsize(%ebp),%ebx				# k
		movl $0,%ecx							# ecx is counter for fitst if
		cmpl %ebx,%eax							# curk+1 - k
		jg first_if
		movl 5*wordsize(%ebp),%ecx				# ecx is counter for main for    i=start
		movl 9*wordsize(%ebp),%eax				# count
		jmp main_for

	main_for:
		movl 6*wordsize(%ebp),%ebx				# ebx is n
		cmpl %ecx,%ebx							# n-i
		jle end_recur

		push %ecx

		movl 4*wordsize(%ebp),%esi				# esi is row ary
		movl 7*wordsize(%ebp),%eax				# eax is curk
		leal (%esi,%eax,4),%edi					# edi is ptr to row[k]
		movl 2*wordsize(%ebp),%ebx				# ebx is item ary
		leal (%ebx,%ecx,4),%ebx					# ebx is ptr to item[i]
		movl (%ebx),%ebx						# ebx is value of item[i]
		movl %ebx,(%edi)						# value of row[k]= item[i]

		#prepare recursive call
		movl 9*wordsize(%ebp),%eax				# count
		push %eax	
		movl 8*wordsize(%ebp),%eax				# eax is k
		push %eax								# maxk
		movl 7*wordsize(%ebp),%eax				# eax is curk
		incl %eax		
		push %eax								# k+1
		movl 6*wordsize(%ebp),%ebx				# ebx is n
		push %ebx
		incl %ecx								# i+1
		push %ecx								
		movl 4*wordsize(%ebp),%esi				# esi is row ary
		push %esi
		movl 3*wordsize(%ebp),%eax				# eax is ary
		push %eax
		movl 2*wordsize(%ebp),%eax				# eax is item ary
		push %eax
		call combination
		# new count in eax
		addl $(8*wordsize),%esp					# clear stack
		movl %eax,9*wordsize(%ebp)				# count = return

		pop %ecx
		incl %ecx
		jmp main_for						

	end_recur:
		#epilogue
			movl %ebp,%esp
			pop %ebp
		ret
		

	first_if:
		# for (i = 0; i < maxk; i++)  ecx is i
		movl 3*wordsize(%ebp),%eax				# eax is ary
		movl 4*wordsize(%ebp),%esi				# esi is row ary
		leal (%esi,%ecx,4),%ebx					# ebx is ptr row[i]
		movl (%ebx),%ebx						# ebx is row[i] value
		movl 9*wordsize(%ebp),%edx				# edx = count
		leal (%eax,%edx,4),%esi					# esi is ptr to ary[count]
		movl (%esi),%esi						# esi is ptr to ary[count][0]
		leal (%esi,%ecx,4),%esi					# esi is ptr to ary[count][i]
		movl %ebx,(%esi)						# ass[count][i] = row[i]
		movl 8*wordsize(%ebp),%eax				# eax is k
		incl %ecx								# i++
		cmpl %ecx,%eax							# k-i
		jg first_if								# repeat
		jmp end_first_for

	end_first_for:
		movl 9*wordsize(%ebp),%edx				# count
		incl %edx								# count++
		movl %edx,%eax
		#epilogue
			movl %ebp,%esp
			pop %ebp
		ret















	
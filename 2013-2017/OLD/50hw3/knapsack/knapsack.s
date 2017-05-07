.global knapsack
.equ wordsize, 4

.text
knapsack:
	#unsigned int knapsack(int* weights, unsigned int* values, unsigned int num_items, int capacity, unsigned int cur_value)

	#esp 5* wordsize = unsigned int cur_value
	#esp 4* wordsize = int capacity
	#esp 3* wordsize = unsigned int num_items
	#esp 2* wordsize = unsigned int * values
	#esp 1* wordsize = int * weights
	#esp    return address
	
	movl 5*wordsize(%esp),%edx     #best value  = cur-value    in edx
	# use ecx to store the current num of item to compare for(i = 0; i < num_items; i++)
	movl $0,%ecx # ecx = i = 0

	#prologue
	
		push %ebp
		movl %esp, %ebp  # new pushed item   so each argument increase 1 wordsize  now ebp is esp  ori ebp is 4ebp 
		.equ weights, 2*wordsize #(%ebp)
		.equ values, 3*wordsize #(%ebp)
		.equ numitem, 4*wordsize #(%ebp)
		.equ capacity, 5*wordsize #(%ebp)
		.equ curvalue, 6*wordsize #(%ebp)

	infor:
		#for(i = 0; i < num_items; i++)
		movl numitem(%ebp),%eax     # eax = num of item
		cmpl %ecx,%eax				# cmp 0 and numitem - i
		jg if						# numitem - i >0   
		
		movl %edx,%eax				#return bestvalue
		jmp end_rec

		if:
			movl weights(%ebp),%esi
			leal (%esi,%ecx,4),%esi			#esi = adress of weight[i]
			movl capacity(%ebp),%edi		#edi = int capacity
			cmpl (%esi),%edi				#capacity-weight[i]
			jge inif						#go inside if
			jmp endfor
		
		inif:
		    #	knapsack(weights + i + 1, values + i + 1, num_items - i - 1, 
            #            capacity - weights[i], cur_value + values[i])
			push %ecx
			push %edx

			movl values(%ebp),%esi			#esi= value[0]
			leal (%esi,%ecx,4),%esi			#esi= value[i]
			movl (%esi),%esi				#esi = value of value[i]
			movl curvalue(%ebp),%edi		#edi  = curvalue
			addl %edi,%esi					# 
			push %esi						# push cur_value + value[i]

			movl capacity(%ebp),%edi		#edi= capacity
			movl weights(%ebp),%esi
			leal (%esi,%ecx,4),%esi			#esi = adress of weight[i]
			subl (%esi),%edi				#edi=capacity-weight[i]
			push %edi

			movl numitem(%ebp),%eax			# eax = num of item
			subl %ecx,%eax					# numitem -i
			decl %eax						# numitem -1
			push %eax						# num_items - i - 1

			movl values(%ebp),%esi			#esi= add value[0]
			leal wordsize(%esi),%esi		# values+1
			leal (%esi,%ecx,4),%esi			#values+i
			push %esi						# push values + i + 1

			movl weights(%ebp),%esi			# esi= add weights[0]
			leal wordsize(%esi),%esi		# weights+1
			leal (%esi,%ecx,4),%esi			# weights+i
			push %esi						#push weights +i +1

			call knapsack
			addl $(5*wordsize),%esp			#clear arguments off stack
			pop %edx
			pop %ecx
			# result is in %eax
			cmpl %eax,%edx
			jb max
			jmp endfor

		endfor:
			incl %ecx  # i ++
			jmp infor
		
	end_rec:
		#epilogue
		movl %ebp,%esp
		pop %ebp
		ret
	
	max:
			movl %eax,%edx
			jmp endfor

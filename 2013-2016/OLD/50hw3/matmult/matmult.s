.global matMult
.equ wordsize, 4


.text

	#matMult(mat_a, rows_mat_a, cols_mat_a, mat_b, 
		#rows_mat_b, cols_mat_b);


matMult:
	#prologue
	push %ebp
	movl %esp, %ebp

	.equ mat_a, -4
	.equ rows_mat_a, -8
	.equ cols_mat_a, -12
	.equ mat_b, -16
	.equ rows_mat_b, -20
	.equ cols_mat_b, -24


	.equ sizeA, -28
	.equ sizeB, -32
	.equ c, -36
	.equ i, -40
	.equ j, -44
	.equ sum, -48
	subl $52, %esp
	

	# eax, ecx, edx will have no live values

	push %ebx
	push %esi
	push %edi

	movl 8(%ebp), %eax
	movl %eax, mat_a(%ebp)

	movl 12(%ebp), %ebx
	movl %ebx, rows_mat_a(%ebp)

	movl 16(%ebp), %ecx
	movl %ecx, cols_mat_a(%ebp)

	movl 20(%ebp), %edx
	movl %edx, mat_b(%ebp)

	movl 24(%ebp), %esi
	movl %esi, rows_mat_b(%ebp)

	movl 28(%ebp), %edi
	movl %edi, cols_mat_b(%ebp)



	movl rows_mat_a(%ebp), %eax
	movl cols_mat_a(%ebp), %ebx
	mull %ebx
	movl %eax, sizeA(%ebp)		#sizeA


	movl rows_mat_b(%ebp), %eax
	movl cols_mat_b(%ebp), %ebx
	mull %ebx
	movl %eax, sizeB(%ebp)	#sizeB


	# int **mat_c = (int **) malloc(mat_a_rows * sizeof(int *));

	movl rows_mat_a(%ebp), %eax
	shll $2, %eax				# mat_a_rows * sizeof(int *)
	push %eax
	call malloc
	movl %eax, c(%ebp)		# var c
	#addl $wordsize, %esp


	
	movl $0, i(%ebp)		# i = 0
	
	
	# for(int i = 0; i < mat_a_rows; i++) 
	# 		mat_c[i] = (int *) malloc(mat_b_cols * sizeof(int));

	initC:
		
		#movl $wordsize, %eax
		movl cols_mat_b(%ebp), %eax
		shll $2, %eax
		push %eax
		call malloc

		movl c(%ebp), %ecx

		movl i(%ebp), %esi
		
		movl %eax, (%ecx, %esi, wordsize)
		#addl $wordsize, %esp

		incl i(%ebp)
		movl i(%ebp), %esi
		movl rows_mat_a(%ebp), %edx
		cmp %edx, %esi
		jl initC

	# calculte multiplication
	movl $0, i(%ebp)
	

	rows:
		movl i(%ebp), %esi
		movl $0, j(%ebp)

		cols:

			movl j(%ebp), %edi
			movl $0, sum(%ebp)
			movl $0, %ecx

			c_calc:

				movl mat_a(%ebp), %eax
				movl (%eax, %esi, wordsize), %eax
				movl (%eax, %ecx, wordsize), %eax


				movl mat_b(%ebp), %ebx
				movl (%ebx, %ecx, wordsize), %ebx
				movl (%ebx, %edi, wordsize), %ebx

				mull %ebx		#mat_a[i][j] * mat_b[j][k]

				addl %eax, sum(%ebp)
				incl %ecx
				cmp cols_mat_a(%ebp), %ecx
				jl c_calc

			end_c_calc:

				
				# mat_c[i][j] = sum;
				push %eax
				movl sum(%ebp), %eax
				movl c(%ebp), %edx
				movl (%edx, %esi, wordsize), %edx
				movl %eax, (%edx, %edi, wordsize)

				pop %eax



				# ----------------------------
				#debug use
			/*
				movl $1, %edx

				movl c(%ebp), %edx
				movl (%edx, %esi, wordsize), %edx
				movl (%edx, %edi, wordsize), %edx

				movl %edx, %edx

			*/

				# -----------------------------

				incl j(%ebp)
				movl j(%ebp), %edi
				cmp cols_mat_b(%ebp), %edi
				jl cols

		end_cols:
			incl i(%ebp)
			movl i(%ebp), %esi
			cmp rows_mat_a(%ebp), %esi
			jl rows

	end_rows:

	movl c(%ebp), %eax
#----------------------------------
# debug use
/*
	movl $0, %esi
	movl $0, %edi

	exam:
		movl $0, %edi
		
		loop:
		movl (%eax, %esi, wordsize), %ebx
		movl (%ebx, %edi, wordsize), %ebx
		movl %ebx, %ebx
		incl %edi
		cmp cols_mat_b(%ebp), %edi
		jl loop
		incl %esi
		cmp rows_mat_a(%ebp), %esi
		jl exam
*/
#-------------------------------------



	# restore registers

	pop %edi
	pop %esi
	pop %ebx


	#epilogue
	movl %ebp, %esp
	pop %ebp

	ret









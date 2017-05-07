all: pipe_test AlarmTest directory_traverse_breadth_first process_tree smallsh
 
pipe_test: 1pipe_test.c
	gcc -W -o pipe_test 1pipe_test.c
AlarmTest: 2AlarmTest.c
	gcc -W -o AlarmTest 2AlarmTest.c
directory_traverse_breadth_first: 3directory_traverse_breadth_first.c
	gcc -W -o directory_traverse_breadth_first 3directory_traverse_breadth_first.c
process_tree: 4process_tree.c
	gcc -W -o process_tree 4process_tree.c
smallsh: 5smallsh.c smallsh.h infptnum.c infptalpha.c
	gcc -W -o smallsh 5smallsh.c smallsh.h
	gcc -W -o int.out infptnum.c
	gcc -W -o char.out infptalpha.c


clean:
	rm -f smallsh pipe_test AlarmTest directory_traverse_breadth_first process_tree int.out char.out 



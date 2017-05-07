all: pipe_test AlarmTest directory_traverse_breadth_first process_tree smallsh
 
pipe_test: pipe_test.c
	gcc -W -o pipe_test pipe_test.c
AlarmTest: AlarmTest.c
	gcc -W -o AlarmTest AlarmTest.c
directory_traverse_breadth_first: directory_traverse_breadth_first.c
	gcc -W -o directory_traverse_breadth_first directory_traverse_breadth_first.c
process_tree: process_tree.c
	gcc -W -o process_tree process_tree.c
smallsh: smallsh.c smallsh.h infptnum.c infptalpha.c
	gcc -W -o smallsh smallsh.c smallsh.h
	gcc -W -o int.out infptnum.c
	gcc -W -o char.out infptalpha.c


clean:
	rm -f smallsh pipe_test AlarmTest directory_traverse_breadth_first process_tree int.out char.out 



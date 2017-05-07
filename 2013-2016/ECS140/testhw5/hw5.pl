/*******************************************/
/**    Your solution goes in this file    **/ 
/*******************************************/

/* Part 1 */
fc_course(Course):- course(Course,_,Num),(Num=3;Num=4).

prereq_110(Prerequisites):- course(Prerequisites,List,_),member(ecs110,List).

ecs140a_students(Students):- student(Students,List),member(ecs140a,List).

instructor_names(Instructor):- instructor(Instructor,_),
                              teach_john(Instructor).
teach_john(Instructor):- student(john,List),instructor(Instructor,List2),member(Class,List),member(Class,List2),!.

students(STUDENTS):- student(STUDENTS,_),
                     in_jims_class(STUDENTS).
in_jims_class(STUDENTS):- instructor(jim,List),student(STUDENTS,List2),member(Class,List),member(Class,List2),!.

allprereq(Theclass,All_Pre):- findall(Class,(course(Class,_,_),prereq(Class,Theclass)),All_Pre).
prereq(Class,Theclass):- course(Theclass,List,_),member(Class,List).
prereq(Class,Theclass):- course(Theclass,List,_),member(Otherclass,List),prereq(Class,Otherclass).

my_length([],0).
my_length([_|T],Len):- my_length(T,LenT),Len is LenT+1.


/* Part 2 */
all_length([],0).
all_length([[]|T],Len):- all_length(T,LenT),Len is LenT+1,!.
all_length([H|T],Len):- atom(H),all_length(T,LenT),Len is LenT+1.
all_length([H|T],Len):- all_length(H,LenH),all_length(T,LenT),Len is LenH + LenT.

equal_a_b(List):- part1(List,A,B),A=B.
part1(List,A,B):- equal_helper(List,A,B),!.
equal_helper([],Acount,Bcount):- Acount is 0,Bcount is 0.
equal_helper([a|T],Acount,Bcount):- equal_helper(T,Acount1,Bcount),Acount is Acount1+1.
equal_helper([b|T],Acount,Bcount):- equal_helper(T,Acount,Bcount1),Bcount is Bcount1+1.
equal_helper([_|T],Acount,Bcount):- equal_helper(T,Acount,Bcount).

swap_prefix_suffix(Middle,List,Result):-append3(L1,Middle,L3,List),append3(L3,Middle,L1,Result).
append3(L1,L2,L3,List):- append(L1,LL,List),append(L2,L3,LL).

palin(List):-my_reverse(List,ListR),List=ListR.
my_reverse([],[]).
my_reverse([H|T],ListR):- my_reverse(T,TR),append(TR,[H],ListR).

good(List):-is_good(List),!.
is_good([]).
is_good([0|T]):- is_good(T).
is_good([1|T]):- is_good2(T,2),!.
is_good2([],0).
is_good2([0|T],C):- C1 is C-1,is_good2(T,C1).
is_good2([1|T],2):- C is 1,is_good2(T,2).
is_good2([1|T],1):- C is 0,is_good2(T,2).


/* part 3 */
solve:- find(AllPaths),
        reverse(AllPaths,ModifiedPaths),
        converttomoves(ModifiedPaths,Moves),
        reverse(Moves,Sol),
        printlist(Sol),!.
        
initial(state(left,left,left,left)).
end(state(right,right,right,right)).

find(AllPaths):- initial(State),process(State,AllPaths).

process(State,AllPaths):- in_process(State,[],AllPaths).

in_process(State,Path,[State|Path]):- end(State).
in_process(State,Paths,AllPaths):- arc(State,State2), safe(State2), \+member(State2,Paths),
                                   in_process(State2,[State|Paths],AllPaths).

/* Farmer & Wolf */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Oppo,Goat,Cabbage)):- Farmer=Wolf,opposite(Farmer,Oppo).

/* Farmer & Cabbage */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Oppo)):- Farmer=Cabbage,opposite(Farmer,Oppo).

/* Farmer & Goat */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Oppo,Cabbage)):- Farmer=Goat,opposite(Farmer,Oppo).

/* Farmer alone */
arc(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Cabbage)):- opposite(Farmer,Oppo).


state(Farmer,Wolf,Goat,Cabbage).
take(Object,Bank1,Bank2).
unsafe(state(Farmer,Wolf,Goat,Cabbage)):- Goat=Wolf,opposite(Farmer,Goat),!.         /* Wolf eat Goat case */
unsafe(state(Farmer,Wolf,Goat,Cabbage)):- Goat=Cabbage,opposite(Farmer,Goat),!.      /* Goat eat Cabbage case */
safe(state(Farmer,Wolf,Goat,Cabbage)):-  \+unsafe(state(Farmer,Wolf,Goat,Cabbage)).
opposite(Bank1,Bank2):- (Bank1 = left,Bank2 = right);(Bank1 = right,Bank2 = left).

converttomoves([H|T],Moves):- initial(H),convert_process(H,T,[],Moves).
convert_process(H,[HH|T],Takes,Moves):- end(HH),generatetake(H,HH,Take),append([Take],Takes,Moves).
convert_process(H,[HH|T],Takes,Moves):- generatetake(H,HH,Take),convert_process(HH,T,[Take|Takes],Moves).

generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Oppo,Goat,Cabbage),take(wolf,Wolf,Oppo)):- Farmer=Wolf,opposite(Farmer,Oppo).
generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Oppo),take(cabbage,Cabbage,Oppo)):- Farmer=Cabbage,opposite(Farmer,Oppo).
generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Oppo,Cabbage),take(goat,Goat,Oppo)):- Farmer=Goat,opposite(Farmer,Oppo).        
generatetake(state(Farmer,Wolf,Goat,Cabbage),state(Oppo,Wolf,Goat,Cabbage),take(none,Farmer,Oppo)):- opposite(Farmer,Oppo).

printlist([]).
printlist([H|T]):- write(H),write('\n'),printlist(T).

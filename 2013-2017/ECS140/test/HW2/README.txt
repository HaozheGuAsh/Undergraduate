Haozhe GU,999200555

#New BNF with for-loop(shift+4 which is $)
program ::= block
block ::= declaration_list statement_list
declaration_list ::= {declaration}
statement_list ::= {statement}
declaration ::= ’@’ id { ’,’ id }
statement ::= assignment | print | do | if
for ::= '$' '('ref_id|declaration ',' expr ',' assignment ')' block '^'
print ::= ’!’ expr
assignment ::= ref_id ’=’ expr
ref_id ::= [ ’ ̃’ [ number ] ] id
do ::= ’<’ guarded_command ’>’
if ::= ’[’ guarded_command { ’|’ guarded_command } [ ’%’ block ] ’]’
guarded_command ::= expr ’:’ block
expr ::= term { addop term }
term ::= factor { multop factor }
factor ::= ’(’ expr ’)’ | ref_id | number
addop ::= ’+’ | ’-’
multop ::= ’*’ | ’/’


My rule in parser is $ (variable; variable < expr; variable= expr){block} ^

Because I need to follow E language grammar and syntax. So I decide to put first part in current scope and then begin the new block.
When I declare a variable, i will name it as variable in next scope, so next block can excute successfully. 

Test case 1
@i,a
i=1
$(i,5,i=i+1)!i^
$(@a=1,4,a=a+1)!a^  // test to declare variable inside for; also test for blocks(since a is already declared in main)

output AS EXPECTED
> running e2c
> compiling the C generated code
> executing the a.out
> 1
> 2
> 3
> 4
> 1
> 2
> 3  
  
Test case 2
@a
a=-6
$(~a,0,~a=~a+1)!~a^ $(~0a,4,~0a=~0a+1)!~1a^  // test referenced ID, ~a and ~0a all related to  a=-6, ~1a in a new block is also related to a=-6

output AS EXPECTED
> running e2c
> compiling the C generated code
> executing the a.out
> -6
> -5
> -4
> -3
> -2
> -1
> 0
> 1
> 2
> 3

Test case 3
@a,b
a=1
b=5
$(@a=9,11,a=a+1) 
                !a
                $(~1a,2,~1a=~1a+1)
                                !~2a
                                $(~2b,7,~2b=~2b+1)
                                                !~3b
                                                $(@b=8,9,b=b+1)
                                                            !b
                                                ^
                                ^
                ^
^					// nested for loop, checking reference ID function and declaration function

output AS EXPECTED
> running e2c
> compiling the C generated code
> executing the a.out
> 9
> 1
> 5
> 8
> 6
> 8
> 10
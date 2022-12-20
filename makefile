assembler: main.o command.o direction.o general.o label.o macro.o oiput.o validation.o
	gcc -g -ansi -Wall -pedantic main.o command.o direction.o general.o label.o macro.o oiput.o validation.o -o assembler
main.o: main.c main.h generaldata.h macro.h
	gcc -c -g -ansi -Wall -pedantic main.c -o main.o
command.o: command.c command.h operators.h memoryimage.h generaldata.h
	gcc -c -g -ansi -Wall -pedantic command.c -o command.o
direction.o: direction.c direction.h memoryimage.h generaldata.h
	gcc -c -g -ansi -Wall -pedantic direction.c -o direction.o
general.o: general.c general.h generaldata.h operators.h memoryimage.h
	gcc -c -g -ansi -Wall -pedantic general.c -o general.o
label.o: label.c label.h generaldata.h
	gcc -c -g -ansi -Wall -pedantic label.c -o label.o
macro.o: macro.c macro.h generaldata.h
	gcc -c -g -ansi -Wall -pedantic macro.c -o macro.o
oiput.o: oiput.c oiput.h label.h
	gcc -c -g -ansi -Wall -pedantic oiput.c -o oiput.o
validation.o: validation.c validation.h label.h
	gcc -c -g -ansi -Wall -pedantic validation.c -o validation.o

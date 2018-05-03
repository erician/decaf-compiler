#
.PHONY: clean test log
COMPILER = decaf
PRODUCTS = $(COMPILER)
default: $(PRODUCTS)

# Set up the list of source and object files
SRCS = nt_class.cpp main.cpp

# OBJS can deal with either .cc or .c files listed in SRCS
OBJS = y.tab.o lex.yy.o nt_genast.cpp.o nt_printast.cpp.o nt_buildsym.cpp.o nt_printsym.cpp.o nt_check.cpp.o nt_gentac.cpp.o nt_printtac.cpp.o nt_genmips.cpp.o error.cpp.o  main.cpp.o

JUNK = *~ *.o lex.yy.c y.tab.c y.tab.h  

# Define the tools we are going to use
CC= g++
LD = g++
LEX = flex
YACC = bison

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare
LEXFLAGS = 
YACCFLAGS = -dvty
LIBS = -lc -lm -ll

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

lex.yy.c: flex.l bison.y y.tab.h
	$(LEX) $(LEXFLAGS) flex.l

y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c -o y.tab.o y.tab.c

y.tab.h y.tab.c: bison.y
	$(YACC) $(YACCFLAGS) bison.y

nt_genast.cpp.o: nt_genast.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
nt_printast.cpp.o:nt_printast.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
nt_buildsym.cpp.o: nt_buildsym.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
nt_printsym.cpp.o: nt_printsym.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
error.cpp.o: error.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
nt_check.cpp.o: nt_check.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
nt_gentac.cpp.o: nt_gentac.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
nt_printtac.cpp.o: nt_printtac.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
nt_genmips.cpp.o: nt_genmips.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
main.cpp.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


$(COMPILER) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LIBS)

test:
	cat test.decaf|./decaf

clean:
	@rm -f $(JUNK) y.output $(PRODUCTS)

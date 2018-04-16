#
.PHONY: clean wrongtest righttest
COMPILER = ../obj/decaf
PRODUCTS = $(COMPILER)
default: $(PRODUCTS)

TESTDIR = ../test/
OBJDIR = ../obj/

include yacc/makefile
include lex/makefile
include core/makefile

# OBJS can deal with either .cc or .c 
OBJS = $(OBJDIR)y.tab.o $(OBJDIR)lex.yy.o $(OBJDIR)dc_genast.cpp.o $(OBJDIR)dc_printast.cpp.o $(OBJDIR)dc_error.cpp.o $(OBJDIR)main.cpp.o

JUNK = *~ $(OBJDIR)*.o $(LEXDIR)lex.yy.c $(YACCDIR)y.tab.c $(YACCDIR)y.tab.h  

# Define the tools we are going to use
CC= g++
LD = g++
LEX = flex
YACC = bison

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare 
LEXFLAGS = 
YACCFLAGS = -dvty
LIBS = -lc -lm -ll

$(OBJDIR)main.cpp.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(COMPILER) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LIBS)

wrongtest:
	cat $(TESTDIR)shouldfail.decaf | $(OBJDIR)decaf

righttest:
	cat $(TESTDIR)shouldpass.decaf | $(OBJDIR)decaf

clean:
	@rm -f $(JUNK) y.output $(PRODUCTS)



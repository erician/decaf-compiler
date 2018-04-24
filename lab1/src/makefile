#
.PHONY: clean wrongtest righttest
COMPILER = ../obj/decaf
PRODUCTS = $(COMPILER)
default: $(PRODUCTS)

TESTDIR = ../decaf-test-src/
OBJDIR = ../obj/

include yacc/makefile
include lex/makefile
include core/makefile
include utils/args/makefile
include compiler/makefile

# OBJS can deal with either .cc or .c 
OBJS = $(OBJDIR)y.tab.o $(OBJDIR)lex.yy.o 
OBJS += $(OBJDIR)dc_genast.cpp.o $(OBJDIR)dc_printast.cpp.o 
OBJS += $(OBJDIR)dc_error.cpp.o 
OBJS += $(OBJDIR)dc_args.cpp.o $(OBJDIR)dc_options.cpp.o $(OBJDIR)dc_option_error.cpp.o 
OBJS += $(OBJDIR)dc_compiler.cpp.o
OBJS += $(OBJDIR)main.cpp.o

JUNK = *~ $(OBJDIR)*.o  $(LEXDIR)lex.yy.c $(YACCDIR)y.tab.c $(YACCDIR)y.tab.h  $(YACCDIR)y.output

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
	cp $(COMPILER) ./

failtest:
	@echo "---------->funNotInClass_Shouldfail" 
	./$(OBJDIR)decaf $(TESTDIR)funNotInClass_Shouldfail.decaf
	@echo "---------->initVarWhenDeclared_Shouldfail.decaf"
	./$(OBJDIR)decaf $(TESTDIR)initVarWhenDeclared_Shouldfail.decaf

passtest:
	@./$(OBJDIR)decaf $(TESTDIR)simpleTest_shouldpass.decaf
	@./$(OBJDIR)decaf $(TESTDIR)withArray_shouldpass.decaf

clean:
	@rm -f $(JUNK) $(PRODUCTS) decaf



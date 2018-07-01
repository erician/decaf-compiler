#
.PHONY: clean wrongtest righttest
COMPILER = ../obj/decaf
PRODUCTS = $(COMPILER)
default: $(PRODUCTS)

TESTDIR = ../decaf-source-file
OBJDIR = ../obj

include yacc/makefile
include lex/makefile
include core/makefile
include utils/args/makefile
include utils/print/makefile
include compiler/makefile
include unittest/utils/print/makefile
include unittest/utils/args/makefile
include unittest/makefile

# OBJS can deal with either .cc or .c 
OBJS = $(OBJDIR)/y.tab.o $(OBJDIR)/lex.yy.o 
OBJS += $(OBJDIR)/dc_error.cpp.o 
OBJS += $(OBJDIR)/dc_args.cpp.o $(OBJDIR)/dc_options.cpp.o $(OBJDIR)/dc_option_error.cpp.o 
OBJS += $(OBJDIR)/dc_compiler.cpp.o
OBJS += $(OBJDIR)/dc_symbol.cpp.o
OBJS += $(OBJDIR)/dc_print.cpp.o
OBJS += $(OBJDIR)/dc_genast.cpp.o $(OBJDIR)/dc_printast.cpp.o 
OBJS += $(OBJDIR)/dc_printsym.cpp.o $(OBJDIR)/dc_buildsym.cpp.o 
OBJS += $(OBJDIR)/dc_check.cpp.o 
OBJS += $(OBJDIR)/main.cpp.o

JUNK = *~ $(OBJDIR)/*.o $(OBJDIR)/*.a  $(LEXDIR)/lex.yy.c $(YACCDIR)/y.tab.c $(YACCDIR)/y.tab.h  $(YACCDIR)/y.output

# Define the tools we are going to use
CC= g++
LD = g++
LEX = flex
YACC = bison

CFLAGS = -g -Wall -Wno-unused -Wno-sign-compare -Wno-parentheses -std=c++11 -I.

LEXFLAGS = 
YACCFLAGS = -dvty
LIBS = -lc -lm -ll

$(OBJDIR)/main.cpp.o: main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(COMPILER) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LIBS)
	cp $(COMPILER) ./

failtest:
	@echo "---------->funNotInClass_Shouldfail" 
	./$(OBJDIR)/decaf $(TESTDIR)/funNotInClass_Shouldfail.decaf
	@echo "---------->initVarWhenDeclared_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/initVarWhenDeclared_Shouldfail.decaf
	@#class 
	@echo "---------->undefinedClass_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/undefinedClass_Shouldfail.decaf
	@echo "---------->undefinedClassInVars_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/undefinedClassInVars_Shouldfail.decaf
	@echo "---------->redefinedClass_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/redefinedClass_Shouldfail.decaf
	@#main
	@echo "---------->redefinedMain_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/redefinedMain_Shouldfail.decaf
	@echo "---------->undefinedMain_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/undefinedMain_Shouldfail.decaf
	@echo "---------->notStaticMain_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/notStaticMain_Shouldfail.decaf
	@#attribute and method
	@echo "---------->redefinedAttribute_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/redefinedAttribute_Shouldfail.decaf
	@echo "---------->redefinedMethod_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/redefinedMethod_Shouldfail.decaf
	@echo "---------->attributeAndMethodWithTheSameName_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/attributeAndMethodWithTheSameName_Shouldfail.decaf
	@echo "---------->redefinedLocalVariables_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/redefinedLocalVariables_Shouldfail.decaf
	@#undefined variables
	@echo "---------->undefinedVariables_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/undefinedVariables_Shouldfail.decaf
	@#uncorrectly dot used
	@echo "---------->unCorrectlyDotUsed_Shouldfail"
	./$(OBJDIR)/decaf $(TESTDIR)/unCorrectlyDotUsed_Shouldfail.decaf

passtest:
	@echo "---------->simpleTest_shouldpass.decaf"
	./$(OBJDIR)/decaf $(TESTDIR)/simpleTest_shouldpass.decaf
	@echo "---------->withArray_shouldpass.decaf"
	./$(OBJDIR)/decaf $(TESTDIR)/withArray_shouldpass.decaf
	@echo "---------->varDeclBetweenStmts_Shouldpass.decaf"
	./$(OBJDIR)/decaf $(TESTDIR)/varDeclBetweenStmts_Shouldpass.decaf
	@echo "---------->multipleNesting_shouldpass.decaf"
	./$(OBJDIR)/decaf $(TESTDIR)/multipleNesting_shouldpass.decaf
	@echo "---------->blankStmtBlock_Shouldpass.decaf"
	./$(OBJDIR)/decaf $(TESTDIR)/blankStmtBlock_Shouldpass.decaf


#unittest,using googletest:https://github.com/google/googletest/blob/master/googletest/docs/Primer.md
#this make no sense, and just test googletest

unittest-utils-print: $(OBJDIR)/utils_dc_print_unittest
	./$(OBJDIR)/utils_dc_print_unittest
unittest-utils-args: $(OBJDIR)/utils_dc_args_unittest
	./$(OBJDIR)/utils_dc_args_unittest

clean:
	@rm -f $(JUNK) $(PRODUCTS) decaf



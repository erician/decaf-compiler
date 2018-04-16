LEXDIR := lex/

${OBJDIR}lex.yy.o: $(LEXDIR)lex.yy.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LEXDIR)lex.yy.c: $(LEXDIR)flex.l
	$(LEX) $(LEXFLAGS) $<
	mv lex.yy.c $(LEXDIR)
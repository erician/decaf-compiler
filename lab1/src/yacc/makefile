YACCDIR := yacc/

$(OBJDIR)y.tab.o: $(YACCDIR)y.tab.c
	@if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
	$(CC) $(CFLAGS) -c -o $@ $<

$(YACCDIR)y.tab.h $(YACCDIR)y.tab.c: $(YACCDIR)bison.y
	$(YACC) $(YACCFLAGS) $<
	mv y.tab.c y.tab.h y.output $(YACCDIR)
# TARGETS = echo.c pwd.c cd.c ls.c pinfo.c shell.c
# TARGETSO = echo.o pwd.o cd.o ls.o pinfo.o shell.o


# makeo: 	$(TARGETSO)
# 	gcc -o main $(TARGETSO)

# compile: $(TARGETS)
# 	gcc -c $(TARGETS)

# debug: $(TARGETS)
# 	gcc -c -g -Wall $(TARGETS)

# clean: $(TARGETSO)
#	rm *.o	
main: *.c
	gcc -o main -g -Wall *.c
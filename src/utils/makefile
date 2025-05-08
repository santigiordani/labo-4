# Paths
objpath      = ../../bin/obj/generadores
includepath  = ../../include/generadores

# Librerías
objfiles     = ran0.o ran1.o ran2.o mzran13.o mtran.o
objfullpaths = $(addprefix $(objpath)/, $(objfiles))

# Compilamos todas las librerías
all : $(objfullpaths)

# Compilamos cada librería individual
$(objfullpaths) : $(objpath)/%.o : %.c
	@echo "Compilando $@"
	@gcc -c $*.c -o $@ -I$(includepath)

# Test
test : $(objfullpaths)
	@gcc -c test.c -o test.o -I$(includepath)
	@gcc test.o $(objfullpaths) -o test 
	@./test
	@rm -f test test.o

# Limpieza
clean :
	@rm -f $(objfullpaths)

.PHONY : clean all test
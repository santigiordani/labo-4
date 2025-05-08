binpath = ../../bin
objpath = ../../bin/obj/ej2
genpath = ../../bin/obj/generadores

includepath =    ../../include/ej2
genincludepath = ../../include/generadores


# Link main
$(binpath)/ej2 : $(objpath)/main.o $(objpath)/ranwalk.o $(wildcard $(genpath)/*.o)
	@gcc $(objpath)/main.o $(objpath)/ranwalk.o $(wildcard $(genpath)/*.o) -o $(binpath)/ej2

# Compile main
$(objpath)/main.o : main.c
	@$(MAKE) -C ../generadores
	@echo "Compilando $@"
	@gcc -c main.c -o $(objpath)/main.o -I$(includepath) -I$(genincludepath)

# Compile ranwalk
$(objpath)/ranwalk.o : ranwalk.c
	@$(MAKE) -C ../generadores
	@echo "Compilando $@"
	@gcc -c ranwalk.c -o $(objpath)/ranwalk.o -I$(includepath) -I$(genincludepath)

# Ejecutamos como si estuvieramos en el directorio principal
run :
	@cd ../.. && bin/ej2 $(PARAM)


plot :
	@cd ../.. && gnuplot scripts/ej2/a.gnuplot
	@cd ../.. && gnuplot scripts/ej2/b.gnuplot
	@cd ../.. && gnuplot scripts/ej2/c.gnuplot
	@cd ../.. && gnuplot scripts/ej2/ejemplos.gnuplot
	@cd ../../informe && pdflatex main.tex


clean :
	@rm -f $(binpath)/ej2 $(objpath)/main.o $(objpath)/ranwalk.o


.PHONY : run plot clean
MAKEFLAGS += --silent
.PHONY : all run plot clean
MAKEFLAGS += --silent


all :
	@$(MAKE) -C src/generadores
#	@$(MAKE) -C src/ej1
#	@$(MAKE) -C src/ej2

run :
	@echo "Not implemented yet"
#	@$(MAKE) -C src/ej1 run
#	@$(MAKE) -C src/ej2 run

plot :
	@echo "Not implemented yet"
#	@$(MAKE) -C src/ej1 plot
#	@$(MAKE) -C src/ej2 plot

clean :
	@$(MAKE) -C src/generadores clean
#	@$(MAKE) -C src/ej1 clean
#	@$(MAKE) -C src/ej2 clean
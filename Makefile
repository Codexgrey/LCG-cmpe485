all: sim

sim: 
	gcc sim.c -o sim
	touch results.doc

clean: 
	rm sim Results.doc

run:
	./sim >> Results.doc

test: sim
	bash test.sh
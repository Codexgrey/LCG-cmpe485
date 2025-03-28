all: sim

sim: 
	gcc sim.c -o sim
	touch Results.doc

clean: 
	rm sim Results.doc

run:
	./sim >> Results.doc

test: sim
	bash test.sh
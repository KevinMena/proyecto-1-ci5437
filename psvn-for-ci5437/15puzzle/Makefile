CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --no_abstraction --no_backwards_moves --history_len=0

psvn2c_core.c:
	cp ../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../global/succ.c
	$(CC) $(OPT) ../global/succ.c -include $< -o $@
	rm -f $*.c

%.a_star: %.c ../global/a_star.cpp
	$(CXX) $(OPT) ../global/a_star.cpp -include $< -o $@
	rm -f $*.c

%.a_star_ddd: %.c ../global/a_star_ddd.cpp
	$(CXX) $(OPT) ../global/a_star_ddd.cpp -include $< -o $@
	rm -f $*.c

%.ida_star: %.c ../global/ida_star.cpp
	$(CXX) $(OPT) ../global/ida_star.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~

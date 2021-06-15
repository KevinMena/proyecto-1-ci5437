CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backwards_moves --fwd_history_len=2

psvn2c_core.c:
	cp ../../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.distSummary: %.c ../../global/distSummary.cpp
	@echo "**** Constructing $@ ..."
	@$(CXX) $(OPT) ../../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.a_star: %.c ../../global/a_star.cpp
	$(CXX) $(OPT) ../../global/a_star.cpp -include $< -include 15puzzle_manhattan.cpp -o $@
	rm -f $*.c

%.ida_star: %.c ../../global/ida_star.cpp
	$(CXX) $(OPT) ../../global/ida_star.cpp -include $< -include 15puzzle_manhattan.cpp -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~

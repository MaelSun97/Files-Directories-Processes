CC=		gcc
CFLAGS=		-g -gdwarf-2 -Wall -std=gnu99
LD=		gcc
LDFLAGS=	-L.
AR=		ar
ARFLAGS=	rcs
TARGETS=	search

all:		$(TARGETS)
main.o: main.c
	@$(CC) $(CFLAGS) -c -o main.o main.c
	@echo "Compiling main.o..."
execute.o: execute.c
	@$(CC) $(CFLAGS) -c -o execute.o execute.c
	@echo "Compiling execute.o..."
filter.o: filter.c
	@$(CC) $(CFLAGS) -c -o filter.o filter.c
	@echo "Compiling filter.o..."
search.o: search.c
	@$(CC) $(CFLAGS) -c -o search.o search.c
	@echo "Compiling search.o..."
utilities.o: utilities.c
	@$(CC) $(CFLAGS) -c -o utilities.o utilities.c
	@echo "Compiling utilities.o..."
search: main.o execute.o filter.o search.o utilities.o
	@$(AR) $(ARFLAGS) search main.o execute.o filter.o search.o utilities.o
	@echo "Linking search..."
test:		search test_search.sh
	@echo Testing $<...
	@./test_search.sh

clean:
	@echo Cleaning...
	@rm -f $(TARGETS) *.o *.log *.input

.PHONY:		all test benchmark clean

# TODO: Add rules for search and object files

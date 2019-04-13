monitor: tables dfdm dumpbatch dumpsamples
	gcc 										\
	-DARCH_06_55 									\
	-Wall 										\
	-std=c99 									\
	-I./msr_tables									\
	-I/home/rountree/local/Sonoma-midterm-support/hwloc-2.0.3-install/include 	\
	-L/home/rountree/local/Sonoma-midterm-support/hwloc-2.0.3-install/lib 		\
	monitor.c 									\
	dfdm.o										\
	dumpbatch.o									\
	dumpsamples.o									\
	-o monitor.so 									\
	-fPIC 										\
	-shared 									\
	-ldl 										\
	-lhwloc

tables:
	cd ./msr_tables ; rm -f msr_table_*.h ; rm -f msr_undefs.h ; ./generate-headers.py

dfdm:
	gcc -DARCH_06_55 -Wall -std=c99 -fPIC -shared -c dfdm.c

dumpbatch:
	gcc -DARCH_06_55 -Wall -std=c99 -fPIC -shared -I./msr_tables	-c dumpbatch.c 

dumpsamples:
	gcc -DARCH_06_55 -Wall -std=c99 -fPIC -shared -I./msr_tables	-c dumpsamples.c 

monitor-E:
	gcc 										\
	-E										\
	-Wall 										\
	-std=c99 									\
	-I./msr_tables									\
	-I/home/rountree/local/Sonoma-midterm-support/hwloc-2.0.3-install/include 	\
	-L/home/rountree/local/Sonoma-midterm-support/hwloc-2.0.3-install/lib 		\
	monitor.c


run: 
	LD_LIBRARY_PATH=/home/rountree/local/Sonoma-midterm-support/hwloc-2.0.3-install/lib	\
	LD_PRELOAD=./monitor.so 							\
	../Sonoma-midterm-support/FIRESTARTER-master/FIRESTARTER --timeout=10 --report > fs.out 2>&1

clean:
	rm -f monitor.so fs.out dumpbatch.o dfdm.o
	rm -f ./msr_tables/msr_table_*.h
	rm -f ./msr_tables/msr_undefs.h




COMPILER = g++ -c -I../include
$(nom).run : $(nom).o libSys.a
	g++ -s -o $(nom).run $(nom).o -L. -lSys
$(nom).o : $(nom).cxx ../include/notreEntete.h
	$(COMPILER)  $(nom).cxx
libSys.a : ../include/notreEntete.h
	$(COMPILER) file2.cxx ; ar -cqs libSys.a file2.o; rm file2.o
clean :
	rm *.o $(nom).run

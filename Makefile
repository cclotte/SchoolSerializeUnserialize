CPPFLAGS=-Wall -Werror -Wextra -Wfatal-errors -Werror=old-style-cast
assignment=hw7
OBJ_DEPENDENCIES=functions.o 
LIB_DEPENDENCIES= IFSerial.o OFSerial.o Serial.o functions.o hw2.o 

all: $(LIB_DEPENDENCIES) 
	ar rcs $(assignment).a $^
 
test: test.cc $(LIB_DEPENDENCIES)
	g++ $(CPPFLAGS) $^ -o $@

IFSerial.o: IFSerial.cc
	g++ $(CPPFLAGS) -I"./" -ggdb -c $^ 

OFSerial.o: OFSerial.cc
	g++ $(CPPFLAGS) -I"./" -ggdb -c $^ 

Serial.o: Serial.cc
	g++ $(CPPFLAGS) -I"./" -ggdb -c $^

functions.o: functions.cc 
	g++ $(CPPFLAGS) -I"./"  -ggdb -c $^

hw2.o: hw2.cc
	g++ $(CPPFLAGS) -ggdb -c $^


tar:
	tar -cv --exclude='test*.cc' $(MAKEFILE_LIST) *.h *.cc >$(assignment).tar 

clean:
	rm -f $(assignment) $(assignment).tar *.o *.gch *.a

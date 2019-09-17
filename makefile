CFLAGS = -std=c++17 -I /usr/local/include/mysql++/ -I /usr/include/mysql/ -lmysqlpp -lmysqlclient

all:

template_login.o:

message_body.o: message_body.hpp message_body.cpp
	-c message_body.cpp

message_header.o: message_header.hpp message_header.cpp
	$(CFLAGS) -c message_header.cpp

message_reader.o: message_reader.hpp message_reader.cpp
	$(CFLAGS) -c message_reader.cpp

CFLAGS = -std=c++17 -I /usr/local/include/mysql++/ -I /usr/include/mysql/ -lmysqlpp -lmysqlclient

all:

template_login.o:

message_body.o: message_body.hpp message_body.cpp
	-c message_body.cpp

message_header.o: message_header.hpp message_header.cpp
	$(CFLAGS) -c message_header.cpp

message_reader.o: message_reader.hpp message_reader.cpp
	$(CFLAGS) -c message_reader.cpp

message_processor.o: message_processor.hpp message_processor.cpp
	$(CFLAGS) -c message_processor.cpp

message_builder.o: message_builder.hpp message_builder.cpp
	-c message_builder.cpp

message_writer.o: message_writer.hpp message_writer.cpp
	-c message_writer.cpp

utility.o: utility.hpp utility.cpp
	-c utility.cpp

session.o: session.hpp session.cpp
	$(CFLAGS) -c session.cpp

db_con.o: db_con.hpp db_con.cpp
	$(CFLAGS) -c db_con.cpp

channel_master_slave.o: channel_master_slave.hpp channel_master_slave.cpp
	-c channel_master_slave.cpp

thread_slave.o: thread_slave.hpp thread_slave.cpp
	-c thread_slave.cpp

thread_master.o

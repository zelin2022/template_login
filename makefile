CPPFLAGS = g++ -std=c++17
LIBS = -I /usr/local/include/mysql++/ -I /usr/include/mysql/
LINKER = -lmysqlpp -lmysqlclient -pthread
DEBUG = -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic
OBJFILES = template_login.o server.o thread_master.o listener.o channel_master_slave.o thread_slave.o db_con.o session.o utility.o message_body.o message_reader.o message_header.o message_writer.o message_processor.o message_builder.o
TEST = tests/mysqltest/mysql++test_2.o db_con.o

all: $(OBJFILES)
	$(CPPFLAGS) $(OBJFILES) -o login $(LIBS) $(LINKER) $(DEBUG)

clean:
	rm  $(OBJFILES) login


template_login.o: template_login.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c template_login.cpp

message_body.o: lib/message_body.hpp lib/message_body.cpp
	$(CPPFLAGS) $(DEBUG) -c lib/message_body.cpp

message_header.o: lib/message_header.hpp lib/message_header.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/message_header.cpp

message_reader.o: lib/message_reader.hpp lib/message_reader.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/message_reader.cpp

message_processor.o: lib/message_processor.hpp lib/message_processor.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/message_processor.cpp

message_builder.o: lib/message_builder.hpp lib/message_builder.cpp
	$(CPPFLAGS) $(DEBUG) -c lib/message_builder.cpp

message_writer.o: lib/message_writer.hpp lib/message_writer.cpp
	$(CPPFLAGS) $(DEBUG) -c lib/message_writer.cpp

utility.o: lib/utility.hpp lib/utility.cpp
	$(CPPFLAGS) $(DEBUG) -c lib/utility.cpp

session.o: lib/session.hpp lib/session.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/session.cpp

db_con.o: lib/db_con.hpp lib/db_con.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/db_con.cpp

channel_master_slave.o: lib/channel_master_slave.hpp lib/channel_master_slave.cpp
	$(CPPFLAGS) $(DEBUG) -c lib/channel_master_slave.cpp

thread_slave.o: lib/thread_slave.hpp lib/thread_slave.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/thread_slave.cpp

thread_master.o: lib/thread_master.hpp lib/thread_master.cpp
	$(CPPFLAGS) $(DEBUG) -c lib/thread_master.cpp

server.o: lib/server.hpp lib/server.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/server.cpp

listener.o: lib/listener.hpp lib/listener.cpp
	$(CPPFLAGS) $(DEBUG) $(LIBS) -c lib/listener.cpp

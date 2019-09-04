/*
* Filename: macro.h
* Author: Zelin Liu
* Date: 2019/08/14
* Description: macros
* Instruction:
*/
#ifndef _MACRO_H_
#define _MACRO_H_

//  main
#define MAIN_MAX_CIN_BUFFER 1024

// Commands


// class Server
#define SERVER_NUM_THREAD_MAX 100
#define SERVER_NUM_THREAD_MIN 0

// class Thread_slave
#define SLAVE_SOCKET_PER_THREAD_MAX 256
#define SLAVE_POLL_TIMEOUT 0



#define LISTENER_MAX_LISTEN_BACKLOG 128

// session
#define SESSION_STANDARD_MSG_LEN 128
#define SESSION_MSG_INDEX_SIGNUP 0x23
#define SESSION_MSG_INDEX_SIGNIN 0x24

// database

/*
CREATE TABLE users (
     id INT NOT NULL AUTO_INCREMENT,
     name VARCHAR(30) UNIQUE NOT NULL,
     hashed_password VARCHAR(30) NOT NULL,
     user_data VARCHAR(100),
     PRIMARY KEY (id)
);

*/

#define DATABASE_CONNECT_ADDR "tcp://127.0.0.1:3306"
#define DATABASE_CONNECT_USERNAME "root"
#define DATABASE_CONNECT_PASSWORD "root"
#define DATABASE_TARGET_DATABASE "tl_test"



#endif

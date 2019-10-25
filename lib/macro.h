/*
* Filename: macro.h
* Author: Zelin Liu
* Date: 2019/08/14
* Description: macros
* Instruction:
*/
#ifndef _MACRO_H_
#define _MACRO_H_

#include "message_code.h"

//  main
#define MAIN_MAX_CIN_BUFFER 1024

// Commands


// class Server
#define SERVER_NUM_THREAD_MAX 100
#define SERVER_NUM_THREAD_MIN 0

// class Thread_slave
#define SLAVE_SOCKET_PER_THREAD_MAX 256
#define SLAVE_SOCKET_PER_THREAD_MIN 0
#define SLAVE_POLL_TIMEOUT 0



#define LISTENER_MAX_LISTEN_BACKLOG 128

// session

// Message_header
#define MESSAGE_HEADER_LEN 2



#define DATABASE_CONNECT_HOSTNAME "127.0.0.1:3306"
#define DATABASE_CONNECT_USERNAME "root"
#define DATABASE_CONNECT_PASSWORD "root"
#define DATABASE_TARGET_DATABASE "tl_test"


// database

/*
CREATE TABLE user (
     ID INT NOT NULL AUTO_INCREMENT,
     USERNAME VARCHAR(30) UNIQUE NOT NULL,
     PASSWORD VARCHAR(30) NOT NULL,
     DATA VARCHAR(100),
     PRIMARY KEY (id)
);


*/

// to understand what's going on here we need to understand message sturcture
///////////////////////////////////////////
// header  2 bytes
  ///////////////////////////////////////////
  // body
  // message code 2bytes
  ///////////////////////////////////////////
  // Length of username 2 byte
    ///////////////////////////////////////////
    // username n bytes
  // ETX 1 byte
  ///////////////////////////////////////////
  // Length of password 2 byte
    ///////////////////////////////////////////
    // password n bytes
  // ETX 1 byte
///////////////////////////////////////////
// EOT 1 byte
///////////////////////////////////////////


// TLDR for message

// 2 byte for header
// --------------------
// 2 byte for message code
// each field is 2+len+1 bytes
// 1 byte for EOT
// -------------------------


#endif

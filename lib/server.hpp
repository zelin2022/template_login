/*
* Filename: server.hpp
* Author: Zelin Liu
* Date: 2019/08/13
* Description: definition for Server
* Instruction:
*/
#ifndef _SERVER_HPP_
#define _SERVER_HPP_


#include <thread>
#include <memory>
#include <atomic>
#include <vector>

class Thread_master;
class Thread_slave;
class Channel_master_slave;



class Server{
public:
  /*
  * @param hostname server ip
  * @param port server port
  * @param num_thread number of slave threads to launch
  * @param socket_per_thread maximum number of sockets per thread
  */
  Server(std::string t_hostname, std::string t_port, int t_num_thread, int t_socket_per_thread);

  /*
  * @param cmd the command to give
  */
  void give_command(std::string t_cmd);

  /*
  * @return true for server exit, false for not
  */
  bool check_want_exit();
  ~Server();

  void exit();

private:

  void start();


  void create_thread_objs();
  void create_thread_handles();

  // thread objects
  std::vector<std::shared_ptr<Thread_slave>> m_v_slave_thread_object;
  std::shared_ptr<Thread_master> m_master_thread_object;

  // inter-thread communication channel
  std::vector<std::shared_ptr<Channel_master_slave>> m_v_channel_master_slave_list;

  // handle for thread objects
  std::thread m_thread_master_handle;
  std::vector<std::thread> m_thread_slave_handle_list;

  // flags for master thread
  std::shared_ptr<std::atomic<bool>> m_flag_master_should_i_continue_;
  std::shared_ptr<std::atomic<bool>> m_flag_master_thread_wants_to_continue_;

  // flags for slave threads
  std::vector<std::shared_ptr<std::atomic<bool>>> m_v_flag_slave_should_i_continue_;
  std::vector<std::shared_ptr<std::atomic<bool>>> m_v_flag_slave_thread_wants_to_continue_;


  bool m_want_exit;
  std::string m_hostname;
  std::string m_port;
  int m_num_thread;
  int m_socket_per_thread;
};
#endif

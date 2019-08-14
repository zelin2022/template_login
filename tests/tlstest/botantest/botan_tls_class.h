#include <botan/tls_callbacks.h>
#include <botan/tls_server.h>

#include <botan/tls_session_manager.h>
#include <botan/tls_policy.h>
#include <botan/auto_rng.h>
#include <botan/certstor.h>
#include <botan/pk_keys.h>
#include <botan/pkcs8.h>
#include <botan/tls_client.h>
#include <botan/certstor_system.h>



#include <sys/socket.h>
#include <iostream>

#include <memory>


#include <thread>         // std::this_thread::sleep_for
#include <chrono>

/**
* @brief Callbacks invoked by TLS::Channel.
*
* Botan::TLS::Callbacks is an abstract class.
* For improved readability, only the functions that are mandatory
* to implement are listed here. See src/lib/tls/tls_callbacks.h.
*/
class Callbacks : public Botan::TLS::Callbacks
{
private:
  int socket;
public:
  void set_socket(int s){
    this->socket = s;
  }
  void tls_emit_data(const uint8_t data[], size_t size) override
  {
    size_t offset = 0;

    while(size)
    {
      ssize_t sent = ::send(this->socket, data + offset, size, MSG_NOSIGNAL);

      if(sent == -1)
      {
        if(errno == EINTR)
        {
          sent = 0;
        }
        else
        {
          throw std::runtime_error("Socket write failed errno=" + std::to_string(errno));
        }
      }

      if(sent != size){
        printf("WARNING:: ::send() is truncating message       ");
      }
      printf("::send() has sent %d bytes \n", sent);

      offset += sent;
      size -= sent;
      // std::this_thread::sleep_for (std::chrono::milliseconds(500));
    }

    // std::this_thread::sleep_for (std::chrono::milliseconds(500));
  }


  void tls_record_received(uint64_t seq_no, const uint8_t data[], size_t size) override
  {
    // process full TLS record received by tls client, e.g.,
    // by passing it to the application
    char print_buffer[size+1];
    memcpy(print_buffer, data, size);

    print_buffer[size]='\0';
    std::cout<<seq_no<<" "<<data<<std::endl;
  }

  void tls_alert(Botan::TLS::Alert alert) override
  {
    // handle a tls alert received from the tls server
    std::cout << "Alert: " << alert.type_string() << "\n";
  }

  bool tls_session_established(const Botan::TLS::Session& session) override
  {
    // the session with the tls client was established
    // return false to prevent the session from being cached, true to
    // cache the session in the configured session manager
    return false;
  }

  void tls_verify_cert_chain(
          const std::vector<Botan::X509_Certificate>& cert_chain,
          const std::vector<std::shared_ptr<const Botan::OCSP::Response>>& ocsp_responses,
          const std::vector<Botan::Certificate_Store*>& trusted_roots,
          Botan::Usage_Type usage,
          const std::string& hostname,
          const Botan::TLS::Policy& policy) override{

          }
};

/**
* @brief Credentials storage for the tls server.
*
* It returns a certificate and the associated private key to
* authenticate the tls server to the client.
* TLS client authentication is not requested.
* See src/lib/tls/credentials_manager.h.
*/
class Server_Credentials : public Botan::Credentials_Manager
{
public:
  Server_Credentials()
  {
    Botan::AutoSeeded_RNG rng;
    this-> m_key.reset(Botan::PKCS8::load_key(std::string("test21.key"), rng ));

  }

  std::vector<Botan::Certificate_Store*> trusted_certificate_authorities(const std::string& type,const std::string& context) override
  {
    // if client authentication is required, this function
    // shall return a list of certificates of CAs we trust
    // for tls client certificates, otherwise return an empty list
    return std::vector<Botan::Certificate_Store*>();
  }

  std::vector<Botan::X509_Certificate> cert_chain(const std::vector<std::string>& cert_key_types,const std::string& type,const std::string& context) override
  {
    // return the certificate chain being sent to the tls client
    // e.g., the certificate file "botan.randombit.net.crt"
    return { Botan::X509_Certificate(std::string("test211.cert")) };
  }

  Botan::Private_Key* private_key_for(const Botan::X509_Certificate& cert,const std::string& type,const std::string& context) override
  {
    // return the private key associated with the leaf certificate,
    // in this case the one associated with "botan.randombit.net.crt"
    return m_key.get();
  }

private:
  std::unique_ptr<Botan::Private_Key> m_key;
};


/**
* @brief Credentials storage for the tls client.
*
* It returns a list of trusted CA certificates from a local directory.
* TLS client authentication is disabled. See src/lib/tls/credentials_manager.h.
*/
class Client_Credentials : public Botan::Credentials_Manager
{
public:
  Client_Credentials()
  {
    // Here we base trust on the system managed trusted CA list
    m_stores.push_back(new Botan::System_Certificate_Store);
  }

  std::vector<Botan::Certificate_Store*> trusted_certificate_authorities(const std::string& type,const std::string& context) override
  {
    // // return a list of certificates of CAs we trust for tls server certificates
    // // ownership of the pointers remains with Credentials_Manager
    // std::vector<Botan::Certificate_Store*> v;
    //
    // // don't ask for client certs
    // // if(type == "tls-server")
    // // {
    // //   return v;
    // // }
    //
    // for(auto const& cs : m_certstores)
    // {
    //   v.push_back(cs.get());
    // }
    //
    // return v;
    return m_stores;
  }

  std::vector<Botan::X509_Certificate> cert_chain(const std::vector<std::string>& cert_key_types,const std::string& type,const std::string& context) override
  {
    // when using tls client authentication (optional), return
    // a certificate chain being sent to the tls server,
    // else an empty list
    return std::vector<Botan::X509_Certificate>();
  }

  Botan::Private_Key* private_key_for(const Botan::X509_Certificate& cert,const std::string& type,const std::string& context) override
  {
    // when returning a chain in cert_chain(), return the private key
    // associated with the leaf certificate here
    return nullptr;
  }

private:
  std::vector<Botan::Certificate_Store*> m_stores;
};




class My_Test_Policy : public Botan::TLS::BSI_TR_02102_2{
public:
  std::vector<std::string> allowed_signature_methods() const override
  {
    // return std::vector<std::string>({"ECDSA", "RSA", "DSA", "IMPLICIT"});
        return std::vector<std::string>({"RSA", "IMPLICIT"});
  }
private:
};

#include <botan/tls_callbacks.h>
#include <botan/tls_server.h>

#include <botan/tls_session_manager.h>
#include <botan/tls_policy.h>
#include <botan/auto_rng.h>
#include <botan/certstor.h>
#include <botan/pk_keys.h>
#include <botan/pkcs8.h>


#include <sys/socket.h>
#include <iostream>

#include <memory>

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
    // send data to tls client, e.g., using BSD sockets or boost asio
    send(this->socket, data, size, 0);
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
  }

  bool tls_session_established(const Botan::TLS::Session& session) override
  {
    // the session with the tls client was established
    // return false to prevent the session from being cached, true to
    // cache the session in the configured session manager
    return false;
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
    this-> m_key.reset(Botan::PKCS8::load_key(std::string("a.key"), rng));

  }

  std::vector<Botan::Certificate_Store*> trusted_certificate_authorities(
    const std::string& type,
    const std::string& context) override
    {
      // if client authentication is required, this function
      // shall return a list of certificates of CAs we trust
      // for tls client certificates, otherwise return an empty list
      return std::vector<Botan::Certificate_Store*>();
    }

    std::vector<Botan::X509_Certificate> cert_chain(
      const std::vector<std::string>& cert_key_types,
      const std::string& type,
      const std::string& context) override
      {
        // return the certificate chain being sent to the tls client
        // e.g., the certificate file "botan.randombit.net.crt"
        return { Botan::X509_Certificate("server.crt") };
      }

      Botan::Private_Key* private_key_for(const Botan::X509_Certificate& cert,
        const std::string& type,
        const std::string& context) override
        {
          // return the private key associated with the leaf certificate,
          // in this case the one associated with "botan.randombit.net.crt"
          return m_key.get();
        }

      private:
        std::unique_ptr<Botan::Private_Key> m_key;
      };

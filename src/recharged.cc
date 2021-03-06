#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <functional>

#include "uv.h"
#include "parser.h"
#include "runtime.h"
#include "server.h"
#include "queue.h"


#define TCP_SERVER_PORT 5293

using namespace std;
using namespace recharged::internal;

typedef struct {
  uv_write_t request;
  uv_buf_t buf;
} incoming_write_req_t;


static void uv_onCloseCallback(uv_handle_t* handle) {
  free(handle);
}


static void uv_afterWriteCallback(uv_write_t* req, int status) {
  incoming_write_req_t* incoming = reinterpret_cast<incoming_write_req_t*>(req);
  free(incoming);

  uv_close(reinterpret_cast<uv_handle_t*>(req->handle), uv_onCloseCallback);
}


static void uv_AfterShutdownCallback(uv_shutdown_t* req, int status) {
  uv_close(reinterpret_cast<uv_handle_t*>(req->handle), uv_onCloseCallback);
  free(req);
}


static void uv_onReadData(uv_stream_t* handle,
                          ssize_t nread,
                          const uv_buf_t* buf) {
  int result;
  incoming_write_req_t* incoming;
  uv_shutdown_t* req;

  if (nread <= 0 && buf->base != NULL)
   free(buf->base);

  if (nread < 0) {
      req = reinterpret_cast<uv_shutdown_t*>(malloc(sizeof(&req)));
      result = uv_shutdown(req, handle, uv_AfterShutdownCallback);
      return;
  }

  incoming = reinterpret_cast<incoming_write_req_t*>(malloc(sizeof(*incoming)));

  // Depending on the used RESP protocol header choose a different runtime
  string response;
  if (buf->base[0] == '%') {

  } else {
    Runtime* runtime = new Runtime();
    response = runtime->Run(buf->base);
  }

  incoming->buf = uv_buf_init(const_cast<char*>(response.c_str()),
                                                response.length());

  result = uv_write(&incoming->request,
                    handle,
                    &incoming->buf,
                    1,
                    uv_afterWriteCallback);
}


static void uv_allocationCallback(uv_handle_t* handle,
                                  size_t suggested_size,
                                  uv_buf_t* buf) {
  buf->base = reinterpret_cast<char*>(malloc(suggested_size));
  buf->len = suggested_size;
}


static void uv_setupServer(uv_stream_t* server, int status) {
  uv_tcp_t* stream;
  int result;
  stream = reinterpret_cast<uv_tcp_t*>(malloc(sizeof(uv_tcp_t)));
  result = uv_tcp_init(uv_default_loop(), stream);

  stream->data = server;
  result = uv_accept(server, reinterpret_cast<uv_stream_t*>(stream));

  result = uv_read_start(reinterpret_cast<uv_stream_t*>(stream),
                         uv_allocationCallback,
                         uv_onReadData);
}


static void setupServer() {
  struct sockaddr_in address;
  int result;

  // Create the hashmaps for commands as well as queues
  Server::GetInstance().queues = new Mapping<Queue*>();

  Server::GetInstance().cmdMap =
    new Mapping<std::function<std::string(Ast*, uv_buf_t*)> >();

  Server::GetInstance().cmdMap->mapped["QCREATE"] =
    &QueueCommands::QueueCreateCommand;

  Server::GetInstance().startedTime = uv_hrtime();
  Server::GetInstance().totalMemory = uv_get_total_memory();

  result = uv_ip4_addr("0.0.0.0", TCP_SERVER_PORT, &address);

  Server::GetInstance().tcpLoop = reinterpret_cast<uv_tcp_t*>(
                                    malloc(
                                      sizeof(*Server::GetInstance().tcpLoop)));

  result = uv_tcp_init(uv_default_loop(), Server::GetInstance().tcpLoop);

  result = uv_tcp_bind(Server::GetInstance().tcpLoop, (
                       const struct sockaddr*)&address, 0);

  result = uv_listen(
             reinterpret_cast<uv_stream_t*>(Server::GetInstance().tcpLoop),
                                            SOMAXCONN,
                                            uv_setupServer);
}


static void replParser() {
  string input;
  Parser parser = Parser();
  while(1) {
    cout << ">";
    cin >> input;
    input = input.substr(0, input.length());
    input += "\r\n";
    if (input.length() > 0) {
      parser.SetInput(input);
      parser.Parse();
    }
  }
}


static void setupArgs(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {

    // Eval mode to get a "repl like" parser
    if (!strcmp(argv[i], "-e")) {
      replParser();
    } else if (!strcmp(argv[i], "-p")) {
      if (argc + 1 <= argc) {
        Server::GetInstance().port = atoi(argv[i+1]);
      } else {
        Server::GetInstance().port = TCP_SERVER_PORT;
      }
    }
  }
}


int main(int argc, char** argv) {
  int result;

  if (argc > 0) {
    setupArgs(argc, argv);
  }

  uv_setup_args(argc, argv);

  setupServer();

  result = uv_run(uv_default_loop(), UV_RUN_DEFAULT);

  return 0;
}

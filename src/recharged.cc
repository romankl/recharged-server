#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "uv.h"
#include "parser.h"
#include "runtime.h"


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
  incoming_write_req_t* incoming = (incoming_write_req_t*)req;
  free(incoming);

  uv_close((uv_handle_t*)req->handle, uv_onCloseCallback);
}


static void uv_AfterShutdownCallback(uv_shutdown_t* req, int status) {
  uv_close((uv_handle_t*)req->handle, uv_onCloseCallback);
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
      req = (uv_shutdown_t*) malloc(sizeof(*req));
      result = uv_shutdown(req, handle, uv_AfterShutdownCallback);
      return;
  }

  incoming = (incoming_write_req_t*) malloc(sizeof(*incoming));

  Runtime* runtime = new Runtime();
  string response = runtime->Run(buf->base);


  incoming->buf = uv_buf_init((char *)response.c_str(), response.length());

  result = uv_write(&incoming->request,
                    handle,
                    &incoming->buf,
                    1,
                    uv_afterWriteCallback);
}


static void uv_allocationCallback(uv_handle_t* handle,
                                  size_t suggested_size,
                                  uv_buf_t* buf) {
  buf->base = (char *) malloc(suggested_size);
  buf->len = suggested_size;
}


static void uv_setupServer(uv_stream_t* server, int status) {
  uv_tcp_t* stream;
  int result;
  stream = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  result = uv_tcp_init(uv_default_loop(), stream);

  stream->data = server;
  result = uv_accept(server, (uv_stream_t*)stream);

  result = uv_read_start((uv_stream_t*)stream,
                         uv_allocationCallback,
                         uv_onReadData);
}


static void setupServer() {
  struct sockaddr_in address;
  uv_tcp_t* tcpServer;
  int result;

  result = uv_ip4_addr("0.0.0.0", TCP_SERVER_PORT, &address);

  tcpServer = (uv_tcp_t*) malloc(sizeof(*tcpServer));

  result = uv_tcp_init(uv_default_loop(), tcpServer);

  result = uv_tcp_bind(tcpServer, (const struct sockaddr*)&address, 0);

  result = uv_listen((uv_stream_t*)tcpServer,
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
    if (strcmp(argv[i], "-e") == 0) {
      replParser();
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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "uv.h"

// TCP TCP_SERVER_PORT for this server
#define TCP_SERVER_PORT 5293

typedef struct {
  uv_write_t req;
  uv_buf_t buf;
} incoming_write_req_t;


static void on_close(uv_handle_t* handle) {
  free(handle);
}


static void after_write(uv_write_t* req, int status) {
    incoming_write_req_t* incoming = (incoming_write_req_t*)req;

    if (incoming->buf.base != NULL) {
        free(incoming->buf.base);
    }

    free(incoming);

    uv_close((uv_handle_t*)req->handle, on_close);
}


static void after_shutdown(uv_shutdown_t* req, int status) {
  fprintf(stderr, "Transfer completed");
  uv_close((uv_handle_t*)req->handle, on_close);
  free(req);
}


static void on_read_data(uv_stream_t* handle,
                       ssize_t nread,
                       const uv_buf_t* buf) {
    int result;
    incoming_write_req_t* incoming;
    uv_shutdown_t* req;

    if (nread <= 0 && buf->base != NULL)
     free(buf->base);

    if (nread < 0) {
        req = (uv_shutdown_t*) malloc(sizeof(*req));
        result = uv_shutdown(req, handle, after_shutdown);
        return;
    }

    incoming = (incoming_write_req_t*) malloc(sizeof(*incoming));

    incoming->buf = uv_buf_init(buf->base, nread);
    result = uv_write(&incoming->req, handle, &incoming->buf, 1, after_write);
    assert(result == 0);
}

static void alloc_cb(uv_handle_t* handle,
                    size_t suggested_size,
                    uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
}


static void on_connection(uv_stream_t* server, int status) {
    uv_tcp_t* stream;
    int result;
    stream = malloc(sizeof(uv_tcp_t));
    result = uv_tcp_init(uv_default_loop(), stream);
    stream->data = server;
    result = uv_accept(server, (uv_stream_t*)stream);
    result = uv_read_start((uv_stream_t*)stream, alloc_cb, on_read_data);
}


static int init_server() {
    struct sockaddr_in address;
    uv_tcp_t* tcp_server;
    int result;

    result = uv_ip4_addr("0.0.0.0", TCP_SERVER_PORT, &address);
    tcp_server = (uv_tcp_t*) malloc(sizeof(*tcp_server));
    result = uv_tcp_init(uv_default_loop(), tcp_server);
    result = uv_tcp_bind(tcp_server, (const struct sockaddr*)&address, 0);
    result = uv_listen((uv_stream_t*)tcp_server, SOMAXCONN, on_connection);

    return 0;
}


int main() {
    int result;
    result = init_server();

    result = uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    return 0;
}

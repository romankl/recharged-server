#include <stdlib.h>
#include <stdio.h>

#include "uv.h"
#include "error.h"

// TCP TCP_SERVER_PORT for this server
#define TCP_SERVER_PORT 5293

typedef struct {
  uv_write_t request;
  uv_buf_t buf;
} incoming_write_req_t;


static void uv_onCloseCallback(uv_handle_t* handle) {
  free(handle);
}


static void uv_afterWriteCallback(uv_write_t* req, int status) {
    incoming_write_req_t* incoming = (incoming_write_req_t*)req;

    if (incoming->buf.base != NULL) {
        free(incoming->buf.base);
    }

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
        checkForError(result);
        return;
    }

    fprintf(stderr, "Content: %s\n", buf->base);

    incoming = (incoming_write_req_t*) malloc(sizeof(*incoming));

    incoming->buf = uv_buf_init(buf->base, nread);

    result = uv_write(&incoming->request, handle, &incoming->buf, 1, uv_afterWriteCallback);
    checkForError(result);
}

static void uv_allocationCallback(uv_handle_t* handle,
                    size_t suggested_size,
                    uv_buf_t* buf) {
    buf->base = malloc(suggested_size);
    buf->len = suggested_size;
}

static void uv_setupServer(uv_stream_t* server, int status) {
    uv_tcp_t* stream;
    int result;
    stream = malloc(sizeof(uv_tcp_t));
    result = uv_tcp_init(uv_default_loop(), stream);
    checkForError(result);

    stream->data = server;
    result = uv_accept(server, (uv_stream_t*)stream);
    checkForError(result);

    result = uv_read_start((uv_stream_t*)stream, uv_allocationCallback, uv_onReadData);
    checkForError(result);
}


static int setupServer() {
    struct sockaddr_in address;
    uv_tcp_t* tcpServer;
    int result;

    result = uv_ip4_addr("0.0.0.0", TCP_SERVER_PORT, &address);
    checkForError(result);

    tcpServer = (uv_tcp_t*) malloc(sizeof(*tcpServer));

    result = uv_tcp_init(uv_default_loop(), tcpServer);
    checkForError(result);

    result = uv_tcp_bind(tcpServer, (const struct sockaddr*)&address, 0);
    checkForError(result);

    result = uv_listen((uv_stream_t*)tcpServer, SOMAXCONN, uv_setupServer);
    checkForError(result);

    return 0;
}


int main() {
    int result;
    result = setupServer();
    checkForError(result);

    result = uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    checkForError(result);

    return 0;
}

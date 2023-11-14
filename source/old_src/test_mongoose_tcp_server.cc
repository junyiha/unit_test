/**
 * @file test_mongoose_tcp_server.cc
 * @author your name (you@domain.com)
 * @brief tcp 服务器测试 后续在做 参考mongoose的示例 tcp
 * @version 0.1
 * @date 2023-07-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "mongoose.h"
#include <string>
#include <iostream>

// SERVER event handler
static void sfn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  if (ev == MG_EV_OPEN && c->is_listening == 1) {
    MG_INFO(("SERVER is listening"));
  } else if (ev == MG_EV_ACCEPT) {
    MG_INFO(("SERVER accepted a connection"));
#if MG_ENABLE_MBEDTLS || MG_ENABLE_OPENSSL
    struct mg_tls_opts opts = {
        //.ca = "ss_ca.pem",         // Uncomment to enable two-way SSL
        .cert = "ss_server.pem",     // Certificate PEM file
        .certkey = "ss_server.pem",  // This pem contains both cert and key
    };
    mg_tls_init(c, &opts);
    MG_INFO(("SERVER initialized TLS"));
#endif
  } else if (ev == MG_EV_READ) {
    struct mg_iobuf *r = &c->recv;
    MG_INFO(("SERVER got data: %.*s", r->len, r->buf));
    mg_send(c, r->buf, r->len);  // echo it back
    r->len = 0;                  // Tell Mongoose we've consumed data
  } else if (ev == MG_EV_CLOSE) {
    MG_INFO(("SERVER disconnected"));
  } else if (ev == MG_EV_ERROR) {
    MG_INFO(("SERVER error: %s", (char *) ev_data));
  }
  (void) fn_data;
}
static void timer_fn(void *arg) {
  struct mg_mgr *mgr = (struct mg_mgr *) arg;
  if (c_res.c == NULL) {
    // connect
    c_res.i = 0;
    c_res.c = mg_connect(mgr, s_conn, cfn, &c_res);
    if (c_res.c == NULL)
      MG_INFO(("CLIENT cant' open a connection"));
    else
      MG_INFO(("CLIENT is connecting"));
  }
}
int main()
{
    struct mg_mgr mgr; // Event manager
    struct mg_connection *c;

    mg_mgr_init(&mgr);                                                             // Initialize event manager
    mg_timer_add(&mgr, 15000, MG_TIMER_REPEAT | MG_TIMER_RUN_NOW, timer_fn, &mgr); // Init timer for demo purposes, 15s
    c = mg_listen(&mgr, s_lsn, sfn, NULL);                                         // Create server connection
    if (c == NULL)
    {
        MG_INFO(("SERVER cant' open a connection"));
        return 0;
    }
    while (true)
        mg_mgr_poll(&mgr, 100); // Infinite event loop, blocks for upto 100ms
                                // unless there is network activity
    mg_mgr_free(&mgr);          // Free resources
    return 0;
}
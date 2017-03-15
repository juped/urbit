#include <uv.h>
#include "all.h"
#include "vere/vere.h"

/* declare callbacks */
void _ctl_boot_cb(uv_connect_t *conn, int status);
void _ctl_test_cb(uv_connect_t *conn, int status);

/* main(): main() for urbctl
*/
c3_i
main(c3_i argc, c3_c **argv)
{
  void (*dispatch)(uv_connect_t *, int);

  if ( argc < 2 ) {
    fprintf(stderr, "Usage: %s <command> [<args>]\n", argv[0]);
    return 1;
  }

  if ( !strcmp(argv[1], "boot") ) {
    dispatch = _ctl_boot_cb;
  } else if ( !strcmp(argv[1], "test") ) {
    dispatch = _ctl_test_cb;
  } else {
    fprintf(stderr, "Unknown command '%s'\n", argv[1]);
    return 1;
  }

  u3_moor *mor_u = malloc(sizeof(u3_moor));
  uv_connect_t *conn = malloc(sizeof(uv_connect_t));
  conn->data = mor_u;
  uv_pipe_init(uv_default_loop(), &mor_u->pyp_u, 0);
  uv_pipe_connect(conn, &mor_u->pyp_u, "/tmp/urbit.sock", dispatch);

  uv_run(uv_default_loop(), UV_RUN_DEFAULT);
  return 0;
}

void
_ctl_boot_cb(uv_connect_t *conn, int status)
{
  if ( status != 0 ) {
    fprintf(stderr, "test: connection failed\n");
    exit(1);
  }
  exit(0);
}

void
_ctl_test_cb(uv_connect_t *conn, int status)
{
  if ( status != 0 ) {
    fprintf(stderr, "test: connection failed\n");
    exit(1);
  }
  exit(0);
}

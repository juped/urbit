#include <uv.h>
#include "all.h"
#include "vere/vere.h"

int g_argc;
char **g_argv;

/* declare callbacks */
void _ctl_boot_cb(uv_connect_t *conn, int status);
void _ctl_commit_cb(uv_connect_t *conn, int status);
void _ctl_stop_cb(uv_connect_t *conn, int status);
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
  } else if ( !strcmp(argv[1], "commit") ) {
    dispatch = _ctl_commit_cb;
  } else if ( !strcmp(argv[1], "stop") ) {
    dispatch = _ctl_stop_cb;
  } else if ( !strcmp(argv[1], "test") ) {
    dispatch = _ctl_test_cb;
  } else {
    fprintf(stderr, "Unknown command '%s'\n", argv[1]);
    return 1;
  }

  g_argc = argc;
  g_argv = argv;

  u3m_boot_lite(); /* get mini loom, so we can use nouns */

  u3_moor *mor_u = u3a_malloc(sizeof(u3_moor));
  uv_connect_t *conn = u3a_malloc(sizeof(uv_connect_t));
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
    fprintf(stderr, "boot: connection failed\n");
    exit(1);
  }
  if ( g_argc != 4 ) {
    fprintf(stderr, "boot: usage: %s boot [path] [pill]\n", g_argv[0]);
    exit(1);
  }

  u3_mojo *moj_u = conn->data;
  u3_atom doom;
  u3_atom pax, sys;

  pax = u3i_string(g_argv[2]);
  sys = u3i_string(g_argv[3]);

  doom = u3ke_jam(u3nc(c3__doom,
                  u3nc(c3__boot,
                  u3nc(0, /* zod */
                  u3nt(pax, sys, 0)))));
  u3_newt_write(moj_u, doom, 0);
  exit(0);
}

void
_ctl_commit_cb(uv_connect_t *conn, int status)
{
  if ( status != 0 ) {
    fprintf(stderr, "commit: connection failed\n");
    exit(1);
  }
  exit(0);
}

void
_ctl_stop_cb(uv_connect_t *conn, int status)
{
  if ( status != 0 ) {
    fprintf(stderr, "stop: connection failed\n");
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
  fprintf(stderr, "test: success\n");
  exit(0);
}

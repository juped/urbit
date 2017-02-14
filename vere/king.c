#include <uv.h>
#include "all.h"
#include "vere/vere.h"

void _king_loop_init()
{
}

void _king_loop_exit()
{
}

void _king_wyrd(u3_noun mat)
{
  u3_noun pax  = u3k(u3h(mat));
  u3_noun fav  = u3k(u3t(mat));
  u3_pier_plan(pax, fav);
  u3z(mat);
}

void _king_boot(u3_noun req)
{
  u3_noun pax_n, sys_n;
  c3_c *pax_c, *sys_c;

  pax_n = u3k(u3h(req));
  sys_n = u3k(u3t(req));

  pax_c = u3r_string(pax_n);
  u3z(pax_n);
  sys_c = u3r_string(sys_n);
  u3z(sys_n);
  u3z(req);

  fprintf(stderr, "boot %s %s\r\n", pax_c, sys_c);
}

void _king_doom(u3_noun doom)
{
  u3_noun load;
  c3_assert(_(u3a_is_cat(u3h(doom))));
  switch ( u3h(doom) ) {
    case c3__boot:
      load = u3k(u3t(doom));
      u3z(doom);
      _king_boot(load);
      break;
    default:
      exit(1);
  }
}

void _king_fate(void *vod_p, u3_noun mat)
{
  u3_noun fate = u3ke_cue(u3k(mat));
  u3_noun load;
  c3_assert(_(u3a_is_cat(u3h(fate))));
  switch ( u3h(fate) ) {
    case c3__wyrd:
      load = u3k(u3t(fate));
      u3z(fate);
      _king_wyrd(load);
      break;
    case c3__doom:
      load = u3k(u3t(fate));
      u3z(fate);
      _king_doom(load);
      break;
    default:
      exit(1);
  }
}

void _king_bail(void *vod_p, const c3_c *err_c)
{
  fprintf(stderr, "_king_bail: %s\r\n", err_c);
  /* use the vod_p to clean up the moor */
}

void _king_socket_connect(uv_stream_t *sock, int status)
{
  u3_moor *mor_u;
  if ( u3K.cli_u == 0 ) {
    u3K.cli_u = u3a_malloc(sizeof(u3_moor));
    mor_u = u3K.cli_u;
    mor_u->nex_u = 0;
  } else {
    for (mor_u = u3K.cli_u; mor_u->nex_u; mor_u = mor_u->nex_u);
    mor_u->nex_u = u3a_malloc(sizeof(u3_moor));
    mor_u = mor_u->nex_u;
    mor_u->nex_u = 0;
  }

  uv_pipe_init(u3L, &mor_u->pyp_u, 0);
  mor_u->pok_f = _king_fate;
  mor_u->bal_f = _king_bail;

  uv_accept(sock, (uv_stream_t *)&mor_u->pyp_u);
  u3_newt_read((u3_moat *)mor_u);
}

void u3_king_commence()
{
  u3_Host.lup_u = uv_default_loop();

  /* start up a "fast-compile" arvo for internal use only
  */
  u3m_boot_pier();
  {
    extern c3_w u3_Ivory_length_w;
    extern c3_y u3_Ivory_pill_y[];
    u3_noun     lit;

    lit = u3i_bytes(u3_Ivory_length_w, u3_Ivory_pill_y);
    u3v_boot_lite(lit);
  }

  /* listen on command socket */
  uv_pipe_init(u3L, &u3K.cmd_u, 0);
  uv_pipe_bind(&u3K.cmd_u, "/tmp/urbit.sock");
  uv_listen((uv_stream_t *)&u3K.cmd_u, 128, _king_socket_connect);
  fprintf(stderr, "cmd socket up\r\n");

  _king_loop_init();

  uv_run(u3L, UV_RUN_DEFAULT);

  _king_loop_exit();
  exit(0);
}

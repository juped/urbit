#include <stdio.h>
#include <uv.h>
#include "all.h"
#include "vere/vere.h"

u3_mojo moj_u;

void _nop_bail(void *vod_p, const c3_c *err)
{
  fprintf(stderr, "_nop_bail: %s\r\n", err);
  exit(1);
}

c3_i main(c3_i argc, c3_c **argv)
{
  u3_Host.ops_u.dem = c3n;
  u3_Host.lup_u = uv_default_loop();

  moj_u.bal_f = _nop_bail;
  uv_pipe_init(u3_Host.lup_u, &moj_u.pyp_u, 0);
  uv_pipe_open(&moj_u.pyp_u, open("client.sock", O_WRONLY));

  u3m_boot_pier();
  {
    extern c3_w u3_Ivory_length_w;
    extern c3_y u3_Ivory_pill_y[];
    u3_noun     lit;

    lit = u3i_bytes(u3_Ivory_length_w, u3_Ivory_pill_y);
    u3v_boot_lite(lit);
  }

  int i, count;
  struct timeval before, after;

  if (argc == 2) { count = atoi(argv[1]); } else { count = 10; }
  printf("nop: count is %d\n", count);

  gettimeofday(&before, 0);
  printf("nop: start time %f\n",
         (double)before.tv_sec + ((double)before.tv_usec / 1000000));

  for (i = 0; i < count; i++) {
    u3_atom evt_a = u3ke_jam(u3nc(u3nq(u3_blip, c3__term, '1', u3_nul),
                                  u3nc(c3__noop, u3_blip)));
    u3_newt_write(&moj_u, evt_a, 0);
  }

  gettimeofday(&after, 0);
  printf("nop: end time   %f\n",
         (double)after.tv_sec + ((double)after.tv_usec / 1000000));

  return 0;
}

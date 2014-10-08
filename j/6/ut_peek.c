/* j/6/peek.c
**
** This file is in the public domain.
*/
#include "all.h"


/* logic
*/
  u3_noun
  _cqfu_peek(u3_noun, u3_noun, u3_noun, u3_atom);

  static u3_noun
  _peek_in(
           u3_noun van,
           u3_noun sut,
           u3_noun way,
           u3_atom axe,
           u3_noun gil)
  {
    u3_noun p_sut, q_sut;
    u3_noun pro;

    if ( (u3_no == u3du(sut)) ) switch ( sut ) {
      default: return u3_cm_bail(c3__fail);

      case c3__noun: {
        return c3__noun;
      }
      case c3__void: {
        return c3__void;
      }
    }
    else switch ( u3h(sut) ) {
      default: return u3_cm_bail(c3__fail);

      case c3__atom: {
        return c3__void;
      }
      case c3__bull: {
        if ( (u3_no == u3_cr_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3_cm_bail(c3__fail);
        } else {
          return _peek_in(van, q_sut, way, axe, gil);
        }
      }
      case c3__cell: {
        if ( (u3_no == u3_cr_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3_cm_bail(c3__fail);
        } else {
          u3_atom tip = u3_cqc_cap(axe);
          u3_atom tap = u3_cqc_mas(axe);

          if ( 2 == tip ) {
            pro = _cqfu_peek(van, p_sut, way, tap);
          }
          else {
            pro = _cqfu_peek(van, q_sut, way, tap);
          }
          u3z(tap);
          u3z(tip);

          return pro;
        }
      }
      case c3__core: {
        u3_noun pq_sut, qq_sut, rq_sut;
        u3_noun prq_sut, qrq_sut;

        if ( (u3_no == u3_cr_trel(sut, 0, &p_sut, &q_sut)) ||
             (u3_no == u3_cr_trel(q_sut, &pq_sut, &qq_sut, &rq_sut)) ||
             (u3_no == u3_cr_cell(rq_sut, &prq_sut, &qrq_sut)) )
        {
          return u3_cm_bail(c3__fail);
        } else {
          u3_atom tip = u3_cqc_cap(axe);
          u3_atom tap = u3_cqc_mas(axe);

          if ( 3 == tip ) {
            if ( u3_no == u3_cqfu_park(van, sut, way, tap) )
            {
              // u3_noun dun = u3_cqfu_dunq(van, "type", sut);
              u3_noun waz = u3_cqfu_shep
                (van, "axis", 'd', u3k(axe));

              // u3_ct_push(u3nc(c3__mean, dun));
              u3_ct_push(u3nc(c3__mean, waz));

              return u3_cm_error("peek-park");
            }
            else pro = _cqfu_peek(van, p_sut, way, tap);
          }
          else {
            pro = c3__noun;
          }
          u3z(tap);
          u3z(tip);

          return pro;
        }
      }
      case c3__cube: {
        if ( (u3_no == u3_cr_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3_cm_bail(c3__fail);
        } else {
          return _peek_in(van, q_sut, way, axe, gil);
        }
      }
      case c3__face: {
        if ( (u3_no == u3_cr_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3_cm_bail(c3__fail);
        } else {
          return _peek_in(van, q_sut, way, axe, gil);
        }
      }
      case c3__fork: {
        if ( (u3_no == u3_cr_trel(sut, 0, &p_sut, &q_sut)) ) {
          return u3_cm_bail(c3__fail);
        } else {
          u3_noun hed = _peek_in(van, p_sut, way, axe, gil);
          u3_noun tal = _peek_in(van, q_sut, way, axe, gil);

          pro = u3_cqf_fork(hed, tal);

          u3z(hed);
          u3z(tal);

          return pro;
        }
      }
      case c3__hold: {
        p_sut = u3t(sut);
        if ( (u3_yes == u3_cqdi_has(gil, sut)) ) {
          return c3__void;
        }
        else {
          u3_noun zoc = u3_cqdi_put(gil, sut);
          u3_noun fop = u3_cqfu_repo(van, sut);
          u3_noun pro = _peek_in(van, fop, way, axe, zoc);

          u3z(fop);
          u3z(zoc);

          return pro;
        }
      }
    }
  }

  u3_noun
  _cqfu_peek(
                        u3_noun van,
                        u3_noun sut,
                        u3_noun way,
                        u3_atom axe)
  {
    if ( 1 == axe ) {
      return u3k(sut);
    }
    else return _peek_in(van, sut, way, axe, u3_nul);
  }

/* boilerplate
*/
  u3_noun
  u3_cwfu_peek(
                       u3_noun cor)
  {
    u3_noun sut, way, axe, van;

    if ( (u3_no == u3_cr_mean(cor, u3_cv_sam_2, &way,
                                u3_cv_sam_3, &axe,
                                u3_cv_con, &van,
                                0)) ||
         (u3_no == u3ud(axe)) ||
         (u3_none == (sut = u3_cr_at(u3_cv_sam, van))) )
    {
      return u3_cm_bail(c3__fail);
    } else {
      return _cqfu_peek(van, sut, way, axe);
    }
  }

  u3_noun
  u3_cqfu_peek(u3_noun van,
                        u3_noun sut,
                        u3_noun way,
                        u3_noun axe)
  {
    c3_m    fun_m = c3__peek;
    u3_noun pro   = u3_cz_find_3(fun_m, sut, way, axe);

    if ( u3_none != pro ) {
      return pro;
    }
    else {
      pro = _cqfu_peek(van, sut, way, axe);

      return u3_cz_save_3(fun_m, sut, way, axe, pro);
    }
  }
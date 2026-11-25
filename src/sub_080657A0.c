/* Per-frame camera/scroll update for an entity: skip when a special camera mode
 * owns the position, otherwise reset and constrain the scroll position, post an
 * idle effect, fire a state effect when the position state is 4, then post and
 * fire a second effect based on a computed effect kind before the final camera
 * update. */
extern s32 D_08671BD8;
s32 sub_0806C4B4(void *, void *);
void sub_0806C5EC(void *, void *, void *, void *);
void sub_0806A884(void *, void *);
s32 sub_08003740(void *, void *);
void sub_0806A800(void *, s32);
u16 sub_0806BCD8(void *, void *, void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
void sub_080C31E8(void *, void *, s32, s32);
void sub_080657A0(u8 *entity)
{
  u16 *pState;
  u8 *cam;
  u8 *pos;
  u8 *view;
  s32 mode;
  cam = *((u8 **) (entity + 0x6C));
 do { pos = cam + 4; } while (0);
  view = *((u8 **) (entity + 0x38));
  mode = sub_0806C4B4(pos, pos);
  if (mode == 0)
  {
    u8 *timer;
    sub_0806C5EC(entity, view, pos, pos);
    sub_0806A884(view, pos);
    timer = cam + 0x2C;
    sub_08003740(timer, view);
    if ((*(pState = (u16 *) (pos + 0x2C))) == 4)
    {
      sub_0806A800(pos, 0x10);
      *((s32 *) (pos + 0x5C)) = 0x15;
      *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x17)) = mode;
      {
        s32 *effectData = &D_08671BD8;
        sub_080C31E8(entity + 0x18, entity + 0x22, 3, *effectData);
      }
    }
    {
      s32 effectKind;
      effectKind = sub_0806BCD8(entity, view, pos, pos);
      view++;
      view--;
      cam += 0xC8;
      *((u32 *) cam) = (u16)effectKind;
      if ((u16)effectKind != 0)
      {
        sub_08003740(timer, view);
        *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x17)) = mode;
        {
          s32 *effectData = &D_08671BD8;
          sub_080C31E8(entity + 0x18, entity + 0x22, *((u32 *) cam), *effectData);
        }
      }
    }
    sub_0806C6B0(entity, view, pos, pos);
  }
}

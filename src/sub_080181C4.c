void sub_080C31E4(void *, void *, void *);
void sub_080C31E8(void *, void *, void *, void *);
void sub_08017C38(void *arg0);
/* Advance the actor's model animation to frame 0xB; when its restart flag is
   set, clear the current step's byte at +0x17 and run the 0x08671BD8 handler
   in mode 1. */
void sub_080181C4(void *arg0)
{
  u8 *obj = arg0;
  void **handlerTable;
  u32 model = *((u32 *) (obj + 0x38));
  int mode;
  u8 *anim = *((u8 **) (obj + 0x3C));
  u8 *animFlags = anim + 0x34;
 mode = 0; sub_08011368(model, animFlags, 0xB, mode); if ((*((u8 *) animFlags)) & 2) {
    ((u8 *) (obj + ((*((s16 *) (obj + 0x22))) * 2)))[0x17] = 0;
    handlerTable = (void **) 0x08671BD8;
    sub_080C31E8(obj + 0x18, obj + 0x22, (void *) 1, *handlerTable);
  }
}

void sub_08017E54(void *arg0);

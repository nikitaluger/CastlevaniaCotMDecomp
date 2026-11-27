void sub_080BB984(void *, void *);
void sub_080BBA08(void *);
void sub_080C31E4(void *, void *, s32);

void sub_080BA79C(void *arg0) {
  u8 *actor = (u8 *)arg0;
  void *work = *(void **)(actor + 0x3C);
  s32 *advanceCb;
  sub_080BB984(work, (u8 *)work + 0x48);
  sub_080BBA08(arg0);
  if (*(u8 *)(actor + (*(s16 *)(actor + 0x22)) * 2 + 0x19) == 0x18) {
    *(u8 *)(actor + (*(s16 *)(actor + 0x22)) * 2 + 0x19) = 0;
    advanceCb = (s32 *)0x08671BB0;
    sub_080C31E4(actor + 0x18, actor + 0x22, *advanceCb);
  }
}

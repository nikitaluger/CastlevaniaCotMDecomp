s32 sub_08007EA8(u16);
void setAnimationFrame(void *, void *, s16, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);
extern s16 D_0810043C[];
extern void *D_08671BD0;

/* Set the entity's animation frame from a table, then on a condition copy a
 * field over; either way clear the script step byte, post a message, advance
 * the step and dispatch its handler. */
void sub_08090854(void *entity) {
  u8 *self = (u8 *)entity;
  void *sprite = *((void **) (self + 0x38));
  u8 *work = *((u8 **) (self + 0x3C));
  u8 *animTrack = work + 0x34;
  u8 *part = work + 0x48;
  s32 stepOffset;

  setAnimationFrame(sprite, animTrack, D_0810043C[*((s32 *) (work + 0x48))], 1);
  if (sub_08007EA8(*((u16 *) ((*((u8 **) (part + 0x14))) + 4))))
  {
    void **handlerPtr;
    *((u32 *) (work + 0x0C)) = *((u32 *) (part + 0x0C));
    *((u8 *) ((u32)(*((s16 *) (self + 0x22))) * 2 + (u32)entity + 0x19)) = 0;
    handlerPtr = &D_08671BD0;
    sub_080C31E8(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, 3, *handlerPtr);
    (*(u8 *)(self + 0x19 + (*(s16 *)(self + 0x22) * 2)))++;
    stepOffset = (*((s16 *) (self + 0x22))) * 2;
    work = ((u8 *) entity) + 0x18;
    work += stepOffset;
    sub_080C31E0((u8 *) entity, *((void **) (((*((u8 *) work)) * 4) + (*((u32 *) (((u8 *) entity) + 0x14))))));
  }
  else
  {
    void **handlerPtr;
    *((u8 *) ((u32)(*((s16 *) (self + 0x22))) * 2 + (u32)entity + 0x19)) = 0;
    handlerPtr = &D_08671BD0;
    sub_080C31E8(((u8 *) entity) + 0x18, ((u8 *) entity) + 0x22, 1, *handlerPtr);
    (*(u8 *)(self + 0x19 + (*(s16 *)(self + 0x22) * 2)))++;
    stepOffset = (*((s16 *) (self + 0x22))) * 2;
    work = ((u8 *) entity) + 0x18;
    work += stepOffset;
    sub_080C31E0((u8 *) entity, *((void **) (((*((u8 *) work)) * 4) + (*((u32 *) (((u8 *) entity) + 0x14))))));
  }
}

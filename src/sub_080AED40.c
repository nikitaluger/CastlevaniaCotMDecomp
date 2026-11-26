s32 divideInt(s32, s32);
s32 sub_080C31E0(void *, s32);
void sub_08013C8C(void *, void *);

/* Script-step handler: dispatch the current step's callback, advance the
 * script byte, steer the entity toward its target with a scaled speed, and
 * store the resulting heading in the work object. */
void sub_080AED40(void *arg0)
{
  unsigned short unusedWord;
  s32 *speedPtr;
  void *work;
  int stride;
  void *entity;
  s32 heading;
  s32 *speedParamPtr;
  int workOffset;
  int stepDataOffset;
  int nextAction;
  s32 handlerIndex;
  s32 *callbackTable;
  workOffset = 0x38;
  work = *((void **) (((u8 *) arg0) + workOffset));
  entity = *((void **) (((u8 *) arg0) + 0x3C));
  ;
  *((s32 *) (((u8 *) arg0) + 0x14)) = 0x08670218;
  stride = 2;
  *((u16 *) (((u8 *) arg0) + 0x22)) = (*((u16 *) (((u8 *) arg0) + 0x22))) + 1;
  stepDataOffset = 0x18;
  nextAction = (*((((u8 *) arg0) + (((s16) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2)) + 0x19)) + 1;
  *((((u8 *) arg0) + (((s16) (*((s16 *) (((u8 *) arg0) + 0x22)))) * stride)) + 0x19) = nextAction;
  handlerIndex = *((u8 *) ((((s16) (*((s16 *) (((u8 *) arg0) + 0x22)))) * stride) + (((u8 *) arg0) + stepDataOffset)));
  speedParamPtr = (s32 *) (((u8 *) arg0) + 0x4C);
  sub_080C31E0(arg0, *((s32 *) (((u8 *) (*((s32 *) (((u8 *) arg0) + 0x14)))) + (handlerIndex * 4))));
  *((u16 *) (((u8 *) arg0) + 0x22)) = (*((u16 *) (((u8 *) arg0) + 0x22))) - 1;
  speedPtr = speedParamPtr;
  callbackTable = (s32 *) 0x08671BFC;
  *((s32 *) (((u8 *) entity) + 0x08)) = (*speedPtr) + (((*((s32 *) (arg0 + 0x6C))) >> 8) * (sub_080C31E0((*((void **) (((u8 *) arg0) + 0x7C))) + 0x4000, *callbackTable) >> 8));
  *((s32 *) (((u8 *) entity) + 0x0C)) = (*((s32 *) (((u8 *) arg0) + 0x5C))) + (((*((s32 *) (((u8 *) arg0) + 0x6C))) >> 8) * (sub_080C31E0(*((void **) (((u8 *) arg0) + 0x7C)), *callbackTable) >> 8));
  heading = divideInt(0x50000000, *((s32 *) (((u8 *) arg0) + 0x6C)));
  *((u16 *) (((u8 *) work) + 0x06)) = (*((u16 *) (((u8 *) work) + 0x04)) = heading);
  sub_08013C8C(arg0, work);
}

struct S_02025FF0
{
  u8 _0x000[0x1C];
  s32 field1C;
};
extern struct S_02025FF0 gMainWorkspace;
void stepDelayTimer(void *, void *);
void sub_0806D588(void *, void *);
void spawnKind2CEntity(void *, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Motion step: accelerate the Y velocity, move the object by its X velocity,
 * and when it falls past 0x7FFFFF spawn a child effect, latch global state 2,
 * clear this step's action byte and advance the script. Always tick the delay
 * timer and copy the world position into the sprite's screen-space box. */
void sub_08088814(void *self)
{
  void *motion;
  void *pos;
  s8 *yField;
  void *sprite;
  s32 newY;
  s32 *handlerTable;

  motion = *((void **) (((s8 *) self) + 0x6C));
  pos = ((s8 *) motion) + 4;
  sprite = *((void **) (((s8 *) self) + 0x38));
  yField = ((s8 *) pos) + 4;
  *((s32 *) (((s8 *) pos) + 0xC)) = (*((s32 *) (((s8 *) pos) + 0xC))) + 0x1000;
  *((s32 *) (((s8 *) motion) + 4)) = (*((s32 *) (((s8 *) motion) + 4))) + (*((s32 *) (((s8 *) pos) + 8)));
  newY = (*((s32 *) yField)) + (*((s32 *) (((s8 *) pos) + 0xC)));
  *((s32 *) (((s8 *) pos) + 4)) = newY;
  if (newY > 0x7FFFFF)
  {
    spawnKind2CEntity(self, 0x20000004, *((s32 *) (((s8 *) motion) + 4)), newY);
    gMainWorkspace.field1C = 2;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19)) = 0;
    handlerTable = (s32 *)0x08671BB0;
    sub_080C31E4(((s8 *) self) + 0x18, ((s8 *) self) + 0x22, *handlerTable);
  }
  stepDelayTimer(((s8 *) motion) + 0x20, sprite);
  sub_0806D588(sprite, pos);
}

extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u8 D_084A4C84[];
extern u8 D_084A4C98[];
/* These symbols are used only for their addresses: they are byte offsets into
 * D_02025FF0 (0x174C/0x1750/0x18C2/0x14ED) materialised as link-time literals. */
extern u8 D_0000174C[];
extern u8 D_00001750[];
extern u8 D_000018C2[];
extern u8 D_000014ED[];
extern s32 sub_0806D35C(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_08003A6C(void *, s32, void *);

/* Update a timer-driven effect: run the area special-behavior check, handle
 * the 0xA5/0xA8 command bytes, snap the effect's position to the shared
 * target point, convert it to screen space and tick its action timer. */
void sub_08075C44(void *arg0)
{
  void *data = *((void **) (((u8 *) arg0) + 0x6C));
  u8 *buf = ((u8 *) data) + 4;
  u8 *gameState;
  void *obj = *((void **) (((u8 *) arg0) + 0x38));
  void *bufCopy = buf;
  u8 *sys = D_02025368;
  s16 threshold;
  u8 command;
  void *timer;

  if (sub_0806D35C(arg0, obj, buf) != 0)
  {
    return;
  }
  command = *((u8 *) (((u8 *) data) + 0x55));
  switch (command)
  {
    case 0xA5:
      threshold = *((s16 *) (sys + 0x2EA));
      if ((*((s32 *) (((u8 *) buf) + 0x58))) < threshold)
      {
        sub_08003A6C(((u8 *) data) + 0x20, 0, D_084A4C84);
      }
      break;

    case 0xA8:
      if ((*((s32 *) (((u8 *) buf) + 0x54))) < (*((s16 *) (sys + 0x2E2))))
      {
        sub_08003A6C(((u8 *) data) + 0x20, 0, D_084A4C84);
      }
      break;
  }

  gameState = D_02025FF0;
  *((s32 *) bufCopy) = *((s32 *) (((u32) gameState) + ((u32) D_0000174C)));
  *((s32 *) (((u8 *) bufCopy) + 4)) = *((s32 *) (((u32) gameState) + ((u32) D_00001750)));
  sub_0806D588(obj, bufCopy);
  *((s32 *) (((u8 *) buf) + 0x54)) = *((s16 *) (sys + 0x2E2));
  *((s32 *) (((u8 *) buf) + 0x58)) = *((s16 *) (sys + 0x2EA));
  *((u16 *) obj) = *((u16 *) (((u32) gameState) + ((u32) D_000018C2)));
  timer = ((u8 *) buf) + 0x1C;
  if (sub_08003740(timer, obj) == 0)
  {
    sub_08003A6C(timer, 0, D_084A4C98);
  }
  if ((*((u8 *) (((u32) gameState) + ((u32) D_000014ED)))) != (*((u8 *) (((u8 *) buf) + 0x51))))
  {
    ((void (*)(void *)) (*((void **) (((u8 *) arg0) + 0x24))))(arg0);
  }
}

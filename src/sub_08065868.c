extern u32 D_08671BD0[];
extern int sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern int sub_08003740(void *, void *);
extern void sub_08084CBC(void *, void *);
extern void sub_0806A7AC(void *, void *, int);
extern void sub_08005E80(int);
extern void sub_080C31E8(void *, void *, int, u32);
extern void sub_0806D7B4(void *, u32);
extern int sub_0806D2A0(void *, int, int, int);
extern int sub_08065CC8(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void D_0806AB04(void *, void *, void *, void *);

/* Runs an entity's AI state machine: updates its sprite and timer, performs
 * the mode-specific action, then spawns/updates child objects. */
void sub_08065868(void *entity)
{
  u8 *data;
  u8 *ai;
  u8 *actor;
  u8 *sprite;
  u8 *state;
  u8 *timer;
  u32 mode;
  s16 childIndex;
  u8 *child;
  s16 childIndex2;
  u8 *child2;
  u8 *field;
  u32 value;
  int spawned;
  u8 *spawnedFlag;
  s16 childIndex3;
  u8 *child3;
  u32 *tablePtr;
  u8 *childArray;
  u8 *childIndexPtr;
  int rv;
  u16 actionId;
  u32 tableValue;

  data = (u8 *) entity;
  ai = *((u8 **) (data + 0x6C));
  actor = ai + 4;
  sprite = *((u8 **) (data + 0x38));
  state = actor;
  if (sub_0806C4B4(state, state) != 0)
  {
    goto end;
  }
  sub_0806C5EC(data, sprite, state, state);
  timer = ai + 0x2C;
  if (sub_08003740(timer, sprite) != 0)
  {
    goto lbl_E8;
  }
  *((u32 *) (state + 0x48)) = 0;
  sub_08084CBC(data, state);
  mode = *((u32 *) (ai + 0xA0));
  switch (mode)
  {
    case 1:
      if ((*((u32 *) (ai + 0x98))) == 2)
    {
      sub_0806A7AC(sprite, state, 0x2A);
      sub_08003740(timer, sprite);
    }
    else
    {
      sub_0806A7AC(sprite, state, 0x26);
      sub_08003740(timer, sprite);
    }
      sub_08005E80(0x7A);
      childIndex = *((s16 *) (data + 0x22));
      child = (u8 *)((u32)(childIndex * 2) + (u32)data);
      child[0x19] = 0;
      {
        u32 *lit = D_08671BD0;
        sub_080C31E8(data + 0x18, data + 0x22, 0x1A, lit[0]);
      }
      break;

    case 3:
      if ((*((u32 *) (ai + 0x98))) == 2)
    {
      sub_0806A7AC(sprite, state, 0x29);
      sub_08003740(timer, sprite);
    }
    else
    {
      sub_0806A7AC(sprite, state, 0x25);
      sub_08003740(timer, sprite);
    }
      sub_08005E80(0x79);
      *((u32 *) (state + 0x10)) = 0;
      childIndex2 = *((s16 *) (data + 0x22));
      child2 = (u8 *)((u32)(childIndex2 * 2) + (u32)data);
      child2[0x19] = 0;
      {
        u32 *lit = D_08671BD0;
        sub_080C31E8(data + 0x18, data + 0x22, 0x1B, lit[0]);
      }
      break;

    case 2:

    default:
      field = actor;
      field += 0xC0;
      value = *((u32 *) field);
      if (value != 0)
    {
      sub_0806D7B4(state, value << 16);
      spawned = sub_0806D2A0(data, 0x3C, 0x0A, 0x12);
      if (spawned != 0)
      {
        spawnedFlag = ((u8 *) spawned) + 0x7C;
        *((u16 *) spawnedFlag) = 1;
      }
      *((u32 *) field) = 0;
    }
      childIndex3 = *((s16 *) (data + 0x22));
      child3 = (u8 *)((u32)(childIndex3 * 2) + (u32)data);
      child3[0x19] = 0;
      tablePtr = D_08671BD0;
      childArray = data + 0x18;
      childIndexPtr = data + 0x22;
      rv = sub_08065CC8(data, sprite, actor, state);
      actionId = (u16) rv;
      tableValue = tablePtr[0];
      sub_080C31E8(childArray, childIndexPtr, actionId, tableValue);
      break;

  }

  lbl_E8:
  D_0806AB04(data, sprite, actor, state);

  sub_0806A884(sprite, state);
  sub_0806C6B0(data, sprite, actor, state);
  end:
  return;
}

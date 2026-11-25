s32 sub_080141AC(void *, void *);
void sub_08013C5C(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_0801E5FC(void *);
void sub_08013AC4(void *);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, u32);
s32 sub_08013B5C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);
void sub_08013C8C(void *, void *);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_0866D748[];
extern u32 D_08671BDC[];

/*
 * Per-frame update for a player-controlled actor: evaluate its ground contact,
 * handle reaction/attack states, dispatch its script, refresh the sprite pose
 * and place it in the world relative to the camera position.
 */
void sub_0801DE04(u8 *actor)
{
  u8 *sprite;
  u8 *player;
  u8 *animState;
  u8 *extra;
  u8 *coordTable;
  u8 *camIndexPtr;
  u32 tableIndex;
  u32 camOffset;
  u32 grounded;
  u8 scriptByte;
  u8 *scriptPtr;
  s32 scriptIdx;
  s32 zero;
  sprite = *((u8 **) (actor + 0x38));
  player = *((u8 **) (actor + 0x3C));
  animState = player + 0x34;
  extra = player + 0x48;
  if (sub_080141AC(sprite, player) == 1)
  {
    *((u16 *) (extra + 0x0A)) = 0;
  }
  else
  {
    *((u16 *) (extra + 0x0A)) = 1;
  }
  zero = 0;
  *((u32 *) (extra + 0x00)) = zero;
  grounded = *((s16 *) (extra + 0x0A));
  if (grounded == ((unsigned short) 1))
  {
    sub_08013C5C(actor, sprite);
    if (sub_08013558(sprite, player, *((void **) (player + 0x28))) != 0)
    {
      sub_08013978(actor, *((void **) (player + 0x28)));
    }
    sub_080142C0(actor, *((void **) (player + 0x28)));
    grounded = grounded & (*((u16 *) player));
    if (grounded && ((*((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x1A))) != 4))
    {
      u32 *scriptTable;
      sub_0801E5FC(actor);
      sub_08013AC4(actor);
      sub_08005E80(0x85);
      *((u8 *) (((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor)) + 0x1B)) = zero;
      scriptTable = D_08671BDC;
      sub_080C31E8(actor + 0x18, actor + 0x22, 4, *scriptTable);
    }
    if ((*((u16 *) player)) & 0x0C)
    {
      sub_0801E5FC(actor);
    }
  }
  if (sub_08013B5C(sprite, player) == 0)
  {
    u8 *p2;
    *((u32 *) (actor + 0x14)) = (u32) D_0866D748;
    *((u16 *) (actor + 0x22)) = (*((u16 *) (actor + 0x22))) + 1;
    p2 = (u8 *) ((((u32) (*((s16 *) (actor + 0x22)))) * 2) + ((u32) actor));
    *((u8 *) (p2 + 0x19)) = (*((u8 *) (p2 + 0x19))) + 1;
    scriptIdx = (*((s16 *) (actor + 0x22))) * 2;
    scriptPtr = actor;
    scriptPtr += 0x18;
    scriptByte = *((u8 *) (((u32) scriptPtr) + ((u32) scriptIdx)));
    sub_080C31E0((s32) actor, *((u32 *) ((*((u32 *) (actor + 0x14))) + (scriptByte * 4))));
    *((u16 *) (actor + 0x22)) = (*((u16 *) (actor + 0x22))) - 1;
    if (((*((u16 *) (actor + 2))) & 0x8000) == 0)
    {
      sub_080113A8(sprite, animState);
      sub_0801165C(player, 0);
    }
    else
    {
      return;
    }
  }
  sub_08013C8C(actor, sprite);
  {
    s32 worldPos = (*((s32 *) (player + 0x0C))) + (*((s32 *) (extra + 0x00)));
    coordTable = D_02021E90;
    camIndexPtr = D_02025FF0;
    camIndexPtr += 0x18A8;
    tableIndex = (((u32) (*camIndexPtr)) + 1) * 0x40;
    coordTable += 0x127C;
    camOffset = *((u32 *) (coordTable + tableIndex));
    *((u32 *) (sprite + 0x18)) = worldPos - ((camOffset + 0xFFFF8000) & 0xFFFF0000);
  }
}

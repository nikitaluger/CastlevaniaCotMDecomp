extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *a);
extern s16 scalePercentSaturate16(u16, s32);
extern void sub_08003A6C(void *a, s32 b, void *c);
extern void setDirectionVector(void *a, u8 b);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, void *c);
extern void sub_0808449C(void);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];

/* Piece of a sprite group: the 0x80-byte flag in `flags` marks the slot as
 * allocated in the pool that allocEffectPart hands out. */
struct SpritePart
{
  u8 flags;
  u8 variant;
  u8 unk02;
  u8 unk03;
  u16 tile;
  u16 width;
  u16 height;
  u16 unk0A;
  u16 unk0C;
  u16 anim;
  u32 owner;
  u8 _14[2];
  u16 unk16;
  u16 unk18;
};

/* The entity's sprite: scale in 8.8 fixed point plus a pointer to its
 * animation data. */
struct Sprite
{
  u8 _0[4];
  u16 scaleX;
  u16 scaleY;
  u16 unk08;
  u8 _a[0x1A];
  u32 animData;
};

/* Set up a sprite group for the entity: take a part from the sprite-part pool,
 * configure its tile, size and animation (bailing out through sub_0806D2D0 when
 * the pool is full), save the entity's current handler in the group, install
 * sub_0808449C instead, hook up the sprite's animation data, then run the
 * group's script commands. */
void sub_08077B9C(u8 *entity)
{
  u8 *group = *((u8 **) (entity + 0x6C));
  u8 *record = group + 4;
  struct Sprite *sprite = *((struct Sprite **) (entity + 0x38));
  u8 *params = gGameStatus;
  struct SpritePart *part = allocEffectPart();
  u8 *game;
  u32 zero;
  u8 *script;
  s32 *cmdTable;
  *((struct SpritePart **) (record + 0x2C)) = part;
  if (part == 0)
  {
    sub_0806D2D0(entity);
    return;
  }
  zero = 0;
  *((u32 *) (record + 0x30)) = zero;
  *((u32 *) (record + 0x34)) = zero;
  *((u32 *) (record + 0x38)) = zero;
  *((u32 *) (record + 0x3C)) = zero;
  game = gMainWorkspace;
  part->variant = game[0x1510] & 1;
  (*((struct SpritePart **) (record + 0x2C)))->unk02 = 2;
  (*((struct SpritePart **) (record + 0x2C)))->unk03 = 8;
  (*((struct SpritePart **) (record + 0x2C)))->tile = params[0x304];
  (*((struct SpritePart **) (record + 0x2C)))->width = 8;
  (*((struct SpritePart **) (record + 0x2C)))->height = 8;
  (*((struct SpritePart **) (record + 0x2C)))->unk0A = zero;
  (*((struct SpritePart **) (record + 0x2C)))->unk0C = zero;
  (*((struct SpritePart **) (record + 0x2C)))->anim = scalePercentSaturate16(*((u16 *) (params + 0x2E2)), 0x8D);
  (*((struct SpritePart **) (record + 0x2C)))->unk16 = 0x1E;
  (*((struct SpritePart **) (record + 0x2C)))->unk18 = 0x51;
  (*((struct SpritePart **) (record + 0x2C)))->owner = (u32) sprite;
  *((u32 *) (record + 0x18)) = *((u32 *) (entity + 0x24));
  *((u32 *) (entity + 0x24)) = (u32) sub_0808449C;
  sprite->scaleX = 0x100;
  sprite->scaleY = 0x100;
  sprite->unk08 = zero;
  sprite->animData = 0x084D7EF4;
  sub_08003A6C(group + 0x20, 0, (void *) 0x084D80FC);
  *((u32 *) (group + 4)) = *((u32 *) (game + 0x174C));
  *((u32 *) (record + 4)) = *((u32 *) (game + 0x1750));
  *((u32 *) (record + 0x40)) = 0x50000;
  {
    u32 v = *((u32 *) (entity + 0x7C));
    u8 *dst = group + 0x48;
    *dst = v;
    setDirectionVector(record, *dst);
  }
  *((u32 *) (record + 0x48)) = 0x18;
  *(((u8 *) ((((s16) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity))) + 0x19) = 0;
  cmdTable = (s32 *) 0x08671BB0;
  script = entity + 0x18;
  sub_080C31E4(script, entity + 0x22, (void *) (*cmdTable));
  {
    u8 *p = (u8 *) ((((s16) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    p[0x19]++;
  }
  {
    u8 *p = script + (((s16) (*((s16 *) (entity + 0x22)))) * 2);
    sub_080C31E0(entity, *((void **) ((*((u32 *) (entity + 0x14))) + ((*p) * 4))));
  }
}

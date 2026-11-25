/* Per-frame update for a multi-part (composite) enemy: refreshes every sprite
 * part's damage/display state, uploads pending part graphics, then either runs
 * the death sequence (state +1) or the hit/collision checks for each part. */
extern void sub_08097F88(s32, void *, void *, void *); /* update one render part */
extern void sub_080142C0(void *, void *);              /* upload part graphics */
extern void sub_08013AC4(void *);                      /* final actor position/score update */
extern void sub_08007E24(s32);                         /* play sound */
extern s32 sub_08013B5C(void *, void *);               /* apply part display state */
extern void sub_0809C618(s32, void *, void *);         /* register part collision */
extern void sub_0809C318(void *, void *, void *, void *, s32); /* collision query */
extern void sub_0809C3F4(void *, void *, void *, void *);      /* collision query */
extern void sub_0809C490(void *, void *, void *, void *);      /* collision query */
extern void sub_08098338(s32, void *);                 /* set sprite flags */
extern void sub_08013C8C(void *, void *);              /* finish part update */
extern void sub_080C31E0(void *, void *);              /* indirect call */
extern void sub_080C31E4(void *, void *, s32);         /* indirect call */

struct Entity
{
  u8 _0[0x22];
  s16 stateIndex;   /* 0x22: state stack index */
};

void sub_08098C90(u8 *entity)
{
  struct Entity *self = (struct Entity *) entity;
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *work = *((u8 **) (entity + 0x3C));      /* composite work block */
  u8 *gfxInit = work + 0x34;
  u8 *parts = work + 0x48;                    /* parts 2/3 and the sub-object */
  int zero;
  s32 zero32;
  u16 tmp;
  tmp = ((*((u16 *) sprite)) & 0xFFF) | (((*((u16 *) (work + 0x22))) + 8) << 12);
  zero32 = 0;
  *((u16 *) sprite) = tmp | zero32;
  sub_08097F88(zero = 0, sprite, work, *((void **) (work + 0x28)));
  sub_08097F88(1, sprite, work, *((void **) ((*((u8 **) ((*((u8 **) (parts + 8))) + 0x3C))) + 0x28)));
  sub_08097F88(1, sprite, work, *((void **) (work + 0x48)));
  sub_08097F88(2, sprite, work, *((void **) (parts + 4)));
  sub_080142C0(entity, *((void **) (work + 0x28)));
  sub_080142C0(entity, *((void **) ((*((u8 **) ((*((u8 **) (parts + 8))) + 0x3C))) + 0x28)));
  sub_080142C0(entity, *((void **) (work + 0x48)));
  sub_080142C0(entity, *((void **) (parts + 4)));
  if ((*((u16 *) (work + zero))) & 1)
  {
    void **stateTable;
    u8 *stateData;
    s32 byteOffset;
    u8 stateId;
    u8 *subWork;
    sub_08013AC4(entity);
    sub_08007E24(0xB3);
    *((u8 *) ((*((u8 **) (work + 0x28))) + 1)) = zero32;
    *((u8 *) ((*((u8 **) (work + 0x48))) + 1)) = zero32;
    *((u8 *) ((*((u8 **) (parts + 4))) + 1)) = zero32;
    subWork = *((u8 **) ((*((u8 **) (parts + 8))) + 0x3C));
    *((u8 *) ((*((u8 **) (subWork + 0x28))) + 1)) = zero32;
    byteOffset = self->stateIndex * 2;
    *((u8 *) ((((u32) byteOffset) + ((u32) self)) + 0x19)) = zero32;
    stateTable = (void **) 0x08671BB0;
    stateData = entity;
    stateData += 0x18;
    sub_080C31E4(stateData, entity + 0x22, (s32) (*stateTable));
    byteOffset = self->stateIndex * 2;
    *((u8 *) ((((u32) byteOffset) + ((u32) self)) + 0x19)) = (*((u8 *) ((((u32) byteOffset) + ((u32) self)) + 0x19))) + 1;
    byteOffset = self->stateIndex * 2;
    stateData += byteOffset;
    stateId = *stateData;
    sub_080C31E0(entity, *((void **) ((stateId * 4) + (*((u32 *) (entity + 0x14))))));
    return;
  }
  if (sub_08013B5C(sprite, work) == zero)
  {
    s32 byteOffset;
    u8 *stateData;
    u8 stateId;
    *((void **) (entity + 0x14)) = (void *) 0x0866FB90;
    self->stateIndex = self->stateIndex + 1;
    byteOffset = self->stateIndex * 2;
    *((u8 *) ((((u32) byteOffset) + ((u32) self)) + 0x19)) = (*((u8 *) ((((u32) byteOffset) + ((u32) self)) + 0x19))) + 1;
    byteOffset = self->stateIndex * 2;
    stateData = entity;
    stateData += 0x18;
    stateData += byteOffset;
    stateId = *stateData;
    sub_080C31E0(entity, *((void **) ((stateId * 4) + (*((u32 *) (entity + 0x14))))));
    self->stateIndex = self->stateIndex - 1;
  }
  sub_0809C618(zero, gfxInit, *((void **) (work + 0x28)));
  sub_0809C618(1, gfxInit, *((void **) (work + 0x48)));
  sub_0809C618(2, gfxInit, *((void **) (parts + 4)));
  sub_0809C318(*((void **) (parts + 8)), sprite, work, gfxInit, *((u16 *) (parts + 0x24)));
  sub_0809C3F4(work + 0x54, sprite, work, gfxInit);
  sub_0809C490(*((void **) (parts + 0x14)), sprite, work, gfxInit);
  sub_08098338(3, sprite);
  sub_08013C8C(entity, sprite);
}

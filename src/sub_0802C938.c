struct OwnerFlags { u8 f0; u8 f1; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; };
struct UpdateObj {
  u8 _0[2];
  u16 f02;
  u8 _4[0x10];
  u32 f14;
  u8 _18[0x0A];
  s16 f22;
  u32 f24;
  u8 _28[0x10];
  u32 f38;
  u32 f3C;
  u8 _40[0x2C];
  u16 f6C;
};
struct Sprite { u8 _0[0x14]; u32 f14; u32 f18; u8 _1C[0xE]; u8 f2A; };
struct Entity {
  u16 f00;
  u16 f02;
  u8 _04[4];
  u32 f08;
  u32 f0C;
  u32 f10;
  u32 f14;
  u8 _18[0x10];
  void *f28;
};

extern void sub_08005E80(s32);              /* play a sound effect */
extern void sub_080113A8(s32, void *);      /* request a frame from frame control */
extern void sub_08011EE8(void *, s32, s32);
extern s32 sub_08013B5C(s32, void *);       /* advance an entity's own AI */
extern s32 sub_08016238(void *);            /* hit-test an object against the global list */
extern void sub_0802CB5C(s32, void *);
extern s32 sub_0805F9B4(s32, s32);          /* entity inside camera bounds? */
extern void sub_080C31E0(void *, void *);   /* cleanup callback */
extern void sub_080C31E8(void *, void *, s32, void *); /* run a script handler */
extern void *D_08671BDC;
extern u8 gCameraState[];                     /* scroll-offset table */
extern struct S_02025FF0 gMainWorkspace;

/* Updates an entity and its sprite: checks collision/death conditions, spawns a death
   effect and runs the step script, then projects the entity into sprite screen space. */
void sub_0802C938(struct UpdateObj *arg0)
{
  struct Sprite *sprite;
  struct Entity *entity;
  u8 *anim;
  u8 *state;
  struct OwnerFlags *owner;
  struct OwnerFlags *owner2;
  s32 zero;
  s32 stepOffset;
  u8 *stepBase;
  u8 byte;
  void **tbl;
  u32 k;
  u8 *scrollTbl;
  u32 scrollX;
  u32 scrollY;

  sprite = (struct Sprite *)arg0->f38;
  entity = (struct Entity *)arg0->f3C;
  anim = ((u8 *)entity) + 0x34;
  state = ((u8 *)entity) + 0x48;
  owner = (struct OwnerFlags *)entity->f28;
  owner->f1 |= 5;
  if (sub_0805F9B4(entity->f08, entity->f0C) == 1) {
    sub_080C31E0(arg0, (void *)arg0->f24);
    return;
  }
  if (sub_08016238(entity->f28) != 0) {
    entity->f00 |= 1;
  }
  owner2 = (struct OwnerFlags *)entity->f28;
  if (((*(u16 *)((u8 *)owner2 + 0x14)) & 1) || (entity->f02 & 0xD)) {
    entity->f00 |= 1;
  }
  if (entity->f00 & 1) {
    owner2->f1 &= 0xFB;
    {
      u8 *q = (u8 *)(((u32)arg0->f22) * 2 + (u32)arg0);
      if (q[0x1A] != 1) {
        zero = 0;
        *(u16 *)state = zero;
        sub_0802CB5C((s32)sprite, entity);
        sub_08005E80(0x18A);
        ((u8 *)(((u32)arg0->f22) * 2 + (u32)arg0))[0x1B] = zero;
        {
          void **fnaddr = &D_08671BDC;
          sub_080C31E8(((u8*)arg0) + 0x18, ((u8*)arg0) + 0x22, 1, *fnaddr);
        }
      }
    }
  }
  if ((sub_08013B5C((s32)sprite, entity) != 0) && (*(s16 *)state != 0)) {
    goto lab_de;
  }
  arg0->f14 = (u32)0x0866DB50;
  arg0->f22 = arg0->f22 + 1;
  {
    u8 *q = (u8 *)(((u32)arg0->f22) * 2 + (u32)arg0);
    q[0x19] = q[0x19] + 1;
  }
  stepOffset = arg0->f22 * 2;
  stepBase = ((u8 *)arg0) + 0x18;
  byte = *(stepBase + stepOffset);
  tbl = *(void **)(&arg0->f14);
  sub_080C31E0(arg0, tbl[byte]);
  arg0->f22 = arg0->f22 - 1;
  if ((arg0->f02 & 0x8000) != 0) {
    goto done;
  }
  sub_080113A8((s32)sprite, anim);
  if (*(s16 *)state == 1) {
    sub_08011EE8(entity, 0x16C1, 0);
  }
lab_de:
  sub_0802CB5C((s32)sprite, entity);
  *(u16 *)((u8 *)entity->f28 + 0x14) = 0;
  k = 0x1278;
  scrollTbl = gCameraState;
  scrollX = *((u32 *)((scrollTbl + k) + ((gMainWorkspace.f18A8 + 1) << 6)));
  scrollX = scrollX + 0x8000;
  scrollX = scrollX & 0xFFFF0000;
  sprite->f14 = entity->f08 - scrollX;
  k = 0x127C;
  scrollY = *((u32 *)((scrollTbl + k) + ((gMainWorkspace.f18A8 + 1) << 6)));
  scrollY = scrollY + 0xFFFF8000;
  scrollY = scrollY & 0xFFFF0000;
  sprite->f18 = entity->f0C - scrollY;
done:
  ;
}

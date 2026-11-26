s32 allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
void sub_08072270(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);
extern u32 gMainObjTimerCallback[];
struct T {
    u16 attr0; u8 pad02[2]; u16 attr1; u16 attr2; u16 attr3;
    u8 pad0A[0x14 - 0x0A]; u32 param0; u32 param1; u32 mode;
    u8 pad20[4]; u32 gfxPtr;
};
struct B19 { u8 pad[0x19]; u8 stateFlag; };

/* Entity setup: checks a spawn condition, allocates and initializes a display object
   with fixed graphics parameters, then runs the entity script and dispatches its handler. */
void sub_08072094(u8 *entity)
{
  void *sprite;
  struct T *spriteData;
  if (allocWorkSlot(entity, 0, 0x38, 3) == 0)
  {
    sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
    return;
  }
  sprite = allocSpriteObject();
  if (sprite == 0)
  {
    sub_08072270(entity);
    return;
  }
  *((void **) (entity + 0x38)) = sprite;
  spriteData = (struct T *)sprite;
  spriteData->mode = 0x80000000;
  {
    spriteData->attr0 = 0x800;
    spriteData->attr1 = 0x300;
    spriteData->attr2 = 0x300;
    spriteData->attr3 = 0;
    spriteData->param0 = 0x780000;
    spriteData->param1 = 0x480000;
    spriteData->gfxPtr = 0x084545A0;
    ((struct B19 *) ((void *) (entity + (*((s16 *) (entity + 0x22)) * 2))) )->stateFlag = 0;
  }
  {
    const u32 *scriptId = (const u32 *) 0x08671BB0;
    void *scriptPtr = entity + 0x18;
    sub_080C31E4(scriptPtr, entity + 0x22, *scriptId);
    *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) += 1;
    scriptPtr = ((u8 *) scriptPtr) + ((*((s16 *) (entity + 0x22))) * 2);
    sub_080C31E0(entity, *((u32 *) ((*((u32 *) (entity + 0x14))) + ((*((u8 *) scriptPtr)) * 4))));
  }
}

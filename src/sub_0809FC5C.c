extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 findKindIndex(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gSpriteAnimDataTable[];

/* Spawn and initialise the sprite for an entity: allocate a sprite slot, pick
 * its kind index and animation table, apply the shared graphics offset, then
 * queue the first script step and dispatch its handler. */
void sub_0809FC5C(void *entity)
{
  void *sprite;
  void *motion;
  void *track;
  s32 kindIndex;
  s32 zero;
  u8 *stepBase;
  void **scriptTable;
  s32 *handlerTable;
  u8 *stepData;

  sprite = allocSpriteObject();
  if (sprite == NULL) {
    sub_080C31E0(entity, *((s32*)(((char*)entity)+0x24)));
    return;
  }
  *((void**)(((char*)entity)+0x38)) = sprite;
  allocWorkSlot(entity, 0, 0x48, 0);
  if ((*((vu32*)(((char*)entity)+0x3C))) == 0) {
    sub_080C31E0(entity, *((s32*)(((char*)entity)+0x24)));
    return;
  }
  *((s32*)(((char*)sprite)+0x1C)) = 0x80000009;
  motion = *((void**)(((char*)entity)+0x3C));
  track = ((char*)motion)+0x34;
  zero = 0;
  *((s16*)(((char*)motion)+0x1C)) = 0x4C;
  kindIndex = findKindIndex();
  *((s16*)(((char*)motion)+0x22)) = (s16)kindIndex;
  if (((s32)(((u32)kindIndex)<<16)) < 0) {
    sub_080C31E0(entity, *((s32*)(((char*)entity)+0x24)));
    return;
  }
  kindIndex = *((s16*)(((char*)motion)+0x22));
  kindIndex <<= 6;
  kindIndex += 0x200;
  kindIndex &= 0xFC0;
  *((u16*)sprite) = (u16)kindIndex;
  *((u16*)sprite) = (u16)(kindIndex | gMainWorkspace.w);
  initSpriteGraphics(sprite, track, (void*)(((s32)(*((s16*)(((char*)motion)+0x1C)))*0xC) + (s32)gSpriteAnimDataTable));
  setAnimationFrame(sprite, track, 0x0B, 0);
  *((u8*)(((char*)sprite)+0x2A)) &= 0xBF;
  *((u8*)(((char*)entity)+0x7C)) = (u8)zero;
  *((u16*)(((char*)entity)+0x02)) |= 0x1000;
  {
    u8 *stepEntry = (u8*)((((s16)(*((s16*)(((char*)entity)+0x22))))*2) + ((u32)entity));
    stepEntry[0x19] = (u8)zero;
  }
  scriptTable = (void**)0x08671BB0;
  stepBase = ((char*)entity)+0x18;
  sub_080C31E4(stepBase, ((char*)entity)+0x22, (s32)(*scriptTable));
  {
    u8 *stepEntry = (u8*)((((s16)(*((s16*)(((char*)entity)+0x22))))*2) + ((u32)entity));
    stepEntry[0x19] = stepEntry[0x19] + 1;
  }
  stepData = stepBase + (((s16)(*((s16*)(((char*)entity)+0x22))))*2);
  {
    u8 stepByte = *stepData;
    handlerTable = *((s32**)(((char*)entity)+0x14));
    sub_080C31E0(entity, handlerTable[stepByte]);
  }
}

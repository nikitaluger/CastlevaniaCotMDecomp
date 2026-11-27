extern u16 gKind66ThreePartAltLayerAttrs[];
/* Spawns the alternate kind-0x66 three-part effect: allocate a sprite and a
 * work block at the object's +0x3C slot, build its graphics and animation,
 * fill a render layer from the kind and attribute tables, then dispatch the
 * current script step. Allocation failures run the saved +0x24 callback. */
struct Kind66AltWorkspace { u8 _0[0x18C2]; u16 gfxFlags; };
struct Kind66AltGfxEntry { u8 _0[0xC]; u16 gfxIndex; u16 palette; u8 _10[0x16]; };
extern struct Kind66AltWorkspace gMainWorkspace;
extern struct Kind66AltGfxEntry gEffectGfxTable[];
extern s32 gMainObjTimerCallbacks;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void initThreePartSpriteGfx(void *, void *, s32, s32);
extern void setObjectAnimation(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern void releaseActorEffectSubObject(void);

void spawnKind66ThreePartEffectAlt(u8 *obj) {
  u8 *spriteObj;
  u8 *work;
  u8 *animData;
  u16 *layerAttrs;
  s32 animSlot;
  s16 kindIndex;
  u8 *layer;
  u8 *scriptSteps;
  u8 *scriptCommand;
  s32 *scriptCallbacks;
  u16 spriteAttr, spriteAttrNew, objAttr, objAttrNew;
  spriteObj = allocSpriteObject();
  if (!spriteObj) goto fail;
  *((void **)(obj + 0x38)) = spriteObj;
  allocWorkSlot(obj, 0, KIND66_ALT_WORK_SLOT_SIZE, 0);
  if ((*((void **)(obj + 0x3C))) == NULL) goto fail;
  *((u32 *)(spriteObj + 0x1C)) = KIND66_ALT_GFX_ID;
  work = *((u8 **)(obj + 0x3C));
  animData = work + 0x34;
  installUpdateHandler(obj, work, releaseActorEffectSubObject);
  *((u16 *)(work + 0x1C)) = KIND66_ALT_KIND;
  animSlot = findKindIndex();
  *((u16 *)(work + 0x22)) = animSlot;
  if (((s32)(animSlot << 16)) < 0) goto fail;
  *((u16 *)spriteObj) |= gMainWorkspace.gfxFlags;
  initThreePartSpriteGfx(spriteObj, animData, 0x50, 3);
  setObjectAnimation(spriteObj, animData, KIND66_ALT_ANIM_FRAME, 0);
  layerAttrs = gKind66ThreePartAltLayerAttrs;
  layer = allocEffectPart();
  *((void **)(work + 0x28)) = layer;
  if (layer != NULL) goto success;
fail:
  sub_080C31E0(obj, *((u32 *)(obj + 0x24)));
  goto done;
success:
  *((u8 *)(layer + 1)) = KIND66_ALT_LAYER_KIND;
  *((u8 *)((*((u8 **)(work + 0x28))) + 2)) = KIND66_ALT_LAYER_INDEX;
  *((u8 *)((*((u8 **)(work + 0x28))) + 3)) = KIND66_ALT_LAYER_PRIORITY;
  kindIndex = *((s16 *)(work + 0x1C));
  *((u16 *)((*((u8 **)(work + 0x28))) + 4)) = gEffectGfxTable[kindIndex].gfxIndex;
  *((u16 *)((*((u8 **)(work + 0x28))) + 6)) = layerAttrs[0];
  *((u16 *)((*((u8 **)(work + 0x28))) + 8)) = layerAttrs[1];
  *((u16 *)((*((u8 **)(work + 0x28))) + 0xA)) = layerAttrs[2];
  *((u16 *)((*((u8 **)(work + 0x28))) + 0xC)) = layerAttrs[3];
  kindIndex = *((s16 *)(work + 0x1C));
  *((u16 *)((*((u8 **)(work + 0x28))) + 0xE)) = gEffectGfxTable[kindIndex].palette;
  do {
    *((void **)((*((u8 **)(work + 0x28))) + 0x10)) = spriteObj;
    spriteAttr = *((u16 *)(spriteObj + 2));
    spriteAttrNew = spriteAttr | KIND66_ALT_SPRITE_ATTR;
    *((u16 *)(spriteObj + 2)) = spriteAttrNew;
  } while (0);
  do {
    objAttr = *((u16 *)(obj + 2));
    objAttrNew = objAttr | KIND66_ALT_READY_FLAG;
    *((u16 *)(obj + 2)) = objAttrNew;
  } while (0);
  *((u8 *)((obj + (((u32)(*((s16 *)(obj + 0x22)))) * 2)) + 0x19)) = 0;
  scriptCallbacks = &gMainObjTimerCallbacks;
  scriptSteps = obj + 0x18;
  sub_080C31E4(scriptSteps, obj + 0x22, *scriptCallbacks);
  *((u8 *)((obj + (((u32)(*((s16 *)(obj + 0x22)))) * 2)) + 0x19)) += 1;
  scriptCommand = scriptSteps + (((u32)(*((s16 *)(obj + 0x22)))) * 2);
  sub_080C31E0(obj, *((u32 *)((*((u32 *)(obj + 0x14))) + ((*((u8 *)scriptCommand)) * 4))));
done:
  return;
}

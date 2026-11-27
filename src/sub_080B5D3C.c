struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
struct S_080CBDD0 { u8 _0[0xC]; u16 a; u16 b; u8 _10[0x16]; };
extern struct S_02025FF0 gMainWorkspace;
extern struct S_080CBDD0 gEffectGfxTable[];
extern u16 D_08102CD4[];
extern s32 gScriptStepCallbackTable;
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

/* Effect spawner: allocate a sprite, bind it to this object's work data and
 * animation, spawn a child effect, copy parameters out of the gEffectGfxTable and
 * D_08102CD4 tables, set display flags, then dispatch the current command-
 * script step; on any allocation failure fall back to the object's default
 * handler at +0x24. */
void sub_080B5D3C(u8 *obj) {
  u8 *sprite;
  u8 *body;
  u8 *anim;
  u16 *values;
  s32 counter;
  s16 index;
  u8 *child;
  u8 *script;
  u8 *entry;
  s32 *func;
  u16 spriteAttr, spriteAttrNew, objAttr, objAttrNew;
  sprite = allocSpriteObject();
  if (!sprite) goto fail;
  *((void **)(obj + 0x38)) = sprite;
  allocWorkSlot(obj, 0, 0x48, 0);
  if ((*((void **)(obj + 0x3C))) == NULL) goto fail;
  *((u32 *)(sprite + 0x1C)) = 0x8000000B;
  body = *((u8 **)(obj + 0x3C));
  anim = body + 0x34;
  installUpdateHandler(obj, body, releaseActorEffectSubObject);
  *((u16 *)(body + 0x1C)) = 0x66;
  counter = findKindIndex();
  *((u16 *)(body + 0x22)) = counter;
  if (((s32)(counter << 16)) < 0) goto fail;
  *((u16 *)sprite) |= gMainWorkspace.w;
  initThreePartSpriteGfx(sprite, anim, 0x50, 3);
  setObjectAnimation(sprite, anim, 0x6A, 0);
  values = D_08102CD4;
  child = allocEffectPart();
  *((void **)(body + 0x28)) = child;
  if (child != NULL) goto success;
fail:
  sub_080C31E0(obj, *((u32 *)(obj + 0x24)));
  goto done;
success:
  *((u8 *)(child + 1)) = 1;
  *((u8 *)((*((u8 **)(body + 0x28))) + 2)) = 8;
  *((u8 *)((*((u8 **)(body + 0x28))) + 3)) = 1;
  index = *((s16 *)(body + 0x1C));
  *((u16 *)((*((u8 **)(body + 0x28))) + 4)) = gEffectGfxTable[index].a;
  *((u16 *)((*((u8 **)(body + 0x28))) + 6)) = values[0];
  *((u16 *)((*((u8 **)(body + 0x28))) + 8)) = values[1];
  *((u16 *)((*((u8 **)(body + 0x28))) + 0xA)) = values[2];
  *((u16 *)((*((u8 **)(body + 0x28))) + 0xC)) = values[3];
  index = *((s16 *)(body + 0x1C));
  *((u16 *)((*((u8 **)(body + 0x28))) + 0xE)) = gEffectGfxTable[index].b;
  do {
    *((void **)((*((u8 **)(body + 0x28))) + 0x10)) = sprite;
    spriteAttr = *((u16 *)(sprite + 2));
    spriteAttrNew = spriteAttr | 0x400;
    *((u16 *)(sprite + 2)) = spriteAttrNew;
  } while (0);
  do {
    objAttr = *((u16 *)(obj + 2));
    objAttrNew = objAttr | 0x1000;
    *((u16 *)(obj + 2)) = objAttrNew;
  } while (0);
  *((u8 *)((obj + (((u32)(*((s16 *)(obj + 0x22)))) * 2)) + 0x19)) = 0;
  func = &gScriptStepCallbackTable;
  script = obj + 0x18;
  sub_080C31E4(script, obj + 0x22, *func);
  *((u8 *)((obj + (((u32)(*((s16 *)(obj + 0x22)))) * 2)) + 0x19)) += 1;
  entry = script + (((u32)(*((s16 *)(obj + 0x22)))) * 2);
  sub_080C31E0(obj, *((u32 *)((*((u32 *)(obj + 0x14))) + ((*((u8 *)entry)) * 4))));
done:
  return;
}

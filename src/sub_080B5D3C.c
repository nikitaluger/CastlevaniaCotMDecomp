struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
struct S_080CBDD0 { u8 _0[0xC]; u16 a; u16 b; u8 _10[0x16]; };
extern struct S_02025FF0 D_02025FF0;
extern struct S_080CBDD0 D_080CBDD0[];
extern u16 D_08102CD4[];
extern s32 D_08671BB0;
extern void *sub_0800355C(void);
extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern s32 sub_08013C2C(void);
extern void sub_080B710C(void *, void *, s32, s32);
extern void sub_080114DC(void *, void *, s32, s32);
extern void *sub_08016190(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097D90(void);

/* Effect spawner: allocate a sprite, bind it to this object's work data and
 * animation, spawn a child effect, copy parameters out of the D_080CBDD0 and
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
  sprite = sub_0800355C();
  if (!sprite) goto fail;
  *((void **)(obj + 0x38)) = sprite;
  sub_0800168C(obj, 0, 0x48, 0);
  if ((*((void **)(obj + 0x3C))) == NULL) goto fail;
  *((u32 *)(sprite + 0x1C)) = 0x8000000B;
  body = *((u8 **)(obj + 0x3C));
  anim = body + 0x34;
  sub_08014288(obj, body, sub_08097D90);
  *((u16 *)(body + 0x1C)) = 0x66;
  counter = sub_08013C2C();
  *((u16 *)(body + 0x22)) = counter;
  if (((s32)(counter << 16)) < 0) goto fail;
  *((u16 *)sprite) |= D_02025FF0.w;
  sub_080B710C(sprite, anim, 0x50, 3);
  sub_080114DC(sprite, anim, 0x6A, 0);
  values = D_08102CD4;
  child = sub_08016190();
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
  *((u16 *)((*((u8 **)(body + 0x28))) + 4)) = D_080CBDD0[index].a;
  *((u16 *)((*((u8 **)(body + 0x28))) + 6)) = values[0];
  *((u16 *)((*((u8 **)(body + 0x28))) + 8)) = values[1];
  *((u16 *)((*((u8 **)(body + 0x28))) + 0xA)) = values[2];
  *((u16 *)((*((u8 **)(body + 0x28))) + 0xC)) = values[3];
  index = *((s16 *)(body + 0x1C));
  *((u16 *)((*((u8 **)(body + 0x28))) + 0xE)) = D_080CBDD0[index].b;
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
  func = &D_08671BB0;
  script = obj + 0x18;
  sub_080C31E4(script, obj + 0x22, *func);
  *((u8 *)((obj + (((u32)(*((s16 *)(obj + 0x22)))) * 2)) + 0x19)) += 1;
  entry = script + (((u32)(*((s16 *)(obj + 0x22)))) * 2);
  sub_080C31E0(obj, *((u32 *)((*((u32 *)(obj + 0x14))) + ((*((u8 *)entry)) * 4))));
done:
  return;
}

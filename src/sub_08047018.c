extern void syncSpriteToWorldPosition(void *, void *);
extern s32 sub_08013B5C(void *, void *);
extern s32 checkActorViewBounds(void *, void *);
extern s32 hitTestEntities(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gScriptEventCallbacks[];
extern u8 D_0866E2F0[];

/* Behaviour-script callback: on a contact request hand control back to the owner;
 * otherwise acquire a nearby target and set the owner's active flag, dispatch a script
 * command, advance to the next command, then copy position offsets onto the target. */
void sub_08047018(u8 *behav) {
  u8 *target;
  u8 *owner;
  u32 *cmdTable;
  u32 newFlags;
  u8 *entry;
  s32 scriptIdx;
  s32 scriptOff;
  u8 *idxPtr;
  s32 cmdOff;
  target = *(u8 **)(behav + 0x38);
  owner = *(u8 **)(behav + 0x3C);
  if (checkActorViewBounds(target, owner) == 1) {
    sub_080C31E0(behav, *(void **)(behav + 0x24));
    return;
  }
  if (hitTestEntities(*(void **)(owner + 0x28)) != 0) {
    newFlags = (u16)(1) | *(u16 *)owner;
    *(u16 *)owner = (u16)newFlags;
  }
  if (*(u16 *)(owner + 2) != 0) {
    newFlags = (u16)(1) | *(u16 *)owner;
    *(u16 *)owner = (u16)newFlags;
  }
  if ((*(u16 *)(*(void **)(owner + 0x28) + 0x14) & 1) != 0) {
    newFlags = (u16)(1) | *(u16 *)owner;
    *(u16 *)owner = (u16)newFlags;
  }
  if (*(u16 *)owner & 1) {
    entry = (u8 *)((u32)(*(s16 *)(behav + 0x22)) * 2 + (u32)behav);
    if (*(u8 *)(entry + 0x1A) != 1) {
      *(u8 *)(entry + 0x1B) = 0;
      cmdTable = gScriptEventCallbacks;
      sub_080C31E8(behav + 0x18, behav + 0x22, 1, *cmdTable);
    }
  }
  if (sub_08013B5C(target, owner) == 0) {
    cmdOff = 0x18;
    *(u32 *)(behav + 0x14) = (u32)D_0866E2F0;
    *(u16 *)(behav + 0x22) += 1;
    idxPtr = behav + 0x22;
    ((u8 *)(behav + (*(s16 *)idxPtr) * 2))[0x19]++;
    scriptIdx = *(s16 *)idxPtr;
    scriptOff = scriptIdx << 1;
    sub_080C31E0(behav, *(void **)(*(u32 *)(behav + 0x14) + *(u8 *)((behav + cmdOff) + scriptOff) * 4));
    *(u16 *)idxPtr -= 1;
  }
  syncSpriteToWorldPosition(behav, target);
}

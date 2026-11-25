extern void sub_08013C8C(void *, void *);
extern s32 sub_08013B5C(void *, void *);
extern s32 sub_08016238(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 D_08671BDC[];
extern u8 D_0866FE98[];

/* Behaviour-script callback: mask the target's state, set the owner's active flag
 * when the world or owner state requests it, clear a child entry and dispatch an
 * effect when active, then advance the script index to invoke one command from the
 * command table before copying position offsets onto the target. */
void sub_080A27E4(u8 *behav) {
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
  *(u16 *)target = *(u16 *)target & 0x0FFF;
  if (sub_08016238(*(void **)(owner + 0x28)) != 0) {
    *(u16 *)owner |= 1;
  }
  if (*(u16 *)(*(void **)(owner + 0x28) + 0x14) & 1) {
    *(u16 *)owner |= 1;
  }
  if (*(u16 *)owner & 1) {
    entry = (u8 *)((u32)(*(s16 *)(behav + 0x22)) * 2 + (u32)behav);
    if (*(u8 *)(entry + 0x1A) != 4) {
      *(u8 *)(entry + 0x1B) = 0;
      cmdTable = D_08671BDC;
      sub_080C31E8(behav + 0x18, behav + 0x22, 4, *cmdTable);
    }
  }
  if (sub_08013B5C(target, owner) == 0) {
    cmdOff = 0x18;
    *(u32 *)(behav + 0x14) = (u32)D_0866FE98;
    *(u16 *)(behav + 0x22) += 1;
    idxPtr = behav + 0x22;
    ((u8 *)(behav + (*(s16 *)idxPtr) * 2))[0x19]++;
    scriptIdx = *(s16 *)idxPtr;
    scriptOff = scriptIdx << 1;
    sub_080C31E0(behav, *(void **)(*(u32 *)(behav + 0x14) + *(u8 *)((behav + cmdOff) + scriptOff) * 4));
    *(u16 *)idxPtr -= 1;
  }
  sub_08013C8C(behav, target);
}

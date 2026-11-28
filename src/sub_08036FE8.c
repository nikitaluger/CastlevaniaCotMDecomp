extern u8 gMainWorkspace[];
extern s32 gMainObjTimerCallbacks;
extern void *spawnBudgetedEffect(s32, s32);
s32 stepAnimationTrack(s32, s32);
s32 addFacingOffsetToX(void *, s32, s32);
void sub_0803B140(u32, void *, void *, void *);
void sub_0803B194(void *);
s32 sub_080C31E4(void *, void *, s32);

/* NPC behaviour callback: reset the owner's anim flags and request a move/anim on the
 * target; when the target matches id 0x49, spawn an attack object (id 0xEB) whose
 * parameter and position offsets are copied from this state. On a flag from the owner,
 * clear the current script state and dispatch the next behaviour command. */
void sub_08036FE8(u8 *behav) {
    u8 *self = behav;
    void *target = *(void **)(self + 0x38);
    void *owner = *(void **)(self + 0x3C);
    u32 ownerInfo = (u32)((u8 *)owner + 0x34);
    u8 *ownerData = (u8 *)owner + 0x48;
    void *proj;
    u8 objParam;
    sub_0803B194((u8 *)owner + 0x54);
    stepAnimationTrack((s32)target, ownerInfo);
    if (*(u16 *)((u8 *)target + 0x28) == 0x49 && *(u8 *)(ownerData + 0x18) == 0) {
        *(u8 *)(ownerData + 0x18) = 1;
        {
            u32 tableBase = (u32)gMainWorkspace;
            u32 objectIdOff = 0x1870;
            proj = spawnBudgetedEffect(*(s32 *)(tableBase + objectIdOff), 0xEB);
        }
        if (proj != 0) {
            objParam = *(u8 *)(self + 0x4C);
            *(u8 *)((u8 *)proj + 0x4C) = objParam;
            *(s32 *)((u8 *)proj + 0x5C) = addFacingOffsetToX(owner, (s32)target, 0xFFD80000);
            *(s32 *)((u8 *)proj + 0x6C) = *(s32 *)((u8 *)owner + 0x0C) + 0xFFE00000;
            if (*(u16 *)((u8 *)target + 2) & 0x10) {
                *(s32 *)((u8 *)proj + 0x7C) = 0x80 << 4;
            } else {
                *(s32 *)((u8 *)proj + 0x7C) = 0xF0 << 7;
            }
        }
    }
    if (*(u8 *)ownerInfo & 2) {
        s16 scriptIdx = *(s16 *)(self + 0x22);
        s32 *callbackTable;
        *(u8 *)(self + scriptIdx * 2 + 0x19) = 0;
        callbackTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callbackTable);
    }
    sub_0803B140(8, target, ownerData + 0x0C, (void *)0x080CEFAA);
}

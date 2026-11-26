struct S_02025FF0b { u8 _0[0x1728]; u32 a; u32 b; };
extern struct S_02025FF0b gMainWorkspace;
extern u8 D_080CF11E[];
extern s16 D_080CF12E[];
extern s32 gMainObjTimerCallback;
s32 sub_08005910(s32, s32);
s32 sub_08011344(s32, s32, s32, s32);
s32 sub_080113A8(s32, s32);
s32 sub_08011EE8(void *, s32, s32);
s32 sub_08014668(s32, s32);
s32 sub_0803B0D8(void *, void *, s32);
s32 sub_0803B0F8(void *, s32, void *, s32);
s32 sub_080C31E4(void *, void *, s32);

/* Behaviour callback: set up the owner's facing from its contact/position state, run
 * the target's movement, and when the owner is in state 3 turn toward the target using
 * the direction tables before dispatching the next script command. */
void sub_08039034(u8 *behav) {
    u8 *self = behav;
    s32 target = *(s32 *)(self + 0x38);
    void *owner = *(void **)(self + 0x3C);
    s32 ownerInfo = (s32)((u8 *)owner + 0x34);
    u8 *ownerData = (u8 *)owner + 0x48;
    s32 dir;
    sub_0803B0D8(owner, ownerData, 0x4000);
    sub_0803B0F8(owner, target, ownerData, (s32)0x080CF114);
    sub_08011EE8(owner, 0x16C1, 0);
    sub_080113A8(target, ownerInfo);
    sub_08014668(target, *(s32 *)((u8 *)owner + 0x10));
    if (*(u8 *)(ownerData + 4) == 3) {
        u8 *flag = *(u8 **)(self + 0x30) + 0x84;
        s32 zero = 0;
        s16 angle;
        s32 scriptIdx;
        s32 *callbackTable;
        *flag = 1;
        dir = sub_08005910((s32)gMainWorkspace.b - *(s32 *)((u8 *)owner + 0x0C),
                           (s32)gMainWorkspace.a - *(s32 *)((u8 *)owner + 8));
        *(u8 *)(ownerData + 0x0C) = D_080CF11E[dir >> 12];
        angle = D_080CF12E[*(u8 *)(ownerData + 0x0C)];
        sub_08011344(target, ownerInfo, angle, 0);
        scriptIdx = *(s16 *)(self + 0x22);
        *(u8 *)(self + scriptIdx * 2 + 0x19) = zero;
        callbackTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callbackTable);
    }
}

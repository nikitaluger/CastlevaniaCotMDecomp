extern void sub_08013C5C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern s32 sub_08013B5C(s32, void *);
extern void sub_080113A8(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *D_08671BDC;
struct B1 { u8 f0; u8 f1; };

/*
 * Companion/attack entity update. arg0 is a manager holding an owner pointer
 * (+0x38) and the entity it drives (+0x3C); the entity's timers live at +0x48.
 * Refreshes animation/state, runs the current pose handler out of the table at
 * 0x0866DC4C, warps the entity to the player and fires the attack routine from
 * D_08671BDC when its flag is set, then handles the off-screen/cleanup paths.
 */
void sub_08030BE0(u8 *arg0) {
    s32 owner = *(s32 *)(arg0 + 0x38);
    u8 *ent = *(u8 **)(arg0 + 0x3C);
    u8 *anim = ent + 0x34;
    u8 *timers = ent + 0x48;
    u8 *subObj = *(u8 **)(timers + 0x14);
    u8 zero = 0;

    subObj[1] = zero;
    if (sub_080141AC(owner, ent) == 1) return;

    sub_08013C5C(arg0, owner);
    if (sub_08013558(owner, ent, *(void **)(ent + 0x28)) != 0) {
        sub_08013978(arg0, *(void **)(ent + 0x28));
    }
    sub_080142C0(arg0, *(void **)(ent + 0x28));
    sub_080142C0(arg0, *(void **)(timers + 0x14));
    if (*(u16 *)ent & 1) {
        u8 *poseSlot = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        if (*(u8 *)(poseSlot + 0x1A) != 2) {
            sub_08013AC4(arg0);
            {
                u8 *poseSlot = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
                *(u8 *)(poseSlot + 0x1B) = zero;
                { void **attackFunc = &D_08671BDC;
                  sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 2, *attackFunc); }
            }
        }
    }
    if (sub_08013B5C(owner, ent) != 0) goto cdc;
    *(u32 *)(arg0 + 0x14) = (u32)0x0866DC4C;
    *(u16 *)(arg0 + 0x22) = (u16)(*(u16 *)(arg0 + 0x22) + 1);
    {
        u8 *poseSlot = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        poseSlot[0x19] = (u8)(poseSlot[0x19] + 1);
    }
    {
        s32 handlerIdx = (*(s16 *)(arg0 + 0x22)) * 2;
        u8 *poseBase = arg0 + 0x18;
        u8 handlerIndex = *(poseBase + handlerIdx);
        void **poseTable = *(void **)(arg0 + 0x14);
        void *handler = poseTable[handlerIndex];
        sub_080C31E0(arg0, handler);
    }
    *(u16 *)(arg0 + 0x22) = (u16)(*(u16 *)(arg0 + 0x22) - 1);
    if ((*(u16 *)(arg0 + 2) & 0x8000) != 0) goto done;
    sub_080113A8(owner, anim);
    sub_08011EE8(ent, 0x16C1, 0);
cdc:
    if ((*(u16 *)ent & 0xC) == 0 && *(u16 *)(owner + 0x28) == 0x17) {
        struct B1 *subObjFlags = (struct B1 *)*(u8 **)(timers + 0x14);
        subObjFlags->f1 |= 1;
    }
    sub_08013C8C(arg0, owner);
done:
    ;
}

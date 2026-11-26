extern s32 sub_080C31E0(void *, s32);
extern void sub_080114A8(void *, void *, s32, s32);
extern void sub_0809C4E0(void *, s32);
extern void sub_0809C744(void);
extern void sub_0808D0A4(s32);
extern void sub_08005E80(s32);
extern s32 sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallback;

/*
 * Finalizes a companion entity: clears its flags and velocity, cancels the
 * callbacks of selected child nodes, marks the owner and children as finished,
 * runs the shared cleanup, then dispatches the current pose handler.
 */
void sub_08098F50(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *owner = *(u8 **)(self + 0x38);
    u8 *ent = *(u8 **)(self + 0x3C);
    void *anim = (void *)(ent + 0x34);
    u8 *timers = ent + 0x48;
    u8 *child;
    u8 *subNode;
    u8 *poseBase = self + 0x18;
    u8 *poseIndexPtr = self + 0x22;
    u32 zero;
    u16 flags;

    flags = (u16)(*(u16 *)(ent + 0x04) & 0xFFFB);
    zero = 0;
    *(u16 *)(ent + 0x04) = flags;
    *(u32 *)(ent + 0x10) = zero;
    *(u32 *)(ent + 0x14) = zero;
    *(u16 *)(timers + 0x24) = zero;

    child = *(u8 **)(self + 0x30);
    while (child != 0) {
        if (*(s16 *)child == 0x17D) {
            sub_080C31E0(child, *(u32 *)(child + 0x24));
        }
        child = *(u8 **)(child + 0x2C);
    }

    *(u8 *)(timers + 0x23) = 0x10;

    *(u16 *)(owner + 0x02) = (u16)(*(u16 *)(owner + 0x02) | 0x0400);

    child = *(u8 **)(self + 0x30);
    while (child != 0) {
        subNode = *(u8 **)(child + 0x38);
        if (subNode != 0) {
            *(u16 *)(subNode + 0x02) = (u16)(*(u16 *)(subNode + 0x02) | 0x0400);
        }
        child = *(u8 **)(child + 0x2C);
    }

    {
        u8 *timerNode = *(u8 **)(timers + 0x18);
        sub_080C31E0(timerNode, *(u32 *)(timerNode + 0x24));
    }
    *(u32 *)(timers + 0x18) = 0;

    sub_0809C744();

    child = *(u8 **)(self + 0x30);
    while (child != 0) {
        if (*(s16 *)child == 0x177) {
            sub_080C31E0(child, *(u32 *)(child + 0x24));
        }
        child = *(u8 **)(child + 0x2C);
    }

    sub_080114A8(owner, anim, 9, 0);
    sub_0809C4E0(*(void **)(timers + 0x08), 1);
    sub_08005E80(0x186);
    sub_0808D0A4(0x0B);

    {
        s16 poseIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + poseIndex * 2 + 0x19) = 0;
    }
    {
        u8 *poseBase = self + 0x18;
        u8 *poseIndexPtr = self + 0x22;
        s32 *handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4(poseBase, poseIndexPtr, *handlerTable);
    }
    {
        s16 poseIndex = *(s16 *)(self + 0x22);
        u8 *counterSlot = (u8 *)(((u32)poseIndex << 1) + (u32)self + 0x19);
        (*counterSlot)++;
    }
    {
        s16 poseIndex = *(s16 *)(self + 0x22);
        u8 *poseBase = self + 0x18;
        u8 *poseSlot = poseBase + poseIndex * 2;
        u8 handlerIndex = *poseSlot;
        u32 tablePtr = *(u32 *)(self + 0x14);
        sub_080C31E0(self, *(u32 *)((u8 *)tablePtr + handlerIndex * 4));
    }
}

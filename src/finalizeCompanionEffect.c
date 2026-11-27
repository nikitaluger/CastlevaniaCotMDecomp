extern s32 _call_via_r1(void *, s32);
extern void forceAnimationFrame(void *, void *, s32, s32);
extern void setEffectBehavior(void *, s32);
extern void loadEffectGfxTile(void);
extern void sub_0808D0A4(s32);
extern void playSound(s32);
extern s32 _call_via_r2(void *, void *, s32);
extern u32 gMainObjTimerCallbacks;

/*
 * Tears down a companion effect: clears its motion and pending-cancel bits,
 * cancels the callbacks of two kinds of child nodes, marks the owner and its
 * children as finished, reloads the graphics tile, restarts the animation and
 * sound, then advances and dispatches the current script step.
 */
void finalizeCompanionEffect(void *arg0)
{
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

    flags = (u16)(*(u16 *)(ent + 0x04) & COMPANION_FINAL_FLAG_MASK);
    zero = 0;
    *(u16 *)(ent + 0x04) = flags;
    *(u32 *)(ent + 0x10) = zero;
    *(u32 *)(ent + 0x14) = zero;
    *(u16 *)(timers + 0x24) = zero;

    child = *(u8 **)(self + 0x30);
    while (child != 0) {
        if (*(s16 *)child == COMPANION_CHILD_CANCEL_A) {
            _call_via_r1(child, *(u32 *)(child + 0x24));
        }
        child = *(u8 **)(child + 0x2C);
    }

    *(u8 *)(timers + 0x23) = COMPANION_FINAL_STATE;

    *(u16 *)(owner + 0x02) = (u16)(*(u16 *)(owner + 0x02) | COMPANION_DONE_FLAG);

    child = *(u8 **)(self + 0x30);
    while (child != 0) {
        subNode = *(u8 **)(child + 0x38);
        if (subNode != 0) {
            *(u16 *)(subNode + 0x02) = (u16)(*(u16 *)(subNode + 0x02) | COMPANION_DONE_FLAG);
        }
        child = *(u8 **)(child + 0x2C);
    }

    {
        u8 *timerNode = *(u8 **)(timers + 0x18);
        _call_via_r1(timerNode, *(u32 *)(timerNode + 0x24));
    }
    *(u32 *)(timers + 0x18) = 0;

    loadEffectGfxTile();

    child = *(u8 **)(self + 0x30);
    while (child != 0) {
        if (*(s16 *)child == COMPANION_CHILD_CANCEL_B) {
            _call_via_r1(child, *(u32 *)(child + 0x24));
        }
        child = *(u8 **)(child + 0x2C);
    }

    forceAnimationFrame(owner, anim, COMPANION_FINAL_FRAME, 0);
    setEffectBehavior(*(void **)(timers + 0x08), COMPANION_FINAL_BEHAVIOR);
    playSound(COMPANION_FINAL_SFX);
    sub_0808D0A4(COMPANION_FINAL_PARAM);

    {
        s16 poseIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + poseIndex * 2 + 0x19) = 0;
    }
    {
        u8 *poseBase = self + 0x18;
        u8 *poseIndexPtr = self + 0x22;
        s32 *handlerTable = (s32 *)0x08671BB0;
        _call_via_r2(poseBase, poseIndexPtr, *handlerTable);
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
        _call_via_r1(self, *(u32 *)((u8 *)tablePtr + handlerIndex * 4));
    }
}

extern s32 syncViewPosition(void *a, void *b);
extern void resetActionResultState(void *a, void *b, void *c, void *d);
extern void sub_0806AB04(void *a, void *b, void *c, void *d);
extern void setEntityForm(void *a, void *b, s32 c);
extern void sub_0806A884(void *a, void *b);
extern s32 stepDelayTimer(void *a, void *b);
extern u16 sub_08065CC8(void *a, void *b, void *c, void *d);
extern u16 sub_0806BCD8(void *a, void *b, void *c, void *d);
extern void sub_0806C6B0(void *a, void *b, void *c, void *d);
extern void _call_via_r3(void *a, void *b, s32 c, s32 d);
extern u8 D_080E03A0[];
extern s32 gMenuScriptCallback;

/* Camera-mode handler for a scripted enemy: mirror its X offset from the
 * per-enemy parameter table according to the target's facing bit, then run the
 * action/timer steps and dispatch the resulting script commands. */
void updateScriptedEnemyWithOffset(u8 *entity) {
    u8 *aiState = *(u8 **)(entity + 0x6C);
    u8 *ai = aiState + 4;
    u8 *target = *(u8 **)(entity + 0x38);
    u8 *work = ai;
    s32 status = syncViewPosition(ai, ai);
    if (status != 0) return;
    resetActionResultState(entity, target, ai, ai);
    if (((*(u16 *)(target + 2)) & 0x10) == 0) {
        u8 *paramTable = D_080E03A0;
        s32 paramIndex = *(s32 *)(work + 0x44);
        s32 entryOffset = paramIndex * 0x58;
        s32 newX;
        paramTable += 0x54;
        newX = *(s32 *)(work + 8) + *(s32 *)(paramTable + entryOffset);
        *(s32 *)(work + 8) = newX;
        if (newX < 0) *(s32 *)(work + 8) = status;
    } else {
        u8 *paramTable = D_080E03A0;
        s32 paramIndex = *(s32 *)(work + 0x44);
        s32 entryOffset = paramIndex * 0x58;
        s32 newX;
        paramTable += 0x54;
        newX = *(s32 *)(work + 8) - *(s32 *)(paramTable + entryOffset);
        *(s32 *)(work + 8) = newX;
        if (newX > 0) *(s32 *)(work + 8) = status;
    }
    sub_0806AB04(entity, target, ai, work);
    status = *(s32 *)(ai + 0x40);
    if (status == 0) {
        s32 *eventTable;
        setEntityForm(target, ai, 0x10);
        *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x17) = (u8)status;
        eventTable = &gMenuScriptCallback;
        _call_via_r3(entity + 0x18, entity + 0x22, 3, *eventTable);
    }
    sub_0806A884(target, work);
    {
        void *timer = ai + 0x28;
        s32 result = stepDelayTimer(timer, target);
        if (result == 0) {
            s32 *eventTable;
            *(s32 *)(work + 8) = result;
            *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x17) = (u8)result;
            eventTable = &gMenuScriptCallback;
            _call_via_r3(entity + 0x18, entity + 0x22, sub_08065CC8(entity, target, ai, work), *eventTable);
        }
        result = sub_0806BCD8(entity, target, ai, work);
        *(u32 *)(ai + 0xC4) = (u16)result;
        if ((u16)result != 0) {
            s32 *eventTable;
            stepDelayTimer(timer, target);
            *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x17) = 0;
            eventTable = &gMenuScriptCallback;
            _call_via_r3(entity + 0x18, entity + 0x22, *(u32 *)(ai + 0xC4), *eventTable);
        }
    }
    sub_0806C6B0(entity, target, ai, work);
}

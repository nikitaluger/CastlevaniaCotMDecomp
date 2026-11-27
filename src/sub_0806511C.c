extern s32 syncViewPosition(void *a, void *b);
extern void resetActionResultState(void *a, void *b, void *c, void *d);
extern void sub_0806AB04(void *a, void *b, void *c, void *d);
extern void sub_0806A7AC(void *a, void *b, s32 c);
extern void sub_0806A884(void *a, void *b);
extern s32 stepDelayTimer(void *a, void *b);
extern u16 sub_08065CC8(void *a, void *b, void *c, void *d);
extern u16 sub_0806BCD8(void *a, void *b, void *c, void *d);
extern void sub_0806C6B0(void *a, void *b, void *c, void *d);
extern void sub_080C31E8(void *a, void *b, s32 c, s32 d);
extern u8 D_080E03A0[];

/* Camera-mode handler: choose a world position for the entity, nudge its X by a
 * mode-table entry, run the position/timer updates and dispatch the resulting
 * script events. */
void sub_0806511C(u8 *entity) {
    u8 *params = *(u8 **)(entity + 0x6C);
    u8 *work = params + 4;
    u8 *target = *(u8 **)(entity + 0x38);
    u8 *pos = work;
    s32 cameraMode = syncViewPosition(work, work);
    if (cameraMode != 0) return;
    resetActionResultState(entity, target, work, work);
    if (((*(u16 *)(target + 2)) & 0x10) == 0) {
        u8 *offsetTable = D_080E03A0;
        s32 entryIndex = *(s32 *)(pos + 0x44);
        s32 byteOffset = entryIndex * 0x58;
        s32 newX;
        offsetTable += 0x54;
        newX = *(s32 *)(pos + 8) + *(s32 *)(offsetTable + byteOffset);
        *(s32 *)(pos + 8) = newX;
        if (newX < 0) *(s32 *)(pos + 8) = cameraMode;
    } else {
        u8 *offsetTable = D_080E03A0;
        s32 entryIndex = *(s32 *)(pos + 0x44);
        s32 byteOffset = entryIndex * 0x58;
        s32 newX;
        offsetTable += 0x54;
        newX = *(s32 *)(pos + 8) - *(s32 *)(offsetTable + byteOffset);
        *(s32 *)(pos + 8) = newX;
        if (newX > 0) *(s32 *)(pos + 8) = cameraMode;
    }
    sub_0806AB04(entity, target, work, pos);
    cameraMode = *(s32 *)(work + 0x40);
    if (cameraMode == 0) {
        s32 *eventTable;
        sub_0806A7AC(target, work, 0x10);
        *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x17) = (u8)cameraMode;
        eventTable = (s32 *)0x08671BD8;
        sub_080C31E8(entity + 0x18, entity + 0x22, 3, *eventTable);
    }
    sub_0806A884(target, pos);
    {
        void *timer = work + 0x28;
        s32 result = stepDelayTimer(timer, target);
        if (result == 0) {
            s32 *eventTable;
            *(s32 *)(pos + 8) = result;
            *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x17) = (u8)result;
            eventTable = (s32 *)0x08671BD8;
            sub_080C31E8(entity + 0x18, entity + 0x22, sub_08065CC8(entity, target, work, pos), *eventTable);
        }
        result = sub_0806BCD8(entity, target, work, pos);
        *(u32 *)(work + 0xC4) = (u16)result;
        if ((u16)result != 0) {
            s32 *eventTable;
            stepDelayTimer(timer, target);
            *(u8 *)(entity + (*(s16 *)(entity + 0x22)) * 2 + 0x17) = 0;
            eventTable = (s32 *)0x08671BD8;
            sub_080C31E8(entity + 0x18, entity + 0x22, *(u32 *)(work + 0xC4), *eventTable);
        }
    }
    sub_0806C6B0(entity, target, work, pos);
}

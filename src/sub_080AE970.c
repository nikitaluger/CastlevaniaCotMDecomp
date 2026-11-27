s32 updateObjectDisplayState(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
s32 sub_080C31E0(s32, s32);

/* When the work state's timed display does not handle this frame, advance the
 * script step. Then position the work relative to the linked object, mirroring
 * its X flip, and apply the camera-relative offset. */
void sub_080AE970(u8 *arg0) {
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *linkedWork = *(u8 **)(*(u8 **)(arg0 + 0x28) + 0x3C);
    s32 actionOffset;
    u8 *actionBase;
    u32 actionId;

    if (updateObjectDisplayState(sprite, work) == 0) {
        u8 *actionPtr;
        *(u32 *)(arg0 + 0x14) = 0x08670200;
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
        actionPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(actionPtr + 0x19) = *(u8 *)(actionPtr + 0x19) + 1;
        actionOffset = *(s16 *)(arg0 + 0x22) * 2;
        actionBase = arg0;
        actionBase += 0x18;
        actionId = *(u8 *)((u32)actionBase + (u32)actionOffset);
        sub_080C31E0((s32)arg0, *(u32 *)(*(u32 *)(arg0 + 0x14) + actionId * 4));
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    }
    {
        s32 linkedX = *(s32 *)(linkedWork + 0x08);
        u8 *linked = *(u8 **)(arg0 + 0x28);
        u32 xFlip = *(u16 *)(*(u8 **)(linked + 0x38) + 2) & 0x10;
        if (xFlip)
            *(s32 *)(work + 0x08) = linkedX + 0x240000;
        else
            *(s32 *)(work + 0x08) = linkedX + (s32)0xFFDC0000;
        *(s32 *)(work + 0x0C) = *(s32 *)(linkedWork + 0x0C) + (s32)0xFFFC0000;
    }
    syncSpriteToWorldPosition(arg0, sprite);
}

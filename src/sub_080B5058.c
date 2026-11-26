void sub_08011528(void *, void *);
void copyPoseAttrs(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Runs the actor controller, maps a code read from a per-frame table to a
 * variant, copies the matching 8-byte parameter block into the sprite, then
 * advances the script step when a controller flag is set. */
void sub_080B5058(void *a0)
{
    u8 *entity = (u8 *)a0;
    s32 variant = 0;
    void *sprite = *(void **)(entity + 0x38);
    u8 *state = *(u8 **)(entity + 0x3C);
    u8 *ctrl = state + 0x34;
    void **frameTablePtr;
    s32 frameIndex;
    u8 frameOffset;
    void *frameTable;
    u8 *entry;
    u32 code;
    s32 *eventPtr;

    sub_08011528(sprite, ctrl);
    frameTablePtr = *(void ***)(ctrl + 0x08);
    frameIndex = *(s16 *)(ctrl + 0x0E);
    frameOffset = *(u8 *)(ctrl + 0x01);
    frameIndex = frameIndex + frameOffset;
    frameTable = *frameTablePtr;
    entry = (u8 *)((s32)(frameIndex * 4) + (s32)frameTable - 4);
    code = *(u16 *)(entry + 2) - 0x5A;
    if (code <= 8) {
        switch (code) {
        case 0:
            variant = 1;
            break;
        case 1:
            variant = 2;
            break;
        case 2:
            variant = 3;
            break;
        case 4:
            variant = 4;
            break;
        case 6:
            variant = 5;
            break;
        case 8:
            variant = 6;
            break;
        }
    }
    copyPoseAttrs(*(void **)(state + 0x28), (void *)(0x08102B84 + variant * 8));
    if (*(u8 *)ctrl & 2) {
        *(u8 *)(entity + 0x4C) = 0;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        eventPtr = (s32 *)0x08671BC0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *eventPtr);
    }
}

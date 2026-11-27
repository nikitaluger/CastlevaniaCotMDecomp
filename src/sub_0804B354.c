extern s32 getSpriteFacingSign(s32);
extern s32 sub_080C31E0(void *, s32);
struct ScriptHolder { u8 pad[0x18]; u8 frameBytes[0x200]; };

/* Run the handler for the current sub-script frame: launch the attached object
 * toward the owner's facing direction, switch to the handler table, bump the
 * frame counter and dispatch the handler for this frame. */
void sub_0804B354(u8 *arg0) {
    void *owner = *(void **)(arg0 + 0x38);
    u8 *attached = *(u8 **)(arg0 + 0x3C);
    u32 *handlerTable;
    u8 handlerIndex;
    s32 frameOffset;
    if (getSpriteFacingSign((s32)owner) > 0)
        *(s32 *)(attached + 0x10) = 0x3000;
    else
        *(s32 *)(attached + 0x10) = 0xFFFFD000;
    *(u32 **)(arg0 + 0x14) = (u32 *)0x0866E464;
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
    ((u8 *)(arg0 + (*(s16 *)(arg0 + 0x22)) * 2))[0x19]++;
    frameOffset = (*(s16 *)(arg0 + 0x22)) * 2;
    handlerIndex = ((struct ScriptHolder *)arg0)->frameBytes[frameOffset];
    handlerTable = *(u32 **)(arg0 + 0x14);
    sub_080C31E0(arg0, handlerTable[handlerIndex]);
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
}

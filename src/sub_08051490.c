extern void advanceMotion(void *, s32);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Falling sparkle: recolour the sprite (it blinks palette 14 once the effect
 * is about to end), integrate the motion with gravity after a per-spawn
 * delay, emit a small sparkle every 8 frames and one last one 30 frames
 * later, then advance the entity's state. */
void sub_08051490(u8 *arg0)
{
    u16 *spriteAttr = *(u16 **)(arg0 + 0x38);
    u8 *motion = *(u8 **)(arg0 + 0x3C);
    u32 startFrame;

    if (arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19] & 2)
        *spriteAttr = (*spriteAttr & 0xFFF) | 0xE000;
    else
        *spriteAttr = (*spriteAttr & 0xFFF) | ((*(u16 *)(motion + 0x22) + 8) << 12);

    startFrame = arg0[0x6C] * 3;
    if (arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19] >= startFrame)
    {
        advanceMotion(motion, 0x16C1);
        *(u32 *)(arg0 + 0x4C) = *(u32 *)(motion + 8);
        *(u32 *)(arg0 + 0x5C) = *(u32 *)(motion + 0xC);
        if (arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19] == startFrame + 0x1E)
        {
            sub_0808DBF8(*(s32 *)(motion + 8), *(s32 *)(motion + 0xC) + 0x50000, 8);
            sub_080C31E0(arg0, *(s32 *)(arg0 + 0x24));
        }
        else if ((arg0[*(s16 *)(arg0 + 0x22) * 2 + 0x19] & 7) == 0)
        {
            sub_0808DBF8(*(s32 *)(motion + 8), *(s32 *)(motion + 0xC) + 0x50000, 8);
        }
    }
}

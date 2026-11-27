struct Entity
{
    u8 _0x00[0x14];
    u32 scriptTable;   /* +0x14: active script command table */
    u8 _0x18[0x0A];
    s16 stepIndex;     /* +0x22: current script step */
    u32 callback;      /* +0x24 */
    u8 _0x28[0x10];
    u32 sprite;        /* +0x38 */
    u32 state;         /* +0x3C */
};

s32 sub_08098400(void);
s32 updateObjectDisplayState(void *, void *);
void sub_080C31E0(void *, void *);

/* Fade step for a special object: if no fade is currently visible, set the
 * global gfx highlight colour and packed crossfade weight; run the object's
 * display-state handler and return if it consumed the frame, otherwise switch
 * to the 0x0866FF64 script table, advance the script step and run it. */
void sub_080A5950(struct Entity *arg0)
{
    void *sprite = (void *)arg0->sprite;
    void *state = (void *)arg0->state;

    if (sub_08098400() == 0)
    {
        vu16 *gfx = (vu16 *)0x03000830;
        u16 highlight = 0x3F40;
        gfx[2] = highlight;
        {
            u16 fadeWeight = 0x060A;
            gfx[3] = fadeWeight;
        }
    }

    {
        u8 *self = (u8 *)arg0;
        u8 *stepPtr;
        u8 *cmdBuf;
        u8 command;
        u32 stepOffset;
        u32 stepOffset2;
        if (updateObjectDisplayState(sprite, state) != 0)
            return;
        *(u32 *)(self + 0x14) = 0x0866FF64;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        stepOffset2 = (u32)*(s16 *)(self + 0x22) * 2;
        stepPtr = (u8 *)(stepOffset2 + (u32)self);
        *(u8 *)(stepPtr + 0x19) += 1;
        stepOffset = (u32)*(s16 *)(self + 0x22) * 2;
        cmdBuf = self + 0x18;
        cmdBuf = cmdBuf + stepOffset;
        command = *cmdBuf;
        sub_080C31E0(arg0, *(void **)((u8 *)*(u32 *)(self + 0x14) + (u32)command * 4));
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    }
}

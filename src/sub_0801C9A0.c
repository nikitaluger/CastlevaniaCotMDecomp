extern void *sub_0805FAEC(s32, s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

struct S_02025FF0_1870 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;

/* Allocate a type-0x90 result object owned by the current world state and set
 * its two screen coordinates from 16.16 fixed-point arguments (negatives are
 * rounded up by 0xFFFF before the >>16). */
void *sub_0801C9A0(s32 arg0, s32 arg1)
{
    void *result = sub_0805FAEC(gMainWorkspace.v, 0x90);
    s32 x16;
    s32 y16;

    if (result == 0)
        return 0;

    x16 = arg0;
    if (x16 < 0)
        x16 += 0xFFFF;
    {
        s32 screenX = x16 >> 16;
        *(s16 *)((u8 *)result + 0x4C) = (s16)screenX;
    }

    y16 = arg1;
    if (y16 < 0)
        y16 += 0xFFFF;
    {
        s32 screenY = y16 >> 16;
        *(s16 *)((u8 *)result + 0x54) = (s16)screenY;
    }

    return result;
}

/* Release the object's slot in its owner's 3-word list: unless bit 1 of the
 * flags at +0x6C is set, scan the three words at owner+0x58 and NULL any that
 * point back to this object. */
void sub_080212E4(void *arg0)
{
    if (!(2 & *(u16 *)((u8 *)arg0 + 0x6C)))
    {
        u32 *slotList = *(u32 **)(*(u8 **)((u8 *)arg0 + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *slot = slotList + 0x16;
        s32 remaining = 2;
        do
        {
            if (*slot == (u32)arg0)
                *slot = zero;
            slot++;
        } while (--remaining >= 0);
    }
}

/* Play animation 0x26 and, when the animator reports completion (bit 2), switch
 * to the object's state handler at +0x24. */
void sub_08021630(void *arg0)
{
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    setAnimationFrame(*(s32 *)((u8 *)arg0 + 0x38), (u8 *)work + 0x34, 0x26, 0);
    if (2 & *(u8 *)((u8 *)work + 0x34))
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}

/* Reset the work block's velocity (+0x10/+0x14), play animation 0x2D and, when
 * the animator reports completion (bit 2), switch to the state handler at
 * +0x24. */
void sub_0802165C(void *arg0)
{
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    void *anim = work + 0x34;
    *(u32 *)(work + 0x14) = 0;
    *(u32 *)(work + 0x10) = 0;
    setAnimationFrame(*(s32 *)((u8 *)arg0 + 0x38), anim, 0x2D, 0);
    if (2 & *(u8 *)anim)
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}

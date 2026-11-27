extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08014DB4(void *, void *, s32, s32);

extern u8 gScriptStepCallbackTable[];
extern u8 D_0866D868[];

struct S_02025FF0_174C { u8 _0[0x174C]; u32 a; u32 b; };
extern struct S_02025FF0_174C gMainWorkspace;

/* Detach every child held in the owner's three slots at work+0x58: mark each one
 * for deletion (bit 1 of its flags at +0x6C) and clear the slot pointer. */
void releaseProjectileSlots(void *arg0)
{
    u32 **slot = (u32 **)(*(u8 **)((u8 *)arg0 + 0x3C) + 0x58);
    s32 remaining = 2;
    u32 zero = 0;
    u32 deleteBit = 2;
    do
    {
        u8 *child = (u8 *)*slot;
        if (child != 0)
        {
            *(u16 *)(child + 0x6C) |= (u16)deleteBit;
            *slot = zero;
        }
        slot++;
        remaining--;
    } while (remaining >= 0);
}

/* Initialise the pose block at work+0x48: set its u16 fields at +8 to 0x14 and
 * at +0x1C to 3, then clear the current step's progress byte and advance the
 * script step. */
void sub_08021D90(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    u8 *pose = *(u8 **)(obj + 0x3C) + 0x48;
    u8 zero = 0;
    void **stepFnTable = (void **)gScriptStepCallbackTable;

    *(u16 *)(pose + 8) = 0x14;
    *(u16 *)(pose + 0x1C) = 3;
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    sub_080C31E4(obj + 0x18, obj + 0x22, (s32)*stepFnTable);
}

/* Restart the actor on command table D_0866D868: play animation 0, install the
 * table at +0x14, push one script step (+0x22), dispatch that step's handler
 * once, then pop the step again. */
void sub_08022058(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    u8 baseOffset;
    s32 stepOffset;

    setAnimationFrame(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = (u32)D_0866D868;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    stepOffset = (*(s16 *)(obj + 0x22)) * 2;
    baseOffset = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(baseOffset + obj))[stepOffset]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

/* Play animation 0x0E and update the pose block from the world-state target
 * coordinates at +0x174C/+0x1750; when the pose's flags at +0x20 have bit 2
 * set, set its state word at +0 to 1. */
void sub_08022708(void *arg0)
{
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    void *anim = (u8 *)work + 0x34;
    void *pose = (u8 *)work + 0x48;

    setAnimationFrame(*(void **)((u8 *)arg0 + 0x38), anim, 0xE, 1);
    sub_08014DB4(work, (u8 *)work + 0x50, gMainWorkspace.a, gMainWorkspace.b);
    if (4 & *(u16 *)((u8 *)pose + 0x20))
        *(u16 *)pose = 1;
}

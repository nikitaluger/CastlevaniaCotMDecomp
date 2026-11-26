struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08097DC8(void);
extern u32 gMainObjTimerCallback;

/* Spawns and initializes an entity's child sprite: allocates the object, sets
 * up its motion/animation from a definition object, assigns sprite flags and
 * clears the step counter, then dispatches its step script. */
void sub_080B8598(u8 *arg0)
{
    s32 sprite;
    u8 *motion;
    u8 *status;
    s32 spriteBase;
    u8 *stepBase;
    u8 zero;
    u8 *angleField;
    u8 *stepData;
    u8 stepByte;
    void **scriptTable;

    sprite = (s32)allocSpriteObject();
    if (sprite == 0)
    {
        sub_080C31E0(arg0, *((void **)(arg0 + 0x24)));
        return;
    }
    *((u32 *)(arg0 + 0x38)) = sprite;
    allocWorkSlot(arg0, 0, 0x48, 0);
    if ((*((vu32 *)(arg0 + 0x3C))) == 0)
    {
        sub_080C31E0(arg0, *((void **)(arg0 + 0x24)));
        return;
    }
    *((u32 *)(sprite + 0x1C)) = 1;
    motion = *((u8 **)(arg0 + 0x3C));
    status = motion + 0x34;
    installUpdateHandler(arg0, motion, sub_08097DC8);
    zero = 0;
    *((u16 *)(motion + 0x1C)) = 0x67;
    spriteBase = findKindIndex();
    *((u16 *)(motion + 0x22)) = spriteBase;
    if ((spriteBase << 16) < 0)
    {
        sub_080C31E0(arg0, *((void **)(arg0 + 0x24)));
        return;
    }
    angleField = motion + 0x22;
    spriteBase = *((s16 *)angleField);
    spriteBase <<= 6;
    spriteBase += 0x200;
    spriteBase &= 0xFC0;
    *((u16 *)sprite) = (u16)spriteBase;
    *((u16 *)sprite) |= gMainWorkspace.w;
    initSpriteGraphics((void *)sprite, status, (void *)(0x080CD400 + (*((s16 *)(motion + 0x1C)) * 12)));
    setAnimationFrame((void *)sprite, status, 0x22, 0);
    *((u16 *)((u8 *)sprite + 2)) |= 0x400;
    *((u8 *)(arg0 + 0x4C)) = zero;
    *((u16 *)(arg0 + 2)) |= 0x1000;
    *((u8 *)((arg0 + ((*((s16 *)(arg0 + 0x22))) * 2)) + 0x19)) = zero;
    gMainObjTimerCallback++;
    gMainObjTimerCallback--;
    scriptTable = (void **)0x08671BB0;
    stepBase = arg0 + 0x18;
    sub_080C31E4(stepBase, arg0 + 0x22, (u32)(*scriptTable));
    *((u8 *)((arg0 + ((*((s16 *)(arg0 + 0x22))) * 2)) + 0x19)) += 1;
    stepData = stepBase + ((*((s16 *)(arg0 + 0x22))) * 2);
    stepByte = *stepData;
    sub_080C31E0(arg0, *((void **)((*((u8 **)(arg0 + 0x14))) + (stepByte * 4))));
}

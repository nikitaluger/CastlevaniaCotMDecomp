s32 sub_080C31E0(s32, s32);
extern s32 gTrigFuncPtr;

/* On animation frames 0x3C and 0x85, re-evaluate the object's bobbing height
 * from the wave-function table at 0x08671BFC and advance the bob phase. */
void sub_08054BEC(void *entity)
{
    u8 *obj = (u8 *)entity;
    u8 *work = *(u8 **)(obj + 0x3C);
    s16 animFrame = *(s16 *)(work + 0x1C);

    if (animFrame == 0x3C || animFrame == 0x85)
    {
        s32 *waveFn = &gTrigFuncPtr;
        s32 phase = *(s32 *)(work + 0x48) << 13;
        s32 wave = sub_080C31E0(phase, *waveFn);
        *(s32 *)(work + 0xC) = (wave << 3) + ((s32)*(s16 *)(obj + 0x54) << 16);
        *(s32 *)(work + 0x48) = *(s32 *)(work + 0x48) + 1;
    }
}

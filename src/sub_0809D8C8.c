extern void setObjectAnimation(void *, void *, s32, s32);
extern void advanceAnimTrack(void *, void *);
extern void sub_080A040C(void *);
extern void sub_080C31E4(void *, void *, u32);
extern u32 gMainObjTimerCallbacks[];

/* Animation step: set and advance sprite animation 0x17; once it has finished,
 * clear the attached action's state, mark its sub-object as removed, copy the
 * work object's Y position into it, clear its flags and run the next script
 * step. */
void sub_0809D8C8(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *action = work + 0x48;

    setObjectAnimation(sprite, anim, 0x17, 0);
    advanceAnimTrack(sprite, anim);
    if (anim[0] & 2)
    {
        *(u32 *)(action + 0x44) = 0;
        sub_080A040C(*(void **)(action + 0x28));
        *(u32 *)(action + 0x08) = *(u32 *)(work + 0x0C);
        *(u8 *)(action + 0x0D) = 0;
        *(u8 *)(*(u8 **)(work + 0x28) + 1) = 0;
        *(u8 *)(self + (*(s16 *)(self + 0x22) * 2) + 0x19) = 0;
        {
            u32 *cmdTable = gMainObjTimerCallbacks;
            sub_080C31E4(self + 0x18, self + 0x22, *cmdTable);
        }
    }
}

extern void sub_080146D0(void *, s32, s32);
extern void sub_08057AF8(void *);
extern void sub_08057B6C(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

/* Update a projectile: turn its angle and speed into velocity, advance its
 * position, flip its orientation every 20 frames and sync its sprite. */
void sub_0805753C(void *arg0)
{
    void *anim;
    u8 *motion;
    u8 *shot;
    s16 scriptIdx;
    s32 scriptOff;
    u32 angle;

    anim = *(void **)((u8 *)arg0 + 0x38);
    motion = *(u8 **)((u8 *)arg0 + 0x3C);
    shot = motion + 0x48;

    angle = ~*(u32 *)(shot + 0x0C);
    angle += 0xFFFF8001;
    angle &= 0xFFFF;
    sub_080146D0(motion, angle, *(s32 *)(shot + 0x10));

    *(u32 *)(shot + 0x04) += *(u32 *)(motion + 0x10);
    *(u32 *)(shot + 0x08) += *(u32 *)(motion + 0x14);

    scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
    scriptOff = scriptIdx * 2;
    if (((u8 *)scriptOff + (s32)(u8 *)arg0)[0x19] == 0x14) {
        sub_08057AF8(shot);

        scriptIdx = *(s16 *)((u8 *)arg0 + 0x22);
        scriptOff = scriptIdx * 2;
        ((u8 *)scriptOff + (s32)(u8 *)arg0)[0x19] = 0;

        {
            void **litp = &gMainObjTimerCallbacks;
            void *a0 = (u8 *)arg0 + 0x18;
            void *a1 = (u8 *)arg0 + 0x22;
            sub_080C31E4(a0, a1, *litp);
        }
    }

    sub_08057B6C(arg0, anim, motion, shot);
}

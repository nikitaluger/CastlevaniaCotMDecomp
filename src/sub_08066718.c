/* Per-frame camera/scroll update for an entity: bail out when a special camera
 * mode owns the position, otherwise reset and re-track the scroll position,
 * spawn a trail object every fourth frame, fire a timed effect, then run the
 * final camera update. */
s32 sub_0806C4B4(void *a, void *b);
void sub_0806C5EC(void *a, void *b, void *c, void *d);
void sub_0806AA64(void *a, void *b);
void *sub_0806D2A0(void *a, s32 b, s32 c, s32 d);
void sub_08003740(void *a, void *b);
void sub_08003A6C(void *a, s32 b, s32 c);
void sub_0806C6B0(void *a, void *b, void *c, void *d);
void sub_080C31E4(void *a, void *b, s32 c);

extern s32 D_080DEA88[];
extern s32 gMainObjTimerCallback;

void sub_08066718(void *entity)
{
    void *self = entity;
    u8 *cam = *(u8 **)((u8 *)self + 0x6C);
    void *pos = cam + 4;
    void *view = *(void **)((u8 *)self + 0x38);
    void *posOut = pos;

    if (sub_0806C4B4(posOut, posOut) != 0)
        return;

    sub_0806C5EC(self, view, posOut, posOut);
    sub_0806AA64(view, posOut);

    {
        s32 *trailCountPtr = (s32 *)(cam + 0xBC);
        s32 trailCount = *trailCountPtr + 1;
        *trailCountPtr = trailCount;
        if ((trailCount & 3) == 0)
        {
            void *trail = sub_0806D2A0(self, 0x26, 0x0A, 0x12);
            if (trail != 0)
                *(s32 *)((u8 *)trail + 0x7C) = *trailCountPtr >> 2;
        }
    }

    {
        void *effectTimer = (u8 *)pos + 0x28;
        sub_08003740(effectTimer, view);
        if (*(s32 *)((u8 *)pos + 0xB8) > 0x1FF)
        {
            sub_08003A6C(effectTimer, 0, D_080DEA88[0xE3 << 1]);
            *(s32 *)((u8 *)pos + 0x10C) = *(s32 *)((u8 *)pos + 0x104);
            *(u8 *)((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = 0;
            {
                s32 *effectData = &gMainObjTimerCallback;
                sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *effectData);
            }
        }
    }

    sub_0806C6B0(self, view, pos, posOut);
}

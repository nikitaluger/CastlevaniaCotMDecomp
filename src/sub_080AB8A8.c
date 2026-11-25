void sub_080B0860(void);
void sub_080B07EC(void);
void sub_080B06A4(s32);
s32 sub_080114DC(s32, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

// Init/reset step: zero the pose and linked-state bytes, set work bytes
// (+0x95=0x10, +0x94=8), run the global resets, pass the three words at
// work+0x68..0x70 to sub_080B06A4, set up the animator via sub_080114DC,
// clear the script-step byte and advance to the next step.
void sub_080AB8A8(void *arg0)
{
    u32 slot;
    s32 word;
    void *work;
    void *part;
    s32 sprite;
    void *animator;
    s32 *scriptTable;

    sprite = *(s32 *)((s8 *)arg0 + 0x38);
    work = *(void **)((s8 *)arg0 + 0x3C);
    animator = (s8 *)work + 0x34;
    part = (s8 *)work + 0x48;
    *(u8 *)((s8 *)part + 0x10) = 0;
    *(u8 *)((s8 *)part + 0x11) = 0;
    *(u8 *)((s8 *)work + 0x95) = 0x10;
    *(u8 *)((s8 *)work + 0x94) = 8;
    part = *(void **)((s8 *)work + 0x28);
    *(u8 *)((s8 *)part + 1) = 0;
    sub_080B0860();
    sub_080B07EC();
    slot = 0;
    work = (s8 *)work + 0x68;
    do {
        word = *(s32 *)work;
        work = (s8 *)work + 4;
        sub_080B06A4(word);
        slot++;
    } while (slot <= 2);
    sub_080114DC(sprite, (s32)animator, 6, 0);
    *(s8 *)(((s8 *)(((*(s16 *)((s8 *)arg0 + 0x22)) * 2) + arg0)) + 0x19) = 0;
    scriptTable = (s32 *)0x08671BB0;
    sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *scriptTable);
}

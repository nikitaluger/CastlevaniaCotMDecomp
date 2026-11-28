extern void setAnimationFrame(s32, void *, u16, u8);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void setPolarOffset(u8 *, s32, s32);

void sub_0804CAB8(u8 *self)
{
    void *sprite = *(void **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *p48 = work + 0x48;
    s32 v;
    s32 r;

    setAnimationFrame((s32)sprite, anim, 0x11, 1);

    v = *(s32 *)p48;
    if ((u32)(v - 0x4000) <= 0x7FFF) {
        s32 r_arm = (v + 0x140) & 0xFFFF;
        *(s32 *)p48 = r_arm;
        if (r_arm <= 0x7800) goto polar;
        *(s32 *)p48 = 0x7800;
    } else {
        r = (v - 0x140) & 0xFFFF;
        *(s32 *)p48 = r;
        if (r > 0x7FF) goto polar;
        *(s32 *)p48 = 0x800;
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        u32 *cb = (u32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *cb);
    }
    return;
polar:
    setPolarOffset(work, *(s32 *)p48, *(s32 *)(self + 0x6C));
}

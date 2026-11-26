struct S_02025FF0 {
    u8 _0[0x14D8];
    u16 scrollX;
    u16 pad14DA;
    u16 scaleX;
    u16 scaleY;
    u16 unk14E0;
    u8 _1[0x1844 - 0x14E2];
    u32 flags;
};
extern struct S_02025FF0 gMainWorkspace;
void sub_080C31E4(void *, void *, s32);

/* Reset the affine screen effect (scroll 0, scale 1) and this object's
 * position, set the effect flag, and run the next script command. */
void sub_0808CC80(void *arg0)
{
    void *work;
    void *pos;
    s32 *litp;

    work = *(void **)((s8 *)arg0 + 0x6C);
    pos = (s8 *)work + 4;
    gMainWorkspace.scrollX = 0;
    gMainWorkspace.scaleX = 0x100;
    gMainWorkspace.scaleY = 0x100;
    gMainWorkspace.unk14E0 = 1;
    *(u16 *)((s8 *)pos + 2) = 0;
    *(u16 *)((s8 *)pos + 4) = 0;
    *(u16 *)((s8 *)work + 4) = 0;
    gMainWorkspace.flags |= 0x10000000;
    *(s8 *)(((s8 *)(((*(s16 *)((s8 *)arg0 + 0x22)) * 2) + arg0)) + 0x19) = 0;
    litp = (s32 *)0x08671BB0;
    sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *litp);
}

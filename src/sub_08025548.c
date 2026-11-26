void setAnimationFrame(void *, void *, s32, s32);
s32 sub_08014990(void *);
void sub_08025A8C(s32, s32, s32, s32, s32);
void sub_08025728(void *, void *);
void sub_080C31E8(void *, void *, s32, void *);

struct S_02025FF0_189C {
    u8 _0[0x189C];
    s32 field189C;
};
extern struct S_02025FF0_189C gMainWorkspace;

extern void *D_08671BD0;

/* Entity defeat frame: clear velocity, choose a variant from the global flag,
 * emit directional particles and a knockback impulse, then play a sound. */
void sub_08025548(void *self)
{
    void *parent = *(void **)((u8 *)self + 0x38);
    u8 *comp = *(u8 **)((u8 *)self + 0x3C);
    u8 *body = comp + 0x34;
    u8 *fx = comp + 0x48;

    *(s32 *)(comp + 0x14) = 0;
    *(s32 *)(comp + 0x10) = 0;

    if (*(u8 *)(body + 1) == 1)
    {
        s32 gameFlags = gMainWorkspace.field189C;
        s32 parity = (s32)(gameFlags + ((u32)gameFlags >> 31));
        if ((parity >> 1) & 1)
            *(s32 *)(fx + 0x14) = 0x10000;
        else
            *(s32 *)(fx + 0x14) = 0;
    }

    setAnimationFrame(parent, body, 5, 0);

    if (*(u8 *)(body + 1) == 2 && *(s32 *)(body + 4) == 1)
    {
        if (sub_08014990(parent) < 0)
        {
            sub_08025A8C(*(s32 *)(comp + 8), *(s32 *)(comp + 0xC), 0x8000, 0x30000, *(s16 *)(comp + 0x1C));
            sub_08025A8C(*(s32 *)(comp + 8), *(s32 *)(comp + 0xC), 0x6000, 0x30000, *(s16 *)(comp + 0x1C));
        }
        else
        {
            sub_08025A8C(*(s32 *)(comp + 8), *(s32 *)(comp + 0xC), 0, 0x30000, *(s16 *)(comp + 0x1C));
            sub_08025A8C(*(s32 *)(comp + 8), *(s32 *)(comp + 0xC), 0x2000, 0x30000, *(s16 *)(comp + 0x1C));
        }
        sub_08025A8C(*(s32 *)(comp + 8), *(s32 *)(comp + 0xC), 0x4000, 0x30000, *(s16 *)(comp + 0x1C));
    }

    if (*(u8 *)body & 2)
    {
        s32 impulse;
        s32 zero;
        u32 *soundTab;

        sub_08025728(fx + 8, fx + 0xC);
        if (sub_08014990(parent) < 0)
            impulse = 0xA000;
        else
            impulse = 0xE000;
        *(s32 *)(fx + 0x1C) = impulse;
        zero = 0;
        *(u16 *)(fx + 0x12) = 2;
        *(u8 *)((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x19) = zero;
        soundTab = (u32 *)0x08671BD0;
        sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 1, (void *)*soundTab);
    }
}

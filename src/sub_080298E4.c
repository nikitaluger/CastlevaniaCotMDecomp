extern void *spawnBudgetedEffect(u32, s32);
extern s32 getSpriteFacingSign(void *);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gMainWorkspace[];

void sub_080298E4(void *self)
{
    int flag;
    u8 *state;
    u8 *sprite;
    u8 *anim;
    u32 kindOffset = 0x1870;
    void *result;
    s32 v;
    s32 *lit;

    sprite = *(u8 **)((u8 *)self + 0x38);
    state = *(u8 **)((u8 *)self + 0x3C);
    anim = state + 0x34;

    if (anim[1] != 3)
        return;

    result = spawnBudgetedEffect(*(u32 *)((u8 *)gMainWorkspace + kindOffset), 0xBA);
    if (result == NULL)
        goto tail;

    if (getSpriteFacingSign(sprite) > 0) {
        v = *(s32 *)(state + 8);
        flag = v < 0;
        if (flag) v += 0xFFFF;
        {
            u16 val = (v >> 16) + 8;
            *(u16 *)((u8 *)result + 0x4C) = val;
        }
        *(u32 *)((u8 *)result + 0x6C) = 0xC0 << 5;
    } else {
        flag = *(s32 *)(state + 8);
        v = flag;
        if (v < 0) v += 0xFFFF;
        {
            u16 val = (v >> 16) - 8;
            *(u16 *)((u8 *)result + 0x4C) = val;
        }
        *(u32 *)((u8 *)result + 0x6C) = 0xB0 << 7;
    }

    v = *(s32 *)(state + 0xC);
    if (v < 0) v += 0xFFFF;
    {
        u16 val = (v >> 16) - 0xC;
        *(u16 *)((u8 *)result + 0x54) = val;
    }

tail:
    ((u8 *)self)[(*(s16 *)((u8 *)self + 0x22) * 2) + 0x19] = 0;
    lit = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *lit);
}

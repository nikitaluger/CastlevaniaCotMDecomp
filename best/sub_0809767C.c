extern u8 gMainWorkspace[];
extern u8 D_08100B98[];
extern u8 gMainObjTimerCallbacks[];
extern u8 gScriptStepCallbacks[];
extern void setObjectAnimationFrame(void *, void *, s16, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

void sub_0809767C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *st = *(u8 **)(self + 0xAC);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *work1c = work + 0x1C;
    u16 one;
    u16 flags;
    u16 bit0;
    u16 zero;
    u8 *p18;
    u8 *tbl;
    s32 *hpIf;
    s32 *hpElse;
    u32 offA;
    u32 offB;

    st = *(u8 **)(st + 4);
    flags = *(u16 *)(st + 6);
    one = 1;
    bit0 = one & flags;
    if (bit0 != 0)
        return;

    if ((flags & 2) != 0)
    {
        offA = 0xC6 << 5;
        if (*(s16 *)(gMainWorkspace + offA) != 2)
            return;
    }

    if ((flags & 4) != 0)
    {
        if (*(s16 *)(work + 0x14) != 1)
            return;
        self[*(s16 *)(self + 0x22) * 2 + 0x19] = bit0;
        hpIf = (s32 *)gScriptStepCallbacks;
        p18 = self + 0x18;
        sub_080C31E8(p18, self + 0x22, 5, *hpIf);
        self[*(s16 *)(self + 0x22) * 2 + 0x19] = self[*(s16 *)(self + 0x22) * 2 + 0x19] + 1;
        p18 += *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(self, *(s32 *)(*(u8 **)(self + 0x14) + *p18 * 4));
    }
    else
    {
        tbl = D_08100B98;
        offB = *(s32 *)work * 4;
        tbl += 2;
        setObjectAnimationFrame(sprite, work1c, *(s16 *)(tbl + offB), 0);
        zero = 0;
        *(u16 *)(work + 0x16) = one;
        self[*(s16 *)(self + 0x22) * 2 + 0x19] = zero;
        hpElse = (s32 *)gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *hpElse);
    }
}

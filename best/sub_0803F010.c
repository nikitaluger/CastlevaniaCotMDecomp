void allocWorkSlot(void *, s32, s32, s32);
void setAnimationFrame(s32, s32, s32, s32);
s16 sub_08014990(s32);
s32 sub_08016830(s32);
void *sub_0805FAEC(s32, s32);
s32 sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
extern u8 gMainWorkspace[];
extern u8 gMainObjTimerCallback[];

void sub_0803F010(void *arg0)
{
    void *temp_r0;
    void *temp_r6;
    void *temp_r1;
    void *temp_r4;
    s32 temp_r0_2;
    s32 temp_r0_3;
    void *temp_r0_4;
    void *temp_r0_5;
    void *temp_r1_2;
    s32 var_r0;
    s32 var_r1;
    s32 zero;
    s32 zero2;
    s32 *pBB0;
    u8 *base;
    u32 off;
    s32 v1, v2;

    temp_r0 = *(void **)((u8 *)arg0 + 0x38);
    temp_r6 = *(void **)((u8 *)arg0 + 0x3C);
    temp_r1 = (u8 *)temp_r6 + 0x34;
    temp_r4 = (u8 *)temp_r6 + 0x48;
    setAnimationFrame((s32)temp_r0, (s32)temp_r1, 0xB, 0);
    temp_r0_2 = *(u16 *)((u8 *)temp_r4 + 0xE) - 1;
    zero = 0;
    *(u16 *)((u8 *)temp_r4 + 0xE) = temp_r0_2;
    if ((s32)(temp_r0_2 << 16) > 0)
    {
        return;
    }
    temp_r0_3 = *(u16 *)((u8 *)temp_r4 + 0x10) - 1;
    *(u16 *)((u8 *)temp_r4 + 0x10) = temp_r0_3;
    if ((s32)(temp_r0_3 << 16) < 0 || (*(u16 *)((u8 *)temp_r4 + 0xE) = 0x46, sub_08016830(0x102) > 6))
    {
        *(u16 *)((u8 *)temp_r4 + 0xE) = 0x14;
        temp_r0_4 = *(void **)((u8 *)temp_r4 + 0x14);
        if (temp_r0_4 != NULL)
        {
            *(u16 *)((u8 *)temp_r0_4 + 0x5C) |= 2;
        }
        *(s8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
        pBB0 = (s32 *)gMainObjTimerCallback;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *pBB0);
        return;
    }
    base = gMainWorkspace;
    off = 0x1870;
    temp_r0_5 = sub_0805FAEC(*(s32 *)(base + off), 0x102);
    if (temp_r0_5 != NULL)
    {
        allocWorkSlot(temp_r0_5, 0, 8, 7);
        temp_r1_2 = *(void **)((u8 *)temp_r0_5 + 0xAC);
        if (temp_r1_2 == NULL)
        {
            sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
            return;
        }
        zero2 = 0;
        *(s16 *)temp_r1_2 = zero2;
        *(s32 *)((u8 *)temp_r1_2 + 4) = 0x080CF444;
        var_r1 = *(s32 *)((u8 *)temp_r6 + 8);
        if (var_r1 < 0) var_r1 += 0xFFFF;
        v1 = var_r1 >> 0x10;
        *(s16 *)((u8 *)temp_r0_5 + 0x4C) = v1;
        var_r0 = *(s32 *)((u8 *)temp_r6 + 0xC);
        if (var_r0 < 0) var_r0 += 0xFFFF;
        v2 = (var_r0 >> 0x10) + 0x17;
        *(s16 *)((u8 *)temp_r0_5 + 0x54) = v2;
        *(s16 *)((u8 *)temp_r0_5 + 0x5C) = sub_08014990((s32)temp_r0);
    }
}

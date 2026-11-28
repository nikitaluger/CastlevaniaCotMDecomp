void setAnimationFrame(s32, void *, u16, u8);
s32 sub_08014A6C(void *, s32, s32, s32);
s32 sub_08014114(s32, s32, s32, s32, s32);
s32 getSpriteFacingSign(s32);
s32 signOf(s32);
s32 absXFromFocus(s32);
void sub_0804C674(void *, void *, void *);
void _call_via_r3(void *, void *, s32, void *);
s32 sub_08013B04(void *, s32, s32, s32, s32);
void sub_08013B1C(void *, void *, s32, s32);
s32 sub_0801478C(s32, s32);
extern u8 gMainWorkspace[];
extern s32 gScriptStepCallbacks;

void sub_0804C0EC(u8 *obj)
{
  s32 sentinel_const0 = 1;
    u8 *__base_gMainWorkspace;
int __repair_constant = 0x168;

    s32 ctx = *(s32 *)(obj + 0x38);
    u8 *work = *(u8 **)(obj + 0x3C);
    u8 *pose = work + 0x48;
    s32 a, b;

    setAnimationFrame(ctx, work + 0x34, 0, 1);
    if (*(s16 *)(pose + 0x14) == sentinel_const0)
    {
        if (sub_08014A6C(work, *(s32 *)(pose + 0x20), 0x1800, 0) == sentinel_const0)
        {
            *(u16 *)(pose + 0x16) = __repair_constant;
            *(u16 *)(pose + 0x14) = 0;
            *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
            { void **slot = (void **) 0x08671BD0; _call_via_r3(obj + 0x18, obj + 0x22, 2, *slot); }
        }
        return;
    }

    (*(s16 *)(pose + 0x16))--;
    *(s16 *)(pose + 0x16) = (*(s16 *)(pose + 0x16));
    if ((s32)((u16)(*(s16 *)(pose + 0x16)) << 16) < 0)
    {
        if (sub_08014114(*(s32 *)(work + 8), *(s32 *)(work + 0xC), 0, 0, 0) != sentinel_const0)
        {
            *(u16 *)(pose + 0x16) = 0x3C;
            goto common;
        }
        if (getSpriteFacingSign(ctx) != signOf(*(s32 *)(work + 8)))
        {
            *(u16 *)(pose + 0x16) = 0x3C;
            goto common;
        }
        if (absXFromFocus(*(s32 *)(work + 8)) > 0x3FFFFF)
        {
            *(u16 *)(pose + 0x14) = 1;
            *(u16 *)(pose + 0x16) = 0x3C;
            goto common;
        }
        __base_gMainWorkspace = gMainWorkspace;
        if (*(s32 *)(work + 0xC) >= *(s32 *)(__base_gMainWorkspace + 0x172C) + *(s32 *)(pose + 0x10) + (s32)0xFFB80000)
        {
            *(u16 *)(pose + 0x14) = 1;
            *(u16 *)(pose + 0x16) = 0x3C;
            goto common;
        }
        *(u16 *)(pose + 0x16) = __repair_constant;
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
        { void **slot = (void **) 0x08671BD0; _call_via_r3(obj + 0x18, obj + 0x22, 3, *slot); }
        return;
    }

common:
    a = *(s32 *)(__base_gMainWorkspace + 0x1728) + *(s32 *)(pose + 0xC);
    b = *(s32 *)(__base_gMainWorkspace + 0x172C) + *(s32 *)(pose + 0x10);
    if (sub_08013B04(work, a, b, 0x100000, 0x100000) == sentinel_const0)
        sub_0804C674(obj, pose + 0xC, pose + 0x10);
    sub_08013B1C(work, pose + 0x1C, a, b);
    sub_0801478C(ctx, *(s32 *)(pose + 0x20));
}

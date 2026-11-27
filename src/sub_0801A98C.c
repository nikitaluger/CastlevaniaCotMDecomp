s32 sub_08014938(void *);
s32 sub_08005820(s32);
s32 sub_08014900(void *);
s32 sub_08014990(void *);
void _call_via_r3(void *, void *, s32, s32);

extern s32 gScriptStepCallbacks;

void sub_0801A98C(void *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *r5 = *(u8 **)(p + 0x38);
    u8 *r4 = *(u8 **)(p + 0x3C);
    u8 *r6 = r4 + 0x48;
    s32 count;

    count = *(u16 *)(r6 + 0x16) - 1;
    *(u16 *)(r6 + 0x16) = count;
    if ((s16)count < 0) {
        if (sub_08014938(*(void **)(r4 + 8)) > 0) {
            *(u16 *)(r5 + 2) |= 0x10;
        } else {
            *(u16 *)(r5 + 2) &= 0xFFEF;
        }

        *(u16 *)(r6 + 0x1A) = sub_08005820(0x29) + 0x64;

        if (sub_08014900(*(void **)(r4 + 8)) > 0x300000) {
            if (sub_08014990(r5) > 0)
                *(s32 *)(r4 + 0x10) = 0x80 << 7;
            else
                *(s32 *)(r4 + 0x10) = (s32)0xFFFFC000;
        } else {
            if (sub_08014990(r5) > 0)
                *(s32 *)(r4 + 0x10) = (s32)0xFFFFC000;
            else
                *(s32 *)(r4 + 0x10) = 0x80 << 7;
        }

        *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptTable = &gScriptStepCallbacks;
            _call_via_r3(p + 0x18, p + 0x22, 0, *scriptTable);
        }
    }
}

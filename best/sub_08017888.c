s32 sub_08014990(void *);
void sub_08011368(void *, void *, s32, s32);
void *sub_08018F6C(void *, s32);
void *sub_080121E8(s32);
void sub_080C31E4(void *, void *, u32);

extern u32 D_080CE5C8[];
extern u32 D_080CE680[];
extern u32 gMainObjTimerCallbacks;

void sub_08017888(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *r8 = *(void **)(self + 0x38);
    u8 *r6 = *(u8 **)(self + 0x3C);
    u8 *r4 = r6 + 0x34;
    u8 *r5 = r6 + 0x48;
    s32 val;
    u8 *obj;

    sub_08011368(r8, r4, 5, 0);
    if (!(*(u8 *)r4 & 2))
        goto end;

    if (sub_08014990(r8) < 0)
        val = *(s32 *)(r6 + 8) - 0x240000;
    else
        val = *(s32 *)(r6 + 8) + 0x240000;

    *(void **)(r5 + 0x30) = sub_08018F6C(self, val);
    *(u16 *)(r5 + 0x16) = 0x78;
    obj = sub_080121E8(0x78);
    *(u8 **)(r5 + 0x34) = obj;
    if (obj == 0)
        goto end;

    obj[1] = 0;
    *(u8 *)(*(u8 **)(r5 + 0x34) + 2) = 8;
    *(u8 *)(*(u8 **)(r5 + 0x34) + 3) = 1;
    {
        u8 *o = *(u8 **)(r5 + 0x34);
        s32 idx = *(s16 *)(r6 + 0x1C);
        u8 *base = (u8 *)D_080CE680;
        *(u16 *)(o + 4) = *(u16 *)(base + idx * 40 + 4);
        *(u16 *)(o + 6) = *(u16 *)(base + idx * 40 + 6);
        *(u16 *)(o + 8) = *(u16 *)(base + idx * 40 + 8);
        *(u16 *)(o + 10) = *(u16 *)(base + idx * 40 + 10);
        *(u16 *)(o + 12) = *(u16 *)(base + idx * 40 + 12);
        *(u16 *)(o + 0xE) = *(u16 *)(base + idx * 40 + 6);
        *(void **)(o + 0x10) = r8;
        *(u16 *)(o + 0x14) = 0;
    }

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    sub_080C31E4(self + 0x18, self + 0x22, gMainObjTimerCallbacks);

end:
    return;
}

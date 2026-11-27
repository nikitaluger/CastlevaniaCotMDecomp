extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern u32 D_08671BFC;
extern u32 gMainWorkspace;
extern u8 D_0866D5F4[];

void sub_0801977C(void *arg0) {
    u8 *entity = (u8 *)arg0;
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *r6 = work + 0x48;
    s32 val;
    s32 __repair_val_1;
    s32 tmp;
    s32 res;
    u8 *r2;
    s32 v;
    s32 t;
    u32 idx;
    u32 off;

    *(u32 *)(work + 0x14) = 0;
    *(u32 *)(work + 0x10) = 0;

    val = *(s32 *)(work + 0x0C) - *(s32 *)(*(u8 **)(r6 + 0x10) + 8);
    *(s32 *)(work + 0x0C) = val;

    tmp = *(s32 *)(r6 + 4) - 0x800000;
    if (val < tmp) {
        *(s32 *)(work + 0x0C) = *(s32 *)(r6 + 4);
    }

    {
        u32 *a1p = &D_08671BFC;
        s32 a0 = *(s32 *)(r6 + 0xC);
        res = sub_080C31E0(a0, *(s32 *)a1p);
    }
    r2 = *(u8 **)(r6 + 0x10);
    *(s32 *)(work + 8) = *(s32 *)(work + 0x48) + *(s16 *)(r2 + 6) * res;

    v = *(s32 *)(r2 + 8);
    if (v < 0) v += 0x3F;
    v >>= 6;

    __repair_val_1 = (*(s32 *)(r6 + 0xC) + v) & 0xFFFF;
    *(s32 *)(r6 + 0xC) = __repair_val_1;

    off = 0x18C2;
    t = __repair_val_1 + 0xFFFFC000;
    if ((u32)t <= 0x7FFF) {
        *(u16 *)sprite |= *(u16 *)((u8 *)&gMainWorkspace + off);
        *(u32 *)(sprite + 0x1C) = 0x80000009;
    } else {
        *(u16 *)sprite |= *(u16 *)((u8 *)&gMainWorkspace + off);
        *(u32 *)(sprite + 0x1C) = 0x8000000B;
    }

    *(u32 *)(entity + 0x14) = (u32)D_0866D5F4;
    *(s16 *)(entity + 0x22) = *(s16 *)(entity + 0x22) + 1;
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) += 1;
    {
        s16 tmp22 = *(s16 *)(entity + 0x22);
        s32 scaled = tmp22 * 2;
        u8 *p = entity + 0x18;
        p += scaled;
        idx = *p;
    }
    sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + idx * 4));
    *(s16 *)(entity + 0x22) = *(s16 *)(entity + 0x22) - 1;
}

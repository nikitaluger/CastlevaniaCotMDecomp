extern void sub_0800B824(u16, u16, s32);
extern void sub_0800B888(void *, void *);
extern void sub_0800BDBC(void *, void *, u32);
extern void sub_0800B9A8(s32, s32, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern u16 D_080CAABE[];
extern u8 D_06004A20[];
struct S_02021E90_x { u8 _0[0x12A2]; u16 f12A2; };
extern struct S_02021E90_x D_02021E90;
#define F50(a) ((s8)*(volatile u8 *)((u32)(a) + 0x50))

void sub_0800A164(u8 *arg0) {
    u8 *p;
    u16 id;
    u32 t;

    p = *(u8 **)(arg0 + 0x3C);

    sub_0800B888(arg0, p);
    *(volatile u8 *)((u32)arg0 + 0x54) = 0xFF;
    switch (*(u8 *)(p + 0x635)) {
    case 0:
        id = D_080CAABE[*(u8 *)(p + 0x636)];
        t = id - 0x36;
        sub_0800B824(id, 0x9C << 2, t);
        *(volatile u8 *)((u32)arg0 + 0x50) = 0;
        break;
    case 1:
        sub_0800B824(0x81D4, 0x9C << 2, 0xC0 << 3);
        sub_0800B9A8(F50(arg0), 0, p);
        break;
    case 3:
        if (*(u8 *)(p + 0x638)) {
            id = 0x81D5;
            t = id - 0x38;
            sub_0800B824(id, 0x9C << 2, t);
        } else {
            sub_0800B824(0x81DD, 0x9C << 2, 0xC0 << 3);
        }
        sub_0800B9A8(F50(arg0), 0, p);
        break;
    case 2:
    case 4:
        t = (u32)D_06004A20 + ((D_02021E90.f12A2 & 0xC) << 12);
        sub_0800BDBC(p + 0x600, arg0, t);
        break;
    case 5:
        if (*(u8 *)(p + 0x638)) {
            id = 0x81D6;
            t = id - 0x38;
            sub_0800B824(id, 0x9C << 2, t);
        } else {
            sub_0800B824(0x81DD, 0x9C << 2, 0xC0 << 3);
        }
        sub_0800B9A8(F50(arg0), 0, p);
        sub_0800B9A8(F50(arg0), 2, p);
        break;
    case 6:
        if (*(u8 *)(p + 0x638))
            sub_0800B824(0x81DA, 0x9C << 2, 0xC0 << 3);
        else
            sub_0800B824(0x81DD, 0x9C << 2, 0xC0 << 3);
        sub_0800B9A8(F50(arg0), 0, p);
        break;
    default:
        break;
    }
    // p dies here
    {
        u8 *base;
        u32 idx;
        u8 *q;
        s32 *g;
        u8 *r;
        u32 v2;

        base = arg0 + 0x18;
        idx = (u32)*(s16 *)(arg0 + 0x22);
        q = (u8 *)((idx * 2) + (u32)arg0);
        q[0x19] = 0;
        g = (s32 *)0x08671BB0;
        sub_080C31E4(base, arg0 + 0x22, *g);
        q = (u8 *)((idx * 2) + (u32)arg0);
        q[0x19] += 1;
        r = (u8 *)((u32)base + idx * 2);
        v2 = *(u32 *)(*(u32 *)(arg0 + 0x14) + (*r * 4));
        sub_080C31E0(arg0, (void *)v2);
    }
}

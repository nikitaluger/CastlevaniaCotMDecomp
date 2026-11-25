extern void sub_08014588(void *, void *);
extern u8 D_08101B70[];
extern u8 D_08101BC8[];

struct Idx { u8 pad[2]; u16 val; };

void sub_080A2E98(void *arg0, void *arg1, u8 *arg2)
{
    void *a1;
    u8 *a2;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 v;
    s32 idx;
    s32 off;
    u32 *p;
    u32 base;
    u16 val;
    struct Idx *e;

    a1 = arg1;
    a2 = arg2;
    r4 = 0;
    r5 = 0;
    r6 = 0;

    p = *(u32 **)((u8 *)arg0 + 8);
    idx = *(s16 *)((u8 *)arg0 + 0x0E) + *(u8 *)((u8 *)arg0 + 1);
    base = *p;
    off = idx * 4;
    e = (struct Idx *)(off + base - 4);
    val = e->val;
    v = (s32)val - 0x0B;

    switch (v) {
    case 0: r4 = 1; break;
    case 1: r4 = 2; r5 = 0; r6 = 5; break;
    case 5: r4 = 2; r5 = 1; r6 = 5; break;
    case 9: r4 = 2; break;
    case 13:
    case 14: r4 = 3; break;
    case 17: r5 = 2; r6 = 5; break;
    case 19: r5 = 3; r6 = 5; break;
    case 22: r4 = 4; r5 = 4; r6 = 5; break;
    case 25: r4 = 5; r5 = 5; r6 = 5; break;
    case 28:
    case 31: r4 = 6; r5 = 6; r6 = 5; break;
    case 34: r4 = 7; break;
    case 37: r4 = 8; break;
    case 40: r4 = 9; break;
    case 42: r4 = 10; break;
    }

    sub_08014588(a1, D_08101B70 + r4 * 8);
    sub_08014588(a2, D_08101BC8 + r5 * 8);
    a2[1] = r6;
}

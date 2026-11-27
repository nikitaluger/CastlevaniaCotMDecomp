struct Ent { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u32 f10; };
struct DefBB { u8 _00[4]; u16 f4; u16 f6; };
extern u16 D_081017D8[];
extern void *gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern void *allocEffectPart(void);
extern void sub_0809C6C0(void);
extern void sub_0809C6EC(void);
extern void sub_0809ACAC(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

static inline u8 andBF(u8 b) { u32 m = 0xBF; m &= b; return (u8)m; }

void sub_0809A960(u8 *arg0_in) {
  u8 * arg0;
    u8 *a; u8 *p; u8 *arr; struct Ent **r4; u16 *t; u32 i; u32 zero;
    u8 *r3;
    void **temp;
    void **temp2;
    temp2 = (void **)(arg0_in + 0x24);
  arg0 = arg0_in;
    a = allocSpriteObject();
    if (a == NULL) goto fail;
    temp = (void **)(arg0 + 0x38);
    *temp = a;
    allocWorkSlot(arg0, 0, 0x114, 0);
    if (*(void **)(arg0 + 0x3C) != NULL) goto cont;
fail:
    sub_080C31E0(arg0, *temp2);
    return;
cont:
    *(u8 *)(a + 0x2A) = andBF(*(u8 *)(a + 0x2A));
    p = *(u8 **)(arg0 + 0x3C);
    arr = p + 0x48;
    installUpdateHandler(arg0, p, sub_0809ACAC);
    *(u16 *)(p + 0x1C) = 0x44;
    sub_0809C6C0();
    sub_0809C6EC();
    t = D_081017D8;
    i = 0;
    do {
        s32 idx;
        r3 = allocEffectPart();
        idx = i * 4;
        r4 = (struct Ent **)(arr + 4 + idx);
        *r4 = (struct Ent *)r3;
        if (r3 == NULL) goto fail;
        zero = 0;
        (*r4)->f1 = zero;
        (*r4)->f2 = 8;
        (*r4)->f3 = 1;
        (*r4)->f4 = ((struct DefBB *)((u8 *)0x080CBDD0 + *(s16 *)(p + 0x1C) * 0x28))->f4;
        (*r4)->f6 = t[0];
        (*r4)->f8 = t[1];
        (*r4)->fA = t[2];
        (*r4)->fC = t[3];
        (*r4)->fE = ((struct DefBB *)((u8 *)0x080CBDD0 + *(s16 *)(p + 0x1C) * 0x28))->f6;
        (*r4)->f10 = (u32)a;
        i++;
    } while (i <= 0x31);
    {
        u32 zero2;
        *(u8 *)(arg0 + 0x74) = zero;
        *(u8 *)arr = 0xFF;
        zero2 = 0;
        *(u16 *)(arr + 2) = ((s16)*(s16 *)(arg0 + 0x6C) - 1) | zero2;
        *(u16 *)(arg0 + 2) |= 0x1000;
        *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) = zero2;
    }
    {
        u32 *cb = (u32 *)0x08671BB0;
        arr = arg0 + 0x18;
        do { do { sub_080C31E4(arr, arg0 + 0x22, *cb); } while (0); } while (0);
    }
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) += 1;
    arr += (u32)(*(s16 *)(arg0 + 0x22)) * 2;
    { u8 b = *arr;
      u8 *vtbl = *(u8 **)(arg0 + 0x14);
      do { do { sub_080C31E0(arg0, *(void **)(vtbl + b * 4)); } while (0); } while (0); }
}

struct ScriptStep { u8 _0[0x19]; u8 counter; };

extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks;

void sub_080A2990(void *obj) {
    u8 *self = (u8 *)obj;
    u16 *sprite = *((u16 **)(self + 0x38));
    u8 *work = *((u8 **)(self + 0x3C));
    s8 zero;
    u32 v;
    u32 k;
    s32 *p;
    u32 c;
    u8 *temp;

    if (!(2 & ((struct ScriptStep *)((u8 *)self + *(s16 *)(self + 0x22) * 2))->counter)) goto plus;
    v = *sprite;
    c = (v & 0xFFF); k = 0xFFFFC000; v = c | k;
    temp = (u8 *)obj + 0x19;
    *sprite = v;
    if (2 & *(u8 *)(temp + *(s16 *)((u8 *)obj + 0x22) * 2)) goto minus;
plus:
    k = (0x80 << 9);
    *(s32 *)(work + 8) = (*(s32 *)(work + 8) + k);
    goto join;
minus:
    *(s32 *)(work + 8) = (*(s32 *)(work + 8) + (s32)0xFFFF0000);
join:
    c = *(u8 *)(0x19 + (u8 *)self + 2 * *(s16 *)(self + 0x22));
    if (c == 0x3c) {
        u32 v_a1;
        zero = 0;
        *(s32 *)(work + 0x14) = zero;
        v_a1 = *(u32 *)(work + 0x28);
        *(u8 *)(v_a1 + 1) = 5;
        ((struct ScriptStep *)((u8 *)self + *(s16 *)(self + 0x22) * 2))->counter = zero;
        p = &gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *p);
    }
}

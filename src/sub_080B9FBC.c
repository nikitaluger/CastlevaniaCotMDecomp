extern u8 D_08102EA8[];
extern u16 D_08102EC8[];
extern u32 D_08670598[];
extern u32 gMainObjTimerCallback;
extern u32 D_08671BD8;
extern s32 sub_08005820(u8);
extern void sub_080BE644(s32);
extern void sub_080BE7D4(void);
extern void sub_080BE87C(void);
extern void sub_080C31E0(s32, s32);
extern void sub_080C31E4(s32, s32, s32);
extern void sub_080C31E8(s32, s32, u16, s32);

struct BossState {
    u8 _0[0x3C];
    u32 mode;
    u8 _1[0x44 - 0x40];
    u32 frame;
    u32 pattern;
};

struct BossEntity {
    u8 _0[0x18];
    u8 _1[0x22 - 0x18];
    s16 stepIndex;
    u8 _2[0x3C - 0x24];
    u32 statePtr;
};

/* Picks a behavior frame from a pattern table and dispatches the matching handler;
 * the finish state plays effects and uses a separate dispatch helper. */
void sub_080B9FBC(struct BossEntity *obj) {
    struct BossState *st;
    u8 *patternTable;
    u32 mode, v, v2, nv, fn, addr;
    u8 b0, b1;
    s32 t;
    s16 i;

    st = (struct BossState *)(obj->statePtr + 0x48);
    mode = st->mode;
    if (mode == 0) goto case_init;
    if (mode == 1) goto case_finish;
    goto dispatch;
case_init:
    patternTable = D_08102EA8;
    v = st->pattern;
    b0 = patternTable[(v >> 1) * 4];
    t = sub_08005820(b0) + 1;
    st->frame = t;
    v2 = st->pattern;
    addr = (u32)t;
    addr += (v2 >> 1) * 4;
    addr += (u32)patternTable;
    b1 = *(u8 *)addr;
    st->frame = b1;
    nv = (1u << b1) | v2;
    st->pattern = nv;
    if (nv == 0xE) st->pattern = mode;
    goto dispatch;
case_finish:
    st->frame = 4;
    sub_080BE7D4();
    sub_080BE87C();
    sub_080BE644((s32)obj);
    {
        u8 *base;
        s32 off;
        i = obj->stepIndex;
        off = (s32)i * 2;
        base = (u8 *)off;
        base += (u32)obj;
        base[0x17] = 0;
    }
    {
        u32 *pbd8 = &D_08671BD8;
        sub_080C31E8((s32)((u8 *)obj + 0x18), (s32)((u8 *)obj + 0x22),
                     D_08102EC8[st->frame], (s32)*pbd8);
    }
    return;
dispatch:
    fn = D_08670598[st->frame];
    sub_080C31E0((s32)obj, (s32)fn);
    {
        u8 *base;
        s32 off;
        i = obj->stepIndex;
        off = (s32)i * 2;
        base = (u8 *)off;
        base += (u32)obj;
        base[0x19] = 0;
    }
    {
        u32 *pbb0 = &gMainObjTimerCallback;
        sub_080C31E4((s32)((u8 *)obj + 0x18), (s32)((u8 *)obj + 0x22), (s32)*pbb0);
    }
}

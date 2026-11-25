extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080144D8(void *, void *);
extern void sub_080144FC(void *, void *);
extern void sub_0803C674(u32, u32, u32);

void sub_0803C818(void *arg0) {
    u8 z = 0;
    u8 *r5;
    void **lit;
    *(u8 *)((u8 *)arg0 + 0x3C) = 1;
    *(u8 *)((u8 *)arg0 + (s32)*(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = z;
    lit = (void **)0x08671BB0;
    r5 = (u8 *)arg0 + 0x18;
    sub_080C31E4(r5, (u8 *)arg0 + 0x22, (s32)*lit);
    *(u8 *)((u8 *)arg0 + (s32)*(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) += 1;
    r5 += (s32)*(s16 *)((u8 *)arg0 + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)r5 * 4));
}

s16 sub_0803C9D0(s32 arg1) {
    return *(s16 *)(0x02000000 + arg1);
}

void sub_0803CCDC(void *arg0) {
    void *r5 = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, r5);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DFD8;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *p = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        p[0x19] = (u8)(p[0x19] + 1);
        {
            s32 idx2 = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *base = (u8 *)arg0 + 0x18;
            u8 b = *(base + idx2);
            u8 **tbl = *(u8 **)((u8 *)arg0 + 0x14);
            void *arg = tbl[b];
            sub_080C31E0(arg0, arg);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, r5);
}

/* Spawn the effect pair for this host: pass its sprite attributes (host+0x38),
 * the source object (host+0x3C) and that object's emitter state (source+0x48). */
void sub_0803C23C(void *arg0) {
    u8 *p = (u8 *)arg0;
    u32 attrs = *(u32 *)(p + 0x38);
    u8 *source = *(u8 **)(p + 0x3C);
    sub_0803C674(attrs, (u32)source, (u32)(source + 0x48));
}

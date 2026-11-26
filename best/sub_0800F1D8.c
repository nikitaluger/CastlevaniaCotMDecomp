extern u8 gGameStatus[];
extern u8 D_020278D0[];
extern u8 D_02027943[];
extern u8 D_080CB007[];
extern u16 D_080CB00A[];
extern u16 D_080CB022[];
extern u16 D_080CFF2A[];
extern u16 D_02023132;
extern void setLayerTilemap(s32, u16);
extern void sub_0805FEC8(u16);
extern void sub_0800FE08(s32, s32, u32, void *);
extern void sub_0800FEDC(s32, void *);
void sub_0800F1D8(u8 arg0, u8 arg1) {
    u16 *__base_D_02023132;
    u8 *__base_D_02027943;
    s32 __index_D_02027943;
    volatile u16 sp0;
    volatile u32 a0 = arg0;
    volatile u32 a1 = arg1;
    u8 *volatile p = gGameStatus;
    u8 *tbl = D_020278D0;
    u8 *base6f = tbl + 0x6F;
    s32 r7 = (s8)base6f[a0] - 2;
    s32 i = 0;
    volatile u16 *r8;
    vu32 *dma;
    u8 byte; u16 t; u32 dst; u16 r6; u16 r5; u8 val; u32 r4off; u8 *r4ptr; u8 v; u16 idx; u8 b; u16 base132; 
  u32 ptr_web1;
  u32 ptr_web;
  u32 ptr_web_web;
  u16 temp;
    dma = (vu32 *)0x040000D4;
    r8 = D_080CB022;
    for (; i < 12; i++) {
        sp0 = 0;
        dma[0] = (u32)&sp0;
        byte = D_080CB007[a1];
        dst = (u32)byte << 14;
        temp = D_080CB00A[i];
        t = temp;
        dst = dst + ((u32)t << 5);
        dst = dst + 0x06000000;
        dma[1] = dst;
        dma[2] = 0x810000A0;
        (void)dma[2];
        r6 = r8[0]; r5 = r8[1];
        if (r7 < 0) goto fail;
        r4off = a0 << 5;
        __index_D_02027943 = r7 + r4off;
        __base_D_02027943 = D_02027943;
        val = *((u8 *) ((u32) __base_D_02027943 + __index_D_02027943));
        if (val == 0xFF) goto fail;
        if (a1 != 0) setLayerTilemap(0, (u16)(t + 0x400));
        else setLayerTilemap(0, t);
        r4ptr = (u8 *) (0x02027943+ (r7 + r4off));
        v = r4ptr[0]; idx = D_080CFF2A[v]; sub_0805FEC8(idx);
        v = r4ptr[0];
        if (v != 0) {
            int temp2;
            temp2 = 0x384 + v;
            b = p[temp2]; __base_D_02023132 = &D_02023132;
 base132 = (*__base_D_02023132);
            temp2 = ((base132 & 0x1F00) << 3);
            temp2 = temp2 + 0x06000000;
            temp2 = temp2 + (((u32)r5 << 6) + ((u32)r6 << 1));
            sub_0800FE08(b, 2, 0x511C, (void *)temp2);
        } else {
            base132 = (*__base_D_02023132);
            ptr_web1 = ((base132 & 0x1F00) << 3);
            ptr_web1 = ptr_web1 + 0x06000000;
            ptr_web1 = ((u32)r5 << 6) + (((u32)r6 << 1) + ptr_web1);
            sub_0800FEDC(2, (void *)ptr_web1);
        }
        goto next;
    fail:
        base132 = (*__base_D_02023132);
        ptr_web_web = ((base132 & 0x1F00) << 3);
        ptr_web_web = ptr_web_web + 0x06000000;
        ptr_web_web = ptr_web_web + (((u32)r5 << 6) + ((u32)r6 << 1));
        sub_0800FEDC(2, (void *)ptr_web_web);
    next:
        r7 = r7 + 1; r8 = r8 + 2;
    }
}

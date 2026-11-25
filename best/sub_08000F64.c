extern void *sub_08000DC4(void **arg0);
extern void sub_08000DD8(void **arg0, void *arg1);
extern u8 D_020223B8[];
extern u8 D_020223BC[];
extern s16 D_080C4214[];
extern u32 *D_0866C1AC[];

void sub_08000F64(void) {
    s32 i;
    s32 j;
    s32 idx;
    void *node;
    u32 tmp;

    for (i = 0; i <= 1; i++) {
        idx = D_080C4214[i];
        for (j = 0; j <= 1; j++) {
            while ((node = sub_08000DC4((void **)(D_020223BC + j * 4 + i * 8))) != 0) {
                if (*(u32 *)((u8 *)node + 8) & 0x01000000) {
                    tmp = *(u32 *)node;
                    *(u32 **)(D_0866C1AC[idx]) = &tmp;
                } else {
                    *(u32 *)(D_0866C1AC[idx]) = *(u32 *)node;
                }
                D_0866C1AC[idx][1] = *(u32 *)((u8 *)node + 4);
                D_0866C1AC[idx][2] = *(u32 *)((u8 *)node + 8);
                sub_08000DD8((void **)D_020223B8, node);
            }
        }
    }
}

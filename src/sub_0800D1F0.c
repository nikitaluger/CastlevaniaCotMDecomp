struct S_020278D0 {
    u8 _0[0x48];
    u32 _48;
    u8 _4C[0x68 - 0x4C];
    s8 stageIndex; /* 0x68: selects an entry in D_080CAFF8 */
};
extern struct S_020278D0 gMenuState;

struct Pair { s16 x; s16 y; };
extern u32 gGameStatus[];
extern u16 D_080CAFF8[];

s32 createChildObject(s32, s32);       /* spawn an actor of the given type */
void sub_0800EB44(s32, s32, s32); /* load a graphics block */
void sub_0800FE08(s16, s32, s32, s32);
void sub_0800EBDC(s16, s16, s32);
void sub_0800EC20(s32);

/* Room setup: spawn the five actor slots kept at gMenuState+0x48 and tag each
 * with its slot index, load the stage-dependent graphics block selected by
 * gMenuState.stageIndex, then copy the coordinate pairs stored in
 * gGameStatus to their VRAM destinations. */
void sub_0800D1F0(s32 arg0) {
    u32 *p;
    struct Pair *arr;
    u32 i;
    u8 *d;

    arr = (struct Pair *)gGameStatus;
    i = 0;
    d = (u8 *)&gMenuState;
    p = (u32 *)(d + 0x48);
    do {
        s32 v = createChildObject(arg0, 0x1B);
        *p = v;
        *(u8 *)(v + 0x3C) = 0;
        *(u8 *)(*p + 0x44) = (u8)i;
        p++;
        i++;
    } while (i <= 4);

    sub_0800EB44(D_080CAFF8[gMenuState.stageIndex], 2, 0xFC0);

    sub_0800FE08(arr[0xB1].y, 4, 0x511C, 0x0600696E);
    sub_0800FE08(arr[0xB3].y, 4, 0x511C, 0x060069AE);
    sub_0800FE08(arr[0xB5].x, 3, 0x511C, 0x060069EE);
    sub_0800EBDC(arr[0xB8].x, *(s16 *)((u8 *)arr + 0x2DE), 0x0600694E);
    sub_0800EBDC(arr[0xBA].x, *(s16 *)((u8 *)arr + 0x2E6), 0x0600698E);
    sub_0800EBDC(arr[0xBC].x, *(s16 *)((u8 *)arr + 0x2EE), 0x060069CE);
    sub_0800EBDC(arr[0xBE].x, *(s16 *)((u8 *)arr + 0x2F6), 0x06006A0E);
    sub_0800EC20(0x06006A8A);
}

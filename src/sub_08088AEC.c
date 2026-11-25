extern void sub_08003A6C(void *, s32, const void *);
extern void sub_08003740(void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E4(void *, void *, u32);

extern u32 D_02025FF0[];
extern const void D_084FEC0C;
extern u32 D_08671BB0[];

/* Tick a mover's attached animation: when the global mode word (+0x1C) is 1,
 * start the sub-script stored at mover+0x20 on its frame data and advance the
 * outer script; then step that sub-script and copy the mover's world position
 * into the sprite's screen position. */
void sub_08088AEC(void *self)
{
    u8 *a = (u8 *)self;
    u8 *mover = *(u8 **)(a + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(a + 0x38);

    if (D_02025FF0[7] == 1) {
        u32 *scriptTable;
        sub_08003A6C(mover + 0x20, 0, &D_084FEC0C);
        D_02025FF0[7] = 2;
        *(u8 *)(a + (*(s16 *)(a + 0x22) * 2) + 0x19) = 0;
        scriptTable = D_08671BB0;
        sub_080C31E4(a + 0x18, a + 0x22, scriptTable[0]);
    }

    sub_08003740(mover + 0x20, sprite);
    sub_0806D588(sprite, pos);
}

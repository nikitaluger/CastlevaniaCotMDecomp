struct S_02025FF0 { u8 _pad[0xC]; u32 fieldC; u8 _pad2[0x18C5 - 0x10]; u8 field18C5; u8 field18C6; };
extern struct S_02025FF0 D_02025FF0;
struct Entry_080E03A0 { s32 value; u8 rest[0x54]; };
struct S_080E03A0 { u8 _pad[0x44]; struct Entry_080E03A0 entries[1]; };
extern struct S_080E03A0 D_080E03A0;
void sub_0806AB04(void *, void *, void *, void *);
s32 sub_08003740(void *, void *);
void sub_0806A884(void *, void *);
s32 sub_0806C4B4(void *, void *);
void sub_0806C5EC(void *, void *, void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);

/* Draw an object's sprite when no camera-follow mode is active, offsetting it
 * by a table value and updating the global display/script flags. */
void sub_0806A510(void *arg0) {
    void *gfx;
    void *gfxData;
    void *sprite;
    s32 cameraMode;
    struct S_02025FF0 *state;
    u32 one;

    gfx = *(void **)((u8 *)arg0 + 0x6C);
    gfxData = (u8 *)gfx + 4;
    sprite = *(void **)((u8 *)arg0 + 0x38);
    cameraMode = sub_0806C4B4(gfxData, gfxData);
    if (cameraMode == 0) {
        sub_0806C5EC(arg0, sprite, gfxData, gfxData);
        state = &D_02025FF0;
        state->field18C6 = 1;
        state->field18C5 = 1;
        one = 1;
        *(s32 *)((u8 *)gfxData + 0xC) += D_080E03A0.entries[*(s32 *)((u8 *)gfxData + 0x44)].value;
        sub_0806AB04(arg0, sprite, gfxData, gfxData);
        if (*(s32 *)((u8 *)gfxData + 0x40) == 1) {
            *(s32 *)((u8 *)gfxData + 8) = cameraMode;
            *(s32 *)((u8 *)gfxData + 0xC) = cameraMode;
        }
        sub_0806A884(sprite, gfxData);
        if (sub_08003740((u8 *)gfx + 0x2C, sprite) == 0) {
            state->fieldC = one;
        }
        sub_0806C6B0(arg0, sprite, gfxData, gfxData);
    }
}

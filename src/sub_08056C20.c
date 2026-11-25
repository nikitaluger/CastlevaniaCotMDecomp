/* State machine driving one scripted effect: waits for the target to come
 * within camera range, moves it along a path, plays an animation step, then
 * finishes by snapping it to a table-derived position. Returns 1 when done. */
extern s32 sub_080059DC(s32, s32);
extern void sub_0801165C(void *, s32);
extern void sub_08056B58(s32, s32, void *, s32, s32);
extern void sub_08056BB8(void *, s32, s32);
extern s32 sub_080C31E0(s32, s32);
struct CameraPos { u8 _0[0x174C]; s32 camX; s32 camY; };
extern struct CameraPos D_02025FF0;

s32 sub_08056C20(u8 *owner, u8 *target, u8 *script, s32 paramA, s32 paramB, u8 *path, s32 mode) {
    s32 done = 0;
    s32 step;
    s32 product;

    switch (*(u8 *)(script + 8)) {
    case 0:
        if (mode == 0) {
            s32 dist = sub_080059DC(D_02025FF0.camX - *(s32 *)(target + 8), D_02025FF0.camY - *(s32 *)(target + 0xC));
            if (dist <= 0x4FFFFF) {
                void *child;
                *(u8 *)(script + 8) = *(u8 *)(script + 8) + 1;
                child = *(void **)(owner + 0x30);
                if (child != NULL) {
                    do {
                        *(u8 *)((u8 *)child + 0x70) = 1;
                        child = *(void **)((u8 *)child + 0x2C);
                    } while (child != NULL);
                }
            }
        } else {
            if (*(u8 *)(owner + 0x70) != 0) {
                *(u8 *)(script + 8) = 1;
            }
        }
        break;
    case 1:
        sub_08056B58(paramA, paramB, script, 4, 4);
        product = *(s32 *)(path + 4) * *(s32 *)(script + 0xC);
        *(s32 *)(target + 0x10) = *(s32 *)(path + 0) + product;
        product = *(s32 *)(path + 0xC) * *(s32 *)(script + 0xC);
        *(s32 *)(target + 0x14) = *(s32 *)(path + 8) + product;
        sub_0801165C(target, 0);
        step = *(s32 *)(script + 0xC) + 1;
        *(s32 *)(script + 0xC) = step;
        if (step == 0x12) {
            *(u8 *)(script + 8) = *(u8 *)(script + 8) + 1;
            *(s32 *)(script + 0xC) = 0;
            *(s32 *)(script + 0x10) = *(s32 *)(target + 0xC);
            sub_08056BB8(script, 0xC, 8);
        }
        break;
    case 2:
        sub_08056B58(paramA, paramB, script, 0xC, 8);
        step = *(s32 *)(script + 0xC) + 1;
        *(s32 *)(script + 0xC) = step;
        if (step == 0x10) {
            *(u8 *)(script + 8) = *(u8 *)(script + 8) + 1;
            *(s32 *)(script + 0xC) = 0;
        }
        break;
    case 3:
        sub_08056B58(paramA, paramB, script, 0xC, 8);
        {
            s32 *divTable;
            divTable = (s32 *)0x08671BFC;
            *(s32 *)(target + 0xC) = *(s32 *)(script + 0x10) + (sub_080C31E0(*(s32 *)(script + 0xC) << 10, *divTable) * 2);
        }
        step = *(s32 *)(script + 0xC) + 1;
        *(s32 *)(script + 0xC) = step;
        if (step == 0x18) {
            s32 z;
            done = 1;
            z = 0;
            *(u8 *)(script + 8) = z;
            *(s32 *)(script + 0xC) = z;
            *(s32 *)(target + 0x10) = 0xFFFF8000;
            *(s32 *)(target + 0x14) = z;
        }
        break;
    }
    return done;
}

extern s32 absXFromFocus(s32);
extern s32 signOf(s32);
extern s32 getSpriteFacingSign(void *);
extern s32 rollProbability(s32);
extern void sub_080186DC(void *, s32);
extern void sub_080186C0(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 gScriptStepCallbacks[];

void sub_08017628(void *arg0)
{
    u8 *actor;
    u8 *sprite;
    u8 *work;
    u8 *control;
    s32 dist;
    s32 dir;
    s32 facing;
    s32 zero;
    s16 step;

    actor = (u8 *)arg0;
    work = *(u8 **)(actor + 0x3C);
    control = work;
    control += 0x48;
    dist = absXFromFocus(*(s32 *)(work + 8));
    dir = signOf(*(s32 *)(work + 8));
    sprite = *(u8 **)(actor + 0x38);
    facing = getSpriteFacingSign(sprite);
    zero = 0;

    *(u16 *)(control + 0x14) = 1;

    if (dist <= 0x37FFFF) {
        if (rollProbability(*(s16 *)(control + 0x2A)) == 1) {
            sub_080186DC(control + 0x2A, 0xAF * 4);
            *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
            do { sub_080C31E8(actor + 0x18, actor + 0x22, 7, gScriptStepCallbacks[0]); } while (0);
        } else {
            sub_080186C0(control + 0x2A, 0xAF * 8);
            goto cleanup;
        }
    } else if (dist <= 0xB3FFFF && facing == dir) {
        if (rollProbability(*(s16 *)(control + 0x2C)) == 1) {
            sub_080186DC(control + 0x2C, 0xFA * 4);
            *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
            sub_080C31E8(actor + 0x18, actor + 0x22, 8, gScriptStepCallbacks[0]);
        } else {
            sub_080186C0(control + 0x2C, 0x96 * 8);
            if (dist > 0x5FFFFF) goto cleanup;
        }
    } else {
        goto cleanup;
    }

    if (dist <= 0x5FFFFF) {
        if (rollProbability(*(s16 *)(control + 0x2E)) == 1) {
            sub_080186DC(control + 0x2E, 0xFA * 4);
            *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
            sub_080C31E8(actor + 0x18, actor + 0x22, 5, gScriptStepCallbacks[0]);
        } else {
            sub_080186C0(control + 0x2E, 0xFA * 4);
            goto cleanup;
        }
    } else {
        goto cleanup;
    }

    goto increment;

cleanup:
    sub_080186C0(work + 0x2A, 400);
    do { do { sub_080186C0(work + 0x2C, 400);
    sub_080186C0(work + 0x2E, 400); } while (0); } while (0);
    *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x19) = zero;
    sub_080C31E8(actor + 0x18, actor + 0x22, 6, gScriptStepCallbacks[0]);

increment:
    dist = *(u8 *)(actor + (step = *(s16 *)(actor + 0x22)) * 2 + 0x19); *(u8 *)(actor + step * 2 + 0x19) = dist + 1;
    step = *(s16 *)(actor + 0x22);
    {
        s32 off = step * 2;
        sprite = actor + 0x18;
        do { do { sub_080C31E0(arg0, *(void **)((u8 *)*(void **)(actor + 0x14) + *(u8 *)(sprite + off) * 4)); } while (0); } while (0);
    }
}

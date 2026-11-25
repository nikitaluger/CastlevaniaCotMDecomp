/* Initialize an entity controlled by the camera/effect system: clear its
 * position state, install callback and data pointers, spawn an effect from a
 * definition table, set its velocity and state, then dispatch its callbacks. */
extern void sub_08003A6C(void *, s32, void *);
extern void sub_080722E0(void *, u8);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0808449C(void);
extern u8 D_02025FF0[];
extern u32 D_084E4850;
extern u32 D_084E48B0;
extern s32 D_08671BB0;

void sub_0807C914(u8 *entity) {
    u32 zero;
    u8 *cam = *(u8 **)(entity + 0x6C);
    u8 *pos = cam + 4;
    u8 *view = *(u8 **)(entity + 0x38);
    zero = 0;

    *(u32 *)(pos + 0x2C) = zero;
    *(u32 *)(pos + 0x30) = zero;
    *(u32 *)(pos + 0x34) = zero;
    *(u32 *)(pos + 0x38) = zero;
    *(u32 *)(pos + 0x3C) = zero;
    *(u32 *)(pos + 0x18) = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)&sub_0808449C;
    *(u32 *)(view + 0x24) = (u32)&D_084E4850;
    sub_08003A6C(cam + 0x20, 0, &D_084E48B0);
    {
        u8 *globals = D_02025FF0;
        *(s32 *)(cam + 4) = *(s32 *)(globals + 0x1728);
        *(s32 *)(pos + 4) = *(s32 *)(globals + 0x172C) + 0xFF800000;
    }
    *(u32 *)(pos + 0x10) = zero;
    *(u32 *)(pos + 0x40) = 0x4000;
    {
        u8 *directionPtr = cam;
        directionPtr += 0x48;
        *(u8 *)directionPtr = 0x40;
        *(u8 *)(cam + 0x49) = 4;
        sub_080722E0(pos, *directionPtr);
    }
    *(u32 *)(pos + 0x54) = zero;
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
    {
        s32 *callback = &D_08671BB0;
        u8 *statePtr = entity;
        statePtr += 0x18;
        sub_080C31E4(statePtr, entity + 0x22, *callback);
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) + 1;
        statePtr += *(s16 *)(entity + 0x22) * 2;
        {
            u8 stateByte = *statePtr;
            sub_080C31E0(entity, *(s32 *)(stateByte * 4 + *(u32 *)(entity + 0x14)));
        }
    }
}

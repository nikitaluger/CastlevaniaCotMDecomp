extern void stepAnimationTrack(void *, void *);
extern void copyPoseAttrs(void *, void *);
extern void sub_080C31E0(void *, void *);
extern u8 D_080CF800[];
extern u16 D_080CF888[];
extern u8 D_080CF5F8[];

void sub_0804692C(u8 *entity) {
    u8 *sprite;
    u8 *state;
    u8 *animTrack;
    u8 *children;
    u8 *base;
    u8 *p;
    u8 *p5;
    u16 *keys;
    u32 i;
    u32 index = 0;
    s32 vals[6];

    sprite = *(u8 **)(entity + 0x38);
    vals[5] = (s32)sprite;
    state = *(u8 **)(entity + 0x3C);
    animTrack = state + 0x34;
    children = state + 0x48;

    stepAnimationTrack(sprite, animTrack);

    i = 0;
    p = D_080CF800;
    p5 = p + 0x34;
    
    keys = D_080CF888;

    for (; i <= 12; i++) {
        if (*(u16 *)(vals[5] + 0x28) == *keys) {
            index = i;
            vals[0] = *p;
            vals[1] = D_080CF800[i + 0xD];
            vals[2] = (*(u8 *)((i + 0x1A) + (u8 *)D_080CF800));
            vals[3] = D_080CF800[i + 0x27];
            vals[4] = *p5;
            break;
        }
        p5++;
        p++;
        keys++;
    }

    copyPoseAttrs(*(void **)(state + 0x28), D_080CF5F8 + index * 8);
    copyPoseAttrs(*(void **)(children + 0), D_080CF5F8 + 0x68 + index * 8);
    copyPoseAttrs(*(void **)(children + 4), D_080CF5F8 + 0xD0 + index * 8);
    copyPoseAttrs(*(void **)(children + 8), D_080CF5F8 + 0x138 + index * 8);
    copyPoseAttrs(*(void **)(children + 0xC), D_080CF5F8 + 0x1A0 + index * 8);

    *(u8 *)(*(u8 **)(state + 0x28) + 1) = vals[0];
    *(u8 *)(*(u8 **)(children + 0) + 1) = vals[1];
    *(u8 *)(*(u8 **)(children + 4) + 1) = vals[2];
    *(u8 *)(*(u8 **)(children + 8) + 1) = vals[3];
    *(u8 *)(*(u8 **)(children + 0xC) + 1) = vals[4];

    if (*animTrack & 2)
        sub_080C31E0(entity, *(void **)(entity + 0x24));
}

extern void sub_0803B194(void *);
extern void sub_080113A8(void *, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_08012704(s32, s32, s32, s32, void *);
extern s32 sub_08012A94(s32, s32, s32);
extern void *sub_08038AEC(s32, s32);
extern void sub_080931E4(void *, void *, s32);
extern void sub_0803B140(u32, void *, void *, void *);
extern u8 gMainWorkspace[];

struct sub_08036304_Result {
    u16 f0;
    u16 pad;
    u32 f4;
    u32 f8;
};

void sub_08036304(void *entity) {
    u8 *self = entity;
    void *sprite = *(void **)(self + 0x38);
    u8 *component = *(u8 **)(self + 0x3C);
    u8 *animator = component + 0x34;
    u8 *pose = component + 0x48;
    s32 speed;
    s32 step;
    struct sub_08036304_Result res;
    void *target;

    sub_0803B194(component + 0x54);
    sub_080113A8(sprite, animator);
    if (*(u16 *)((u8 *)sprite + 0x28) == 0x1C) {
        if (*(u8 *)(pose + 0x18) == 0) {
            if (*(u16 *)((u8 *)sprite + 2) & 0x10)
                *(u32 *)(component + 0x10) = 0x40000;
            else
                *(u32 *)(component + 0x10) = 0xFFFC0000;
            *(u8 *)(pose + 0x18) = 1;
        }
    } else {
        if (*(u8 *)(pose + 0x18) != 0 && *(u32 *)(component + 0x10) != 0) {
            if (*(u16 *)((u8 *)sprite + 2) & 0x10)
                *(u32 *)(component + 0x10) = *(u32 *)(component + 0x10) + 0xFFFF0000;
            else
                *(u32 *)(component + 0x10) = *(u32 *)(component + 0x10) + 0x10000;
        }
    }
    sub_08011EE8(component, 0x16C1, 0);

    if (*(u16 *)((u8 *)sprite + 0x28) == 0x22 && *(u8 *)(pose + 0x18) != 2 &&
        *(u32 *)(component + 0x10) == 0) {
        speed = (*(u16 *)((u8 *)sprite + 2) & 0x10) ? 0x220000 : -0x220000;
        sub_08012704(*(s32 *)(component + 8), *(s32 *)(component + 0xC), speed, 0, &res);
        if ((res.f0 & 1) != 0) goto set_state;
        if ((res.f0 & 2) != 0) goto set_state;
        if (sub_08012A94(res.f4, res.f8, 2) != 0) goto set_state;
        target = sub_08038AEC(*(u32 *)(gMainWorkspace + 0x1870), 0xE9);
        if (target == 0) goto set_state;
        *(u32 *)((u8 *)target + 0x4C) = res.f4;
        *(u32 *)((u8 *)target + 0x5C) = res.f8;
        if ((*(u16 *)((u8 *)sprite + 2) & 0x10) != 0)
            *(u8 *)((u8 *)target + 0x6C) = 1;
        else
            *(u8 *)((u8 *)target + 0x6C) = 0;
        *(u8 *)((u8 *)target + 0x70) = 0;
    }
set_state:
    *(u8 *)(pose + 0x18) = 2;
    if (*(u8 *)animator & 2) {
        step = *(s16 *)(self + 0x22);
        *(u8 *)(self + step * 2 + 0x19) = 0;
        {
            u32 *cbTable = (u32 *)0x080CEF8A;
            sub_080931E4(self + 0x18, self + 0x22, *cbTable);
        }
    }
    sub_0803B140(3, sprite, pose + 0xC, (void *)0x080CEF8A);
}

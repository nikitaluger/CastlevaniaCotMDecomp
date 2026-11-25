extern void sub_0806D588(void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0808C9BC(void *);
extern s32 D_08671BB0[];

struct Sprite {
    u8 pad0[4];
    u16 unk4;
    u16 unk6;
    u16 unk8;
};

void sub_0808C694(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *params = *(u8 **)(self + 0x6C);
    u8 *params2 = params + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    s32 *anim;
    s32 index;

    index = *(s32 *)(self + 0x7C);
    *(s32 *)(params2 + 0x30) = index;
    anim = (s32 *)(0x080F3DFC + index * 16);
    *(s32 *)(params2 + 0x18) = *(s32 *)(self + 0x24);
    *(s32 *)(self + 0x24) = (s32)sub_0808C9BC;
    *(s32 *)(sprite + 0x24) = anim[2];
    *(s32 *)(params + 4) = anim[0];
    *(s32 *)(params2 + 4) = anim[1];
    sub_0806D588(sprite);
    ((struct Sprite *)sprite)->unk4 = 0x100;
    ((struct Sprite *)sprite)->unk6 = 0x800;
    ((struct Sprite *)sprite)->unk8 = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptHandlers = D_08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *stepBase = self + 0x18;
        s16 idx = *(s16 *)(self + 0x22);
        stepBase += idx * 2;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *stepBase * 4));
    }
}

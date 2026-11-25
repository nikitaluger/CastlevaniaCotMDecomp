struct S_02025FF0 { u8 _0[0x174C]; s32 v174C; s32 v1750; };
extern struct S_02025FF0 D_02025FF0;
extern s32 D_08102064[];
typedef struct { s32 a; s32 b; } Pair;
extern Pair D_08102084[];

s32 sub_08005910(s32, s32);
s32 sub_080147A4(s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

void sub_080A6498(void *arg0) {
    u8 *r3base;
    u8 *r6ptr;
    s32 z;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 res;
    s32 *cb8;
    s32 *cb0;

    r3base = *(void **)((u8 *)arg0 + 0x3C);
    r6ptr = (u8 *)r3base + 0x48;
    temp_r0 = *(s32 *)((u8 *)r3base + 0x12C) + 1;
    *(s32 *)((u8 *)r3base + 0x12C) = temp_r0;
    if (temp_r0 == 6) {
        *(s32 *)((u8 *)r3base + 0x12C) = 0;
        temp_r0_2 = *(s32 *)((u8 *)r3base + 0x128) + 1;
        *(s32 *)((u8 *)r3base + 0x128) = temp_r0_2;
        if (temp_r0_2 == 4) {
            *(s32 *)((u8 *)r3base + 0x128) = 0;
        }
        z = D_08102064[*(s32 *)((u8 *)r3base + 0x128)];
        *((u8 *)r3base + 0xEE) = z;
    }
    if (*(((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) == 0x48) {
        res = sub_08005910(D_02025FF0.v1750 - (*(s32 *)((u8 *)r6ptr + 0x94) + *(s32 *)((u8 *)arg0 + 0x6C)), D_02025FF0.v174C - (*(s32 *)((u8 *)r6ptr + 0x90) + *(s32 *)((u8 *)arg0 + 0x5C)));
        *(s32 *)((u8 *)r6ptr + 0xE8) = res;
        res = sub_080147A4(D_08102084[*(u8 *)((u8 *)arg0 + 0x4C)].a, D_08102084[*(u8 *)((u8 *)arg0 + 0x4C)].b);
        if (res != 0) {
            *(((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x17) = 0;
            cb8 = (s32 *)0x08671BD8;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0, *cb8);
            return;
        }
        *(((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) = res;
        cb0 = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *cb0);
    }
}

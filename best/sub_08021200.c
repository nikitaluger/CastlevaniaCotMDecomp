void setAnimationFrame(s32, void *, s32, s32);
void *sub_0805FAEC(s32, s32);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 {
    u8 _0x000[0x1870];
    u32 v;
};
extern struct S_02025FF0 gMainWorkspace;

void sub_08021200(void *arg0) {
    s32 v38 = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *p = *(u8 **)((u8 *)arg0 + 0x3C);

    setAnimationFrame(v38, p + 0x34, 0xB, 1);
    if (*(u16 *)((u8 *)arg0 + 0x6C) & 1) {
        void *r2 = sub_0805FAEC(gMainWorkspace.v, 0x9D);
        if (r2 != 0) {
            s32 x = *(s32 *)(p + 8);
            s32 sx;
            if (x < 0) {
                x += 0xFFFF;
            }
            sx = x >> 16;
            *(s16 *)((u8 *)r2 + 0x4C) = sx;

            {
                s32 y = *(s32 *)(p + 0xC);
                s32 sy;
                if (y < 0) {
                    y += 0xFFFF;
                }
                sy = y >> 16;
                *(s16 *)((u8 *)r2 + 0x54) = sy;
            }
        }
        ((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2)[0x19] = 0;
        {
            void **pp = (void **)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
        }
    }
}

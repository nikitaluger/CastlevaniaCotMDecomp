extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0801165C(void *, s32);
extern void sub_080113A8(s32, void *);
extern void sub_08014588(s32, s32);

/* While the work value at +0x20 is zero, set byte +0x80 of the object at
 * (entity+0x30); once the entity's wait byte reaches 0x78, clear it and advance
 * the command script through the 0x08671BD0 handler table. */
void sub_080391BC(void *arg0) {
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    if (*(s16 *)((u8 *)work + 0x20) == 0) {
        *(u8 *)((u8 *)*(void **)((u8 *)arg0 + 0x30) + 0x80) = 1;
    }
    {
        s16 step = *(s16 *)((u8 *)arg0 + 0x22);
        u8 *slot = (u8 *)((step << 1) + (u32)arg0);
        if (*(u8 *)(slot + 0x19) == 0x78) {
            s32 *script;
            *(u8 *)(slot + 0x19) = 0;
            script = (s32 *)0x08671BD0;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0, *script);
        }
    }
}

extern void sub_080C31E4(void *, void *, s32);
struct Z { u8 b; u16 h; };
static inline u8 zero_b(void) { u8 v = 0; return v; }
static inline u16 zero_h(void) { u16 v = 0; return v; }

/* Initialize the object's state block and script slot, then start its script
 * from the 0x18/0x22 fields. */
void sub_08022FBC(void *arg0)
{
    u8 *obj = (u8 *)arg0;
    u8 *state = *(u8 **)(obj + 0x3C) + 0x48;
    register u16 halfZero = zero_h();
    register u8 byteZero = zero_b();

    *(u16 *)(state + 8) = 0x10;
    *(u16 *)(state + 0x0E) = 0x0A;
    *(u16 *)(state + 0x12) = 0x3C;
    *(u16 *)(state + 0x10) = halfZero;
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = byteZero;
    {
        void **pp = (void **)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, (s32)*pp);
    }
}

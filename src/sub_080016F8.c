extern void sub_080C31E0(void *obj, s32 handler);
extern s32 D_0866C1B8[];

/* Dispatch one update to the object's handler: if the script flag (bit 0x800 at
 * +2) is set, advance the script step counter and call the handler installed at
 * +0x14; otherwise call the per-type handler from the type table (the object id
 * at +0 masked with 0x3FFF). */
void sub_080016F8(void *arg0)
{
    u8 *obj = arg0;
    if (*(u16 *)(obj + 2) & 0x800) {
        *(u16 *)(obj + 0x22) += 1;
        sub_080C31E0(arg0, *(s32 *)(obj + 0x14));
    } else {
        s32 type = *(u16 *)obj & 0x3FFF;
        sub_080C31E0(arg0, *(s32 *)((u32)&D_0866C1B8[0] + type * 4));
    }
}

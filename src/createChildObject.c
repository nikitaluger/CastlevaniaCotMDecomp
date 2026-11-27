void *sub_0800141C(s32);
extern void sub_08002D7C(void);
extern u16 D_0202574E[];

/* Allocates an object of `kind`, links it as the first child of `parent` when
 * one is given, installs the recursive-destruct callback, and bumps the
 * per-kind instance counter. */
void *sub_08001480(void *parent, s32 kind) {
    void *obj;
    obj = sub_0800141C(kind);
    if (obj != NULL) {
        u32 invalidId;

        kind &= 0x3FFF;
        invalidId = 0xFFFF;
        *(u16 *)((u8 *)obj + 0x22) = invalidId;
        if (parent != NULL) {
            *(void **)((u8 *)obj + 0x28) = parent;
            *(void **)((u8 *)obj + 0x2C) = *(void **)((u8 *)parent + 0x30);
            *(void **)((u8 *)parent + 0x30) = obj;
        }
        *(void **)((u8 *)obj + 0x24) = &sub_08002D7C;
        {
            s32 counterIdx = kind;
            counterIdx <<= 1;
            *(u16 *)((u8 *)D_0202574E + counterIdx) += 1;
        }
    }
    return obj;
}

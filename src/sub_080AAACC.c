/* Destroy one child object: the harness calls the callback stored at +0x24. */
extern void sub_080C31E0(void *, s32);
/* Allocate one budgeted child object of the given type under `owner`, or NULL. */
extern void *sub_0805FAEC(void *, s32);

/* Shared child-object list: gMainWorkspace+0x1870 points at the owner object; its
 * +0x30 is the first live child. Each child starts with an s16 type id, keeps a
 * destroy argument at +0x24 and links to the next child at +0x2C. */
struct ObjectRoot { u8 _0[0x1870]; u32 owner; };
extern struct ObjectRoot gMainWorkspace;

/* Kill every live child of type 0x19E (0xCF << 1) in the shared list. */
void sub_080AAACC(void) {
    void *owner = (void *)gMainWorkspace.owner;
    void *child = *(void **)((u8 *)owner + 0x30);
    if (child != NULL) {
        s32 typeId = 0xCF << 1;
        do {
            if (*(s16 *)child == typeId) {
                sub_080C31E0(child, *(s32 *)((u8 *)child + 0x24));
            }
            child = *(void **)((u8 *)child + 0x2C);
        } while (child != NULL);
    }
}

/* Spawn a type-0x1A0 child and fill its +0x4C/+0x5C/+0x6C parameter slots. */
void sub_080AAB04(void *parent, s32 value1, s32 value2) {
    void *obj = sub_0805FAEC((void *)gMainWorkspace.owner, 0xD0 << 1);
    if (obj != 0) {
        *(s32 *)((u8 *)obj + 0x4C) = value1;
        *(s32 *)((u8 *)obj + 0x5C) = value2;
        *(s32 *)((u8 *)obj + 0x6C) = *(s32 *)((u8 *)*(void **)((u8 *)parent + 0x38) + 0x24);
    }
}

/* Spawn a type-0x1A1 child, storing two word parameters and a byte flag at +0x6C. */
void sub_080AAB3C(s32 value1, s32 value2, u8 flag) {
    void *obj = sub_0805FAEC((void *)gMainWorkspace.owner, 0x1A1);
    if (obj != 0) {
        u8 *p;
        *(s32 *)((u8 *)obj + 0x4C) = value1;
        *(s32 *)((u8 *)obj + 0x5C) = value2;
        p = (u8 *)obj + 0x6C;
        *p = flag;
    }
}

/* Spawn a type-0x1A4 child, storing a byte flag at +0x7C and two word parameters. */
void sub_080AAC20(u8 flag, s32 value1, s32 value2) {
    void *obj = sub_0805FAEC((void *)gMainWorkspace.owner, 0xD2 << 1);
    if (obj != 0) {
        u8 *p = (u8 *)obj + 0x7C;
        *p = flag;
        *(s32 *)((u8 *)obj + 0x4C) = value1;
        *(s32 *)((u8 *)obj + 0x5C) = value2;
    }
}

extern void sub_080B7298(void *);
extern void sub_080C31E0(void *, void *);

struct S_02025FF0 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

/* Scans both child lists (this object's and the global root's); children of a
 * specific kind have their position copied out and an effect triggered. */
void sub_080B7454(void *parent) {
    void *child;

    child = *(void **)((u8 *)parent + 0x30);
    while (child != 0) {
        u16 kind = *(u16 *)child - 0x1C6;
        if (kind <= 3) {
            sub_080B7298(child);
            sub_080C31E0(child, *(void **)((u8 *)child + 0x24));
        }
        child = *(void **)((u8 *)child + 0x2C);
    }

    child = *(void **)(gMainWorkspace.v + 0x30);
    while (child != 0) {
        u16 kind = *(u16 *)child - 0x1C6;
        if (kind <= 3) {
            sub_080B7298(child);
            sub_080C31E0(child, *(void **)((u8 *)child + 0x24));
        }
        child = *(void **)((u8 *)child + 0x2C);
    }
}

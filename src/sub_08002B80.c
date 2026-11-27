void sub_08002B44(s16);
void *createChildObject(void *, u32);
void sub_08002C5C(void *);
extern void *D_02025B80;
struct Entry { u8 pad[4]; u16 childKind; u8 pad2[2]; };
extern struct Entry D_0866CA04[];
struct Obj { u8 pad[2]; u16 flags; u8 pad2[0x10]; u32 updateFn; u8 pad3[0x34]; u32 child; };

/* Create a manager object for kind: allocate it and its table-defined child,
 * link the two, set the active flag and install the update callback. */
void sub_08002B80(s16 arg0) {
    u16 uarg = arg0;
    void *res;
    struct Obj *obj;
    sub_08002B44(arg0);
    D_02025B80 = createChildObject(0, 1);
    *(u16 *)((u8 *)D_02025B80 + 0x38) = uarg;
    res = createChildObject(D_02025B80, D_0866CA04[arg0].childKind);
    obj = D_02025B80;
    obj->child = (u32)res;
    obj->flags |= 0x4000;
    obj->updateFn = (u32)sub_08002C5C;
}

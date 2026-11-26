void *sub_08001480(void *parent, s32 kind);
s32 sub_0808D330(void);

struct ObjNode {
    s16 kind;
    u8 pad02[0x2A];
    struct ObjNode *next;
};

struct ObjList {
    u8 pad0[0x30];
    struct ObjNode *firstChild;
};

struct S_02025FF0 {
    u8 pad0[0x14DC];
    u16 w14DC;
    u16 w14DE;
    u8 pad14E0[0x1874 - 0x14E0];
    struct ObjList *p1874;
};
extern struct S_02025FF0 gMainWorkspace;

/* Spawn a single helper object of kind 0x212 under the object list, storing
 * `data` in its field at +0x3C, unless such an object already exists. */
void sub_0808D2FC(void *data)
{
    if (sub_0808D330() != 0) {
        void *obj = sub_08001480(gMainWorkspace.p1874, 0x212);
        if (obj != 0) {
            *(void **)((u8 *)obj + 0x3C) = data;
        }
    }
}

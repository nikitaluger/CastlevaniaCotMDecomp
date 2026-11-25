extern void sub_08002E34(void);
extern void sub_08001738(void *root);
extern void sub_08003AC8(void);
extern void sub_080062AC(void);
extern void sub_08002FD4(void);

/* Node of the object tree: id at +0, parent at +0x28, next sibling at +0x2C,
 * first child at +0x30. */
struct ObjNode;

/* The main-object manager. +0x4C holds the root of the object tree that
 * sub_08001738 walks. */
struct MainObj {
    u8 pad[0x4C];
    struct ObjNode *root;
};

/* One frame of the object system: retire expired timed objects, walk the tree
 * rooted at mainObj->root and update every live object, refresh the affine/input
 * state, then project entities to screen space and build the display lists. */
void sub_08002C74(struct MainObj *mainObj) {
    sub_08002E34();
    sub_08001738(mainObj->root);
    sub_08003AC8();
    sub_080062AC();
    sub_08002FD4();
}

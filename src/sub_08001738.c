extern void sub_080016F8(void *);

/* Node of the object tree: id at +0, parent at +0x28, next sibling at +0x2C,
 * first child at +0x30. */
struct ObjNode {
    s16 id;
    u8 pad[0x26];
    struct ObjNode *parent;
    struct ObjNode * volatile next;
    struct ObjNode * volatile child;
};

/* One frame of the object system: depth-first walk of the tree from the given
 * root (down to first children, across to next siblings, back up to parents) and
 * one update dispatch for every live object (id > 0). */
void sub_08001738(void *arg0) {
    struct ObjNode *obj = arg0;
    struct ObjNode *root = arg0;
    goto visit;
down:
    obj = obj->child;
visit:
    if ((s32)obj->id > 0) sub_080016F8(obj);
    if (obj->child != 0) goto down;
    goto check;
up:
    if (obj->parent == 0) goto done;
    obj = obj->parent;
check:
    if (obj == root) goto done;
    if (obj->next == 0) goto up;
    obj = obj->next;
    goto visit;
done:
    return;
}

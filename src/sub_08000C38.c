s32 *sub_08000C0C(s32);                         /* extern */

/* Push a node grabbed from the object pool onto the front of a singly-linked
 * list: the node's next pointer is set to the current head, then the head is
 * advanced to the new node. */
void sub_08000C38(s32 **pList, s32 value) {
    s32 *node;

    node = sub_08000C0C(value);
    if (node != NULL) {
        *node = *pList;
        *pList = node;
    }
}

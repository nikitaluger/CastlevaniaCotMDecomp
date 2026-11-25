/* Pushes a node onto the head of a singly-linked list: the node's next pointer
 * (at +0xC) receives the old head, then the head points at the node. */
void sub_08000DD8(void **head, void *node) {
    *(void **)((s8 *)node + 0xC) = (void *)*head;
    *head = node;
}

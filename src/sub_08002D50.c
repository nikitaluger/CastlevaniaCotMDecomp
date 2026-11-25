typedef void (*Callback)(void *);

void sub_080C31E0(void *, void *);

struct Child {
    u8 pad[0x24];
    Callback func;      /* per-frame update callback */
    u8 pad28[4];
    struct Child *next; /* next sibling */
};

struct Parent {
    u8 pad[0x30];
    struct Child *head; /* first child */
};

/* Run the update callback of every child of `parent`, walking the sibling chain. */
void sub_08002D50(struct Parent *parent)
{
    struct Child *child = parent->head;
    if (child != 0) {
        sub_080C31E0(child, (void *)child->func);
        child = child->next;
        if (child != 0) {
            struct Child *next;
            do {
                next = child->next;
                sub_080C31E0(child, (void *)child->func);
                child = next;
            } while (child != 0);
        }
    }
}

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
void sub_080B31AC(struct Parent *parent)
{
    struct Child *child = parent->head;
    if (child != NULL) {
        do {
            sub_080C31E0(child, (void *)child->func);
            child = child->next;
        } while (child != NULL);
    }
}

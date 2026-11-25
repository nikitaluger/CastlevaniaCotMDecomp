typedef void (*Callback)(void *);

void sub_08002C94(void *);
void sub_080C31E0(void *, void *);

struct Child {
    u8 pad[0x24];
    Callback func;
    u8 pad28[4];
    struct Child *next;
};

struct Parent {
    u8 pad[0x30];
    struct Child *head;
};

/* Invoke each child's callback in list order, then destroy the object (unlink
 * it and release its resources) through sub_08002C94. */
void sub_08002D7C(struct Parent *arg0)
{
    struct Child *child = arg0->head;
    if (child) {
        Callback fp = child->func;
        sub_080C31E0(child, (void *)fp);
        child = child->next;
        if (child) {
            do {
                struct Child *next = child->next;
                Callback fp2 = child->func;
                sub_080C31E0(child, (void *)fp2);
                child = next;
            } while (child);
        }
    }
    sub_08002C94(arg0);
}

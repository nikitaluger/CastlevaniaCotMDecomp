struct HandlerOwner {
    u8 pad[0x24];
    void *handler;
};

/* Hand the current behavior handler off to another object, then install a new one. */
void sub_08014288(struct HandlerOwner *obj, struct HandlerOwner *other, void *handler) {
    other->handler = obj->handler;
    obj->handler = handler;
}

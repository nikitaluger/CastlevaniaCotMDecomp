struct Entity_0x24 {
    u8 _0[0x24];
    void (*update)(struct Entity_0x24 *);
};

/* Invoke the update callback saved in the entity at +0x24. */
void sub_08002B38(struct Entity_0x24 *entity) {
    entity->update(entity);
}

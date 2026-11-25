s32 sub_08011650(s32);
void sub_08015974(void *);
void sub_080161F0(void *);
void sub_08016678(void *);
void sub_080C31E0(void *, s32);

/* Destructor callback for an entity: unlink/free the resources and sub-objects
 * it owns, then free the entity itself. */
void sub_080B4ACC(void *entity) {
    s32 resource;
    void *data;

    resource = *(s32 *)((u8 *)entity + 0x38);
    data = *(void **)((u8 *)entity + 0x3C);
    if (*(void **)((u8 *)data + 0x28) != NULL) {
        sub_080161F0(*(void **)((u8 *)data + 0x28));
    }
    if (*(void **)((u8 *)data + 0x48) != NULL) {
        sub_080161F0(*(void **)((u8 *)data + 0x48));
    }
    sub_08011650(resource);
    if (*(void **)((u8 *)data + 0x2C) != NULL) {
        sub_08015974(*(void **)((u8 *)data + 0x2C));
    }
    sub_08016678(entity);
    sub_080C31E0(entity, *(s32 *)((u8 *)data + 0x24));
}

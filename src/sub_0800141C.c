void *sub_080C31DC(void *);
void sub_080C2E4C(void *, int);

#define ENTITY_SIZE 0xBC

struct Entity { s16 type; };

/* Allocate a zero-filled entity object of `kind` (< 0xBC bytes) through the
 * allocator callback stored at 0x08671C08; return NULL when it fails. */
void *sub_0800141C(s32 kind) {
    void *obj;
    obj = sub_080C31DC(*(void**)0x08671C08);
    if (obj == 0) {
        return 0;
    }
    sub_080C2E4C(obj, ENTITY_SIZE);
    ((struct Entity *)obj)->type = (s16)kind;
    return obj;
}

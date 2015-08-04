#include <soundpipe.h>
#include "sporth.h"

enum {
PLUMBER_CREATE,
PLUMBER_INIT,
PLUMBER_COMPUTE,
PLUMBER_DESTROY,
PLUMBER_OK,
PLUMBER_NOTOK,
PLUMBER_PANIC
};

typedef struct plumber_ftbl {
    sp_ftbl *ft;
    char *name;
    struct plumber_ftbl *next;
} plumber_ftbl;

typedef struct {
    uint32_t nftbl;
    plumber_ftbl root;
    plumber_ftbl *last;
} plumber_ftentry;

typedef struct plumber_pipe {
    uint32_t type;
    size_t size;
    void *ud;
    struct plumber_pipe *next;
} plumber_pipe;

typedef struct plumber_data {
    int nchan;
    int mode;
    sp_data *sp;
    sporth_data sporth;
    sp_ftbl tbl_stack[32];
    uint32_t npipes;
    plumber_pipe root;
    plumber_pipe *last;

    plumber_ftentry ftmap[256];
} plumber_data;

int plumber_init(plumber_data *plumb);
int plumber_clean(plumber_data *plumb);
int plumber_add_float(plumber_data *plumb, float num);
int plumber_add_string(plumber_data *plumb, const char *str);
int plumber_add_module(plumber_data *plumb, 
        uint32_t id, size_t size, void *ud);
int plumber_compute(plumber_data *plumb, int mode);
int plumber_parse(plumber_data *plumb, const char *filename);
int plumber_gettype(plumber_data *plumb, char *str, int mode);
int plumber_show_pipes(plumber_data *plumb);
int plumber_error(plumber_data *plumb, const char *str);
int plumber_ftmap_init(plumber_data *plumb);
int plumber_ftmap_add(plumber_data *plumb, const char *str, sp_ftbl *ft);
int plumber_ftmap_search(plumber_data *plumb, const char *str, sp_ftbl **ft);
int plumber_ftmap_destroy(plumber_data *plumb);
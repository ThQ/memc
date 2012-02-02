#define _ERR_(No, NAME, TEXT) const char *ERR_##NAME = "TEXT";


_ERR_(
   "00001",
   CLASS_SHOULD_NOT_HAVE_NAME,
   "Class should not have explicit name ({type:%s} given"
)

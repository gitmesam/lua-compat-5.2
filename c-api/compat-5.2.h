#ifndef COMPAT52_H_
#define COMPAT52_H_

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"


#if defined(COMPAT52_PREFIX)
/* - change the symbol names of functions to avoid linker conflicts
 * - compat-5.2.c needs to be compiled (and linked) separately
 */
#  if !defined(COMPAT52_API)
#    define COMPAT52_API extern
#  endif
#  undef COMPAT52_INCLUDE_SOURCE
#else /* COMPAT52_PREFIX */
/* - make all functions static and include the source.
 * - compat-5.2.c doesn't need to be compiled (and linked) separately
 */
#  define COMPAT52_PREFIX compat52
#  undef COMPAT52_API
#  if defined(__GNUC__) || defined(__clang__)
#    define COMPAT52_API __attribute__((__unused__)) static
#  else
#    define COMPAT52_API static
#  endif
#  define COMPAT52_INCLUDE_SOURCE
#endif /* COMPAT52_PREFIX */

#define COMPAT52_CONCAT_HELPER(a, b) a##b
#define COMPAT52_CONCAT(a, b) COMPAT52_CONCAT_HELPER(a, b)


/* declarations for Lua 5.0 only */
#if !defined(LUA_VERSION_NUM)

#define LUA_QL(x) "'" x "'"
#define LUA_QS LUA_QL("%s")

#define luaL_Reg luaL_reg

#define luaL_opt(L, f, n, d) \
  (lua_isnoneornil(L, n) ? (d) : f(L, n))

#define luaL_addchar(B,c) \
  ((void)((B)->p < ((B)->buffer+LUAL_BUFFERSIZE) || luaL_prepbuffer(B)), \
   (*(B)->p++ = (char)(c)))

#define lua_createtable(L, narr, nrec) \
  ((void)(narr),(void)(nrec),lua_newtable(L))

#endif /* Lua 5.0 */



/* declarations for Lua 5.1 only */
#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM == 501

/* LuaJIT doesn't define these unofficial macros ... */
#if !defined(LUAI_INT32)
#  include <limits.h>
#  if INT_MAX-20 < 32760
#    define LUAI_INT32  long
#    define LUAI_UINT32 unsigned long
#  elif INT_MAX > 2147483640L
#    define LUAI_INT32  int
#    define LUAI_UINT32 unsigned int
#  else
#    error "could not detect suitable lua_Unsigned datatype"
#  endif
#endif

#ifndef LUA_OPADD
#  define LUA_OPADD 0
#endif
#ifndef LUA_OPSUB
#  define LUA_OPSUB 1
#endif
#ifndef LUA_OPMUL
#  define LUA_OPMUL 2
#endif
#ifndef LUA_OPDIV
#  define LUA_OPDIV 3
#endif
#ifndef LUA_OPMOD
#  define LUA_OPMOD 4
#endif
#ifndef LUA_OPPOW
#  define LUA_OPPOW 5
#endif
#ifndef LUA_OPUNM
#  define LUA_OPUNM 6
#endif
#ifndef LUA_OPEQ
#  define LUA_OPEQ 0
#endif
#ifndef LUA_OPLT
#  define LUA_OPLT 1
#endif
#ifndef LUA_OPLE
#  define LUA_OPLE 2
#endif

typedef LUAI_UINT32 lua_Unsigned;

typedef struct luaL_Buffer_52 {
  luaL_Buffer b; /* make incorrect code crash! */
  char *ptr;
  size_t nelems;
  size_t capacity;
  lua_State *L2;
} luaL_Buffer_52;
#define luaL_Buffer luaL_Buffer_52


#define lua_tounsigned(L, i) lua_tounsignedx(L, i, NULL)

#define lua_rawlen(L, i) lua_objlen(L, i)

#define lua_arith COMPAT52_CONCAT(COMPAT52_PREFIX, _arith)
COMPAT52_API void lua_arith (lua_State *L, int op);

#define lua_compare COMPAT52_CONCAT(COMPAT52_PREFIX, _compare)
COMPAT52_API int lua_compare (lua_State *L, int idx, int idx2, int op);

#define lua_pushunsigned COMPAT52_CONCAT(COMPAT52_PREFIX, _pushunsigned)
COMPAT52_API void lua_pushunsigned (lua_State *L, lua_Unsigned n);

#define luaL_checkunsigned COMPAT52_CONCAT(COMPAT52_PREFIX, L_checkunsigned)
COMPAT52_API lua_Unsigned luaL_checkunsigned (lua_State *L, int i);

#define lua_tounsignedx COMPAT52_CONCAT(COMPAT52_PREFIX, _tounsignedx)
COMPAT52_API lua_Unsigned lua_tounsignedx (lua_State *L, int i, int *isnum);

#define luaL_optunsigned COMPAT52_CONCAT(COMPAT52_PREFIX, L_optunsigned)
COMPAT52_API lua_Unsigned luaL_optunsigned (lua_State *L, int i, lua_Unsigned def);

#define lua_tointegerx COMPAT52_CONCAT(COMPAT52_PREFIX, _tointegerx)
COMPAT52_API lua_Integer lua_tointegerx (lua_State *L, int i, int *isnum);

#define lua_len COMPAT52_CONCAT(COMPAT52_PREFIX, _len)
COMPAT52_API void lua_len (lua_State *L, int i);

#define luaL_len COMPAT52_CONCAT(COMPAT52_PREFIX, L_len)
COMPAT52_API int luaL_len (lua_State *L, int i);

#define luaL_tolstring COMPAT52_CONCAT(COMPAT52_PREFIX, L_tolstring)
COMPAT52_API const char *luaL_tolstring (lua_State *L, int idx, size_t *len);

#define luaL_requiref COMPAT52_CONCAT(COMPAT52_PREFIX, L_requiref)
COMPAT52_API void luaL_requiref (lua_State *L, char const* modname, lua_CFunction openf, int glb);

#define luaL_buffinit COMPAT52_CONCAT(COMPAT52_PREFIX, _buffinit_52)
COMPAT52_API void luaL_buffinit (lua_State *L, luaL_Buffer_52 *B);

#define luaL_prepbuffsize COMPAT52_CONCAT(COMPAT52_PREFIX, _prepbufsize_52)
COMPAT52_API char *luaL_prepbuffsize (luaL_Buffer_52 *B, size_t s);

#define luaL_addlstring COMPAT52_CONCAT(COMPAT52_PREFIX, _addlstring_52)
COMPAT52_API void luaL_addlstring (luaL_Buffer_52 *B, const char *s, size_t l);

#define luaL_addvalue COMPAT52_CONCAT(COMPAT52_PREFIX, _addvalue_52)
COMPAT52_API void luaL_addvalue (luaL_Buffer_52 *B);

#define luaL_pushresult COMPAT52_CONCAT(COMPAT52_PREFIX, _pushresult_52)
COMPAT52_API void luaL_pushresult (luaL_Buffer_52 *B);

#undef luaL_buffinitsize
#define luaL_buffinitsize(L, B, s) \
  (luaL_buffinit(L, B), luaL_prepbuffsize(B, s))

#undef luaL_prepbuffer
#define luaL_prepbuffer(B) \
  luaL_prepbuffsize(B, LUAL_BUFFERSIZE)

#undef luaL_addchar
#define luaL_addchar(B, c) \
  ((void)((B)->nelems < (B)->capacity || luaL_prepbuffsize(B, 1)), \
   ((B)->ptr[(B)->nelems++] = (c)))

#undef luaL_addsize
#define luaL_addsize(B, s) \
  ((B)->nelems += (s))

#undef luaL_addstring
#define luaL_addstring(B, s) \
  luaL_addlstring(B, s, strlen(s))

#undef luaL_pushresultsize
#define luaL_pushresultsize(B, s) \
  (luaL_addsize(B, s), luaL_pushresult(B))

#endif /* Lua 5.1 */



/* declarations for both Lua 5.0 *and* Lua 5.1 */
#if !defined(LUA_VERSION_NUM) || LUA_VERSION_NUM == 501

#ifndef LUA_OK
#  define LUA_OK 0
#endif

#define lua_pushglobaltable(L) \
  lua_pushvalue(L, LUA_GLOBALSINDEX)

#ifndef luaL_newlibtable
#  define luaL_newlibtable(L, l) \
  (lua_createtable(L, 0, sizeof(l)/sizeof(*(l))-1))
#endif
#ifndef luaL_newlib
#  define luaL_newlib(L, l) \
  (luaL_newlibtable(L, l),luaL_setfuncs(L, l, 0))
#endif

#define lua_getuservalue(L, i) \
  (lua_getfenv(L, i))
#define lua_setuservalue(L, i) \
  (luaL_checktype(L, -1, LUA_TTABLE), lua_setfenv(L, i))

#define lua_callk(L, na, nr, ctx, cont) \
  ((void)(ctx),(void)(cont),lua_call(L, na, nr))
#define lua_pcallk(L, na, nr, err, ctx, cont) \
  ((void)(ctx),(void)(cont),lua_pcall(L, na, nr, err))

#define lua_absindex COMPAT52_CONCAT(COMPAT52_PREFIX, _absindex)
COMPAT52_API int lua_absindex (lua_State *L, int i);

#define lua_copy COMPAT52_CONCAT(COMPAT52_PREFIX, _copy)
COMPAT52_API void lua_copy (lua_State *L, int from, int to);

#define lua_rawgetp COMPAT52_CONCAT(COMPAT52_PREFIX, _rawgetp)
COMPAT52_API void lua_rawgetp (lua_State *L, int i, const void *p);

#define lua_rawsetp COMPAT52_CONCAT(COMPAT52_PREFIX, _rawsetp)
COMPAT52_API void lua_rawsetp (lua_State *L, int i, const void *p);

#define luaL_testudata COMPAT52_CONCAT(COMPAT52_PREFIX, L_testudata)
COMPAT52_API void *luaL_testudata (lua_State *L, int i, const char *tname);

#define lua_tonumberx COMPAT52_CONCAT(COMPAT52_PREFIX, _tonumberx)
COMPAT52_API lua_Number lua_tonumberx (lua_State *L, int i, int *isnum);

#define luaL_setfuncs COMPAT52_CONCAT(COMPAT52_PREFIX, L_setfuncs)
COMPAT52_API void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup);

#define luaL_setmetatable COMPAT52_CONCAT(COMPAT52_PREFIX, L_setmetatable)
COMPAT52_API void luaL_setmetatable (lua_State *L, const char *tname);

#define luaL_getsubtable COMPAT52_CONCAT(COMPAT52_PREFIX, L_getsubtable)
COMPAT52_API int luaL_getsubtable (lua_State *L, int i, const char *name);

#define luaL_traceback COMPAT52_CONCAT(COMPAT52_PREFIX, L_traceback)
COMPAT52_API void luaL_traceback (lua_State *L, lua_State *L1, const char *msg, int level);

#define luaL_fileresult COMPAT52_CONCAT(COMPAT52_PREFIX, L_fileresult)
COMPAT52_API int luaL_fileresult (lua_State *L, int stat, const char *fname);

#define luaL_checkversion COMPAT52_CONCAT(COMPAT52_PREFIX, L_checkversion)
COMPAT52_API void luaL_checkversion (lua_State *L);

#define luaL_execresult COMPAT52_CONCAT(COMPAT52_PREFIX, L_execresult)
COMPAT52_API int luaL_execresult (lua_State *L, int stat);

#endif /* Lua 5.0 and 5.1 */


#if defined(COMPAT52_INCLUDE_SOURCE)
#  include "compat-5.2.c"
#endif


#endif /* COMPAT52_H_ */


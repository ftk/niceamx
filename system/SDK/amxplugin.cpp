//----------------------------------------------------------
//
//   SA:MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2007 SA:MP Team
//
//----------------------------------------------------------

//
// This provides an interface to call amx library functions
// within samp-server.
//
// To use:
//    In your Initialize function, assign:
//        pawn::init_amx_funcs(data[PLUGIN_DATA_AMX]);
//
//
// To regenerate thunks for calls from prototypes in amx.h
// Run a regex with:
//   S: ^(.*)(AMXAPI amx_)([^(]*)([^\;]*);$
//   R: \ttypedef \1 AMXAPI (*amx_\3_t)\4;\n\tamx_\3 = reinterpret_cast<amx_\3_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_\3]));\n
//
// Run a regex with:
//   S: ^(.*)(AMXAPI amx_)([^(]*)([^\;]*);$
//   R: \1AMXAPI \(\*amx_\3\)\4;
//
//

//----------------------------------------------------------

#include "plugin.h"

#include <cstddef>

//----------------------------------------------------------

#ifdef  __cplusplus
extern  "C" {
#endif


uint16_t * AMXAPI (*amx_Align16)(uint16_t *v);
uint32_t * AMXAPI (*amx_Align32)(uint32_t *v);
#if defined _I64_MAX || defined HAVE_I64
  uint64_t * AMXAPI (*amx_Align64)(uint64_t *v);
#endif
int AMXAPI (*amx_Allot)(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
int AMXAPI (*amx_Callback)(AMX *amx, cell index, cell *result, cell *params);
int AMXAPI (*amx_Cleanup)(AMX *amx);
int AMXAPI (*amx_Clone)(AMX *amxClone, AMX *amxSource, void *data);
int AMXAPI (*amx_Exec)(AMX *amx, cell *retval, int index);
int AMXAPI (*amx_FindNative)(AMX *amx, const char *name, int *index);
int AMXAPI (*amx_FindPublic)(AMX *amx, const char *funcname, int *index);
int AMXAPI (*amx_FindPubVar)(AMX *amx, const char *varname, cell *amx_addr);
int AMXAPI (*amx_FindTagId)(AMX *amx, cell tag_id, char *tagname);
int AMXAPI (*amx_Flags)(AMX *amx,uint16_t *flags);
int AMXAPI (*amx_GetAddr)(AMX *amx,cell amx_addr,cell **phys_addr);
int AMXAPI (*amx_GetNative)(AMX *amx, int index, char *funcname);
int AMXAPI (*amx_GetPublic)(AMX *amx, int index, char *funcname);
int AMXAPI (*amx_GetPubVar)(AMX *amx, int index, char *varname, cell *amx_addr);
int AMXAPI (*amx_GetString)(char *dest,const cell *source, int use_wchar, size_t size);
int AMXAPI (*amx_GetTag)(AMX *amx, int index, char *tagname, cell *tag_id);
int AMXAPI (*amx_GetUserData)(AMX *amx, long tag, void **ptr);
int AMXAPI (*amx_Init)(AMX *amx, void *program);
int AMXAPI (*amx_InitJIT)(AMX *amx, void *reloc_table, void *native_code);
int AMXAPI (*amx_MemInfo)(AMX *amx, long *codesize, long *datasize, long *stackheap);
int AMXAPI (*amx_NameLength)(AMX *amx, int *length);
AMX_NATIVE_INFO * AMXAPI (*amx_NativeInfo)(const char *name, AMX_NATIVE func);
int AMXAPI (*amx_NumNatives)(AMX *amx, int *number);
int AMXAPI (*amx_NumPublics)(AMX *amx, int *number);
int AMXAPI (*amx_NumPubVars)(AMX *amx, int *number);
int AMXAPI (*amx_NumTags)(AMX *amx, int *number);
int AMXAPI (*amx_Push)(AMX *amx, cell value);
int AMXAPI (*amx_PushArray)(AMX *amx, cell *amx_addr, cell **phys_addr, const cell array[], int numcells);
int AMXAPI (*amx_PushString)(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int use_wchar);
int AMXAPI (*amx_RaiseError)(AMX *amx, int error);
int AMXAPI (*amx_Register)(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);
int AMXAPI (*amx_Release)(AMX *amx, cell amx_addr);
int AMXAPI (*amx_SetCallback)(AMX *amx, AMX_CALLBACK callback);
int AMXAPI (*amx_SetDebugHook)(AMX *amx, AMX_DEBUG debug);
int AMXAPI (*amx_SetString)(cell *dest, const char *source, int pack, int use_wchar, size_t size);
int AMXAPI (*amx_SetUserData)(AMX *amx, long tag, void *ptr);
int AMXAPI (*amx_StrLen)(const cell *cstring, int *length);
int AMXAPI (*amx_UTF8Check)(const char *string, int *length);
int AMXAPI (*amx_UTF8Get)(const char *string, const char **endptr, cell *value);
int AMXAPI (*amx_UTF8Len)(const cell *cstr, int *length);
int AMXAPI (*amx_UTF8Put)(char *string, char **endptr, int maxchars, cell value);

#ifdef  __cplusplus
}
#endif


namespace pawn {

enum 
{
	MAX_PLUGIN_AMX_EXPORT = 44
};

void init_amx_funcs(void * functable[MAX_PLUGIN_AMX_EXPORT])
{
	typedef uint16_t *  AMXAPI (*amx_Align16_t)(uint16_t *v);
	amx_Align16 = reinterpret_cast<amx_Align16_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Align16]));

	typedef uint32_t *  AMXAPI (*amx_Align32_t)(uint32_t *v);
	amx_Align32 = reinterpret_cast<amx_Align32_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Align32]));

#if defined _I64_MAX || defined HAVE_I64
	typedef   uint64_t *  AMXAPI (*amx_Align64_t)(uint64_t *v);
	amx_Align64 = reinterpret_cast<amx_Align64_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Align64]));

#endif
	typedef int  AMXAPI (*amx_Allot_t)(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
	amx_Allot = reinterpret_cast<amx_Allot_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Allot]));

	typedef int  AMXAPI (*amx_Callback_t)(AMX *amx, cell index, cell *result, cell *params);
	amx_Callback = reinterpret_cast<amx_Callback_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Callback]));

	typedef int  AMXAPI (*amx_Cleanup_t)(AMX *amx);
	amx_Cleanup = reinterpret_cast<amx_Cleanup_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Cleanup]));

	typedef int  AMXAPI (*amx_Clone_t)(AMX *amxClone, AMX *amxSource, void *data);
	amx_Clone = reinterpret_cast<amx_Clone_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Clone]));

	typedef int  AMXAPI (*amx_Exec_t)(AMX *amx, cell *retval, int index);
	amx_Exec = reinterpret_cast<amx_Exec_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Exec]));

	typedef int  AMXAPI (*amx_FindNative_t)(AMX *amx, const char *name, int *index);
	amx_FindNative = reinterpret_cast<amx_FindNative_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_FindNative]));

	typedef int  AMXAPI (*amx_FindPublic_t)(AMX *amx, const char *funcname, int *index);
	amx_FindPublic = reinterpret_cast<amx_FindPublic_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_FindPublic]));

	typedef int  AMXAPI (*amx_FindPubVar_t)(AMX *amx, const char *varname, cell *amx_addr);
	amx_FindPubVar = reinterpret_cast<amx_FindPubVar_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_FindPubVar]));

	typedef int  AMXAPI (*amx_FindTagId_t)(AMX *amx, cell tag_id, char *tagname);
	amx_FindTagId = reinterpret_cast<amx_FindTagId_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_FindTagId]));

	typedef int  AMXAPI (*amx_Flags_t)(AMX *amx,uint16_t *flags);
	amx_Flags = reinterpret_cast<amx_Flags_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Flags]));

	typedef int  AMXAPI (*amx_GetAddr_t)(AMX *amx,cell amx_addr,cell **phys_addr);
	amx_GetAddr = reinterpret_cast<amx_GetAddr_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_GetAddr]));

	typedef int  AMXAPI (*amx_GetNative_t)(AMX *amx, int index, char *funcname);
	amx_GetNative = reinterpret_cast<amx_GetNative_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_GetNative]));

	typedef int  AMXAPI (*amx_GetPublic_t)(AMX *amx, int index, char *funcname);
	amx_GetPublic = reinterpret_cast<amx_GetPublic_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_GetPublic]));

	typedef int  AMXAPI (*amx_GetPubVar_t)(AMX *amx, int index, char *varname, cell *amx_addr);
	amx_GetPubVar = reinterpret_cast<amx_GetPubVar_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_GetPubVar]));

	typedef int  AMXAPI (*amx_GetString_t)(char *dest,const cell *source, int use_wchar, size_t size);
	amx_GetString = reinterpret_cast<amx_GetString_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_GetString]));

	typedef int  AMXAPI (*amx_GetTag_t)(AMX *amx, int index, char *tagname, cell *tag_id);
	amx_GetTag = reinterpret_cast<amx_GetTag_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_GetTag]));

	typedef int  AMXAPI (*amx_GetUserData_t)(AMX *amx, long tag, void **ptr);
	amx_GetUserData = reinterpret_cast<amx_GetUserData_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_GetUserData]));

	typedef int  AMXAPI (*amx_Init_t)(AMX *amx, void *program);
	amx_Init = reinterpret_cast<amx_Init_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Init]));

	typedef int  AMXAPI (*amx_InitJIT_t)(AMX *amx, void *reloc_table, void *native_code);
	amx_InitJIT = reinterpret_cast<amx_InitJIT_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_InitJIT]));

	typedef int  AMXAPI (*amx_MemInfo_t)(AMX *amx, long *codesize, long *datasize, long *stackheap);
	amx_MemInfo = reinterpret_cast<amx_MemInfo_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_MemInfo]));

	typedef int  AMXAPI (*amx_NameLength_t)(AMX *amx, int *length);
	amx_NameLength = reinterpret_cast<amx_NameLength_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_NameLength]));

	typedef AMX_NATIVE_INFO *  AMXAPI (*amx_NativeInfo_t)(const char *name, AMX_NATIVE func);
	amx_NativeInfo = reinterpret_cast<amx_NativeInfo_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_NativeInfo]));

	typedef int  AMXAPI (*amx_NumNatives_t)(AMX *amx, int *number);
	amx_NumNatives = reinterpret_cast<amx_NumNatives_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_NumNatives]));

	typedef int  AMXAPI (*amx_NumPublics_t)(AMX *amx, int *number);
	amx_NumPublics = reinterpret_cast<amx_NumPublics_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_NumPublics]));

	typedef int  AMXAPI (*amx_NumPubVars_t)(AMX *amx, int *number);
	amx_NumPubVars = reinterpret_cast<amx_NumPubVars_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_NumPubVars]));

	typedef int  AMXAPI (*amx_NumTags_t)(AMX *amx, int *number);
	amx_NumTags = reinterpret_cast<amx_NumTags_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_NumTags]));

	typedef int  AMXAPI (*amx_Push_t)(AMX *amx, cell value);
	amx_Push = reinterpret_cast<amx_Push_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Push]));

	typedef int  AMXAPI (*amx_PushArray_t)(AMX *amx, cell *amx_addr, cell **phys_addr, const cell array[], int numcells);
	amx_PushArray = reinterpret_cast<amx_PushArray_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_PushArray]));

	typedef int  AMXAPI (*amx_PushString_t)(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int use_wchar);
	amx_PushString = reinterpret_cast<amx_PushString_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_PushString]));

	typedef int  AMXAPI (*amx_RaiseError_t)(AMX *amx, int error);
	amx_RaiseError = reinterpret_cast<amx_RaiseError_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_RaiseError]));

	typedef int  AMXAPI (*amx_Register_t)(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number);
	amx_Register = reinterpret_cast<amx_Register_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Register]));

	typedef int  AMXAPI (*amx_Release_t)(AMX *amx, cell amx_addr);
	amx_Release = reinterpret_cast<amx_Release_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_Release]));

	typedef int  AMXAPI (*amx_SetCallback_t)(AMX *amx, AMX_CALLBACK callback);
	amx_SetCallback = reinterpret_cast<amx_SetCallback_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_SetCallback]));

	typedef int  AMXAPI (*amx_SetDebugHook_t)(AMX *amx, AMX_DEBUG debug);
	amx_SetDebugHook = reinterpret_cast<amx_SetDebugHook_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_SetDebugHook]));

	typedef int  AMXAPI (*amx_SetString_t)(cell *dest, const char *source, int pack, int use_wchar, size_t size);
	amx_SetString = reinterpret_cast<amx_SetString_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_SetString]));

	typedef int  AMXAPI (*amx_SetUserData_t)(AMX *amx, long tag, void *ptr);
	amx_SetUserData = reinterpret_cast<amx_SetUserData_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_SetUserData]));

	typedef int  AMXAPI (*amx_StrLen_t)(const cell *cstring, int *length);
	amx_StrLen = reinterpret_cast<amx_StrLen_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_StrLen]));

	typedef int  AMXAPI (*amx_UTF8Check_t)(const char *string, int *length);
	amx_UTF8Check = reinterpret_cast<amx_UTF8Check_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_UTF8Check]));

	typedef int  AMXAPI (*amx_UTF8Get_t)(const char *string, const char **endptr, cell *value);
	amx_UTF8Get = reinterpret_cast<amx_UTF8Get_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_UTF8Get]));

	typedef int  AMXAPI (*amx_UTF8Len_t)(const cell *cstr, int *length);
	amx_UTF8Len = reinterpret_cast<amx_UTF8Len_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_UTF8Len]));

	typedef int  AMXAPI (*amx_UTF8Put_t)(char *string, char **endptr, int maxchars, cell value);
	amx_UTF8Put = reinterpret_cast<amx_UTF8Put_t>(reinterpret_cast<std::ptrdiff_t>(functable[PLUGIN_AMX_EXPORT_UTF8Put]));

}



}

//----------------------------------------------------------
// EOF

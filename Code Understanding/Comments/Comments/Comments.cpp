#include "../incall.h"

#ifdef _WIN32
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif //_WIN32

void CMnemaxBookingAgent::init()
{
	CLINICAL_RISK_LOW;
	book_query = NULL;
	objdata = NULL;
	indexBookingClient = NULL;
	dual_index_mode = pra_false;
}
CMnemaxBookingAgent::CMnemaxBookingAgent(E_MnemaxAgentType type, const char* idxpath) :
	CMnemaxAgent(type, idxpath)
{
	CLINICAL_RISK_LOW;
	init();
}
CMnemaxBookingAgent::~CMnemaxBookingAgent()
{
	CLINICAL_RISK_LOW;
	if (book_query) { Free_IdxResult(book_query); }
	if (objdata) { Free_IdxSdaEntry(objdata); }
}
int CMnemaxBookingAgent::PerformBooking()
{
	CLINICAL_RISK_HIGH;
	int return_value = LAI_SUCCESS;
	int lockRes = 0;
	lockRes = prasys_rwLockWrite("MANY_READ_SINGLE_WRITE_IDX_ACCES", INFINITE);
	if (lockRes == LAI_FAILURE) sln("lockwrite ERROR!");
	TIdxUpdateData idx_update;
	MnemaxDcmKeyMapperCache* key_cache = (MnemaxDcmKeyMapperCache*)cache->keycache;
	if (!ConnectToIndex())
	{
		sln("idx == NULL && !ConnectToIndex()");
		goto _end;
	}
	if (!prepareForBooking())
	{
		slexit("!prepareForBooking()", 0);
		return_value = LAI_FAILURE;
		goto _end;
	}
	memset(&idx_update, 0, sizeof(TIdxUpdateData));
	idx_update.user_data = this;
	idx_update.key = (char*)objdata->key;
	idx_update.key_len = objdata->hdr.key_len;
	idx_update.key_data_len = objdata->hdr.key_data_len;
	idx_update.cur_tree_level = 0;
	if (idx_update.key == NULL)
	{
		sln(" !!!WARNNING!!! PerformBooking - index update key is NULL!!!!!");
		return_value = LAI_FAILURE;
		goto _end;
	}
	if (idx_update.key_len == 0)
	{
		slnfmt1(" !!!WARNNING!!! Index key [%s] length is 0!!!!!", idx_update.key);
		return_value = LAI_FAILURE;
		goto _end;
	}
	if (idx_update.key_data_len < sizeof(TIdxSdaEntryFixed))
	{
		slnfmt2(" !!!WARNNING!!! Data length [%d] < than the size of
			'TIdxSdaEntryFixed'[% d] !!!!",idx_update.key_data_len, sizeof(TIdxSdaEntryFixed));
			return_value = LAI_FAILURE;
		goto _end;
	}
	int localCode = getGlbIdxWrapper()->Start_Index_Update_WF(idx, &idx_update);
	objdata->processing_code = localCode;
	// 2 = re-storing a deleted entry
	// 3 = re-storing an entry that is alredy in index ( multithread store of the same suid
	);
		if ((localCode != LAI_SUCCESS) && (localCode != 2))
		{
			slefmt1("Index Update Failed for key: [%s].", idx_update.key);
			return_value = LAI_FAILURE;
		}
	_end:
		if (dual_index_mode)
		{
			if (indexBookingClient == NULL)
			{
				indexBookingClient = new IndexHtAgentClient();
			}
				char key[2048];
			strncpy(key, (char*)objdata->key, objdata->hdr.key_len);
			key[objdata->hdr.key_len - 4] = 0;
			idx_update.key_data_len = objdata->hdr.key_data_len;
			int size_of_data = sizeof(tag_IdxSdaEntry);
			EIStatus newIdxBookingRes = indexBookingClient->AddRecord_IPC(key,
				(void*)objdata, size_of_data);
			if (newIdxBookingRes != EIS_OK)
			{
				slefmt1("[ERROR] AddRecord_IPC return error code = [%d]",
					newIdxBookingRes);
			}
			//sln("DUAL INDEX MODE ACTIVE!!");
		}
		lockRes = prasys_rwUnlock("MANY_READ_SINGLE_WRITE_IDX_ACCES", INFINITE);
		if (lockRes == LAI_FAILURE) sln("unlock ERROR!");
		return return_value;
}
int CMnemaxBookingAgent::SetObjRelPath(const char* path)
{
	CLINICAL_RISK_MEDIUM;
	if (objdata == NULL) { slexit("objdata == NULL", 0); return LAI_FAILURE; }
	strcpy(objdata->fx.relpath, path);
	return LAI_SUCCESS;
}
int CMnemaxBookingAgent::SetObjTarRelPath(const char* path)
{
	CLINICAL_RISK_MEDIUM;
	if (objdata == NULL) { slexit("objdata == NULL", 0); return LAI_FAILURE; }
	strcpy(objdata->fx.tar_relpath, path);
	return LAI_SUCCESS;
}
int CMnemaxBookingAgent::SetObjStateFlag(pra_byte _state)
{
	CLINICAL_RISK_MEDIUM;
	if (objdata == NULL) { slexit("objdata == NULL", 0); return LAI_FAILURE; }
	objdata->fx.obj_state = _state;
	return LAI_SUCCESS;
}
int CMnemaxBookingAgent::SetObjTarOffset(pra_ulong offset)
{
	CLINICAL_RISK_MEDIUM;
	if (objdata == NULL) { slexit("objdata == NULL", 0); return LAI_FAILURE; }
	objdata->fx.tar_offset = offset;
	return LAI_SUCCESS;
}
int CMnemaxBookingAgent::SetTomeNumber(const pra_ulong tome_nr)
{
	CLINICAL_RISK_MEDIUM;
	if (objdata == NULL)
	{
		slexit("objdata == NULL", 0);
		return LAI_FAILURE;
	}
	objdata->fx.tome_nr = tome_nr;
		return LAI_SUCCESS;
}
// Copies the incoming signature (assumed to be 16 bytes MD5 )
// into the index entry's md5. The signature is presumed to be correct.
int CMnemaxBookingAgent::UpdateObjectSignature(pra_byte* digest)
{
	CLINICAL_RISK_HIGH;
	if (digest == NULL)
	{
		sle("FATAL: Cannot update object signature: digest == NULL");
		return LAI_FAILURE;
	}
	memcpy(objdata->fx.md5, digest, 16);
	return LAI_SUCCESS;
}
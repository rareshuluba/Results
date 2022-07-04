#ifndef _LAITEK_SDA_INCLUDE_MNEMAX_BOOKING_AGENT_CORE_DEFINITION_HEADERS
#define _LAITEK_SDA_INCLUDE_MNEMAX_BOOKING_AGENT_CORE_DEFINITION_HEADERS
class IndexHtAgentClient;
class PRA_EXPORT CMnemaxBookingAgent : public CMnemaxAgent
{
public:
	CMnemaxBookingAgent(E_MnemaxAgentType type, const char* idxpath = NULL);
	virtual ~CMnemaxBookingAgent();
private:
	CMnemaxBookingAgent(const CMnemaxBookingAgent& src);
public:
	virtual int SetObjRelPath(const char* path);
	virtual int SetTomeNumber(const pra_ulong tome_nr);
	virtual int SetObjStateFlag(pra_byte _state);
	virtual int SetObjTarRelPath(const char* path);
	virtual int SetObjTarOffset(pra_ulong offset);
	virtual const PIdxResult CheckForAvailability(void* object) = 0;
	virtual PIdxSdaEntry CreateMnemaxDataFromObject(void* object) = 0;
	virtual int PerformBooking();
	virtual int UpdateObjectSignature(IN pra_byte* digest);
	virtual void invent_unique_sopuid_for_object(void* object, pra_ulong index) = 0;
	virtual int UseMetadataFilter(CMetadataFilter* filter)
	{
		CLINICAL_RISK_LOW;
		if (oce_index == NULL) return LAI_FAILURE;
		return oce_index->UseFilter(filter);
	}
private:
	void init();
protected:
	virtual int prepareForBooking() = 0;
public:
	PIdxResult book_query;
	PIdxSdaEntry objdata;
	pra_bool dual_index_mode;
protected:
	TIdxSearchData sdata;
private:
	IndexHtAgentClient* indexBookingClient;
};
#endif
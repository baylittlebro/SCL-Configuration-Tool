#include "mmslite.h"
#include "tinyxml2.h"
#include <msclr/marshal.h>
using namespace tinyxml2;
using namespace msclr::interop;

#define cvt_nibble(a)   ((ST_UCHAR) ((a) > 9 ? (a) + 'A' - 10 : (a) + '0'))
#define MAX_MAC_STRING_LEN      60
static ST_CHAR *empty_string = "";

ST_VOID ConvertSclInfo (SCL_INFO *scl_info, ST_CHAR *fileName);

ST_VOID LinkSCL (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc);
ST_VOID LinkHeader (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkCommunication (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkSubNetwork (SCL_SUBNET *scl_subnet, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkConnectedAP (SCL_CAP *scl_cap, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkAddress (SCL_ADDRESS address, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkAddress_P (SCL_ADDRESS address, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR* type);
ST_VOID LinkGSE (SCL_GSE *scl_gse, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkGSE_Address (SCL_GSE *scl_gse, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkGSE_Address_P (SCL_GSE *scl_gse, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR *type);
ST_VOID LinkIED (SCL_SERVER *scl_server, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkServices (SCL_SERVICES scl_services, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkServices_Elem (
	SCL_SERVICES scl_services,
	tinyxml2::XMLDocument *doc,
	XMLElement *parent,
	ST_CHAR *name);
ST_VOID LinkAccessPoint (SCL_SERVER *scl_server, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkServer (SCL_SERVER *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkServerAt_SFun (SCL_SERVER *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkLDevice (SCL_LD *scl_, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkLN (SCL_LN *scl_ln, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDataSet (SCL_DATASET *scl_dataset, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkFCDA (SCL_FCDA *scl_fcda, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkReportControl (SCL_RCB *scl_rcb, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkLogControl (SCL_LCB *scl_lcb, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkGSEControl (SCL_GCB *scl_gcb, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkGSEControl_Protocol (SCL_GCB *scl_gcb, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkGSEControl_IEDName (
	SCL_GCB_IEDNAME *scl_gcb_iedname,
	tinyxml2::XMLDocument *doc,
	XMLElement *parent);
//ST_VOID LinkSettingControl_SFun (SCL_ *scl_, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkTrgOps_SFun (SCL_ *scl_, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkOptFlds_SFun (SCL_ *scl_, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkRptEnabled_SFun (SCL_ *scl_, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDOI (SCL_DAI *scl_dai, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkSDI (SCL_DAI *scl_dai, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR* str);
ST_VOID LinkDAI (SCL_DAI *scl_dai, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR* str);
//ST_VOID LinkDAI_Val (SCL_DAI *scl_dai, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDataTypeTemplates (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkLNodeType (SCL_LNTYPE *scl_lntype, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDO (SCL_DO *scl_do, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDOType (SCL_DOTYPE *scl_dotype, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDA (SCL_DA *scl_da, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkSDO (SCL_DA *scl_da, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDA_Val (SCL_DA *scl_da, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkDAType (SCL_DATYPE *scl_datype, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkBDA (SCL_BDA *scl_bda, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkBDA_Val (SCL_BDA *scl_bda, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkEnumType (SCL_ENUMTYPE *scl_enumtype, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkEnumVal (SCL_ENUMVAL *scl_enumval, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkInputs (SCL_LN *scl_ln, tinyxml2::XMLDocument *doc, XMLElement *parent);
ST_VOID LinkExtRef (SCL_EXTREF *scl_extref, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkGSE_MinTime (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkGSE_MaxTime (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);
//ST_VOID LinkClientLN_SFun (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent);

ST_VOID ConvertHex (ST_CHAR *astr, ST_UCHAR *hstr);
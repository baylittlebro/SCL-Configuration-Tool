#include "copy.h"

ST_VOID copy_scl_cap (SCL_CAP *dst, SCL_CAP *src){
	SCL_GSE *scl_gse_dst;
	SCL_GSE *scl_gse_src;

	dst->iedName = (ST_CHAR*)calloc (strlen (src->iedName) + 1, sizeof (ST_CHAR));
	strcpy (dst->iedName, src->iedName);
	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	dst->apName = (ST_CHAR*)calloc (strlen (src->apName) + 1, sizeof (ST_CHAR));
	strcpy (dst->apName, src->apName);
	dst->address = src->address;
	for (scl_gse_src = (SCL_GSE *)list_find_last ((DBL_LNK *)src->gseHead);
		scl_gse_src != NULL;
		scl_gse_src = (SCL_GSE *)list_find_prev ((DBL_LNK *)src->gseHead, (DBL_LNK *)scl_gse_src)){
		scl_gse_dst = add_scl_gse (dst);
		copy_scl_gse (scl_gse_dst, scl_gse_src);
	}
}

ST_VOID copy_scl_gse (SCL_GSE *dst, SCL_GSE *src){
	dst->ldInst = (ST_CHAR*)calloc (strlen (src->ldInst) + 1, sizeof (ST_CHAR));
	strcpy (dst->ldInst, src->ldInst);
	dst->cbName = (ST_CHAR*)calloc (strlen (src->cbName) + 1, sizeof (ST_CHAR));
	strcpy (dst->cbName, src->cbName);
	memcpy (dst->MAC, src->MAC, sizeof (ST_CHAR)*CLNP_MAX_LEN_MAC);
	dst->APPID = src->APPID;
	dst->VLANPRI = src->VLANPRI;
	dst->VLANID = src->VLANID;
	dst->MinTime = src->MinTime;
	dst->MaxTime = src->MaxTime;
	dst->IP_IGMPv3Src = src->IP_IGMPv3Src;
	dst->IP = src->IP;
	dst->IP_SUBNET = src->IP_SUBNET;
	dst->IP_GATEWAY = src->IP_GATEWAY;
	dst->IP_ClassOfTraffic = src->IP_ClassOfTraffic;
	dst->KDAParticipant = src->KDAParticipant;
}

ST_VOID copy_scl_server (SCL_SERVER *dst, SCL_SERVER *src){
	SCL_LD *scl_ld_dst;
	SCL_LD *scl_ld_src;

	for (scl_ld_src = (SCL_LD *)list_find_last ((DBL_LNK *)src->ldHead);
		scl_ld_src != NULL;
		scl_ld_src = (SCL_LD *)list_find_prev ((DBL_LNK *)src->ldHead, (DBL_LNK *)scl_ld_src)){
		scl_ld_dst = add_scl_ld (dst);
		copy_scl_ld (scl_ld_dst, scl_ld_src);
	}
	dst->iedName = (ST_CHAR*)calloc (strlen (src->iedName) + 1, sizeof (ST_CHAR));
	strcpy (dst->iedName, src->iedName);
	dst->apName = (ST_CHAR*)calloc (strlen (src->apName) + 1, sizeof (ST_CHAR));
	strcpy (dst->apName, src->apName);
	dst->scl_services = src->scl_services;
}

ST_VOID copy_scl_ld (SCL_LD *dst, SCL_LD *src){
	SCL_LN *scl_ln_dst;
	SCL_LN *scl_ln_src;

	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	dst->inst = (ST_CHAR*)calloc (strlen (src->inst) + 1, sizeof (ST_CHAR));
	strcpy (dst->inst, src->inst);
	dst->ldName = (ST_CHAR*)calloc (strlen (src->ldName) + 1, sizeof (ST_CHAR));
	strcpy (dst->ldName, src->ldName);
	for (scl_ln_src = (SCL_LN *)list_find_last ((DBL_LNK *)src->lnHead);
		scl_ln_src != NULL;
		scl_ln_src = (SCL_LN *)list_find_prev ((DBL_LNK *)src->lnHead, (DBL_LNK *)scl_ln_src)){
		scl_ln_dst = add_scl_ln (dst);
		copy_scl_ln (scl_ln_dst, scl_ln_src);
	}
}

ST_VOID copy_scl_ln (SCL_LN *dst, SCL_LN *src){
	SCL_DATASET *scl_dataset_dst;
	SCL_DATASET *scl_dataset_src;
	SCL_DAI *scl_dai_dst;
	SCL_DAI *scl_dai_src;
	SCL_GCB *scl_gcb_dst;
	SCL_GCB *scl_gcb_src;
	SCL_EXTREF *scl_extref_dst;
	SCL_EXTREF *scl_extref_src;

	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	dst->lnType = (ST_CHAR*)calloc (strlen (src->lnType) + 1, sizeof (ST_CHAR));
	strcpy (dst->lnType, src->lnType);
	dst->lnClass = (ST_CHAR*)calloc (strlen (src->lnClass) + 1, sizeof (ST_CHAR));
	strcpy (dst->lnClass, src->lnClass);
	dst->inst = (ST_CHAR*)calloc (strlen (src->inst) + 1, sizeof (ST_CHAR));
	strcpy (dst->inst, src->inst);
	dst->prefix = (ST_CHAR*)calloc (strlen (src->prefix) + 1, sizeof (ST_CHAR));
	strcpy (dst->prefix, src->prefix);
	for (scl_dataset_src = (SCL_DATASET *)list_find_last ((DBL_LNK *)src->datasetHead);
		scl_dataset_src != NULL;
		scl_dataset_src = (SCL_DATASET *)list_find_prev ((DBL_LNK *)src->datasetHead, (DBL_LNK *)scl_dataset_src)){
		scl_dataset_dst = add_scl_dataset (dst);
		copy_scl_dataset (scl_dataset_dst, scl_dataset_src);
	}
	for (scl_dai_src = (SCL_DAI *)list_find_last ((DBL_LNK *)src->daiHead);
		scl_dai_src != NULL;
		scl_dai_src = (SCL_DAI *)list_find_prev ((DBL_LNK *)src->daiHead, (DBL_LNK *)scl_dai_src)) {
		scl_dai_dst = add_scl_dai (dst);
		copy_scl_dai (scl_dai_dst, scl_dai_src);
	}
	for (scl_gcb_src = (SCL_GCB *)list_find_last ((DBL_LNK *)src->gcbHead);
		scl_gcb_src != NULL;
		scl_gcb_src = (SCL_GCB *)list_find_prev ((DBL_LNK *)src->gcbHead, (DBL_LNK *)scl_gcb_src)){
		scl_gcb_dst = add_scl_gcb (dst);
		copy_scl_gcb (scl_gcb_dst, scl_gcb_src);
	}
	for (scl_extref_src = (SCL_EXTREF *)list_find_last ((DBL_LNK *)src->extrefHead);
		scl_extref_src != NULL;
		scl_extref_src = (SCL_EXTREF *)list_find_prev ((DBL_LNK *)src->extrefHead, (DBL_LNK *)scl_extref_src)) {
		scl_extref_dst = add_scl_extref (dst);
		copy_scl_extref (scl_extref_dst, scl_extref_src);
	}

}

ST_VOID copy_scl_dataset (SCL_DATASET *dst, SCL_DATASET *src){
	SCL_FCDA *scl_fcda_dst;
	SCL_FCDA *scl_fcda_src;

	dst->name = (ST_CHAR*)calloc (strlen (src->name) + 1, sizeof (ST_CHAR));
	strcpy (dst->name, src->name);
	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	dst->fcdaCount = src->fcdaCount;
	for (scl_fcda_src = (SCL_FCDA *)list_find_last ((DBL_LNK *)src->fcdaHead);
		scl_fcda_src != NULL;
		scl_fcda_src = (SCL_FCDA *)list_find_prev ((DBL_LNK *)src->fcdaHead, (DBL_LNK *)scl_fcda_src)){
		scl_fcda_dst = add_scl_fcda (dst);
		copy_scl_fcda (scl_fcda_dst, scl_fcda_src);
	}
}

ST_VOID copy_scl_dai (SCL_DAI *dst, SCL_DAI *src) {

	dst->flattened = (ST_CHAR*)calloc (strlen (src->flattened) + 1, sizeof (ST_CHAR));
	strcpy (dst->flattened, src->flattened);
	dst->sAddr = (ST_CHAR*)calloc (strlen (src->sAddr) + 1, sizeof (ST_CHAR));
	strcpy (dst->sAddr, src->sAddr);
	strcpy (dst->valKind, src->valKind);
	
}

ST_VOID copy_scl_fcda (SCL_FCDA *dst, SCL_FCDA *src){
	dst->ldInst = (ST_CHAR*)calloc (strlen (src->ldInst) + 1, sizeof (ST_CHAR));
	strcpy (dst->ldInst, src->ldInst);
	dst->prefix = (ST_CHAR*)calloc (strlen (src->prefix) + 1, sizeof (ST_CHAR));
	strcpy (dst->prefix, src->prefix);
	dst->lnInst = (ST_CHAR*)calloc (strlen (src->lnInst) + 1, sizeof (ST_CHAR));
	strcpy (dst->lnInst, src->lnInst);
	dst->lnClass = (ST_CHAR*)calloc (strlen (src->lnClass) + 1, sizeof (ST_CHAR));
	strcpy (dst->lnClass, src->lnClass);
	dst->doName = (ST_CHAR*)calloc (strlen (src->doName) + 1, sizeof (ST_CHAR));
	strcpy (dst->doName, src->doName);
	dst->daName = (ST_CHAR*)calloc (strlen (src->daName) + 1, sizeof (ST_CHAR));
	strcpy (dst->daName, src->daName);
	strcpy (dst->fc, src->fc);
	strcpy (dst->ix, src->ix);
}

ST_VOID copy_scl_gcb (SCL_GCB *dst, SCL_GCB *src){
	dst->name = (ST_CHAR*)calloc (strlen (src->name) + 1, sizeof (ST_CHAR));
	strcpy (dst->name, src->name);
	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	dst->datSet = (ST_CHAR*)calloc (strlen (src->datSet) + 1, sizeof (ST_CHAR));
	strcpy (dst->datSet, src->datSet);
	dst->confRev = src->confRev;
	dst->isGoose = src->isGoose;
	dst->appID = (ST_CHAR*)calloc (strlen (src->appID) + 1, sizeof (ST_CHAR));
	strcpy (dst->appID, src->appID);
	dst->fixedOffs = src->fixedOffs;
}

ST_VOID copy_scl_extref (SCL_EXTREF *dst, SCL_EXTREF *src)
{
	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	dst->intAddr = (ST_CHAR*)calloc (strlen (src->intAddr) + 1, sizeof (ST_CHAR));
	dst->iedName = (ST_CHAR*)calloc (strlen (src->iedName) + 1, sizeof (ST_CHAR));
	dst->ldInst = (ST_CHAR*)calloc (strlen (src->ldInst) + 1, sizeof (ST_CHAR));
	dst->prefix = (ST_CHAR*)calloc (strlen (src->prefix) + 1, sizeof (ST_CHAR));
	dst->lnClass = (ST_CHAR*)calloc (strlen (src->lnClass) + 1, sizeof (ST_CHAR));
	dst->lnInst = (ST_CHAR*)calloc (strlen (src->lnInst) + 1, sizeof (ST_CHAR));
	dst->doName = (ST_CHAR*)calloc (strlen (src->doName) + 1, sizeof (ST_CHAR));
	dst->daName = (ST_CHAR*)calloc (strlen (src->daName) + 1, sizeof (ST_CHAR));
	dst->serviceType = (ST_CHAR*)calloc (strlen (src->serviceType) + 1, sizeof (ST_CHAR));
	dst->srcLDInst = (ST_CHAR*)calloc (strlen (src->srcLDInst) + 1, sizeof (ST_CHAR));
	dst->srcPrefix = (ST_CHAR*)calloc (strlen (src->srcPrefix) + 1, sizeof (ST_CHAR));
	dst->srcLNClass = (ST_CHAR*)calloc (strlen (src->srcLNClass) + 1, sizeof (ST_CHAR));
	dst->srcLNInst = (ST_CHAR*)calloc (strlen (src->srcLNInst) + 1, sizeof (ST_CHAR));
	dst->srcCBName = (ST_CHAR*)calloc (strlen (src->srcCBName) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	strcpy (dst->intAddr, src->intAddr);
	strcpy (dst->iedName, src->iedName);
	strcpy (dst->ldInst, src->ldInst);
	strcpy (dst->prefix, src->prefix);
	strcpy (dst->lnClass, src->lnClass);
	strcpy (dst->lnInst, src->lnInst);
	strcpy (dst->doName, src->doName);
	strcpy (dst->daName, src->daName);
	strcpy (dst->serviceType, src->serviceType);
	strcpy (dst->srcLDInst, src->srcLDInst);
	strcpy (dst->srcPrefix, src->srcPrefix);
	strcpy (dst->srcLNClass, src->srcLNClass);
	strcpy (dst->srcLNInst, src->srcLNInst);
	strcpy (dst->srcCBName, src->srcCBName);
}

ST_VOID copy_scl_lntype (SCL_LNTYPE *dst, SCL_LNTYPE *src){
	SCL_DO *scl_do_dst;
	SCL_DO *scl_do_src;

	dst->id = (ST_CHAR*)calloc (strlen (src->id) + 1, sizeof (ST_CHAR));
	strcpy (dst->id, src->id);
	dst->lnClass = (ST_CHAR*)calloc (strlen (src->lnClass) + 1, sizeof (ST_CHAR));
	strcpy (dst->lnClass, src->lnClass);
	for (scl_do_src = (SCL_DO *)list_find_last ((DBL_LNK *)src->doHead);
		scl_do_src != NULL;
		scl_do_src = (SCL_DO *)list_find_prev ((DBL_LNK *)src->doHead, (DBL_LNK *)scl_do_src)){
		scl_do_dst = add_scl_do (dst);
		copy_scl_do (scl_do_dst, scl_do_src);
	}
}

ST_VOID copy_scl_do (SCL_DO *dst, SCL_DO *src){
	dst->name = (ST_CHAR*)calloc (strlen (src->name) + 1, sizeof (ST_CHAR));
	strcpy (dst->name, src->name);
	dst->type = (ST_CHAR*)calloc (strlen (src->type) + 1, sizeof (ST_CHAR));
	strcpy (dst->type, src->type);
}

ST_VOID copy_scl_dotype (SCL_DOTYPE *dst, SCL_DOTYPE *src)
{
	SCL_DA *scl_da_dst;
	SCL_DA *scl_da_src;

	dst->id = (ST_CHAR*)calloc (strlen (src->id) + 1, sizeof (ST_CHAR));
	strcpy (dst->id, src->id);
	dst->cdc = (ST_CHAR*)calloc (strlen (src->cdc) + 1, sizeof (ST_CHAR));
	strcpy (dst->cdc, src->cdc);
	for (scl_da_src = (SCL_DA *)list_find_last ((DBL_LNK *)src->daHead);
		scl_da_src != NULL;
		scl_da_src = (SCL_DA *)list_find_prev ((DBL_LNK *)src->daHead, (DBL_LNK *)scl_da_src)){
		scl_da_dst = add_scl_da (dst);
		copy_scl_da (scl_da_dst, scl_da_src);
	}
}

ST_VOID copy_scl_da (SCL_DA *dst, SCL_DA *src)
{
	dst->objtype = src->objtype;
	dst->name = (ST_CHAR*)calloc (strlen (src->name) + 1, sizeof (ST_CHAR));
	strcpy (dst->name, src->name);
	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	if (src->sAddr != NULL){
		dst->sAddr = (ST_CHAR*)calloc (strlen (src->sAddr) + 1, sizeof (ST_CHAR));
		strcpy (dst->sAddr, src->sAddr);
	}
	if (src->bType != NULL){
		dst->bType = (ST_CHAR*)calloc (strlen (src->bType) + 1, sizeof (ST_CHAR));
		strcpy (dst->bType, src->bType);
	}
	strcpy (dst->valKind, src->valKind);
	dst->type = (ST_CHAR*)calloc (strlen (src->type) + 1, sizeof (ST_CHAR));
	strcpy (dst->type, src->type);
	dst->count = src->count;
	strcpy (dst->fc, src->fc);
	dst->dchg = src->dchg;
	dst->qchg = src->qchg;
	dst->dupd = src->dupd;
	if (src->objtype == SCL_OBJTYPE_DA) {/* for DA only: attribute value text    */
		if (src->Val != NULL) {
			dst->Val = (ST_CHAR*)calloc (strlen (src->Val) + 1, sizeof (ST_CHAR));
			strcpy (dst->Val, src->Val);
		}
	}
}

ST_VOID copy_scl_datype (SCL_DATYPE *dst, SCL_DATYPE *src)
{
	SCL_BDA *scl_bda_dst;
	SCL_BDA *scl_bda_src;

	dst->id = (ST_CHAR*)calloc (strlen (src->id) + 1, sizeof (ST_CHAR));
	strcpy (dst->id, src->id);
	for (scl_bda_src = (SCL_BDA *)list_find_last ((DBL_LNK *)src->bdaHead);
		scl_bda_src != NULL;
		scl_bda_src = (SCL_BDA *)list_find_prev ((DBL_LNK *)src->bdaHead, (DBL_LNK *)scl_bda_src)){
		scl_bda_dst = add_scl_bda (dst);
		copy_scl_bda (scl_bda_dst, scl_bda_src);
	}
}

ST_VOID copy_scl_bda (SCL_BDA *dst, SCL_BDA *src)
{
	dst->name = (ST_CHAR*)calloc (strlen (src->name) + 1, sizeof (ST_CHAR));
	strcpy (dst->name, src->name);
	dst->desc = (ST_CHAR*)calloc (strlen (src->desc) + 1, sizeof (ST_CHAR));
	strcpy (dst->desc, src->desc);
	dst->sAddr = (ST_CHAR*)calloc (strlen (src->sAddr) + 1, sizeof (ST_CHAR));
	strcpy (dst->sAddr, src->sAddr);
	dst->bType = (ST_CHAR*)calloc (strlen (src->bType) + 1, sizeof (ST_CHAR));
	strcpy (dst->bType, src->bType);
	strcpy (dst->valKind, src->valKind);
	dst->type = (ST_CHAR*)calloc (strlen (src->type) + 1, sizeof (ST_CHAR));
	strcpy (dst->type, src->type);
	dst->count = src->count;
	if (src->Val != NULL){
		dst->Val = (ST_CHAR*)calloc (strlen (src->Val) + 1, sizeof (ST_CHAR));
		strcpy (dst->Val, src->Val);
	}
}

ST_VOID copy_scl_enumtype (SCL_ENUMTYPE *dst, SCL_ENUMTYPE *src){
	SCL_ENUMVAL *scl_enumval_dst;
	SCL_ENUMVAL *scl_enumval_src;

	dst->id = (ST_CHAR*)calloc (strlen (src->id) + 1, sizeof (ST_CHAR));
	strcpy (dst->id, src->id);
	dst->enumvalCount = src->enumvalCount;
	dst->enum_info_idx = src->enum_info_idx;
	for (scl_enumval_src = (SCL_ENUMVAL *)list_find_last ((DBL_LNK *)src->enumvalHead);
		scl_enumval_src != NULL;
		scl_enumval_src = (SCL_ENUMVAL *)list_find_prev ((DBL_LNK *)src->enumvalHead, (DBL_LNK *)scl_enumval_src)){
		scl_enumval_dst = add_scl_enumval (dst);
		copy_scl_enumval (scl_enumval_dst, scl_enumval_src);
	}
}

ST_VOID copy_scl_enumval (SCL_ENUMVAL *dst, SCL_ENUMVAL *src){
	dst->ord = src->ord;
	dst->EnumVal = (ST_CHAR*)calloc (strlen (src->EnumVal) + 1, sizeof (ST_CHAR));
	strcpy (dst->EnumVal, src->EnumVal);
}
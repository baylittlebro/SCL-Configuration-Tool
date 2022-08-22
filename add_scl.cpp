#include "add_scl.h"

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

SCL_CAP* add_scl_cap (SCL_SUBNET *scl_subnet){
	SCL_CAP *scl_cap = NULL;

	if (scl_subnet){
		scl_cap = (SCL_CAP*)chk_calloc (1, sizeof (SCL_CAP));
		list_add_first (&scl_subnet->capHead, scl_cap);
	}

	return scl_cap;
}

SCL_GSE* add_scl_gse (SCL_CAP *scl_cap){
	SCL_GSE *scl_gse = NULL;

	if (scl_cap){
		scl_gse = (SCL_GSE*)chk_calloc (1, sizeof (SCL_GSE));
		list_add_first (&scl_cap->gseHead, scl_gse);
	}

	return scl_gse;
}

SCL_SERVER* add_scl_server (SCL_INFO *scl_info){
	SCL_SERVER *scl_server = NULL;

	if (scl_info){
		scl_server = (SCL_SERVER*)chk_calloc (1, sizeof (SCL_SERVER));
		list_add_first (&scl_info->serverHead, scl_server);
	}

	return scl_server;
}

SCL_LD* add_scl_ld (SCL_SERVER *scl_server){
	SCL_LD* scl_ld = NULL;

	if (scl_server){
		scl_ld = (SCL_LD*)chk_calloc (1, sizeof (SCL_LD));
		list_add_first (&scl_server->ldHead, scl_ld);
	}

	return scl_ld;
}

SCL_LN* add_scl_ln (SCL_LD *scl_ld){
	SCL_LN* scl_ln = NULL;
	
	if (scl_ld){
		scl_ln = (SCL_LN*)chk_calloc (1, sizeof (SCL_LN));
		list_add_first (&scl_ld->lnHead, scl_ln);
	}

	return scl_ln;
}

SCL_DATASET* add_scl_dataset (SCL_LN *scl_ln){
	SCL_DATASET* scl_dataset = NULL;
	
	if (scl_ln){
		scl_dataset = (SCL_DATASET*)chk_calloc (1, sizeof (SCL_DATASET));
		list_add_first (&scl_ln->datasetHead, scl_dataset);
	}

	return scl_dataset;
}

SCL_DAI* add_scl_dai (SCL_LN *scl_ln) {
	SCL_DAI* scl_dai = NULL;

	if (scl_ln) {
		scl_dai = (SCL_DAI*)chk_calloc (1, sizeof (SCL_DAI));
		list_add_first (&scl_ln->daiHead, scl_dai);
	}

	return scl_dai;
}

SCL_FCDA* add_scl_fcda (SCL_DATASET *scl_dataset){
	SCL_FCDA *scl_fcda = NULL;
	
	if (scl_dataset){
		scl_fcda = (SCL_FCDA*)chk_calloc (1, sizeof (SCL_DATASET));
		list_add_first (&scl_dataset->fcdaHead, scl_fcda);
	}

	return scl_fcda;
}

SCL_GCB* add_scl_gcb (SCL_LN *scl_ln){
	SCL_GCB *scl_gcb = NULL;
	
	if (scl_ln){
		scl_gcb = (SCL_GCB*)chk_calloc (1, sizeof (SCL_GCB));
		list_add_first (&scl_ln->gcbHead, scl_gcb);
	}

	return scl_gcb;
}

SCL_LNTYPE* add_scl_lntype (SCL_INFO *scl_info){
	SCL_LNTYPE *scl_lnType = NULL;
	
	if (scl_info){
		scl_lnType = (SCL_LNTYPE*)chk_calloc (1, sizeof (SCL_LNTYPE));
		list_add_first (&scl_info->lnTypeHead, scl_lnType);
	}

	return scl_lnType;
}

SCL_DO* add_scl_do (SCL_LNTYPE *scl_lnType){
	SCL_DO *scl_do = NULL;
	
	if (scl_lnType){
		scl_do = (SCL_DO*)chk_calloc (1, sizeof (SCL_DO));
		list_add_first (&scl_lnType->doHead, scl_do);
	}

	return scl_do;
}

SCL_DOTYPE* add_scl_dotype (SCL_INFO *scl_info){
	SCL_DOTYPE *scl_dotype = NULL;
	
	if (scl_info){
		scl_dotype = (SCL_DOTYPE*)chk_calloc (1, sizeof (SCL_DOTYPE));
		list_add_first (&scl_info, scl_dotype);
	}
	
	return scl_dotype;
}

SCL_DA* add_scl_da (SCL_DOTYPE *scl_dotype){
	SCL_DA *scl_da = NULL;
	
	if (scl_dotype){
		scl_da = (SCL_DA*)chk_calloc (1, sizeof (SCL_DA));
		list_add_first (&scl_dotype->daHead, scl_da);
	}
	
	return scl_da;
}

SCL_DATYPE* add_scl_datype (SCL_INFO *scl_info){
	SCL_DATYPE *scl_datype = NULL;
	
	if (scl_info){
		scl_datype = (SCL_DATYPE*)chk_calloc (1, sizeof (SCL_DATYPE));
		list_add_first (&scl_info->daTypeHead, scl_datype);
	}
	
	return scl_datype;
}

SCL_BDA* add_scl_bda (SCL_DATYPE *scl_datype){
	SCL_BDA *scl_bda = NULL;
	
	if (scl_datype){
		scl_bda = (SCL_BDA*)chk_calloc (1, sizeof (SCL_BDA));
		list_add_first (&scl_datype->bdaHead, scl_bda);
	}
	
	return scl_bda;
}

SCL_ENUMTYPE* add_scl_enumtype (SCL_INFO *scl_info){
	SCL_ENUMTYPE *scl_enumtype = NULL;
	
	if (scl_info){
		scl_enumtype = (SCL_ENUMTYPE*)chk_calloc (1, sizeof (SCL_ENUMTYPE));
		list_add_first (&scl_info->enumTypeHead, scl_enumtype);
	}
	
	return scl_enumtype;
}

SCL_ENUMVAL* add_scl_enumval (SCL_ENUMTYPE *scl_enumtype){
	SCL_ENUMVAL *scl_enumval = NULL;
	
	if (scl_enumtype){
		scl_enumval = (SCL_ENUMVAL*)chk_calloc (1, sizeof (SCL_ENUMVAL));
		list_add_first (&scl_enumtype->enumvalHead, scl_enumval);
	}
	
	return scl_enumval;
}

SCL_EXTREF* add_scl_extref (SCL_LN *scl_ln) {
	SCL_EXTREF *scl_extref = NULL;

	if (scl_ln) {
		scl_extref = (SCL_EXTREF*)chk_calloc (1, sizeof (SCL_EXTREF));
		list_add_first (&scl_ln->extrefHead, scl_extref);
	}

	return scl_extref;
}

SCL_GCB_IEDNAME* add_scl_gcb_iedName (SCL_GCB *scl_gcb)
{
	SCL_GCB_IEDNAME *scl_gcb_iedName = NULL;
	if (scl_gcb)
	{
		scl_gcb_iedName = (SCL_GCB_IEDNAME*)chk_calloc (1, sizeof (SCL_GCB_IEDNAME));
		list_add_first (&scl_gcb->iedNameHead, scl_gcb_iedName);
	}
	return scl_gcb_iedName;
}
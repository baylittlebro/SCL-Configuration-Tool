#include "find.h"

SCL_SUBNET *find_scl_subnet (
	SCL_INFO *scl_info,
	ST_CHAR *name)
{
	SCL_SUBNET *scl_subnet;

	for (scl_subnet = (SCL_SUBNET *)list_find_last ((DBL_LNK *)scl_info->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *)list_find_prev ((DBL_LNK *)scl_info->subnetHead, (DBL_LNK *)scl_subnet))
	{
		if (!strcmp (scl_subnet->name, name))
			return (scl_subnet);
	}

	return (NULL);        /* match not found      */
}

SCL_CAP *find_scl_cap (
	SCL_SUBNET *scl_subnet,
	ST_CHAR *iedName)
{
	SCL_CAP *scl_cap;

	for (scl_cap = (SCL_CAP *)list_find_last ((DBL_LNK *)scl_subnet->capHead);
		scl_cap != NULL;
		scl_cap = (SCL_CAP *)list_find_prev ((DBL_LNK *)scl_subnet->capHead, (DBL_LNK *)scl_cap))
	{
		if (!(strcmp (scl_cap->iedName, iedName)))
			return (scl_cap);
	}

	return (NULL);        /* match not found      */
}

SCL_SERVER *find_scl_server (
	SCL_INFO *scl_info,
	ST_CHAR *iedName)
{
	SCL_SERVER *scl_server;

	for (scl_server = (SCL_SERVER *)list_find_last ((DBL_LNK *)scl_info->serverHead);
		scl_server != NULL;
		scl_server = (SCL_SERVER *)list_find_prev ((DBL_LNK *)scl_info->serverHead, (DBL_LNK *)scl_server))
	{
		if (!strcmp (scl_server->iedName, iedName))
			return (scl_server);
	}

	return (NULL);        /* match not found      */
}

SCL_LD *find_scl_ld (
	SCL_SERVER *scl_server,
	ST_CHAR *inst)
{
	SCL_LD *scl_ld;

	for (scl_ld = (SCL_LD *)list_find_last ((DBL_LNK *)scl_server->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev ((DBL_LNK *)scl_server->ldHead, (DBL_LNK *)scl_ld))
	{
		if (!strcmp (scl_ld->inst, inst))
			return (scl_ld);
	}

	return (NULL);        /* match not found      */
}

SCL_LN *find_scl_ln (
	SCL_LD *scl_ld,
	ST_CHAR *prefix,
	ST_CHAR *lnClass,
	ST_CHAR *inst)
{
	SCL_LN *scl_ln;

	if (strcmp (lnClass, "LLN0") == 0)//LLN0일 경우 prefix와 inst를 무시
	{
		for (scl_ln = (SCL_LN *)list_find_last ((DBL_LNK *)scl_ld->lnHead);
			scl_ln != NULL;
			scl_ln = (SCL_LN *)list_find_prev ((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
		{
			if (strcmp (scl_ln->lnClass, lnClass) == 0)
				return scl_ln;
		}
	}		
	else
	{
		for (scl_ln = (SCL_LN *)list_find_last ((DBL_LNK *)scl_ld->lnHead);
			scl_ln != NULL;
			scl_ln = (SCL_LN *)list_find_prev ((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
		{
			if (strcmp (scl_ln->prefix, prefix) == 0 &&
				strcmp (scl_ln->lnClass, lnClass) == 0 &&
				strcmp (scl_ln->inst, inst) == 0)
				return scl_ln;
		}
	}

	return (NULL);        /* match not found      */
}

SCL_GCB *find_scl_gcb (
	SCL_LN *scl_ln,
	ST_CHAR *name)
{
	SCL_GCB *scl_gcb;

	for (scl_gcb = (SCL_GCB *)list_find_last ((DBL_LNK *)scl_ln->gcbHead);//lnHead에 LLN0이 있다고 가정
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev ((DBL_LNK *)scl_ln->gcbHead, (DBL_LNK *)scl_gcb))
	{
		if (!strcmp (scl_gcb->name, name))
			return (scl_gcb);
	}

	return (NULL);        /* match not found      */
}

SCL_DATASET *find_scl_dataset (
	SCL_LN *scl_ln,
	ST_CHAR *name)
{
	SCL_DATASET *scl_dataset;

	for (scl_dataset = (SCL_DATASET *)list_find_last ((DBL_LNK *)scl_ln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev ((DBL_LNK *)scl_ln->datasetHead, (DBL_LNK *)scl_dataset))
	{
		if (!strcmp (scl_dataset->name, name))
			return (scl_dataset);
	}

	return (NULL);        /* match not found      */
}

SCL_EXTREF *find_scl_extref (
	SCL_LN *scl_ln,
	ST_CHAR *iedName,
	ST_CHAR *ldInst,
	ST_CHAR *lnClass,
	ST_CHAR *lnInst,
	ST_CHAR *doName,
	ST_CHAR *daName)
{
	SCL_EXTREF *scl_extref;
	for(scl_extref = (SCL_EXTREF*)list_find_last((DBL_LNK*)scl_ln->extrefHead);
		scl_extref !=NULL;
		scl_extref = (SCL_EXTREF*)list_find_prev ((DBL_LNK*)scl_ln->extrefHead, (DBL_LNK*)scl_extref))
	{
		if (
			!strcmp (scl_extref->iedName, iedName) &&
			!strcmp (scl_extref->ldInst, ldInst) &&
			!strcmp (scl_extref->lnClass, lnClass) &&
			!strcmp (scl_extref->lnInst, lnInst) &&
			!strcmp (scl_extref->doName, doName) &&
			!strcmp (scl_extref->daName, daName)
			)
			return(scl_extref);
	}
	return (NULL);
}

SCL_DAI *find_scl_dai (
	SCL_LN *scl_ln,
	ST_CHAR *flattened)
{
	SCL_DAI *scl_dai;
	for (scl_dai = (SCL_DAI*)list_find_last ((DBL_LNK*)scl_ln->daiHead);
		scl_dai != NULL;
		scl_dai = (SCL_DAI*)list_find_prev ((DBL_LNK*)scl_ln->daiHead, (DBL_LNK*)scl_dai))
	{
		if (!strcmp (scl_dai->flattened, flattened))
			return scl_dai;
	}
	return NULL;
}

SCL_GCB_IEDNAME* find_scl_gcb_iedName (
	SCL_GCB *scl_gcb,
	ST_CHAR *iedName)
{
	SCL_GCB_IEDNAME *scl_gcb_iedName;
	for (scl_gcb_iedName = (SCL_GCB_IEDNAME*)list_find_last ((DBL_LNK*)scl_gcb->iedNameHead);
		scl_gcb_iedName != NULL;
		scl_gcb_iedName = (SCL_GCB_IEDNAME*)list_find_prev ((DBL_LNK*)scl_gcb->iedNameHead, (DBL_LNK*)scl_gcb_iedName))
	{
		if (!strcmp (scl_gcb_iedName->iedName, iedName))
			return scl_gcb_iedName;
	}
	return NULL;
}

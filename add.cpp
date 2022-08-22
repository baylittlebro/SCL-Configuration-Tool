#include "add.h"

ST_RET AddSubscription (CONFIG_CTRL *config_ctrl)
{
	AddConnectedAP (config_ctrl);

	AddIED (config_ctrl);

	AddProxyLDevice (config_ctrl);

	AddExtRef (config_ctrl);

	AddDAI (config_ctrl);

	AddIEDName (config_ctrl);

	AddDataTypeTemplates (config_ctrl);

	return SD_SUCCESS;
}

ST_RET AddConnectedAP (CONFIG_CTRL *config_ctrl)
{
	SCL_SUBNET *scl_subnet_agg;
	SCL_SUBNET *scl_subnet_pub;
	SCL_CAP *scl_cap_dst;
	SCL_CAP *scl_cap_src;

	//find Source ConnectedAP
	scl_subnet_pub = find_scl_subnet (config_ctrl->scl_info_publisher, config_ctrl->subNetworkNamePublisher);
	if (scl_subnet_pub == NULL) 
		return SD_FAILURE;
	scl_cap_src = find_scl_cap (scl_subnet_pub, config_ctrl->iedNamePublisher);
	if (scl_cap_src == NULL) 
		return SD_FAILURE;

	//Check ConnectedAP already exist. If exist, remove and create.
	scl_subnet_agg = find_scl_subnet (config_ctrl->scl_info_aggregator, config_ctrl->subNetworkNameAggregator);
	if (scl_subnet_agg == NULL) 
		return SD_FAILURE;
	scl_cap_dst = find_scl_cap (scl_subnet_agg, config_ctrl->iedNamePublisher);
	if (scl_cap_dst != NULL) //이미 값이 존재함
		return SD_FAILURE;
	
	scl_cap_dst = add_scl_cap (scl_subnet_agg);
	copy_scl_cap (scl_cap_dst, scl_cap_src);

	return SD_SUCCESS;
}

ST_RET AddIED (CONFIG_CTRL *config_ctrl)
{
	SCL_SERVER *sclServerSrc;
	SCL_SERVER *sclServerDst;

	//find Source Server
	sclServerSrc = find_scl_server (config_ctrl->scl_info_publisher, config_ctrl->iedNamePublisher);
	if (sclServerSrc == NULL) return SD_FAILURE;

	//Check Server already exist. If exist, remove and create.
	sclServerDst = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNamePublisher);
	if (sclServerDst != NULL) return SD_FAILURE;
	//RemoveIED (config_ctrl->scl_info_aggregator->serverHead, sclServerDst);
	
	sclServerDst = add_scl_server (config_ctrl->scl_info_aggregator);
	copy_scl_server (sclServerDst, sclServerSrc);

	return SD_SUCCESS;
}

ST_RET AddDataTypeTemplates (CONFIG_CTRL *config_ctrl)
{
	SCL_LNTYPE *lnTypePIED;
	SCL_LNTYPE *lnTypeAIED;
	SCL_DOTYPE *doTypePIED;
	SCL_DOTYPE *doTypeAIED;
	SCL_DATYPE *daTypePIED;
	SCL_DATYPE *daTypeAIED;
	SCL_ENUMTYPE *enumTypePIED;
	SCL_ENUMTYPE *enumTypeAIED;

	ST_BOOLEAN dup;
	for (lnTypePIED = (SCL_LNTYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_publisher)->lnTypeHead);
		lnTypePIED != NULL;
		lnTypePIED = (SCL_LNTYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_publisher)->lnTypeHead, (DBL_LNK *)lnTypePIED))
	{
		dup = 0;
		for (lnTypeAIED = (SCL_LNTYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->lnTypeHead);
			lnTypeAIED != NULL;
			lnTypeAIED = (SCL_LNTYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->lnTypeHead, (DBL_LNK *)lnTypeAIED))
		{
			if (strcmp (lnTypePIED->id, lnTypeAIED->id) == 0)
			{
				dup = 1;
				break;
			}
		}
		if (dup != 1)
		{
			lnTypeAIED = add_scl_lntype (config_ctrl->scl_info_aggregator);
			copy_scl_lntype (lnTypeAIED, lnTypePIED);
		}


	}

	for (doTypePIED = (SCL_DOTYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_publisher)->doTypeHead);
		doTypePIED != NULL;
		doTypePIED = (SCL_DOTYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_publisher)->doTypeHead, (DBL_LNK *)doTypePIED))
	{
		dup = 0;
		for (doTypeAIED = (SCL_DOTYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->doTypeHead);
			doTypeAIED != NULL;
			doTypeAIED = (SCL_DOTYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->doTypeHead, (DBL_LNK *)doTypeAIED))
		{
			if (strcmp (doTypePIED->id, doTypeAIED->id) == 0)
			{
				dup = 1;
				break;
			}
		}
		if (dup != 1)
		{
			doTypeAIED = add_scl_dotype (config_ctrl->scl_info_aggregator);
			copy_scl_dotype (doTypeAIED, doTypePIED);
		}

	}

	for (daTypePIED = (SCL_DATYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_publisher)->daTypeHead);
		daTypePIED != NULL;
		daTypePIED = (SCL_DATYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_publisher)->daTypeHead, (DBL_LNK *)daTypePIED))
	{
		dup = 0;
		for (daTypeAIED = (SCL_DATYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->daTypeHead);
			daTypeAIED != NULL;
			daTypeAIED = (SCL_DATYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->daTypeHead, (DBL_LNK *)daTypeAIED))
		{
			if (strcmp (daTypePIED->id, daTypeAIED->id) == 0)
			{
				dup = 1;
				break;
			}
		}
		if (dup != 1)
		{
			daTypeAIED = add_scl_datype (config_ctrl->scl_info_aggregator);
			copy_scl_datype (daTypeAIED, daTypePIED);
		}

	}

	for (enumTypePIED = (SCL_ENUMTYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_publisher)->enumTypeHead);
		enumTypePIED != NULL;
		enumTypePIED = (SCL_ENUMTYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_publisher)->enumTypeHead, (DBL_LNK *)enumTypePIED))
	{
		dup = 0;
		for (enumTypeAIED = (SCL_ENUMTYPE *)list_find_last ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->enumTypeHead);
			enumTypeAIED != NULL;
			enumTypeAIED = (SCL_ENUMTYPE *)list_find_prev ((DBL_LNK *)(config_ctrl->scl_info_aggregator)->enumTypeHead, (DBL_LNK *)enumTypeAIED))
		{
			if (strcmp (enumTypePIED->id, enumTypeAIED->id) == 0)
			{
				dup = 1;
				break;
			}
		}
		if (dup != 1)
		{
			enumTypeAIED = add_scl_enumtype (config_ctrl->scl_info_aggregator);
			copy_scl_enumtype (enumTypeAIED, enumTypePIED);
		}

	}

	return SD_SUCCESS;
}

/*
ST_RET AddProxyLDevice (CONFIG_CTRL *config_ctrl)
{
	SCL_SERVER *sclServerAIED;
	SCL_SERVER *sclServerPIED;

	SCL_SUBNET *sclSubnet;
	SCL_CAP *sclCap;
	SCL_GSE *sclGse;

	SCL_LD *sclLd;//LD Ref by GSE, 컨트롤 블록이 위치함
	SCL_LN *sclLn;
	SCL_GCB *sclGcb;
	SCL_DATASET *sclDataset;
	SCL_FCDA *sclFcda;

	SCL_LD *sclLdStorage;
	SCL_LD *sclLdSrc;
	SCL_LN *sclLnStorage;
	SCL_LN *sclLnSrc;

	ST_CHAR *ldInst;

	sclServerAIED = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNameAggregator);
	if (sclServerAIED == NULL) return SD_FAILURE;
	sclServerPIED = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNamePublisher);
	if (sclServerPIED == NULL)return SD_FAILURE;
	sclSubnet = find_scl_subnet (config_ctrl->scl_info_publisher, config_ctrl->subNetworkNamePublisher);
	if (sclSubnet == NULL)return SD_FAILURE;
	sclCap = find_scl_cap (sclSubnet, config_ctrl->iedNamePublisher);//하나의 IED만 존재
	if (sclCap == NULL)return SD_FAILURE;
	for (sclGse = (SCL_GSE *)list_find_last ((DBL_LNK *)sclCap->gseHead);
		sclGse != NULL;
		sclGse = (SCL_GSE *)list_find_prev ((DBL_LNK *)sclCap->gseHead, (DBL_LNK *)sclGse))
	{

		//GSE에 해당하는DataSet 탐색
		sclLd = find_scl_ld (sclServerPIED, sclGse->ldInst);
		sclLn = find_scl_ln (sclLd, "", "LLN0", "");
		sclGcb = find_scl_gcb (sclLn, sclGse->cbName);
		sclDataset = find_scl_dataset (sclLn, sclGcb->datSet);

		for (sclFcda = (SCL_FCDA *)list_find_last ((DBL_LNK *)sclDataset->fcdaHead);
			sclFcda != NULL;
			sclFcda = (SCL_FCDA *)list_find_prev ((DBL_LNK *)sclDataset->fcdaHead, (DBL_LNK *)sclFcda))
		{
			ldInst = (ST_CHAR*)calloc (strlen (config_ctrl->iedNamePublisher) +
				strlen (sclFcda->ldInst) + 1, sizeof (ST_CHAR));
			strcpy (ldInst, config_ctrl->iedNamePublisher);
			strcat (ldInst, sclFcda->ldInst);

			sclLdStorage = find_scl_ld (sclServerAIED, ldInst);

			//LD 및 LLN0추가
			if (sclLdStorage == NULL)
			{
				sclLdSrc = find_scl_ld (sclServerPIED, sclFcda->ldInst);
				if (sclLdSrc == NULL)return SD_FAILURE;//error

				sclLdStorage = add_scl_ld (sclServerAIED);

				sclLdStorage->inst = (ST_CHAR *)calloc (strlen (ldInst) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLdStorage->inst, ldInst);

				sclLdStorage->desc = (ST_CHAR *)calloc (1, (sizeof (ST_CHAR)));//필요시 추가
				strcpy (sclLdStorage->desc, "");

				sclLdStorage->ldName = (ST_CHAR *)calloc (1, (sizeof (ST_CHAR)));//필요시 추가
				strcpy (sclLdStorage->ldName, "");

				sclLnStorage = add_scl_ln (sclLdStorage);
				sclLnSrc = find_scl_ln (sclLdSrc, "", "LLN0", "");

				sclLnStorage->desc = (ST_CHAR *)calloc (strlen (sclLnSrc->desc) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->desc, sclLnSrc->desc);

				sclLnStorage->lnType = (ST_CHAR *)calloc (strlen (sclLnSrc->lnType) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->lnType, sclLnSrc->lnType);

				sclLnStorage->lnClass = (ST_CHAR *)calloc (strlen (sclLnSrc->lnClass) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->lnClass, sclLnSrc->lnClass);

				sclLnStorage->inst = (ST_CHAR *)calloc (strlen (sclLnSrc->inst) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->inst, sclLnSrc->inst);

				sclLnStorage->prefix = (ST_CHAR *)calloc (strlen (sclLnSrc->prefix) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->prefix, sclLnSrc->prefix);
			}

			//LN추가
			if (find_scl_ln (sclLdStorage, sclFcda->prefix, sclFcda->lnClass, sclFcda->lnInst) == NULL)
			{
				sclLnStorage = add_scl_ln (sclLdStorage);
				sclLnSrc = find_scl_ln (sclLdSrc, sclFcda->prefix, sclFcda->lnClass, sclFcda->lnInst);

				sclLnStorage->desc = (ST_CHAR *)calloc (strlen (sclLnSrc->desc) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->desc, sclLnSrc->desc);

				sclLnStorage->lnType = (ST_CHAR *)calloc (strlen (sclLnSrc->lnType) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->lnType, sclLnSrc->lnType);

				sclLnStorage->lnClass = (ST_CHAR *)calloc (strlen (sclLnSrc->lnClass) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->lnClass, sclLnSrc->lnClass);

				sclLnStorage->inst = (ST_CHAR *)calloc (strlen (sclLnSrc->inst) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->inst, sclLnSrc->inst);

				sclLnStorage->prefix = (ST_CHAR *)calloc (strlen (sclLnSrc->prefix) + 1, (sizeof (ST_CHAR)));
				strcpy (sclLnStorage->prefix, sclLnSrc->prefix);
			}
		}
	}

	return SD_SUCCESS;
}
*/

ST_RET AddProxyLDevice (CONFIG_CTRL *config_ctrl)
{
	SCL_SERVER *sclServerAIED;
	SCL_SERVER *sclServerPIED;
	SCL_LD *sclLdSrc;
	SCL_LD *sclLdDst;
	SCL_LN *sclLnDst;
	SCL_LN *sclLnSrc;
	SCL_GCB *scl_gcb;
	SCL_DATASET *scl_dataset;
	SCL_FCDA *scl_fcda;
	ST_CHAR *ldInst;

	sclServerAIED = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNameAggregator);
	if (sclServerAIED == NULL) return SD_FAILURE;
	sclServerPIED = find_scl_server (config_ctrl->scl_info_publisher, config_ctrl->iedNamePublisher);
	if (sclServerPIED == NULL)return SD_FAILURE;


	for (sclLdSrc = (SCL_LD *)list_find_last ((DBL_LNK *)sclServerPIED->ldHead);
		sclLdSrc != NULL;
		sclLdSrc = (SCL_LD *)list_find_prev ((DBL_LNK *)sclServerPIED->ldHead, (DBL_LNK *)sclLdSrc))
	{
		ldInst = (ST_CHAR*)calloc (strlen (config_ctrl->iedNamePublisher) +
			strlen (sclLdSrc->inst) + 1, sizeof (ST_CHAR));
		strcpy (ldInst, config_ctrl->iedNamePublisher);
		strcat (ldInst, sclLdSrc->inst);
		if (find_scl_ld (sclServerAIED, ldInst) == NULL)
		{
			sclLdDst = add_scl_ld (sclServerAIED);

			sclLdDst->desc = (ST_CHAR*)calloc (strlen (sclLdSrc->desc) + 1, sizeof (ST_CHAR));
			strcpy (sclLdDst->desc, sclLdSrc->desc);
			sclLdDst->inst = (ST_CHAR*)calloc (strlen (sclLdSrc->inst) + 1, sizeof (ST_CHAR));
			strcpy (sclLdDst->inst, ldInst);
			sclLdDst->ldName = (ST_CHAR*)calloc (strlen (sclLdSrc->ldName) + 1, sizeof (ST_CHAR));
			strcpy (sclLdDst->ldName, sclLdSrc->ldName);
			for (sclLnSrc = (SCL_LN *)list_find_last ((DBL_LNK *)sclLdSrc->lnHead);
				sclLnSrc != NULL;
				sclLnSrc = (SCL_LN *)list_find_prev ((DBL_LNK *)sclLdSrc->lnHead, (DBL_LNK *)sclLnSrc)) {
				sclLnDst = add_scl_ln (sclLdDst);
				{
					sclLnDst->desc = (ST_CHAR*)calloc (strlen (sclLnSrc->desc) + 1, sizeof (ST_CHAR));
					strcpy (sclLnDst->desc, sclLnSrc->desc);
					sclLnDst->lnType = (ST_CHAR*)calloc (strlen (sclLnSrc->lnType) + 1, sizeof (ST_CHAR));
					strcpy (sclLnDst->lnType, sclLnSrc->lnType);
					sclLnDst->lnClass = (ST_CHAR*)calloc (strlen (sclLnSrc->lnClass) + 1, sizeof (ST_CHAR));
					strcpy (sclLnDst->lnClass, sclLnSrc->lnClass);
					sclLnDst->inst = (ST_CHAR*)calloc (strlen (sclLnSrc->inst) + 1, sizeof (ST_CHAR));
					strcpy (sclLnDst->inst, sclLnSrc->inst);
					sclLnDst->prefix = (ST_CHAR*)calloc (strlen (sclLnSrc->prefix) + 1, sizeof (ST_CHAR));
					strcpy (sclLnDst->prefix, sclLnSrc->prefix);
				}
			}
			
		}
	}

	return SD_SUCCESS;
}

ST_RET AddExtRef (CONFIG_CTRL *config_ctrl)
{
	SCL_SERVER *scl_server = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNameAggregator);
	if (scl_server == NULL)
	{
		printf ("scl_server not found. check IEDName");
		return SD_FAILURE;
	}

	SCL_LD *scl_ld = find_scl_ld (scl_server, "LD0");
	if (scl_ld == NULL)
		return SD_FAILURE;
	SCL_LN *scl_ln = find_scl_ln (scl_ld, "", "LLN0", "");
	SCL_SUBNET *scl_subnet = find_scl_subnet (config_ctrl->scl_info_aggregator, config_ctrl->subNetworkNameAggregator);
	SCL_CAP *scl_cap = find_scl_cap (scl_subnet, config_ctrl->iedNamePublisher);
	SCL_GSE *scl_gse;
	SCL_GCB *scl_gcb;
	SCL_DATASET *scl_dataset;
	SCL_FCDA *scl_fcda;
	SCL_EXTREF *scl_extref;
	SCL_LD *scl_ld_gse;
	SCL_LN *scl_ln_gse;

	for (scl_gse = (SCL_GSE *)list_find_last ((DBL_LNK *)scl_cap->gseHead);
		scl_gse != NULL;
		scl_gse = (SCL_GSE *)list_find_prev ((DBL_LNK *)scl_cap->gseHead, (DBL_LNK *)scl_gse))
	{
		scl_server = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNamePublisher);
		scl_ld_gse = find_scl_ld (scl_server, scl_gse->ldInst);//gse의 ldInst에 의해 참조된 ld
		//find LLN0
		scl_ln_gse = find_scl_ln (scl_ld_gse, "", "LLN0", "");//모든 컨트롤 블록은 LLN0에 위치함
		//find gcb
		scl_gcb = find_scl_gcb (scl_ln_gse, scl_gse->cbName);//gse의 cbName에 의해 참조된 gcb
		//find dataset
		scl_dataset = find_scl_dataset (scl_ln_gse, scl_gcb->datSet);//gcb에 의해 참조된 dataset
		for (scl_fcda = (SCL_FCDA *)list_find_last ((DBL_LNK *)scl_dataset->fcdaHead);
			scl_fcda != NULL;
			scl_fcda = (SCL_FCDA *)list_find_prev ((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
		{
			if (find_scl_extref(
				scl_ln,
				scl_server->iedName,
				scl_fcda->ldInst,
				scl_fcda->lnClass,
				scl_fcda->lnInst,
				scl_fcda->doName,
				scl_fcda->daName
				) == NULL)//중복검사
			{
				scl_extref = add_scl_extref (scl_ln);

				scl_extref->desc = "";

				scl_extref->intAddr = "user set this";

				scl_extref->iedName = (ST_CHAR*)calloc (strlen (config_ctrl->iedNamePublisher) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->iedName, config_ctrl->iedNamePublisher);

				scl_extref->ldInst = (ST_CHAR*)calloc (strlen (scl_fcda->ldInst) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->ldInst, scl_fcda->ldInst);

				scl_extref->prefix = (ST_CHAR*)calloc (strlen (scl_fcda->prefix) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->prefix, scl_fcda->prefix);

				scl_extref->lnClass = (ST_CHAR*)calloc (strlen (scl_fcda->lnClass) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->lnClass, scl_fcda->lnClass);

				scl_extref->lnInst = (ST_CHAR*)calloc (strlen (scl_fcda->lnInst) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->lnInst, scl_fcda->lnInst);

				scl_extref->doName = (ST_CHAR*)calloc (strlen (scl_fcda->doName) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->doName, scl_fcda->doName);

				scl_extref->daName = (ST_CHAR*)calloc (strlen (scl_fcda->daName) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->daName, scl_fcda->daName);

				scl_extref->serviceType = "GOOSE";

				scl_extref->srcLDInst = (ST_CHAR*)calloc (strlen (scl_gse->ldInst) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->srcLDInst, scl_gse->ldInst);

				scl_extref->srcPrefix = (ST_CHAR*)calloc (strlen (scl_ln_gse->prefix) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->srcPrefix, scl_ln_gse->prefix);

				scl_extref->srcLNClass = (ST_CHAR*)calloc (strlen (scl_ln_gse->lnClass) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->srcLNClass, scl_ln_gse->lnClass);

				scl_extref->srcLNInst = (ST_CHAR*)calloc (strlen (scl_ln_gse->inst) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->srcLNInst, scl_ln_gse->inst);

				scl_extref->srcCBName = (ST_CHAR*)calloc (strlen (scl_gcb->name) + 1, sizeof (ST_CHAR));
				strcpy (scl_extref->srcCBName, scl_gcb->name);

				strcpy (scl_extref->srcPrefix, scl_ln_gse->prefix);
				scl_extref->srcLNClass = "LLN0";
				scl_extref->srcLNInst = "";
			}
		}
	}

	return SD_SUCCESS;
}

ST_RET AddDAI (CONFIG_CTRL *config_ctrl)
{
	SCL_SERVER *sclServerAIED;
	SCL_SERVER *sclServerPIED;

	SCL_SUBNET *sclSubnet;
	SCL_CAP *sclCap;
	SCL_GSE *sclGse;

	SCL_LD *sclLd;//LD Ref by GSE, 컨트롤 블록이 위치함
	SCL_LN *sclLn;
	SCL_GCB *sclGcb;
	SCL_DATASET *sclDataset;
	SCL_FCDA *sclFcda;

	SCL_LD *sclLd_proxy;
	SCL_LN *sclLn_proxy;
	SCL_DAI *scl_dai;


	ST_CHAR *ldInst;
	ST_CHAR sAddr[256];
	ST_CHAR flattened[256];

	sclServerAIED = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNameAggregator);
	if (sclServerAIED == NULL) return SD_FAILURE;
	sclServerPIED = find_scl_server (config_ctrl->scl_info_publisher, config_ctrl->iedNamePublisher);
	if (sclServerPIED == NULL)return SD_FAILURE;
	sclSubnet = find_scl_subnet (config_ctrl->scl_info_publisher, config_ctrl->subNetworkNamePublisher);
	if (sclSubnet == NULL)return SD_FAILURE;
	sclCap = find_scl_cap (sclSubnet, config_ctrl->iedNamePublisher);//하나의 IED만 존재
	if (sclCap == NULL)return SD_FAILURE;
	for (sclGse = (SCL_GSE *)list_find_last ((DBL_LNK *)sclCap->gseHead);
		sclGse != NULL;
		sclGse = (SCL_GSE *)list_find_prev ((DBL_LNK *)sclCap->gseHead, (DBL_LNK *)sclGse))
	{

		//GSE에 해당하는DataSet 탐색
		sclLd = find_scl_ld (sclServerPIED, sclGse->ldInst);
		sclLn = find_scl_ln (sclLd, "", "LLN0", "");
		sclGcb = find_scl_gcb (sclLn, sclGse->cbName);
		sclDataset = find_scl_dataset (sclLn, sclGcb->datSet);

		for (sclFcda = (SCL_FCDA *)list_find_last ((DBL_LNK *)sclDataset->fcdaHead);
			sclFcda != NULL;
			sclFcda = (SCL_FCDA *)list_find_prev ((DBL_LNK *)sclDataset->fcdaHead, (DBL_LNK *)sclFcda))
		{
			ldInst = (ST_CHAR*)calloc (strlen (config_ctrl->iedNamePublisher) + strlen (sclFcda->ldInst) + 1, sizeof (ST_CHAR));
			sprintf (ldInst, "%s%s", config_ctrl->iedNamePublisher, sclFcda->ldInst);
			sclLd_proxy = find_scl_ld (sclServerAIED, ldInst);
			sclLn_proxy = find_scl_ln (sclLd_proxy, sclFcda->prefix, sclFcda->lnClass, sclFcda->lnInst);
			sprintf (flattened, "%s$%s", sclFcda->doName, sclFcda->daName);
			if (find_scl_dai (sclLn_proxy, flattened) == NULL)
			{
				scl_dai = add_scl_dai (sclLn_proxy);
				scl_dai->flattened = (ST_CHAR*)calloc (256, sizeof (ST_CHAR));
				sprintf (scl_dai->flattened, "%s$%s", sclFcda->doName, sclFcda->daName);
				scl_dai->sAddr = (ST_CHAR*)calloc (256, sizeof (ST_CHAR));
				convertDollarToPoint (scl_dai->flattened, sAddr);
				sprintf (scl_dai->sAddr, "%s/%s%s.%s", ldInst, sclFcda->lnClass, sclFcda->lnInst, sAddr);
			}
		}
	}
	return SD_SUCCESS;
}

ST_RET AddIEDName (CONFIG_CTRL *config_ctrl)
{
	SCL_SERVER* scl_server;
	SCL_SERVER* scl_server_ptr;
	SCL_LD* scl_ld;
	SCL_LN* scl_ln;
	SCL_GCB* scl_gcb;
	SCL_GCB_IEDNAME *scl_gcb_iedName;
	for (scl_server = (SCL_SERVER *)list_find_last ((DBL_LNK *)config_ctrl->scl_info_aggregator->serverHead);
		scl_server != NULL;
		scl_server = (SCL_SERVER *)list_find_prev ((DBL_LNK *)config_ctrl->scl_info_aggregator->serverHead, (DBL_LNK *)scl_server))
	{
		if (strcmp (scl_server->iedName, config_ctrl->iedNameAggregator))//자신을 제외한 IED
		{
			for (scl_ld = (SCL_LD *)list_find_last ((DBL_LNK *)scl_server->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev ((DBL_LNK *)scl_server->ldHead, (DBL_LNK *)scl_ld))
			{
				for (scl_ln = (SCL_LN *)list_find_last ((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev ((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					for (scl_gcb = (SCL_GCB *)list_find_last ((DBL_LNK *)scl_ln->gcbHead);
						scl_gcb != NULL;
						scl_gcb = (SCL_GCB *)list_find_prev ((DBL_LNK *)scl_ln->gcbHead, (DBL_LNK *)scl_gcb))
					{
						if (find_scl_gcb_iedName (scl_gcb, config_ctrl->iedNameAggregator) == NULL)//GCB에 자신이없다면 추가
						{
							scl_gcb_iedName = add_scl_gcb_iedName (scl_gcb);
							scl_server_ptr = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNameAggregator);
							scl_gcb_iedName->apRef = (ST_CHAR*)calloc (strlen (scl_server_ptr->apName + 1), sizeof (ST_CHAR));
							strcpy (scl_gcb_iedName->apRef, scl_server_ptr->apName);
							scl_gcb_iedName->iedName = (ST_CHAR*)calloc (strlen (config_ctrl->iedNameAggregator), sizeof (ST_CHAR));
							strcpy (scl_gcb_iedName->iedName, config_ctrl->iedNameAggregator);
							scl_gcb_iedName->ldInst = (ST_CHAR*)calloc (1, sizeof (ST_CHAR));
							scl_gcb_iedName->prefix = (ST_CHAR*)calloc (1, sizeof (ST_CHAR));
							scl_gcb_iedName->lnClass = (ST_CHAR*)calloc (1, sizeof (ST_CHAR));
							scl_gcb_iedName->lnInst = (ST_CHAR*)calloc (1, sizeof (ST_CHAR));
						}
					}
				}
			}
		}
	}
	return SD_SUCCESS;
}

ST_VOID convertDollarToPoint (ST_CHAR* flattened, ST_CHAR* result)
{
	ST_CHAR temp[256];
	ST_CHAR *ptr;
	strcpy (temp, flattened);
	strcpy(result,ptr = strtok (temp, "$"));
	ptr = strtok (NULL, "$");
	while (ptr)
	{
		strcat (result, ".");
		strcat (result, ptr);
		ptr = strtok (NULL, "$");
	}
}
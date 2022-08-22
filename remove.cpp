#include "remove.h"



ST_VOID RemoveConnectedAP (SCL_CAP **capHead, SCL_CAP *scl_cap)
{
	SCL_GSE *scl_gse;
	SCL_SMV *scl_smv;

	list_unlink (capHead,scl_cap);

	while ((scl_gse = (SCL_GSE *)list_get_first (&scl_cap->gseHead)) != NULL)
	{
		chk_free (scl_gse);
	}
	while ((scl_smv = (SCL_SMV *)list_get_first (&scl_cap->smvHead)) != NULL)
	{
		chk_free (scl_smv);
	}
	chk_free (scl_cap);
}

ST_VOID RemoveIED (SCL_SERVER **serverHead, SCL_SERVER *scl_server)
{
	SCL_LD *scl_ld;

	list_unlink (serverHead, scl_server);

	while ((scl_ld = (SCL_LD *)list_get_first (&scl_server->ldHead)) != NULL)
	{
		scl_ld_destroy (scl_ld);
	}
	chk_free (scl_server);
}

ST_VOID RemoveLD (SCL_LD **ldHead ,SCL_LD *scl_ld)
{
	SCL_LN *scl_ln;
	SCL_RCB *scl_rcb;
	SCL_LCB *scl_lcb;
	SCL_GCB *scl_gcb;
	SCL_GCB_IEDNAME *scl_gcb_iedname;
	SCL_SVCB *scl_svcb;
	SCL_SVCB_IEDNAME *scl_svcb_iedname;
	SCL_DAI *scl_dai;
	SCL_SDI *scl_sdi;
	SCL_DATASET *scl_dataset;
	SCL_FCDA *scl_fcda;
	SCL_SG_VAL *scl_sg_val;
	SCL_EXTREF *scl_extref;
	SCL_CLIENTLN *scl_clientln;

	list_unlink (ldHead, scl_ld);

	while ((scl_ln = (SCL_LN *)list_get_first (&scl_ld->lnHead)) != NULL)
	{
		while ((scl_dai = (SCL_DAI *)list_get_first (&scl_ln->daiHead)) != NULL)
		{
			while ((scl_sg_val = (SCL_SG_VAL *)list_get_first (&scl_dai->sgValHead)) != NULL)
			{
				chk_free (scl_sg_val);
			}
			chk_free (scl_dai);
		}
		while ((scl_sdi = (SCL_SDI *)list_get_first (&scl_ln->sdiHead)) != NULL)
		{
			chk_free (scl_sdi);
		}
		while ((scl_dataset = (SCL_DATASET *)list_get_first (&scl_ln->datasetHead)) != NULL)
		{
			while ((scl_fcda = (SCL_FCDA *)list_get_first (&scl_dataset->fcdaHead)) != NULL)
			{
				chk_free (scl_fcda);
			}
			chk_free (scl_dataset);
		}
		while ((scl_rcb = (SCL_RCB *)list_get_first (&scl_ln->rcbHead)) != NULL)
		{
			while ((scl_clientln = (SCL_CLIENTLN *)list_get_first (&scl_rcb->clientlnHead)) != NULL)
			{
				chk_free (scl_clientln);
			}
			chk_free (scl_rcb);
		}
		while ((scl_lcb = (SCL_LCB *)list_get_first (&scl_ln->lcbHead)) != NULL)
		{
			chk_free (scl_lcb);
		}
		while ((scl_gcb = (SCL_GCB *)list_get_first (&scl_ln->gcbHead)) != NULL)
		{
			while ((scl_gcb_iedname = (SCL_GCB_IEDNAME *)list_get_first (&scl_gcb->iedNameHead)) != NULL)
			{
				chk_free (scl_gcb_iedname);
			}
			chk_free (scl_gcb);
		}
		while ((scl_svcb = (SCL_SVCB *)list_get_first (&scl_ln->svcbHead)) != NULL)
		{
			while ((scl_svcb_iedname = (SCL_SVCB_IEDNAME *)list_get_first (&scl_svcb->iedNameHead)) != NULL)
			{
				chk_free (scl_svcb_iedname);
			}
			chk_free (scl_svcb);
		}
		while ((scl_extref = (SCL_EXTREF *)list_get_first (&scl_ln->extrefHead)) != NULL)
		{
			chk_free (scl_extref);
		}
		if (scl_ln->sgcb)
		{
			chk_free (scl_ln->sgcb);
		}
		chk_free (scl_ln);
	}
	chk_free (scl_ld);
}

ST_VOID RemoveExtRef (SCL_EXTREF **extrefHead, SCL_EXTREF *scl_extref)
{
	list_unlink (extrefHead, scl_extref);
	chk_free (scl_extref);
}

ST_VOID DeleteSubscription (CONFIG_CTRL *config_ctrl)
{
	SCL_SUBNET *scl_subnet;
	SCL_CAP *scl_cap;
	SCL_SERVER *scl_server;
	SCL_LD *scl_ld;
	SCL_LD *scl_ld_remove;
	SCL_LN *scl_ln;
	SCL_EXTREF *scl_extref;
	SCL_EXTREF *scl_extref_remove;
	
	scl_subnet = find_scl_subnet (config_ctrl->scl_info_aggregator, config_ctrl->subNetworkNameAggregator);
	if (scl_subnet == NULL)return;
	scl_cap = find_scl_cap (scl_subnet, config_ctrl->iedNamePublisher);
	if (scl_cap == NULL)return;
	RemoveConnectedAP (&scl_subnet->capHead, scl_cap);

	scl_server = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNamePublisher);
	if (scl_server == NULL)return;
	RemoveIED (&(config_ctrl->scl_info_aggregator)->serverHead, scl_server);


	scl_server = find_scl_server (config_ctrl->scl_info_aggregator, config_ctrl->iedNameAggregator);
	scl_ld = find_scl_ld (scl_server, "LD0");
	scl_ln = find_scl_ln (scl_ld, "", "LLN0", "");
	scl_extref = (SCL_EXTREF *)list_find_last ((DBL_LNK *)scl_ln->extrefHead);
	while (scl_extref != NULL)
	{
		if (!strcmp (scl_extref->iedName, config_ctrl->iedNamePublisher))
		{
			scl_extref_remove = scl_extref;
			scl_extref = (SCL_EXTREF *)list_find_prev ((DBL_LNK *)scl_ln->extrefHead, (DBL_LNK *)scl_extref);
			RemoveExtRef (&scl_ln->extrefHead, scl_extref_remove);
		}
		else
			scl_extref = (SCL_EXTREF *)list_find_prev ((DBL_LNK *)scl_ln->extrefHead, (DBL_LNK *)scl_extref);
	}

	scl_ld = (SCL_LD *)list_find_last ((DBL_LNK *)scl_server->ldHead);
	while (scl_ld != NULL)
	{
		if (strstr (scl_ld->inst, config_ctrl->iedNamePublisher))
		{
			scl_ld_remove = scl_ld;
			scl_ld = (SCL_LD *)list_find_prev ((DBL_LNK *)scl_server->ldHead, (DBL_LNK *)scl_ld);
			RemoveLD (&scl_server->ldHead, scl_ld_remove);
		}
		else
			scl_ld = (SCL_LD *)list_find_prev ((DBL_LNK *)scl_server->ldHead, (DBL_LNK *)scl_ld);
	}
}

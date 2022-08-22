#include "ngn.h"

ST_RET GetSclInfo (ST_CHAR *fileName, SCL_INFO *scl_info) {
	ST_RET ret;

	SCL_OPTIONS options = { 0 };
	options.forceEdition = 2;   /* Treat as Edition 2 file no matter what*/
	options.includeOwner = SD_FALSE;
	options.buf_size = 100000;

	ret = scl_parse_scd_all (fileName, &options, scl_info);

	if (ret)
	{
		if (ret == 100)
			return SD_SUCCESS;
		return SD_FAILURE;
	}
	else
		return SD_SUCCESS;
}

ST_VOID CreateTreeView (SCL_INFO *scl_info, System::Windows::Forms::TreeView^ treeView, System::String^IEDName) {
	SCL_SERVER *scl_server;
	SCL_LD *scl_ld;
	SCL_LN *scl_ln;
	SCL_DATASET *scl_dataset;
	//SCL_FCDA *scl_fcda;
	SCL_EXTREF *scl_extref;

	ST_UINT server_idx = 0;
	ST_UINT ld_idx = 0;
	ST_UINT ln_idx = 0;
	ST_UINT dataset_idx = 0;

	ST_CHAR string[256];
	ST_CHAR temp[256];

	System::String^ marshal_string;
	marshal_context^ context = gcnew marshal_context ();

	/*for (scl_server = (SCL_SERVER*)list_find_last ((DBL_LNK*)scl_info->serverHead);
		scl_server != NULL;
		scl_server = (SCL_SERVER*)list_find_prev ((DBL_LNK*)scl_info->serverHead, (DBL_LNK*)scl_server))*/
	if (strcmp ((ST_CHAR*)context->marshal_as<const char*> (IEDName), ""))
		scl_server = find_scl_server (scl_info, (ST_CHAR*)context->marshal_as<const char*> (IEDName));
	else
		scl_server = scl_info->serverHead;
	delete context;
	{
		marshal_string = marshal_as<System::String^> (scl_server->iedName);
		treeView->Nodes->Add ("IED : " + marshal_string);

		for (scl_ld = (SCL_LD *)list_find_last ((DBL_LNK *)scl_server->ldHead);
			scl_ld != NULL;
			scl_ld = (SCL_LD *)list_find_prev ((DBL_LNK *)scl_server->ldHead, (DBL_LNK *)scl_ld)) {
			marshal_string = marshal_as<System::String^> (scl_ld->inst);
			treeView->Nodes[server_idx]->Nodes->Add ("LD : " + marshal_string);

			for (scl_ln = (SCL_LN *)list_find_last ((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev ((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln)) {
				strcpy (temp, scl_ln->prefix);
				strcat (temp, scl_ln->lnClass);
				strcat (temp, scl_ln->inst);
				marshal_string = marshal_as<System::String^> (temp);
				treeView->Nodes[server_idx]->Nodes[ld_idx]->Nodes->Add ("LN : " + marshal_string);

				for (scl_dataset = (SCL_DATASET *)list_find_last ((DBL_LNK *)scl_ln->datasetHead);
					scl_dataset != NULL;
					scl_dataset = (SCL_DATASET *)list_find_prev ((DBL_LNK *)scl_ln->datasetHead, (DBL_LNK *)scl_dataset)) {
					marshal_string = marshal_as<System::String^> (scl_dataset->name);
					treeView->Nodes[server_idx]->Nodes[ld_idx]->Nodes[ln_idx]->Nodes->Add ("Dataset : " + marshal_string);
				}

				for (scl_extref = (SCL_EXTREF *)list_find_last ((DBL_LNK *)scl_ln->extrefHead);
					scl_extref != NULL;
					scl_extref = (SCL_EXTREF *)list_find_prev ((DBL_LNK *)scl_ln->extrefHead, (DBL_LNK *)scl_extref)) {
					sprintf (string, "%s%s %s%s%s", scl_extref->iedName, scl_extref->ldInst, scl_extref->prefix, scl_extref->lnClass, scl_extref->lnInst);
					if (strcmp (scl_extref->doName, ""))
					{
						strcat (string, " ");
						strcat (string, scl_extref->doName);
					}
						
					if (strcmp (scl_extref->daName, ""))
					{
						strcat (string, ".");
						strcat (string, scl_extref->daName);
					}
						
					marshal_string = marshal_as<System::String^> (string);
					treeView->Nodes[server_idx]->Nodes[ld_idx]->Nodes[ln_idx]->Nodes->Add ("ExtRef : " + marshal_string);
				}
				ln_idx++;
			}
			ln_idx = 0;
			ld_idx++;
		}
		ld_idx = 0;
		server_idx++;
	}
	treeView->ExpandAll ();
}

ST_RET InitConfigCtrl (
	CONFIG_CTRL *config_ctrl,
	SCL_INFO* agg,
	SCL_INFO* pub,
	System::String^ iedNameAggregator,
	System::String^ iedNamePublisher,
	System::String^ subNetworkNameAggregator,
	System::String^ subNetworkNamePublisher
) {
	ST_RET ret;
	marshal_context^ context = gcnew marshal_context ();
	config_ctrl->scl_info_aggregator = agg;
	config_ctrl->scl_info_publisher = pub;
	strcpy (config_ctrl->iedNameAggregator,
					(ST_CHAR*)context->marshal_as<const char*> (iedNameAggregator));
	strcpy (config_ctrl->iedNamePublisher,
					(ST_CHAR*)context->marshal_as<const char*> (iedNamePublisher));
	strcpy (config_ctrl->subNetworkNameAggregator,
					(ST_CHAR*)context->marshal_as<const char*> (subNetworkNameAggregator));
	strcpy (config_ctrl->subNetworkNamePublisher,
					(ST_CHAR*)context->marshal_as<const char*> (subNetworkNamePublisher));

	delete context;
	return SD_SUCCESS;
}

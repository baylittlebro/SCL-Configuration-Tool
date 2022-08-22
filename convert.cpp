#include "convert.h"

ST_VOID ConvertSclInfo (SCL_INFO* scl_info, ST_CHAR *fileName){
	tinyxml2::XMLDocument doc;

	XMLDeclaration* decl = doc.NewDeclaration ();
	doc.LinkEndChild (decl);

	LinkSCL (scl_info, &doc);

	doc.SaveFile (fileName);
}

ST_VOID LinkSCL (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc){
	SCL_SERVER *scl_server;

	XMLElement* elem = doc->NewElement ("SCL");
	doc->LinkEndChild (elem);

	elem->SetAttribute ("xmlns", "http://www.iec.ch/61850/2003/SCL");
	elem->SetAttribute ("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	elem->SetAttribute ("xsi:schemaLocation", "http://www.iec.ch/61850/2003/SCL SCL.xsd");
	/*
	if (scl_info->edition == 2)
	{
		elem->SetAttribute ("version", "2007");
		elem->SetAttribute ("revisioin", "B");
	}
	*/
	LinkHeader (scl_info, doc, elem);
	LinkCommunication (scl_info, doc, elem);
	for (scl_server = (SCL_SERVER *)list_find_last ((DBL_LNK *)scl_info->serverHead);
		scl_server != NULL;
		scl_server = (SCL_SERVER *)list_find_prev ((DBL_LNK *)scl_info->serverHead, (DBL_LNK *)scl_server))
		LinkIED (scl_server, doc, elem);
	LinkDataTypeTemplates (scl_info, doc, elem);
}

ST_VOID LinkHeader (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("Header");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("id", scl_info->Header.id);
	/* Always assume nameStructure="IEDName" (i.e. "Product Naming")      */
	//if (scl_info->Header.nameStructure == SCL_NAMESTRUCTURE_IEDNAME)
	elem->SetAttribute ("nameStructure", "IEDName");
}

ST_VOID LinkCommunication (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_SUBNET *scl_subnet;

	XMLElement* elem = doc->NewElement ("Communication");
	parent->LinkEndChild (elem);

	for (scl_subnet = (SCL_SUBNET *)list_find_last ((DBL_LNK *)scl_info->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *)list_find_prev ((DBL_LNK *)scl_info->subnetHead, (DBL_LNK *)scl_subnet))
		LinkSubNetwork (scl_subnet, doc, elem);
}

ST_VOID LinkSubNetwork (SCL_SUBNET *scl_subnet, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_CAP *scl_cap;

	XMLElement* elem = doc->NewElement ("SubNetwork");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("name", scl_subnet->name);
	if (strcmp (scl_subnet->desc, empty_string))
		elem->SetAttribute ("desc", scl_subnet->desc);
	if (strcmp (scl_subnet->type, empty_string))
		elem->SetAttribute ("type", scl_subnet->type);

	for (scl_cap = (SCL_CAP *)list_find_last ((DBL_LNK *)scl_subnet->capHead);
		scl_cap != NULL;
		scl_cap = (SCL_CAP *)list_find_prev ((DBL_LNK *)scl_subnet->capHead, (DBL_LNK *)scl_cap))
		LinkConnectedAP (scl_cap, doc, elem);
}

ST_VOID LinkConnectedAP (SCL_CAP *scl_cap, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_GSE *scl_gse;

	XMLElement* elem = doc->NewElement ("ConnectedAP");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("iedName", scl_cap->iedName);
	elem->SetAttribute ("apName", scl_cap->apName);
	if (strcmp (scl_cap->desc, empty_string))
		elem->SetAttribute ("desc", scl_cap->desc);

	LinkAddress (scl_cap->address, doc, elem);
	for (scl_gse = (SCL_GSE *)list_find_last ((DBL_LNK *)scl_cap->gseHead);
		scl_gse != NULL;
		scl_gse = (SCL_GSE *)list_find_prev ((DBL_LNK *)scl_cap->gseHead, (DBL_LNK *)scl_gse))
		LinkGSE (scl_gse, doc, elem);
}

ST_VOID LinkAddress (SCL_ADDRESS address, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement *elem = doc->NewElement ("Address");
	parent->LinkEndChild (elem);

	/* Shall be present for remote addressing. Both may be present for local addressing. */
	LinkAddress_P (address, doc, elem, "IP");
	
	/* Shall be present if IP is specified */
	LinkAddress_P (address, doc, elem, "IP-SUBNET");
	LinkAddress_P (address, doc, elem, "IP-GATEWAY");
	
	/* Mandatory */
	LinkAddress_P (address, doc, elem, "OSI-PSEL");
	LinkAddress_P (address, doc, elem, "OSI-SSEL");
	LinkAddress_P (address, doc, elem, "OSI-TSEL");

	/* Optional */
	if (address.ae_title.AP_title_pres == SD_TRUE)
		LinkAddress_P (address, doc, elem, "OSI-AP-Title");
	if (address.ae_title.AE_qual_pres == SD_TRUE)
		LinkAddress_P (address, doc, elem, "OSI-AE-Qualifier");
	if (address.ae_title.AP_inv_id_pres == SD_TRUE)
		LinkAddress_P (address, doc, elem, "OSI-AP-Invoke");
	if (address.ae_title.AE_inv_id_pres == SD_TRUE)
		LinkAddress_P (address, doc, elem, "OSI-AE-Invoke");
	/*
	if (strcmp ((ST_CHAR*)address.ipv6Addr, empty_string))
		LinkAddress_P (address, doc, elem, "IPv6");
	if (strcmp ((ST_CHAR*)address.ipv6SubnetAddr, empty_string))
		LinkAddress_P (address, doc, elem, "IPv6-SUBNET");
	if (strcmp ((ST_CHAR*)address.ipv6GatewayAddr, empty_string))
		LinkAddress_P (address, doc, elem, "IPv6-GATEWAY");
	*/
}

ST_VOID LinkAddress_P (SCL_ADDRESS address, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR* type){
	int i;
	struct in_addr ipv4;
	//struct in6_addr ipv6;
	ST_CHAR strOut[17]; //Shall be limited to no more than 16 characters.

	XMLElement* elem = doc->NewElement ("P");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("type", type);

	if (strcmp (type, "IP") == 0){
		ipv4.s_addr = address.ip;
		elem->SetText (inet_ntoa (ipv4));
	}
	else if (strcmp (type, "IP-SUBNET") == 0){
		ipv4.s_addr = address.IP_SUBNET;
		elem->SetText (inet_ntoa (ipv4));
	}
	else if (strcmp (type, "IP-GATEWAY") == 0){
		ipv4.s_addr = address.IP_GATEWAY;
		elem->SetText (inet_ntoa (ipv4));
	}
	else if (strcmp (type, "OSI-PSEL") == 0){
		hex_to_ascii_str (strOut, address.psel, address.psel_len, SD_TRUE);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "OSI-SSEL") == 0){
		hex_to_ascii_str (strOut, address.ssel, address.ssel_len, SD_TRUE);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "OSI-TSEL") == 0){
		hex_to_ascii_str (strOut, address.tsel, address.tsel_len, SD_TRUE);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "OSI-AP-Title") == 0){
		for (i = 0; i < address.ae_title.AP_title.num_comps; i++){
			if (i != 0)
				elem->LinkEndChild (doc->NewText (" "));
			elem->LinkEndChild (doc->NewText (sInt16ToAscii (address.ae_title.AP_title.comps[i], strOut)));
		}
	}
	else if (strcmp (type, "OSI-AE-Qualifier") == 0)
		elem->SetText (sInt32ToAscii (address.ae_title.AE_qual, strOut));
	else if (strcmp (type, "OSI-AP-Invoke") == 0)
		elem->SetText (sInt32ToAscii (address.ae_title.AP_inv_id, strOut));
	else if (strcmp (type, "OSI-AE-Invoke") == 0)
		elem->SetText (sInt32ToAscii (address.ae_title.AE_inv_id, strOut));
	//else if (strcmp (type, "IPv6") == 0) {}
	//else if (strcmp (type, "IPv6-SUBNET") == 0) {}
	//else if (strcmp (type, "IPv6-GATEWAY") == 0) {}
}

ST_VOID LinkGSE (SCL_GSE *scl_gse, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement *elem = doc->NewElement ("GSE");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("ldInst", scl_gse->ldInst);
	elem->SetAttribute ("cbName", scl_gse->cbName);

	LinkGSE_Address (scl_gse, doc, elem);
}

ST_VOID LinkGSE_Address (SCL_GSE *scl_gse, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement *elem = doc->NewElement ("Address");
	parent->LinkEndChild (elem);

	/* Mandatory (R-GOOSE의 경우 필요하지 않을수 있음)*/
	if (scl_gse->MAC != 0)
		LinkGSE_Address_P (scl_gse, doc, elem, "MAC-Address");

	if (scl_gse->APPID != 0)
		LinkGSE_Address_P (scl_gse, doc, elem, "APPID");
	if (scl_gse->VLANPRI != 0)
		LinkGSE_Address_P (scl_gse, doc, elem, "VLAN-PRIORITY");
	if (scl_gse->VLANID != 0)
		LinkGSE_Address_P (scl_gse, doc, elem, "VLAN-ID");
	if (scl_gse->IP_IGMPv3Src != 0)
		LinkGSE_Address_P (scl_gse, doc, elem, "IP-IGMPv3Src");
	if (scl_gse->IP != INADDR_ANY)
		LinkGSE_Address_P (scl_gse, doc, elem, "IP");
	if (scl_gse->IP_SUBNET != INADDR_ANY)
		LinkGSE_Address_P (scl_gse, doc, elem, "IP-SUBNET");
	if (scl_gse->IP_GATEWAY != INADDR_ANY)
		LinkGSE_Address_P (scl_gse, doc, elem, "IP-GATEWAY");
	if (scl_gse->IP_ClassOfTraffic != 0)
		LinkGSE_Address_P (scl_gse, doc, elem, "IP-ClassOfTraffic");
	if (scl_gse->KDAParticipant != 0)
		LinkGSE_Address_P (scl_gse, doc, elem, "KDAParticipant");
}

ST_VOID LinkGSE_Address_P (SCL_GSE *scl_gse, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR* type){
	ST_CHAR strOut[MAX_MAC_STRING_LEN + 1];
	struct in_addr ipv4;

	XMLElement *elem = doc->NewElement ("P");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("type", type);

	if (strcmp (type, "MAC-Address") == 0){
		ConvertHex (strOut, scl_gse->MAC);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "APPID") == 0){
		sprintf (strOut, "%X", scl_gse->APPID);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "VLAN-PRIORITY") == 0){
		sprintf (strOut, "%X", scl_gse->VLANPRI);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "VLAN-ID") == 0){
		sprintf (strOut, "%X", scl_gse->VLANID);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "IP-IGMPv3Src") == 0){
		ipv4.s_addr = scl_gse->IP_IGMPv3Src;
		elem->SetText (inet_ntoa (ipv4));
	}
	else if (strcmp (type, "IP") == 0){
		ipv4.s_addr = scl_gse->IP;
		elem->SetText (inet_ntoa (ipv4));
	}
	else if (strcmp (type, "IP-SUBNET") == 0){
		ipv4.s_addr = scl_gse->IP_SUBNET;
		elem->SetText (inet_ntoa (ipv4));
	}
	else if (strcmp (type, "IP-GATEWAY") == 0){
		ipv4.s_addr = scl_gse->IP_GATEWAY;
		elem->SetText (inet_ntoa (ipv4));
	}
	else if (strcmp (type, "IP-ClassOfTraffic") == 0){
		sprintf (strOut, "%d", scl_gse->IP_ClassOfTraffic);
		elem->SetText (strOut);
	}
	else if (strcmp (type, "KDAParticipant") == 0)
		elem->SetText ("true");
}

ST_VOID LinkIED (SCL_SERVER *scl_server, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("IED");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("name", scl_server->iedName);

	LinkServices (scl_server->scl_services, doc, elem);
	LinkAccessPoint (scl_server, doc, elem);
	//AccessPoint별로 다른 서비스를 제공할 수 있음
	//LinkServer_Services(scl_server->scl_services, doc, elem);
}

ST_VOID LinkServices (SCL_SERVICES scl_services, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("Services");
	parent->LinkEndChild (elem);

	/* booleans */
	if (scl_services.GetDirectory)
		LinkServices_Elem (scl_services, doc, elem, "GetDirectory");
	if (scl_services.GetDataObjectDefinition)
		LinkServices_Elem (scl_services, doc, elem, "GetDataObjectDefinition");
	if (scl_services.DataObjectDirectory)
		LinkServices_Elem (scl_services, doc, elem, "DataObjectDirectory");
	if (scl_services.GetDataSetValue)
		LinkServices_Elem (scl_services, doc, elem, "GetDataSetValue");
	if (scl_services.SetDataSetValue)
		LinkServices_Elem (scl_services, doc, elem, "SetDataSetValue");
	if (scl_services.DataSetDirectory)
		LinkServices_Elem (scl_services, doc, elem, "DataSetDirectory");
	if (scl_services.ReadWrite)
		LinkServices_Elem (scl_services, doc, elem, "ReadWrite");
	if (scl_services.TimerActivatedControl)
		LinkServices_Elem (scl_services, doc, elem, "TimerActivatedControl");
	if (scl_services.GetCBValues)
		LinkServices_Elem (scl_services, doc, elem, "GetCBValues");
	if (scl_services.GSEDir)
		LinkServices_Elem (scl_services, doc, elem, "GSEDir");
	if (scl_services.FileHandling)
		LinkServices_Elem (scl_services, doc, elem, "FileHandling");
	if (scl_services.ConfLdName)
		LinkServices_Elem (scl_services, doc, elem, "ConfLdName");

	/* complicated */
	if (scl_services.ConfLogControl.enabled)
		LinkServices_Elem (scl_services, doc, elem, "ConfLogControl");
	if (scl_services.GOOSE.enabled)
		LinkServices_Elem (scl_services, doc, elem, "GOOSE");
	if (scl_services.GSSE.enabled)
		LinkServices_Elem (scl_services, doc, elem, "GSSE");
	if (scl_services.SMVsc.enabled)
		LinkServices_Elem (scl_services, doc, elem, "SMVsc");
	if (scl_services.SupSubscription.enabled)
		LinkServices_Elem (scl_services, doc, elem, "SupSubscription");
	if (scl_services.ConfSigRef.enabled)
		LinkServices_Elem (scl_services, doc, elem, "ConfSigRef");
	if (scl_services.DynAssociation.enabled)
		LinkServices_Elem (scl_services, doc, elem, "DynAssociation");
	if (scl_services.SettingGroups.ConfSG ||
		scl_services.SettingGroups.SGEdit)
		LinkServices_Elem (scl_services, doc, elem, "SettingGroups");
	if (scl_services.ConfDataSet.enabled)
		LinkServices_Elem (scl_services, doc, elem, "ConfDataSet");
	if (scl_services.DynDataSet.enabled)
		LinkServices_Elem (scl_services, doc, elem, "DynDataSet");
	if (scl_services.ConfReportControl.enabled)
		LinkServices_Elem (scl_services, doc, elem, "ConfReportControl");

	/*
	if (strcmp (scl_services.LogSettings.cbName, "Fix") ||
		strcmp (scl_services.LogSettings.datSet, "Fix") ||
		strcmp (scl_services.LogSettings.logEna, "Fix") ||
		strcmp (scl_services.LogSettings.trgOps, "Fix") ||
		strcmp (scl_services.LogSettings.intgPd, "Fix"))
		LinkServices_Elem (scl_services, doc, elem, "LogSettings");
	*/

	if (strcmp (scl_services.GSESettings.cbName, "Fix") ||
		strcmp (scl_services.GSESettings.datSet, "Fix") ||
		strcmp (scl_services.GSESettings.appID, "Fix") ||
		strcmp (scl_services.GSESettings.dataLabel, "Fix"))
		LinkServices_Elem (scl_services, doc, elem, "GSESettings");
	
	//LinkServices_Elem (scl_services, doc, elem, "SMVSettings");

	if (scl_services.ConfLNs.fixPrefix ||
		scl_services.ConfLNs.fixLnInst)
		LinkServices_Elem (scl_services, doc, elem, "ConfLNs");

	if (scl_services.ClientServices.goose ||
		scl_services.ClientServices.gsse ||
		scl_services.ClientServices.bufReport ||
		scl_services.ClientServices.unbufReport ||
		scl_services.ClientServices.readLog ||
		scl_services.ClientServices.sv)
		LinkServices_Elem (scl_services, doc, elem, "ConfLNs");

	if (strcmp (scl_services.ReportSettings.cbName, "Fix") ||
		strcmp (scl_services.ReportSettings.datSet, "Fix") ||
		strcmp (scl_services.ReportSettings.rptID, "Fix") ||
		strcmp (scl_services.ReportSettings.optFields, "Fix") ||
		strcmp (scl_services.ReportSettings.bufTime, "Fix") ||
		strcmp (scl_services.ReportSettings.trgOps, "Fix") ||
		strcmp (scl_services.ReportSettings.intgPd, "Fix") ||
		(scl_services.ReportSettings.resvTms == SD_TRUE) ||
		(scl_services.ReportSettings.owner == SD_TRUE))
		LinkServices_Elem (scl_services, doc, elem, "ReportSettings");
	
}

ST_VOID LinkServices_Elem (
	SCL_SERVICES scl_services,
	tinyxml2::XMLDocument *doc,
	XMLElement *parent,
	ST_CHAR *name){

	XMLElement* elem = doc->NewElement (name);
	parent->LinkEndChild (elem);

	if (strcmp (name, "ConfLogControl") == 0)
		elem->SetAttribute ("max", scl_services.ConfLogControl.max);
	if (strcmp (name, "GOOSE") == 0)
		elem->SetAttribute ("max", scl_services.GOOSE.max);
	if (strcmp (name, "GSSE") == 0)
		elem->SetAttribute ("max", scl_services.GSSE.max);
	if (strcmp (name, "SMVsc") == 0)
		elem->SetAttribute ("max", scl_services.SMVsc.max);
	if (strcmp (name, "SupSubscription") == 0){
		elem->SetAttribute ("maxGo", scl_services.SupSubscription.maxGo);
		elem->SetAttribute ("maxSv", scl_services.SupSubscription.maxSv);
	}
	if (strcmp (name, "ConfSigRef") == 0)
		elem->SetAttribute ("max", scl_services.ConfSigRef.max);
	if (strcmp (name, "DynAssociation") == 0)
		if(scl_services.DynAssociation.max != 0)
		elem->SetAttribute ("max", scl_services.DynAssociation.max);
	if (strcmp (name, "SettingGroups") == 0){
		if (scl_services.SettingGroups.SGEdit)
			elem->LinkEndChild(doc->NewElement ("SGEdit"));
		if (scl_services.SettingGroups.ConfSG)
			elem->LinkEndChild (doc->NewElement ("ConfSG"));
	}
	if (strcmp (name, "ConfDataSet") == 0){
		elem->SetAttribute ("max", scl_services.ConfDataSet.max);
		if (scl_services.ConfDataSet.maxAttributesPres)
			elem->SetAttribute ("maxAttributes", scl_services.ConfDataSet.maxAttributes);
		if(scl_services.ConfDataSet.modify == SD_FALSE)
		elem->SetAttribute ("modify", "false");
	}
	if (strcmp (name, "DynDataSet") == 0){
		elem->SetAttribute ("max", scl_services.DynDataSet.max);
		if (scl_services.DynDataSet.maxAttributesPres)
			elem->SetAttribute ("maxAttributes", scl_services.DynDataSet.maxAttributes);
	}
}

ST_VOID LinkAccessPoint (SCL_SERVER *scl_server, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("AccessPoint");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("name", scl_server->apName);

	LinkServer (scl_server, doc, elem);
}
ST_VOID LinkServer (SCL_SERVER *scl_server, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_LD *scl_ld;

	XMLElement* elem = doc->NewElement ("Server");
	parent->LinkEndChild (elem);

	if (scl_server->timeout)
		elem->SetAttribute ("timeout", scl_server->timeout);
	for (scl_ld = (SCL_LD *)list_find_last ((DBL_LNK *)scl_server->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev ((DBL_LNK *)scl_server->ldHead, (DBL_LNK *)scl_ld))
		LinkLDevice (scl_ld, doc, elem);
}

/*
ST_VOID LinkServer_Services (SCL_SERVICES *scl_services, tinyxml2::XMLDocument *doc, XMLElement *parent)
{
	XMLElement* elem = doc->NewElement (name);
	parent->LinkEndChild (elem);
}
*/

ST_VOID LinkLDevice (SCL_LD *scl_ld, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_LN *scl_ln;

	XMLElement* elem = doc->NewElement ("LDevice");
	parent->LinkEndChild (elem);

	if (strcmp (scl_ld->desc, empty_string) != 0)
		elem->SetAttribute ("desc", scl_ld->desc);
	if (strcmp (scl_ld->desc, empty_string) != 0)
		elem->SetAttribute ("ldName", scl_ld->ldName);
	elem->SetAttribute ("inst", scl_ld->inst);

	for (scl_ln = (SCL_LN *)list_find_last ((DBL_LNK *)scl_ld->lnHead);
		scl_ln != NULL;
		scl_ln = (SCL_LN *)list_find_prev ((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
		LinkLN (scl_ln, doc, elem);
}

ST_VOID LinkLN (SCL_LN *scl_ln, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_DATASET *scl_dataset;
	SCL_GCB     *scl_gcb;
	SCL_DAI *scl_dai;

	XMLElement* elem;
	if (strcmp (scl_ln->lnClass, "LLN0") == 0)
		elem = doc->NewElement ("LN0");
	else
		elem = doc->NewElement ("LN");
	parent->LinkEndChild (elem);

	if (strcmp (scl_ln->desc, empty_string))
		elem->SetAttribute ("desc", scl_ln->desc);
	if (strcmp (scl_ln->prefix, empty_string))
		elem->SetAttribute ("prefix", scl_ln->prefix);
	elem->SetAttribute ("lnType", scl_ln->lnType);
	elem->SetAttribute ("inst", scl_ln->inst);
	elem->SetAttribute ("lnClass", scl_ln->lnClass);

	for (scl_dataset = (SCL_DATASET *)list_find_last ((DBL_LNK *)scl_ln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev ((DBL_LNK *)scl_ln->datasetHead, (DBL_LNK *)scl_dataset))
		LinkDataSet (scl_dataset, doc, elem);

	for (scl_dai = (SCL_DAI *)list_find_last ((DBL_LNK *)scl_ln->daiHead);
		scl_dai != NULL;
		scl_dai = (SCL_DAI *)list_find_prev ((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
		LinkDOI (scl_dai, doc, elem);

	for (scl_gcb = (SCL_GCB *)list_find_last ((DBL_LNK *)scl_ln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev ((DBL_LNK *)scl_ln->gcbHead, (DBL_LNK *)scl_gcb))
		LinkGSEControl (scl_gcb, doc, elem);

	if (scl_ln->extrefHead != NULL)
		LinkInputs (scl_ln,doc,elem);
}
ST_VOID LinkDataSet (SCL_DATASET *scl_dataset, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_FCDA *scl_fcda;

	XMLElement* elem = doc->NewElement ("DataSet");
	parent->LinkEndChild (elem);

	if (strcmp (scl_dataset->desc, empty_string))
		elem->SetAttribute ("desc", scl_dataset->desc);
	elem->SetAttribute ("name", scl_dataset->name);

	for (scl_fcda = (SCL_FCDA *)list_find_last ((DBL_LNK *)scl_dataset->fcdaHead);
		scl_fcda != NULL;
		scl_fcda = (SCL_FCDA *)list_find_prev ((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
		LinkFCDA (scl_fcda, doc, elem);
}
ST_VOID LinkFCDA (SCL_FCDA *scl_fcda, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("FCDA");
	parent->LinkEndChild (elem);

	if (strcmp (scl_fcda->ldInst, empty_string))
		elem->SetAttribute ("ldInst", scl_fcda->ldInst);
	if (strcmp (scl_fcda->prefix, empty_string))
		elem->SetAttribute ("prefix", scl_fcda->prefix);
	if (strcmp (scl_fcda->lnInst, empty_string))
		elem->SetAttribute ("lnInst", scl_fcda->lnInst);
	if (strcmp (scl_fcda->lnClass, empty_string))
		elem->SetAttribute ("lnClass", scl_fcda->lnClass);
	if (strcmp (scl_fcda->doName, empty_string))
		elem->SetAttribute ("doName", scl_fcda->doName);
	if (strcmp (scl_fcda->daName, empty_string))
		elem->SetAttribute ("daName", scl_fcda->daName);
	elem->SetAttribute ("fc", scl_fcda->fc);
	if (strcmp (scl_fcda->ix, empty_string))
		elem->SetAttribute ("ix", scl_fcda->ix);
}

/*
ST_VOID LinkReportControl (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
{
	XMLElement* elem = doc->NewElement (name);
	parent->LinkEndChild (elem);
}
ST_VOID LinkLogControl (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
{
	XMLElement* elem = doc->NewElement (name);
	parent->LinkEndChild (elem);
}
*/

ST_VOID LinkGSEControl (SCL_GCB *scl_gcb, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_GCB_IEDNAME *scl_gcb_iedname;

	XMLElement* elem = doc->NewElement ("GSEControl");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("name", scl_gcb->name);
	if (strcmp (scl_gcb->desc, empty_string))
		elem->SetAttribute ("desc", scl_gcb->desc);
	if (scl_gcb->confRev)
		elem->SetAttribute ("confRev", scl_gcb->confRev);
	if (strcmp (scl_gcb->datSet, empty_string))
		elem->SetAttribute ("datSet", scl_gcb->datSet);
	if (scl_gcb->isGoose == SD_FALSE)
		elem->SetAttribute ("type", "GSSE");
	if (scl_gcb->fixedOffs == SD_TRUE)
		elem->SetAttribute ("fixedOffs", "true");
	elem->SetAttribute ("appID", scl_gcb->appID);

	if (scl_gcb->isRgoose == SD_TRUE)
		LinkGSEControl_Protocol (scl_gcb, doc, elem);
	for (scl_gcb_iedname = (SCL_GCB_IEDNAME *)list_find_last ((DBL_LNK *)scl_gcb->iedNameHead);
		scl_gcb_iedname != NULL;
		scl_gcb_iedname = (SCL_GCB_IEDNAME *)list_find_prev ((DBL_LNK *)scl_gcb->iedNameHead, (DBL_LNK *)scl_gcb_iedname))
		LinkGSEControl_IEDName (scl_gcb_iedname, doc, elem);
}

ST_VOID LinkGSEControl_Protocol (SCL_GCB *scl_gcb, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("Protocol");
	parent->LinkEndChild (elem);

	elem->SetText ("R-GOOSE");
}

ST_VOID LinkGSEControl_IEDName (
	SCL_GCB_IEDNAME *scl_gcb_iedname,
	tinyxml2::XMLDocument *doc,
	XMLElement *parent){

	XMLElement* elem = doc->NewElement ("IEDName");
	parent->LinkEndChild (elem);

	if (strcmp (scl_gcb_iedname->apRef, empty_string))
		elem->SetAttribute ("apRef", scl_gcb_iedname->apRef);
	if (strcmp (scl_gcb_iedname->ldInst, empty_string))
		elem->SetAttribute ("ldInst", scl_gcb_iedname->ldInst);
	if (strcmp (scl_gcb_iedname->prefix, empty_string))
		elem->SetAttribute ("prefix", scl_gcb_iedname->prefix);
	if (strcmp (scl_gcb_iedname->lnClass, empty_string))
		elem->SetAttribute ("lnClass", scl_gcb_iedname->lnClass);
	if (strcmp (scl_gcb_iedname->lnInst, empty_string))
		elem->SetAttribute ("lnInst", scl_gcb_iedname->lnInst);

	elem->SetText (scl_gcb_iedname->iedName);
}

//ST_VOID LinkSettingControl (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}
//ST_VOID LinkTrgOps (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}
//ST_VOID LinkOptFlds (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}
//ST_VOID LinkRptEnabled (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}

ST_VOID LinkDOI (SCL_DAI* scl_dai, tinyxml2::XMLDocument *doc, XMLElement *parent)
{
	
	ST_CHAR *temp = (ST_CHAR*)calloc (strlen (scl_dai->flattened) + 1, sizeof (ST_CHAR));
	strcpy (temp, scl_dai->flattened);
	ST_CHAR *ptr_front;
	ST_CHAR *ptr_back;
	ptr_front = strtok_s (temp, "$", &ptr_back);
	XMLElement* elem = parent->FirstChildElement ();
	while (elem)
	{
		if (!strcmp (elem->Name (), "DOI"))
			if (!strcmp (elem->FindAttribute ("name")->Value (), ptr_front))
				break;
		elem = elem->NextSiblingElement ();
	}
	if (elem == NULL)
	{
		elem = doc->NewElement ("DOI");
		elem->SetAttribute ("name", ptr_front);
		parent->LinkEndChild (elem);
	}
	LinkSDI (scl_dai, doc, elem,ptr_back);
}

ST_VOID LinkSDI (SCL_DAI* scl_dai, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR *str)
{
	ST_CHAR *ptr_front;
	ST_CHAR *ptr_back;
	ptr_front = strtok_s (str, "$", &ptr_back);
	XMLElement* elem;
	if (strcmp (ptr_back, empty_string) != 0)
	{
		elem = parent->FirstChildElement ();
		while (elem)
		{
			if (!strcmp (elem->Name (), "SDI"))
				if (!strcmp (elem->FindAttribute ("name")->Value (), ptr_front))
					break;
			elem = elem->NextSiblingElement ();
		}
		if (elem == NULL)
		{
			elem = doc->NewElement ("SDI");
			elem->SetAttribute ("name", ptr_front);
			parent->LinkEndChild (elem);
		}
		LinkSDI (scl_dai, doc, elem, ptr_back);
	}
	else
		LinkDAI (scl_dai, doc, parent, ptr_front);
}

ST_VOID LinkDAI (SCL_DAI* scl_dai, tinyxml2::XMLDocument *doc, XMLElement *parent, ST_CHAR *str)
{
	XMLElement* elem = doc->NewElement ("DAI");
	elem->SetAttribute ("name", str);
	if (strcmp (scl_dai->sAddr, empty_string) != 0)
		elem->SetAttribute ("sAddr", scl_dai->sAddr);
	parent->LinkEndChild (elem);
}

//ST_VOID LinkDAI_Val (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}

ST_VOID LinkDataTypeTemplates (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_LNTYPE *scl_lntype;
	SCL_DOTYPE *scl_dotype;
	SCL_DATYPE *scl_datype;
	SCL_ENUMTYPE *scl_enumtype;

	XMLElement* elem = doc->NewElement ("DataTypeTemplates");
	parent->LinkEndChild (elem);

	for (scl_lntype = (SCL_LNTYPE *)list_find_last ((DBL_LNK *)scl_info->lnTypeHead);
		scl_lntype != NULL;
		scl_lntype = (SCL_LNTYPE *)list_find_prev ((DBL_LNK *)scl_info->lnTypeHead, (DBL_LNK *)scl_lntype))
		LinkLNodeType (scl_lntype, doc, elem);

	for (scl_dotype = (SCL_DOTYPE *)list_find_last ((DBL_LNK *)scl_info->doTypeHead);
		scl_dotype != NULL;
		scl_dotype = (SCL_DOTYPE *)list_find_prev ((DBL_LNK *)scl_info->doTypeHead, (DBL_LNK *)scl_dotype))
		LinkDOType (scl_dotype, doc, elem);

	for (scl_datype = (SCL_DATYPE *)list_find_last ((DBL_LNK *)scl_info->daTypeHead);
		scl_datype != NULL;
		scl_datype = (SCL_DATYPE *)list_find_prev ((DBL_LNK *)scl_info->daTypeHead, (DBL_LNK *)scl_datype))
		LinkDAType (scl_datype, doc, elem);

	for (scl_enumtype = (SCL_ENUMTYPE *)list_find_last ((DBL_LNK *)scl_info->enumTypeHead);
		scl_enumtype != NULL;
		scl_enumtype = (SCL_ENUMTYPE *)list_find_prev ((DBL_LNK *)scl_info->enumTypeHead, (DBL_LNK *)scl_enumtype))
		LinkEnumType (scl_enumtype, doc, elem);
}

ST_VOID LinkLNodeType (SCL_LNTYPE *scl_lntype, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_DO *scl_do;

	XMLElement* elem = doc->NewElement ("LNodeType");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("id", scl_lntype->id);
	elem->SetAttribute ("lnClass", scl_lntype->lnClass);

	for (scl_do = (SCL_DO *)list_find_last ((DBL_LNK *)scl_lntype->doHead);
		scl_do != NULL;
		scl_do = (SCL_DO *)list_find_prev ((DBL_LNK *)scl_lntype->doHead, (DBL_LNK *)scl_do))
		LinkDO (scl_do,doc,elem);
}

ST_VOID LinkDO (SCL_DO *scl_do, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("DO");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("name", scl_do->name);
	elem->SetAttribute ("type", scl_do->type);
}

ST_VOID LinkDOType (SCL_DOTYPE *scl_dotype, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_DA *scl_da;

	XMLElement* elem = doc->NewElement ("DOType");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("id", scl_dotype->id);
	elem->SetAttribute ("cdc", scl_dotype->cdc);

	for (scl_da = (SCL_DA *)list_find_last ((DBL_LNK *)scl_dotype->daHead);
		scl_da != NULL;
		scl_da = (SCL_DA *)list_find_prev ((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da)){
		if (scl_da->objtype == SCL_OBJTYPE_DA)
			LinkDA (scl_da, doc, elem);
		else
			LinkSDO (scl_da, doc, elem);
	}
}
ST_VOID LinkDA (SCL_DA *scl_da, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("DA");
	parent->LinkEndChild (elem);

	if (strcmp (scl_da->desc, empty_string))
		elem->SetAttribute ("desc", scl_da->desc);
	if (strcmp (scl_da->sAddr, empty_string))
		elem->SetAttribute ("sAddr", scl_da->sAddr);
	if (strcmp (scl_da->valKind, "Set"))
		elem->SetAttribute ("valKind", scl_da->valKind);
	if (strcmp (scl_da->type, empty_string))
		elem->SetAttribute ("type", scl_da->type);
	if (scl_da->count != 0)
		elem->SetAttribute ("count", scl_da->count_text);
	if (scl_da->dchg != 0)
		elem->SetAttribute ("dchg", "true");
	if (scl_da->qchg != 0)
		elem->SetAttribute ("qchg", "true");
	if (scl_da->dupd != 0)
		elem->SetAttribute ("dupd", "true");
	elem->SetAttribute ("name", scl_da->name);
	elem->SetAttribute ("bType", scl_da->bType);
	elem->SetAttribute ("fc", scl_da->fc);
	
	if (scl_da->Val != NULL)
		LinkDA_Val (scl_da, doc, elem);
}

ST_VOID LinkSDO (SCL_DA *scl_da, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("SDO");
	parent->LinkEndChild (elem);

	if (strcmp (scl_da->desc, empty_string))
		elem->SetAttribute ("desc", scl_da->desc);
	if (scl_da->count != 0)
		elem->SetAttribute ("count", scl_da->count_text);
	elem->SetAttribute ("name", scl_da->name);
	elem->SetAttribute ("type", scl_da->type);
}

ST_VOID LinkDA_Val (SCL_DA *scl_da, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("Val");
	parent->LinkEndChild (elem);

	elem->SetText (scl_da->Val);
}

ST_VOID LinkDAType (SCL_DATYPE *scl_datype, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_BDA *scl_bda;

	XMLElement* elem = doc->NewElement ("DAType");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("id", scl_datype->id);

	for (scl_bda = (SCL_BDA *)list_find_last ((DBL_LNK *)scl_datype->bdaHead);
		scl_bda != NULL;
		scl_bda = (SCL_BDA *)list_find_prev ((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
		LinkBDA (scl_bda, doc, elem);
}

ST_VOID LinkBDA (SCL_BDA *scl_bda, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("BDA");
	parent->LinkEndChild (elem);
	
	if (strcmp (scl_bda->desc, empty_string))
		elem->SetAttribute ("desc", scl_bda->desc);
	if (strcmp (scl_bda->sAddr, empty_string))
		elem->SetAttribute ("sAddr", scl_bda->sAddr);
	if (strcmp (scl_bda->valKind, "Set"))
		elem->SetAttribute ("valKind", scl_bda->desc);
	if (strcmp (scl_bda->type, empty_string))
		elem->SetAttribute ("type", scl_bda->type);
	if (scl_bda->count != 0)
		elem->SetAttribute ("count", scl_bda->count);
	elem->SetAttribute ("name", scl_bda->name);
	elem->SetAttribute ("bType", scl_bda->bType);

	if (scl_bda->Val != NULL)
		LinkBDA_Val (scl_bda, doc, elem);
}

ST_VOID LinkBDA_Val (SCL_BDA *scl_bda, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("Val");
	parent->LinkEndChild (elem);

	elem->SetText (scl_bda->Val);
}

ST_VOID LinkEnumType (SCL_ENUMTYPE *scl_enumtype, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_ENUMVAL *scl_enumval;

	XMLElement* elem = doc->NewElement ("EnumType");
	parent->LinkEndChild (elem);

	elem->SetAttribute ("id", scl_enumtype->id);

	for (scl_enumval = (SCL_ENUMVAL *)list_find_last ((DBL_LNK *)scl_enumtype->enumvalHead);
		scl_enumval != NULL;
		scl_enumval = (SCL_ENUMVAL *)list_find_prev ((DBL_LNK *)scl_enumtype->enumvalHead, (DBL_LNK *)scl_enumval))
		LinkEnumVal (scl_enumval, doc, elem);
}
ST_VOID LinkEnumVal (SCL_ENUMVAL *scl_enumval, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("EnumVal");
	parent->LinkEndChild (elem);

	elem->SetText (scl_enumval->EnumVal);
	elem->SetAttribute ("ord", scl_enumval->ord);
}

ST_VOID LinkInputs (SCL_LN *scl_ln, tinyxml2::XMLDocument *doc, XMLElement *parent){
	SCL_EXTREF *scl_extref;
	
	XMLElement* elem = doc->NewElement ("Inputs");
	parent->LinkEndChild (elem);

	for (scl_extref = (SCL_EXTREF *)list_find_last ((DBL_LNK *)scl_ln->extrefHead);
		scl_extref != NULL;
		scl_extref = (SCL_EXTREF *)list_find_prev ((DBL_LNK *)scl_ln->extrefHead, (DBL_LNK *)scl_extref))
		LinkExtRef (scl_extref, doc, elem);
}
ST_VOID LinkExtRef (SCL_EXTREF *scl_extref, tinyxml2::XMLDocument *doc, XMLElement *parent){
	XMLElement* elem = doc->NewElement ("ExtRef");
	parent->LinkEndChild (elem);

	if (strcmp (scl_extref->desc, empty_string))
		elem->SetAttribute ("desc", scl_extref->desc);
	if (strcmp (scl_extref->intAddr, empty_string))
		elem->SetAttribute ("intAddr", scl_extref->intAddr);
	if (strcmp (scl_extref->iedName, empty_string))
		elem->SetAttribute ("iedName", scl_extref->iedName);
	if (strcmp (scl_extref->ldInst, empty_string))
		elem->SetAttribute ("ldInst", scl_extref->ldInst);
	if (strcmp (scl_extref->prefix, empty_string))
		elem->SetAttribute ("prefix", scl_extref->prefix);
	if (strcmp (scl_extref->lnClass, empty_string))
		elem->SetAttribute ("lnClass", scl_extref->lnClass);
	if (strcmp (scl_extref->lnInst, empty_string))
		elem->SetAttribute ("lnInst", scl_extref->lnInst);
	if (strcmp (scl_extref->doName, empty_string))
		elem->SetAttribute ("doName", scl_extref->doName);
	if (strcmp (scl_extref->daName, empty_string))
		elem->SetAttribute ("daName", scl_extref->daName);
	if (strcmp (scl_extref->serviceType, empty_string))
		elem->SetAttribute ("serviceType", scl_extref->serviceType);
	if (strcmp (scl_extref->srcLDInst, empty_string))
		elem->SetAttribute ("srcLDInst", scl_extref->srcLDInst);
	if (strcmp (scl_extref->srcPrefix, empty_string))
		elem->SetAttribute ("srcPrefix", scl_extref->srcPrefix);
	if (strcmp (scl_extref->srcLNClass, empty_string))
		elem->SetAttribute ("srcLNClass", scl_extref->srcLNClass);
	if (strcmp (scl_extref->srcLNInst, empty_string))
		elem->SetAttribute ("srcLNInst", scl_extref->srcLNInst);
	if (strcmp (scl_extref->srcCBName, empty_string))
		elem->SetAttribute ("srcCBName", scl_extref->srcCBName);
}
//ST_VOID LinkGSE_MinTime (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}
//ST_VOID LinkGSE_MaxTime (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}
//ST_VOID LinkClientLN_SFun (SCL_INFO *scl_info, tinyxml2::XMLDocument *doc, XMLElement *parent)
//{
//	XMLElement* elem = doc->NewElement (name);
//	parent->LinkEndChild (elem);
//}



ST_VOID ConvertHex (ST_CHAR *astr, ST_UCHAR *hstr)
{
	ST_INT j;
	ST_INT hex_index = 0;
	ST_UCHAR ch;
	ST_UCHAR hex;

	for (j = 0; j < 6; j++){
		if (j != 0)
			astr[hex_index++] = '-';  /* dash between bytes, but not before first*/

		ch = *hstr++;                       /* get next character           */
		hex = (ch >> 4) & (ST_UCHAR)0x0f;/* write HEX chars for the byte   */
		hex = cvt_nibble (hex);
		astr[hex_index++] = hex;
		hex = ch & (ST_UCHAR)0x0f;
		hex = cvt_nibble (hex);
		astr[hex_index++] = hex;
	}
	astr[hex_index] = '\0';       /* NULL terminate it.           */
}
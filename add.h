#pragma once
#include "mmslite.h"
#include "ngn.h"
#include "find.h"
#include "copy.h"
#include "add_scl.h"
#include "remove.h"



ST_RET AddSubscription (CONFIG_CTRL *config_ctrl);

ST_RET AddConnectedAP (CONFIG_CTRL *config_ctrl);

ST_RET AddIED (CONFIG_CTRL *config_ctrl);

ST_RET AddDataTypeTemplates (CONFIG_CTRL *config_ctrl);

ST_RET AddProxyLDevice (CONFIG_CTRL *config_ctrl);

ST_RET AddExtRef (CONFIG_CTRL *config_ctrl);

ST_RET AddDAI (CONFIG_CTRL *config_ctrl);

ST_RET AddIEDName (CONFIG_CTRL *config_ctrl);

ST_VOID convertDollarToPoint (ST_CHAR* flattened, ST_CHAR *result);


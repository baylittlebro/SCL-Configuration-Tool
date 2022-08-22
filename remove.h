#pragma once
#include "mmslite.h"
#include "ngn.h"
#include "find.h"

ST_VOID RemoveConnectedAP (SCL_CAP **capHead, SCL_CAP *scl_cap);
ST_VOID RemoveIED (SCL_SERVER **serverHead, SCL_SERVER *scl_server);
ST_VOID RemoveExtRef (SCL_EXTREF **extrefHead, SCL_EXTREF *scl_extref);
ST_VOID RemoveLD (SCL_LD **ldHead, SCL_LD *scl_ld);
ST_VOID DeleteSubscription (CONFIG_CTRL *config_ctrl);
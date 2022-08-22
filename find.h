#pragma once
#include "mmslite.h"

SCL_SUBNET *find_scl_subnet (
	SCL_INFO *scl_info,
	ST_CHAR *name);

SCL_CAP *find_scl_cap (
	SCL_SUBNET *scl_subnet,
	ST_CHAR *iedName);

SCL_SERVER *find_scl_server (
	SCL_INFO *scl_info,
	ST_CHAR *iedName);

SCL_LD *find_scl_ld (
	SCL_SERVER *scl_server,
	ST_CHAR *inst);

SCL_LN *find_scl_ln (
	SCL_LD *scl_ld,
	ST_CHAR *prefix,
	ST_CHAR *lnClass,
	ST_CHAR *inst);

SCL_GCB *find_scl_gcb (
	SCL_LN *scl_ln,
	ST_CHAR *name);

SCL_DATASET *find_scl_dataset (
	SCL_LN *scl_ln,
	ST_CHAR *name);

SCL_EXTREF *find_scl_extref (
	SCL_LN *scl_ln,
	ST_CHAR *iedName,
	ST_CHAR *ldInst,
	ST_CHAR *lnClass,
	ST_CHAR *lnInst,
	ST_CHAR *doName,
	ST_CHAR *daName);

SCL_DAI *find_scl_dai (
	SCL_LN *scl_ln,
	ST_CHAR *flattened);

SCL_GCB_IEDNAME* find_scl_gcb_iedName (
	SCL_GCB *scl_gcb,
	ST_CHAR *iedName);
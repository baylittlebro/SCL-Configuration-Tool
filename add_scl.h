#pragma once
#include "mmslite.h"

SCL_CAP* add_scl_cap (SCL_SUBNET *scl__subnet);
SCL_GSE* add_scl_gse (SCL_CAP *scl__cap);
SCL_SERVER* add_scl_server (SCL_INFO *scl__info);
SCL_LD* add_scl_ld (SCL_SERVER *scl_server);
SCL_LN* add_scl_ln (SCL_LD *scl_ld);
SCL_DATASET* add_scl_dataset (SCL_LN *scl_ln);
SCL_DAI* add_scl_dai (SCL_LN *scl_ln);
SCL_FCDA* add_scl_fcda (SCL_DATASET *scl_dataset);
SCL_GCB* add_scl_gcb (SCL_LN *scl_ln);
SCL_LNTYPE* add_scl_lntype (SCL_INFO *scl_info);
SCL_DO* add_scl_do (SCL_LNTYPE *scl_lntype);
SCL_DOTYPE* add_scl_dotype (SCL_INFO *scl_info);
SCL_DA* add_scl_da (SCL_DOTYPE *scl_dotype);
SCL_DATYPE* add_scl_datype (SCL_INFO *scl_info);
SCL_BDA* add_scl_bda (SCL_DATYPE *scl_datype);
SCL_ENUMTYPE* add_scl_enumtype (SCL_INFO *scl_info);
SCL_ENUMVAL* add_scl_enumval (SCL_ENUMTYPE *scl_enumtype);
SCL_EXTREF* add_scl_extref (SCL_LN *scl_ln);
SCL_GCB_IEDNAME* add_scl_gcb_iedName (SCL_GCB *scl_gcb);
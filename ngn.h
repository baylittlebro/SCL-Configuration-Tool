#pragma once
#include "mmslite.h"
#include "tinyxml2.h"
#include <msclr/marshal.h>
#include "find.h"
using namespace msclr::interop;

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif

typedef struct config_ctrl{
	SCL_INFO *scl_info_aggregator;
	SCL_INFO *scl_info_publisher;
	ST_CHAR iedNameAggregator[MAX_IDENT_LEN + 1];
	ST_CHAR iedNamePublisher[MAX_IDENT_LEN + 1];
	ST_CHAR subNetworkNameAggregator[MAX_IDENT_LEN + 1];
	ST_CHAR subNetworkNamePublisher[MAX_IDENT_LEN + 1];
}CONFIG_CTRL;

ST_RET GetSclInfo (ST_CHAR *fileName, SCL_INFO *scl_info);

void CreateTreeView (SCL_INFO *scl_info, System::Windows::Forms::TreeView^ treeView, System::String^ IEDName);

ST_RET InitConfigCtrl (
	CONFIG_CTRL *config_ctrl,
	SCL_INFO* agg,
	SCL_INFO* pub,
	System::String^ iedNameAggregator,
	System::String^ iedNamePublisher,
	System::String^ subNetworkNameAggregator,
	System::String^ subNetworkNamePublisher
);
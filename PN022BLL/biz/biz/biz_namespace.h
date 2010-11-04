/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	biz_namespace.h
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Namespaces for C++
*/

#pragma once

#define THE_PRODUCT Scor
#define ATCOR_BIZ   AtCor::THE_PRODUCT::BusinessLogic

#define START_ATCOR_BIZ namespace AtCor {                 \
                                namespace THE_PRODUCT {       \
                                    namespace BusinessLogic {
#define END_ATCOR_BIZ   }}}


// Use following pair to include C++ code in the namespace
#define START_BIZ_NAMESPACE START_ATCOR_BIZ
#define END_BIZ_NAMESPACE   END_ATCOR_BIZ

// Use following for "using namespace <...>;" in C++
#define BIZ_NAMESPACE ATCOR_BIZ

// Helper to use other layer's namespace
#define DAL_NAMESPACE AtCor::THE_PRODUCT::DataAccess
#define CRX_CONFIG_NAMESPACE AtCor::THE_PRODUCT::CrossCutting::Configuration
#define CRX_MSG_NAMESPACE AtCor::THE_PRODUCT::CrossCutting::Messaging
#define CRX_LOG_NAMESPACE AtCor::THE_PRODUCT::CrossCutting::Logging


/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_namespace.h
	
	Author       :  Victor Aung

    Description  :	Cross Cutting Namespaces for C++
*/

#pragma once

#define THE_PRODUCT Scor
#define ATCOR_CRX   AtCor::THE_PRODUCT::CrossCutting

#define START_ATCOR_CRX namespace AtCor {                 \
                                namespace THE_PRODUCT {       \
                                    namespace CrossCutting {
#define END_ATCOR_CRX   }}}


// Use following pairs to include C++ code in the namespace
#define START_CRX_CONFIG_NAMESPACE START_ATCOR_CRX \
                                       namespace Configuration {
#define END_CRX_CONFIG_NAMESPACE   }END_ATCOR_CRX

#define START_CRX_EXPORT_NAMESPACE START_ATCOR_CRX \
                                       namespace Export {
#define END_CRX_EXPORT_NAMESPACE   }END_ATCOR_CRX

#define START_CRX_DB_NAMESPACE START_ATCOR_CRX \
                                   namespace Database {
#define END_CRX_DB_NAMESPACE   }END_ATCOR_CRX

#define START_CRX_MSG_NAMESPACE START_ATCOR_CRX \
                                    namespace Messaging {
#define END_CRX_MSG_NAMESPACE   }END_ATCOR_CRX

// Use following for "using namespace <...>;" in C++
#define CRX_CONFIG_NAMESPACE ATCOR_CRX::Configuration
#define CRX_EXPORT_NAMESPACE ATCOR_CRX::Export
#define CRX_DB_NAMESPACE     ATCOR_CRX::Database
#define CRX_MSG_NAMESPACE    ATCOR_CRX::Messaging


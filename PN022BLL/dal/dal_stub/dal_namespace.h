/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_namespace.h
	
	Author       :  Victor Aung

    Description  :	Data Access Layer Namespaces for C++
*/

#pragma once

#define THE_PRODUCT Scor
#define ATCOR_DAL   AtCor::THE_PRODUCT::DataAccess

#define START_ATCOR_DAL namespace AtCor {                 \
                                namespace THE_PRODUCT {       \
                                    namespace DataAccess {
#define END_ATCOR_DAL   }}}

// Use following pair to include C++ code in the namespace
#define START_DAL_NAMESPACE START_ATCOR_DAL
#define END_DAL_NAMESPACE   END_ATCOR_DAL

// Use following for "using namespace <...>;" in C++
#define DAL_NAMESPACE ATCOR_DAL


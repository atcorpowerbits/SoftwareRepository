/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxCrossCutting.h
        
     Author       :		 Smarajit Mishra
 
     Description  :      Declaration for namespaces
*/
#pragma once

using namespace System;

/**
 * @namespace	AtCor
 * @brief		Main namespace for AtCor software.
 * 
 */

namespace AtCor
{ 
	/**
	 * @namespace	AtCor::Scor
	 * @brief		Main namespace for SphygmoCor product.
	 * 
	 */
	namespace Scor
	{ 
		/**
		 * @namespace	AtCor::Scor::CrossCutting
		 * @brief		Namespace for Cross Cutting Components.
		 * 
		 */
		namespace CrossCutting
		{
			/**
			* @class CrxException
			* @brief Exception class for CrxConfiguration namespace.
			*/
			public ref class CrxException:Exception
			{
			private:
				int			_errCode;
				String^		_errMsg;
				Exception^	_eObj;
			public: 
				/**
				* Default constructor, Initializes error code to Zero, which is a Unknown System Error.
				*/
				CrxException(): _errCode(0), _errMsg(""), _eObj(nullptr) { }
				
				/**
				* Overloaded constructor
				* @param[in]	exError	The error code to intitialize this constructor with.
				*/
				CrxException(int exError): _errCode(exError), _errMsg(""), _eObj(nullptr) { }

				/**
				* Overloaded constructor for Exception object
				* @param[in]	errExp	The Unknown (System) Exception object to intitialize this constructor with.
				*/
				CrxException(Exception^ errExp): _errCode(0), _errMsg(errExp->Message), _eObj(errExp) { }

				/**
				* Overloaded constructor for String
				* @param[in]	errExpStr	The String to intitialize this constructor with.
				*/
				CrxException(String^ errExpStr): _errCode(0), _errMsg(errExpStr), _eObj(nullptr) { }

				/**
				* Overloaded constructor for String
				* @param[in]	exError	The error code to intitialize this constructor with.
				* @param[in]	errExpStr	The String to intitialize this constructor with.
				* @param[in]	errExp	The Unknown (System) Exception object to intitialize this constructor with.
				*/
				CrxException(int exError, String^ errExpStr, Exception^ errExp): _errCode(exError), _errMsg(errExpStr), _eObj(errExp) { }
				
				/**
				* Error code property of the exception
				*/ 
				property int ErrorCode
				{
					int get()
					{
						return _errCode;
					}

					void set(int exError)
					{
						_errCode = exError;
					}
				}
				/**
				* Error code String property of the exception
				*/ 
				property String^ ErrorString
				{
					String^ get()
					{
						return _errMsg;
					}

					void set(String^ exError)
					{
						_errMsg = exError;
					}
				}

				/**
				* Exception Object property of the exception
				*/ 
				property Exception^ ExceptionObject
				{
					Exception^ get()
					{
						return _eObj;
					}
				}

			};

		}
	}
}
// Subtracter.cpp : Implementation of CSubtracter

#include "stdafx.h"
#include "Math.h"
#include "Subtracter.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "regexpr2.h"

using namespace std;
using namespace regex;

// CSubtracter

//*******************************************************************
//	Subtract
//
//	PURPOSE:
//		Implements Subtract method of the ISubtracter interface.
//		Returns residual of first two arguments.
//
//	PARAMETERS:
//		lMinuend
//			[in] - first addend.
//		lSubtrahend
//			[in] - second addend.
//		plResidual
//			[in] - pointer to the residual.
//
//	RETURN VALUE:
//		S_OK - if the function succeeds.
//		E_INVALIDARG - if NULL is passed as a plResidual.
//********************************************************************
STDMETHODIMP CSubtracter::Subtract(long lMinuend, long lSubtrahend, long* plResidual)
{
	// Check pointer.
	if (plResidual == NULL)
		return E_INVALIDARG;

	string eqn, s, header, sParenExp, sParenthesized;
	rpattern step1, step2, step3, step4, r5, r6;
	string single;
	subst_results sresults;
	match_results match_res;
	match_results::backref_type bres;
	rpattern basePat, key, replaceKey;
	rpattern r1, r2;

	key.init("(?<=[R])[0-9]+");
	r1.init("#", GLOBAL);
	r1.substitute(eqn, sresults, 0);	// remove all the # values from the result string


	// Do sabtraction.
	*plResidual = lMinuend - lSubtrahend;

	return S_OK;
}

STDMETHODIMP CSubtracter::ExcelExecute(IDispatch *pExcel, BSTR expr, VARIANT *rslt)
{
	HRESULT ret;
	VARIANT result = { 0 };
	VARIANT arg = { 0 };
	DISPPARAMS  params = { 0 };

	arg.vt = VT_BSTR;
	arg.bstrVal = expr;

	params.cArgs = 1;
	params.rgvarg = &arg;

	//ret = pExcel->Invoke(1, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, &params, &result, NULL, NULL);
	ret = pExcel->Invoke(1, IID_NULL, 1033, DISPATCH_METHOD, &params, &result, NULL, NULL);
	if (ret == S_OK)
		*rslt = result;
	return ret;
}


#include "pch.h"
#include "jBase.h"

ll J::systemtime2ms_sameDay(const SYSTEMTIME& st)
{
	return (st.wHour * 3600 + st.wMinute * 60 + st.wSecond) * 1000 + st.wMilliseconds;
}

void J::showLine(CDC* pDC, const CPoint leftTop, const CString& content)
{
	//pDC->TextOutW(leftTop.x,)
}

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

std::shared_ptr<vector<vector<CRect>>> J::avgCRect(const CRect& area, size_t rowCount, size_t colCount)
{
	std::shared_ptr<vector<vector<CRect>>> ret(new vector<vector<CRect>>
		(rowCount, vector<CRect>(colCount)));
	size_t x = area.left, y = area.top;
	double increX = double(area.Width()) / colCount;
	double increY = double(area.Height()) / rowCount;
	for (int i = 0; i < rowCount; ++i) {
		double cx = x;
		for (int j = 0; j < colCount; ++j)
		{
			CRect& cur =(* ret.get())[i][j];
			cur.left = cx;
			cur.top = y;
			cur.right = cx += increX;
			cur.bottom = y + increY;
		}
		y += increY;
	}
	return ret;
}

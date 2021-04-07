#pragma once


// DlgDynamicInputNeeds 对话框

class DlgDynamicInputNeeds : public CDialogEx
{
	DECLARE_DYNAMIC(DlgDynamicInputNeeds)

public:

	DlgDynamicInputNeeds(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgDynamicInputNeeds();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif
	/// <summary>
	/// 字符串数组初始化控件池，而非模板参数初始化
	/// </summary>
	class TreeWidgetPool {
	public:
		class Widget {

		};
	};
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};

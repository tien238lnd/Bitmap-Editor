
// BitmapEditorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Bitmap.h"
#include "afxcmn.h"
#include "afxcolorbutton.h"


// CBitmapEditor2Dlg dialog
class CBitmapEditor2Dlg : public CDialogEx
{
// Construction
public:
	CBitmapEditor2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BitmapEditor_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CStatic picture_control;
	CEdit topleft_x;
	CEdit topleft_y;
	CEdit botright_x;
	CEdit botright_y;
	CEdit resize_h;
	CEdit resize_w;

	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedUndo();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedSaveas();
	afx_msg void OnBnClickedRedo();
	afx_msg void OnBnClickedCropOk();
	afx_msg void OnBnClickedResizeOk();
	afx_msg void OnBnClickedGray();
	afx_msg void OnBnClickedInvert();
	afx_msg void OnBnClickedRotate();
	afx_msg void OnBnClickedFlip1();
	afx_msg void OnBnClickedFlip2();
	
	vector<Bitmap> BMP_vers;
	vector<CString> files_name;
	int current_ver;
	string fname(CString file_name);
	void update_image(CString file_name);
	double val(const CEdit &input_box);
	void update();
	void update_res(int version);

	CSliderCtrl sat_slider;
	vector<int> sat_slider_pos;
	afx_msg void OnReleasedcaptureSatSlider(NMHDR *pNMHDR, LRESULT *pResult);
	
	CSliderCtrl bright_slider;
	vector<int> bright_slider_pos;
	afx_msg void OnReleasedcaptureBrightSlider(NMHDR *pNMHDR, LRESULT *pResult);

	CSliderCtrl blur_slider;
	vector<int> blur_slider_pos;
	afx_msg void OnReleasedcaptureBlurSlider(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnClose();
	CMFCColorButton colorbutton_val;
	CEdit text_insert;
	CEdit text_size;
	CEdit text_x;
	CEdit text_y;
	afx_msg void OnBnClickedColorOk();
	afx_msg void OnBnClickedHistogram();
	afx_msg void OnBnClickedBinary();
	CStatic resolution;
	CSliderCtrl hue_slider;
	vector<int> hue_slider_pos;
	afx_msg void OnReleasedcaptureHue(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEdge();
	CSliderCtrl contrast_slider;
	vector<int> contrast_slider_pos;
	afx_msg void OnReleasedcaptureContrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedAboutbutton();
};

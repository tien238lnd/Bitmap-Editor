
// BitmapEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BitmapEditor.h"
#include "BitmapEditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBitmapEditor2Dlg dialog



CBitmapEditor2Dlg::CBitmapEditor2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBitmapEditor2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBitmapEditor2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PICTURE_CONTROL, picture_control);
	DDX_Control(pDX, IDC_TOPLEFT_X, topleft_x);
	DDX_Control(pDX, IDC_TOPLEFT_Y, topleft_y);
	DDX_Control(pDX, IDC_BOTRIGHT_X, botright_x);
	DDX_Control(pDX, IDC_BOTRIGHT_Y, botright_y);
	DDX_Control(pDX, IDC_RESIZE_HEIGHT, resize_h);
	DDX_Control(pDX, IDC_RESIZE_WIDTH, resize_w);
	DDX_Control(pDX, IDC_SAT_SLIDER, sat_slider);
	DDX_Control(pDX, IDC_BRIGHT_SLIDER, bright_slider);
	DDX_Control(pDX, IDC_BLUR_SLIDER, blur_slider);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, colorbutton_val);
	DDX_Control(pDX, IDC_TEXT_INSERT, text_insert);
	DDX_Control(pDX, IDC_TEXT_SIZE, text_size);
	DDX_Control(pDX, IDC_TEXT_X, text_x);
	DDX_Control(pDX, IDC_TEXT_Y, text_y);
	DDX_Control(pDX, IDC_RESOLUTION, resolution);
	DDX_Control(pDX, IDC_HUE, hue_slider);
	DDX_Control(pDX, IDC_CONTRAST, contrast_slider);
}

BEGIN_MESSAGE_MAP(CBitmapEditor2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CBitmapEditor2Dlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_UNDO, &CBitmapEditor2Dlg::OnBnClickedUndo)
	ON_BN_CLICKED(IDC_SAVE, &CBitmapEditor2Dlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_SAVEAS, &CBitmapEditor2Dlg::OnBnClickedSaveas)
	ON_BN_CLICKED(IDC_REDO, &CBitmapEditor2Dlg::OnBnClickedRedo)
	ON_BN_CLICKED(IDC_CROP_OK, &CBitmapEditor2Dlg::OnBnClickedCropOk)
	ON_BN_CLICKED(IDC_RESIZE_OK, &CBitmapEditor2Dlg::OnBnClickedResizeOk)
	ON_BN_CLICKED(IDC_GRAY, &CBitmapEditor2Dlg::OnBnClickedGray)
	ON_BN_CLICKED(IDC_INVERT, &CBitmapEditor2Dlg::OnBnClickedInvert)
	ON_BN_CLICKED(IDC_ROTATE, &CBitmapEditor2Dlg::OnBnClickedRotate)
	ON_BN_CLICKED(IDC_FLIP1, &CBitmapEditor2Dlg::OnBnClickedFlip1)
	ON_BN_CLICKED(IDC_FLIP2, &CBitmapEditor2Dlg::OnBnClickedFlip2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SAT_SLIDER, &CBitmapEditor2Dlg::OnReleasedcaptureSatSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_BRIGHT_SLIDER, &CBitmapEditor2Dlg::OnReleasedcaptureBrightSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_BLUR_SLIDER, &CBitmapEditor2Dlg::OnReleasedcaptureBlurSlider)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_COLOR_OK, &CBitmapEditor2Dlg::OnBnClickedColorOk)
	ON_BN_CLICKED(IDC_HISTOGRAM, &CBitmapEditor2Dlg::OnBnClickedHistogram)
	ON_BN_CLICKED(IDC_BINARY, &CBitmapEditor2Dlg::OnBnClickedBinary)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_HUE, &CBitmapEditor2Dlg::OnReleasedcaptureHue)
	ON_BN_CLICKED(IDC_EDGE, &CBitmapEditor2Dlg::OnBnClickedEdge)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_CONTRAST, &CBitmapEditor2Dlg::OnReleasedcaptureContrast)
	ON_BN_CLICKED(IDC_ABOUTBUTTON, &CBitmapEditor2Dlg::OnBnClickedAboutbutton)
END_MESSAGE_MAP()


void CBitmapEditor2Dlg::update_image(CString file_name)
{
	HBITMAP image = (HBITMAP)LoadImage(0, file_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	picture_control.SetBitmap(image);							// có thể set góc dưới phải ở đây
}

string CBitmapEditor2Dlg::fname(CString file_name)
{
	// Convert a TCHAR string to a LPCSTR
	CT2CA pszConvertedAnsiString(file_name);
	// construct a std::string using the LPCSTR input
	string name(pszConvertedAnsiString);
	return name;
}

void CBitmapEditor2Dlg::update_res(int version)
{
	string res = "Resolution: ";
	res = res + to_string(BMP_vers[version].width) + " x " + to_string(BMP_vers[version].height);
	resolution.SetWindowTextW(CString(res.c_str()));
}

void CBitmapEditor2Dlg::update()
{
	// Xóa các file trong folder History_file có phiên bản lớn hơn hiện tại
	for (int i = current_ver + 1; i < files_name.size(); i++)
	{
		char name[20] = "History_file/";
		char num[3];
		strcat(name, _itoa(i, num, 10));
		strcat(name, ".bmp");
		remove(name);
	}

	current_ver++;

	string name1("History_file/");
	char ver_num[3];
	_itoa(current_ver, ver_num, 10);
	name1 = name1 + ver_num + ".bmp";
	
	// lưu phiên bản mới nhất (hiện tại) thành file
	SaveBitmap(name1, BMP_vers[current_ver]);

	files_name.resize(current_ver);
	CString name2(name1.c_str());
	files_name.push_back(name2);

	update_image(files_name[current_ver]);
	update_res(current_ver);

	bright_slider_pos.resize(current_ver);
	bright_slider_pos.push_back(bright_slider.GetPos());

	sat_slider_pos.resize(current_ver);
	sat_slider_pos.push_back(sat_slider.GetPos());

	blur_slider_pos.resize(current_ver);
	blur_slider_pos.push_back(blur_slider.GetPos());

	hue_slider_pos.resize(current_ver);
	hue_slider_pos.push_back(hue_slider.GetPos());

	contrast_slider_pos.resize(current_ver);
	contrast_slider_pos.push_back(contrast_slider.GetPos());
}

double CBitmapEditor2Dlg::val(const CEdit &input_box)
{
	CString str = _T("");
	input_box.GetWindowText(str);
	return _tstof(str);
}

// CBitmapEditor2Dlg message handlers

BOOL CBitmapEditor2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MAXIMIZE);

	// TODO: Add extra initialization here
	sat_slider.SetRange(0, 50);
	sat_slider.SetPos(25);
	sat_slider_pos.push_back(25);

	bright_slider.SetRange(0, 50);
	bright_slider.SetPos(25);
	bright_slider_pos.push_back(25);

	blur_slider.SetRange(0, 20);
	blur_slider.SetPos(0);
	blur_slider_pos.push_back(0);

	hue_slider.SetRange(0, 360);
	hue_slider.SetPos(180);
	hue_slider_pos.push_back(180);

	contrast_slider.SetRange(0, 50);
	contrast_slider.SetPos(25);
	contrast_slider_pos.push_back(25);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBitmapEditor2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBitmapEditor2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBitmapEditor2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBitmapEditor2Dlg::OnBnClickedOpen()			// còn vấn đề mở 2 file trong một lần chạy ct
{
	// hiển thị hộp thoại Open
	CString Filter = _T("Image file (*.bmp)|*.bmp|");
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, Filter, NULL);

	if (dlg.DoModal() == IDOK)
	{
		// lấy tên file được Open
		files_name.resize(1);
		files_name[0] = dlg.GetPathName();
		// in ảnh ra dialog
		update_image(files_name[0]);
		// load file vào biến bitmap
		BMP_vers.resize(1);
		BMP_vers[0] = LoadBitmap(fname(files_name[0]));
		if (BMP_vers[0].height == 0)
		{
			BMP_vers.clear();
			return;
		}
		current_ver = 0;
		update_res(0);
	}
}


void CBitmapEditor2Dlg::OnBnClickedUndo()
{
	if (BMP_vers.empty())
		return;

	if (current_ver > 0)
	{
		current_ver--;
		update_image(files_name[current_ver]);
		bright_slider.SetPos(bright_slider_pos[current_ver]);
		sat_slider.SetPos(sat_slider_pos[current_ver]);
		blur_slider.SetPos(blur_slider_pos[current_ver]);
		hue_slider.SetPos(hue_slider_pos[current_ver]);
		contrast_slider.SetPos(contrast_slider_pos[current_ver]);
		update_res(current_ver);
	}
}

void CBitmapEditor2Dlg::OnBnClickedRedo()
{
	if (BMP_vers.empty())
		return;

	if (current_ver < files_name.size() - 1)
	{
		current_ver++;
		update_image(files_name[current_ver]);
		bright_slider.SetPos(bright_slider_pos[current_ver]);
		sat_slider.SetPos(sat_slider_pos[current_ver]);
		blur_slider.SetPos(blur_slider_pos[current_ver]);
		hue_slider.SetPos(hue_slider_pos[current_ver]);
		contrast_slider.SetPos(contrast_slider_pos[current_ver]);
		update_res(current_ver);
	}	
}

void CBitmapEditor2Dlg::OnBnClickedSave()		//save vào file, chứ BMP_vers[0] thì vẫn ko đổi
{
	if (BMP_vers.empty())
		return;

	SaveBitmap(fname(files_name[0]), BMP_vers[current_ver]);
}

void CBitmapEditor2Dlg::OnBnClickedSaveas()
{
	if (BMP_vers.empty())
		return;

	// hiển thị hộp thoại Open
	CString Filter = _T("Image file (*.bmp)|*.bmp|");
	CFileDialog dlg(FALSE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, Filter, NULL);

	if (dlg.DoModal() == IDOK)
		SaveBitmap(fname(dlg.GetPathName()), BMP_vers[current_ver]);
}

void CBitmapEditor2Dlg::OnBnClickedCropOk()
{
	if (BMP_vers.empty())
		return;

	UpdateData(TRUE);

	// lấy giá trị trong ô saturation value
	int hoanh1 = val(topleft_x);
	int tung1 = val(topleft_y);
	int hoanh2 = val(botright_x);
	int tung2 = val(botright_y);

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(CropIm(BMP_vers[current_ver], tung1, tung2, hoanh1, hoanh2));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedResizeOk()
{
	if (BMP_vers.empty())
		return;

	UpdateData(TRUE);

	int width = val(resize_w);
	int height = val(resize_h);

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(resizeIm(BMP_vers[current_ver], width, height));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedGray()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(BGR2Gray(BMP_vers[current_ver]));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedInvert()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(Invert(BMP_vers[current_ver]));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedRotate()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(Rotate(BMP_vers[current_ver]));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedFlip1()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(Flip(BMP_vers[current_ver]));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedFlip2()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(Flip(BMP_vers[current_ver], 2));

	update();
}

void CBitmapEditor2Dlg::OnReleasedcaptureSatSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (BMP_vers.empty())
	{
		sat_slider.SetPos(25);
		return;
	}

	int new_pos = sat_slider.GetPos();
	int old_pos = sat_slider_pos[current_ver];

	double delta_S = (new_pos - old_pos) / 100.0;
	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(AdjustSaturation(BMP_vers[current_ver], delta_S));

	update();
}

void CBitmapEditor2Dlg::OnReleasedcaptureBrightSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (BMP_vers.empty())
	{
		bright_slider.SetPos(25);
		return;
	}
		
	int new_pos = bright_slider.GetPos();
	int old_pos = bright_slider_pos[current_ver];

	double delta_V = (new_pos - old_pos) / 100.0;
	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(AdjustBrightness(BMP_vers[current_ver], delta_V));

	update();
}

void CBitmapEditor2Dlg::OnReleasedcaptureBlurSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (BMP_vers.empty())
	{
		blur_slider.SetPos(0);
		return;
	}

	int new_pos = blur_slider.GetPos();
	int old_pos = blur_slider_pos[current_ver];
	
	BMP_vers.resize(current_ver + 1);
	if (new_pos > old_pos)
	{
		BMP_vers.push_back(Blur(BMP_vers[current_ver], new_pos - old_pos));
		update();
	}
	else
		blur_slider.SetPos(old_pos);
}

void CBitmapEditor2Dlg::OnReleasedcaptureHue(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (BMP_vers.empty())
	{
		hue_slider.SetPos(180);
		return;
	}

	int new_pos = hue_slider.GetPos();
	int old_pos = hue_slider_pos[current_ver];

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(Hue(BMP_vers[current_ver], new_pos - old_pos));

	update();
}


void CBitmapEditor2Dlg::OnReleasedcaptureContrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (BMP_vers.empty())
	{
		contrast_slider.SetPos(25);
		return;
	}

	int new_pos = contrast_slider.GetPos();
	int old_pos = contrast_slider_pos[current_ver];

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(Contrast(BMP_vers[current_ver], new_pos - old_pos));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedColorOk()
{
	if (BMP_vers.empty())
		return;

	UpdateData(TRUE);

	CString cstr = _T("");
	text_insert.GetWindowText(cstr);
	string text = fname(cstr);
	int size = val(text_size);
	int x = val(text_x);
	int y = val(text_y);
	COLORREF color = colorbutton_val.GetColor();

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(insertText(BMP_vers[current_ver], y, x, text, size, color));
	
	update();
}


void CBitmapEditor2Dlg::OnBnClickedHistogram()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(histogramEqualisation(BMP_vers[current_ver]));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedBinary()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(BGR2Binary(BMP_vers[current_ver]));

	update();
}

void CBitmapEditor2Dlg::OnBnClickedEdge()
{
	if (BMP_vers.empty())
		return;

	BMP_vers.resize(current_ver + 1);
	BMP_vers.push_back(edgeDetect(BMP_vers[current_ver]));

	update();
}


void CBitmapEditor2Dlg::OnClose()
{
	for (int i = 1; i < files_name.size(); i++)
	{
		char name[20] = "History_file/";
		char num[3];
		strcat(name, _itoa(i, num, 10));
		strcat(name, ".bmp");
		remove(name);
	}

	CDialogEx::OnClose();
}


void CBitmapEditor2Dlg::OnBnClickedAboutbutton()
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


// SynapticsToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SynapticsTool.h"
#include "SynapticsToolDlg.h"
#include "afxdialogex.h"
#include "SDK\Include\SynKit.h"
#include <string>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSynapticsToolDlg dialog



CSynapticsToolDlg::CSynapticsToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYNAPTICSTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSynapticsToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSynapticsToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CSynapticsToolDlg message handlers

BOOL CSynapticsToolDlg::OnInitDialog()
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

	// Synaptics API Initialization
	ISynAPI *pAPI = 0;
	HRESULT result = SynCreateAPI(&pAPI);
	if (result)
	{
		printf("Cannot obtain an API object, error: %.8x.\n", result);
		exit(-1);
	}

	// Test some API properties.
	LONG lValue = 0;
	result = pAPI->GetProperty(SP_Version, &lValue);

	TBYTE tBuf[256];
	long lBufLen = sizeof(tBuf);
	result = pAPI->GetStringProperty(SP_VersionString, tBuf, &lBufLen);

	// Update Version Info
	CString API("API Version: "),APIVer;
	APIVer.Format(_T("%.8x"), lValue);
	GetDlgItem(IDC_APIVer)->SetWindowTextA(API+APIVer);
	CString DriVer(tBuf);
	GetDlgItem(IDC_DriverVer)->SetWindowTextA(DriVer);

	// Find a device, preferentially a TouchPad or Styk.
	ISynDevice *pDevice = 0;
	LONG lHandle = -1;
	if ((pAPI->FindDevice(SE_ConnectionAny, SE_DeviceTouchPad, &lHandle) &&
		pAPI->FindDevice(SE_ConnectionAny, SE_DeviceStyk, &lHandle) &&
		pAPI->FindDevice(SE_ConnectionAny, SE_DeviceAny, &lHandle)) ||
		pAPI->CreateDevice(lHandle, &pDevice))
	{
		printf("Unable to find a Synaptics Device.\n");
		exit(-1);
	}

	// Test some device properties.
	result = pDevice->GetProperty(SP_Handle, &lValue);
	result = pDevice->GetProperty(SP_DeviceType, &lValue);
	CString DeviceType;
	switch (lValue)
	{
	case(SE_DeviceUnknown) : DeviceType = "Unknown"; break;
	case(SE_DeviceMouse) : DeviceType = "Relative Mode Mouse";	break;
	case(SE_DeviceTouchPad) : DeviceType = "Synaptics TouchPad"; break;
	case(SE_DeviceWheelMouse) : DeviceType = "Mouse (Scroll Wheel)"; break;
	case(SE_DeviceIBMCompatibleStick) : DeviceType = "IBM Compatible (TrackPoint) Pointing Stick"; break;
	case(SE_DeviceStyk) : DeviceType = "Synaptics TouchStyk"; break;
	case(SE_DeviceFiveButtonWheelMouse) : DeviceType = "Five Button Mouse (Scroll Wheel)"; break;
	case(SE_DevicecPad) : DeviceType = "Synaptics cPad"; break;
	default: DeviceType = "Error"; break;
	}
	GetDlgItem(IDC_DeviceType)->SetWindowTextA("Found Device Type: "+DeviceType);
	result = pDevice->GetProperty(SP_ConnectionType, &lValue);
	CString ConnecttionType;
	switch (lValue)
	{
	case(SE_ConnectionUnknown) : ConnecttionType = "Unknown"; break;
	case(SE_ConnectionCOM) : ConnecttionType = "COM"; break;
	case(SE_ConnectionPS2) : ConnecttionType = "PS2"; break;
	case(SE_ConnectionUSB) : ConnecttionType = "USB"; break;
	case(SE_ConnectionSMB) : ConnecttionType = "SMB"; break;
	case(SE_ConnectionI2C) : ConnecttionType = "I2C"; break;
	case(SE_ConnectionRMIHID) : ConnecttionType = "RMIHID"; break;
	default: ConnecttionType = "Error"; break;
	}
	GetDlgItem(IDC_ConnecttionType)->SetWindowTextA("Connection Type: " + ConnecttionType);

	//AfxMessageBox(_T(text));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSynapticsToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSynapticsToolDlg::OnPaint()
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
HCURSOR CSynapticsToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


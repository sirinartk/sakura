/*!	@file
	@brief �풓��
	
	�^�X�N�g���C�A�C�R���̊Ǘ��C�^�X�N�g���C���j���[�̃A�N�V�����C
	MRU�A�L�[���蓖�āA���ʐݒ�A�ҏW�E�B���h�E�̊Ǘ��Ȃ�

	@author Norio Nakatani
	@date 1998/05/13 �V�K�쐬
	@date 2001/06/03 N.Nakatani grep�P��P�ʂŌ�������������Ƃ��̂��߂ɃR�}���h���C���I�v�V�����̏����ǉ�
*/
/*
	Copyright (C) 1998-2001, Norio Nakatani
	Copyright (C) 2000, jepro, genta
	Copyright (C) 2001, Stonee, jepro, genta, aroka, hor, YAZAKI
	Copyright (C) 2002, MIK, Moca, genta, YAZAKI, towest
	Copyright (C) 2003, MIK, Moca, KEITA, genta, aroka
	Copyright (C) 2004, Moca
	Copyright (C) 2005, genta
	Copyright (C) 2006, ryoji
	Copyright (C) 2007, ryoji
	Copyright (C) 2008, ryoji

	This source code is designed for sakura editor.
	Please contact the copyright holders to use this code for other purpose.
*/

#include "stdafx.h"
#define ID_HOTKEY_TRAYMENU	0x1234

#include <windows.h>
#include "debug/Debug.h"
#include "CControlTray.h"
#include "window/CEditWnd.h"		//Nov. 21, 2000 JEPROtest
#include "dlg/CDlgAbout.h"		//Nov. 21, 2000 JEPROtest
#include "sakura_rc.h"
#include "dlg/CDlgOpenFile.h"
#include "global.h"
#include "debug/CRunningTimer.h"
#include <htmlhelp.h>
#include "CEditApp.h"
#include "util/module.h"
#include "util/shell.h"
#include "util/window.h"
#include "util/string_ex2.h"
#include "env/CShareData_IO.h"
#include "env/CSakuraEnvironment.h"

/////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK CEditAppWndProc( HWND, UINT, WPARAM, LPARAM );


CControlTray*	g_m_pCEditApp;

//Stonee, 2001/03/21
//Stonee, 2001/07/01  ���d�N�����ꂽ�ꍇ�͑O��̃_�C�A���O��O�ʂɏo���悤�ɂ����B
void CControlTray::DoGrep()
{
	//Stonee, 2001/06/30
	//�O��̃_�C�A���O������ΑO�ʂ� (suggested by genta)
	if ( ::IsWindow(m_cDlgGrep.GetHwnd()) ){
		::OpenIcon(m_cDlgGrep.GetHwnd());
		::BringWindowToTop(m_cDlgGrep.GetHwnd());
		return;
	}

	wcscpy( m_cDlgGrep.m_szText, m_pShareData->m_sSearchKeywords.m_aSearchKeys[0] );

	/* Grep�_�C�A���O�̕\�� */
	int nRet = m_cDlgGrep.DoModal( m_hInstance, NULL, _T("") );
	if( !nRet || GetTrayHwnd() == NULL ){
		return;
	}


	/*======= Grep�̎��s =============*/
	/* Grep���ʃE�B���h�E�̕\�� */

	CNativeW		cmWork1;
	CNativeT		cmWork2;
	CNativeT		cmWork3;
	cmWork1.SetString( m_cDlgGrep.m_szText );
	cmWork2.SetString( m_cDlgGrep.m_szFile );
	cmWork3.SetString( m_cDlgGrep.m_szFolder );
	cmWork1.Replace( L"\"", L"\"\"" );
	cmWork2.Replace( _T("\""), _T("\"\"") );
	cmWork3.Replace( _T("\""), _T("\"\"") );

	// -GREPMODE -GKEY="1" -GFILE="*.*;*.c;*.h" -GFOLDER="c:\" -GCODE=0 -GOPT=S
	CCommandLineString cCmdLine;
	cCmdLine.AppendF( _T("-GREPMODE -GKEY=\"%ls\" -GFILE=\"%ts\" -GFOLDER=\"%ts\" -GCODE=%d"),
		cmWork1.GetStringPtr(),
		cmWork2.GetStringPtr(),
		cmWork3.GetStringPtr(),
		m_cDlgGrep.m_nGrepCharSet
	);

	//GOPT�I�v�V����
	TCHAR pOpt[64] = _T("");
	if( m_cDlgGrep.m_bSubFolder					)_tcscat( pOpt, _T("S") );	// �T�u�t�H���_�������������
	if( m_cDlgGrep.m_sSearchOption.bLoHiCase	)_tcscat( pOpt, _T("L") );	// �p�啶���Ɖp����������ʂ���
	if( m_cDlgGrep.m_sSearchOption.bRegularExp	)_tcscat( pOpt, _T("R") );	// ���K�\��
	if( m_cDlgGrep.m_bGrepOutputLine			)_tcscat( pOpt, _T("P") );	// �s���o�͂��邩�Y�����������o�͂��邩
	if( m_cDlgGrep.m_sSearchOption.bWordOnly	)_tcscat( pOpt, _T("W") );	// �P��P�ʂŒT��
	if( 1 == m_cDlgGrep.m_nGrepOutputStyle		)_tcscat( pOpt, _T("1") );	// Grep: �o�͌`��
	if( 2 == m_cDlgGrep.m_nGrepOutputStyle		)_tcscat( pOpt, _T("2") );	// Grep: �o�͌`��
	if( 0 < _tcslen( pOpt ) ){
		cCmdLine.AppendF( _T(" -GOPT=%ts"), pOpt );
	}

	/* �V�K�ҏW�E�B���h�E�̒ǉ� ver 0 */
	SLoadInfo sLoadInfo;
	sLoadInfo.cFilePath = _T("");
	sLoadInfo.eCharCode = CODE_NONE;
	sLoadInfo.bViewMode = false;
	CControlTray::OpenNewEditor( m_hInstance, m_pShareData->m_sHandles.m_hwndTray, sLoadInfo, cCmdLine.c_str());
}


/* �E�B���h�E�v���V�[�W������ */
LRESULT CALLBACK CEditAppWndProc(
	HWND	hwnd,	// handle of window
	UINT	uMsg,	// message identifier
	WPARAM	wParam,	// first message parameter
	LPARAM	lParam 	// second message parameter
)
{
	CControlTray* pSApp;
	switch( uMsg ){
	case WM_CREATE:
		pSApp = ( CControlTray* )g_m_pCEditApp;
		return pSApp->DispatchEvent( hwnd, uMsg, wParam, lParam );
	default:
		// Modified by KEITA for WIN64 2003.9.6
		//RELPRINT_A("dispatch\n");
		pSApp = ( CControlTray* )::GetWindowLongPtr( hwnd, GWLP_USERDATA );
		if( NULL != pSApp ){
			return pSApp->DispatchEvent( hwnd, uMsg, wParam, lParam );
		}
		return ::DefWindowProc( hwnd, uMsg, wParam, lParam );
	}
}




/////////////////////////////////////////////////////////////////////////////
// CControlTray
//	@date 2002.2.17 YAZAKI CShareData�̃C���X�^���X�́ACProcess�ɂЂƂ���̂݁B
CControlTray::CControlTray()
//	Apr. 24, 2001 genta
: m_uCreateTaskBarMsg( ::RegisterWindowMessage( TEXT("TaskbarCreated") ) )
, m_bCreatedTrayIcon( FALSE )	//�g���C�ɃA�C�R���������
, m_hInstance( NULL )
, m_hWnd( NULL )
{
	/* ���L�f�[�^�\���̂̃A�h���X��Ԃ� */
	m_pShareData = CShareData::getInstance()->GetShareData();
	if( m_pShareData->m_sHandles.m_hAccel != NULL ){
		::DestroyAcceleratorTable( m_pShareData->m_sHandles.m_hAccel );
		m_pShareData->m_sHandles.m_hAccel = NULL;
	}
	m_pShareData->m_sHandles.m_hAccel =
		CKeyBind::CreateAccerelator(
			m_pShareData->m_Common.m_sKeyBind.m_nKeyNameArrNum,
			m_pShareData->m_Common.m_sKeyBind.m_pKeyNameArr
		);
	if( NULL == m_pShareData->m_sHandles.m_hAccel ){
		ErrorMessage(
			NULL,
			_T("CControlTray::CControlTray()\n")
			_T("�A�N�Z�����[�^ �e�[�u�����쐬�ł��܂���B\n")
			_T("�V�X�e�����\�[�X���s�����Ă��܂��B")
		);
	}

	m_bUseTrayMenu = false;

	return;
}


CControlTray::~CControlTray()
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CControlTray �����o�֐�




/* �쐬 */
HWND CControlTray::Create( HINSTANCE hInstance )
{
	MY_RUNNINGTIMER( cRunningTimer, "CControlTray::Create" );

	//�������N���X�̃E�B���h�E�����ɑ��݂��Ă�����A���s
	m_hInstance = hInstance;
	HWND hwndWork = ::FindWindow( GSTR_CEDITAPP, GSTR_CEDITAPP );
	if( NULL != hwndWork ){
		return NULL;
	}

	//�E�B���h�E�N���X�o�^
	WNDCLASS	wc;
	{
		wc.style			=	CS_HREDRAW |
								CS_VREDRAW |
								CS_DBLCLKS |
								CS_BYTEALIGNCLIENT |
								CS_BYTEALIGNWINDOW;
		wc.lpfnWndProc		= CEditAppWndProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hInstance		= m_hInstance;
		wc.hIcon			= LoadIcon( NULL, IDI_APPLICATION );
		wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
		wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName		= NULL;
		wc.lpszClassName	= GSTR_CEDITAPP;
		ATOM	atom = RegisterClass( &wc );
		if( 0 == atom ){
			ErrorMessage( NULL, _T("CControlTray::Create()\n�E�B���h�E�N���X��o�^�ł��܂���ł����B") );
		}
	}
	g_m_pCEditApp = this;

	// �E�B���h�E�쐬 (WM_CREATE�ŁAGetHwnd() �� HWND ���i�[�����)
	::CreateWindow(
		GSTR_CEDITAPP,						// pointer to registered class name
		GSTR_CEDITAPP,						// pointer to window name
		WS_OVERLAPPEDWINDOW/*WS_VISIBLE *//*| WS_CHILD *//* | WS_CLIPCHILDREN*/	,	// window style
		CW_USEDEFAULT,						// horizontal position of window
		0,									// vertical position of window
		100,								// window width
		100,								// window height
		NULL,								// handle to parent or owner window
		NULL,								// handle to menu or child-window identifier
		m_hInstance,						// handle to application instance
		NULL								// pointer to window-creation data
	);

	// �őO�ʂɂ���i�g���C����̃|�b�v�A�b�v�E�B���h�E���őO�ʂɂȂ�悤�Ɂj
	::SetWindowPos( GetTrayHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE );
	
	// �^�X�N�g���C�A�C�R���쐬
	m_hIcons.Create( m_hInstance );	//	Oct. 16, 2000 genta
	m_CMenuDrawer.Create( m_hInstance, GetTrayHwnd(), &m_hIcons );
	if( GetTrayHwnd() ){
		CreateTrayIcon( GetTrayHwnd() );
	}

	return GetTrayHwnd();
}

//! �^�X�N�g���C�ɃA�C�R����o�^����
bool CControlTray::CreateTrayIcon( HWND hWnd )
{
	// �^�X�N�g���C�̃A�C�R�������
	if( TRUE == m_pShareData->m_Common.m_sGeneral.m_bUseTaskTray ){	/* �^�X�N�g���C�̃A�C�R�����g�� */
		//	Dec. 02, 2002 genta
		HICON hIcon = GetAppIcon( m_hInstance, ICON_DEFAULT_APP, FN_APP_ICON, true );
//From Here Jan. 12, 2001 JEPRO �g���C�A�C�R���Ƀ|�C���g����ƃo�[�W����no.���\�������悤�ɏC��
//			TrayMessage( GetTrayHwnd(), NIM_ADD, 0,  hIcon, GSTR_APPNAME );
		/* �o�[�W������� */
		//	UR version no.��ݒ� (cf. cDlgAbout.cpp)
		TCHAR	pszTips[64];
		//	2004.05.13 Moca �o�[�W�����ԍ��́A�v���Z�X���ƂɎ擾����
		DWORD dwVersionMS, dwVersionLS;
		GetAppVersionInfo( NULL, VS_VERSION_INFO,
			&dwVersionMS, &dwVersionLS );

		auto_snprintf_s( pszTips, _countof(pszTips), _T("%ts %d.%d.%d.%d"),		//Jul. 06, 2001 jepro UR �͂����t���Ȃ��Ȃ����̂�Y��Ă���
			GSTR_APPNAME,
			HIWORD( dwVersionMS ),
			LOWORD( dwVersionMS ),
			HIWORD( dwVersionLS ),
			LOWORD( dwVersionLS )
		);
		TrayMessage( GetTrayHwnd(), NIM_ADD, 0,  hIcon, pszTips );
//To Here Jan. 12, 2001
		m_bCreatedTrayIcon = TRUE;	/* �g���C�ɃA�C�R��������� */
	}
	return true;
}




/* ���b�Z�[�W���[�v */
void CControlTray::MessageLoop( void )
{
//�����v���Z�X��
	MSG	msg;
	int ret;
	
	//2004.02.17 Moca GetMessage�̃G���[�`�F�b�N
	while ( GetTrayHwnd() != NULL && (ret = ::GetMessage(&msg, NULL, 0, 0 )) ){
		if( ret == -1 ){
			break;
		}
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}
	return;

}




/* �^�X�N�g���C�̃A�C�R���Ɋւ��鏈�� */
BOOL CControlTray::TrayMessage( HWND hDlg, DWORD dwMessage, UINT uID, HICON hIcon, const TCHAR* pszTip )
{
	BOOL			res;
	NOTIFYICONDATA	tnd;
	tnd.cbSize				= sizeof_raw( tnd );
	tnd.hWnd				= hDlg;
	tnd.uID					= uID;
	tnd.uFlags				= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= MYWM_NOTIFYICON;
	tnd.hIcon				= hIcon;
	if( pszTip ){
		lstrcpyn( tnd.szTip, pszTip, _countof( tnd.szTip ) );
	}else{
		tnd.szTip[0] = _T('\0');
	}
	res = Shell_NotifyIcon( dwMessage, &tnd );
	if( hIcon ){
		DestroyIcon( hIcon );
	}
	return res;
}





/* ���b�Z�[�W���� */
//@@@ 2001.12.26 YAZAKI MRU���X�g�́ACMRU�Ɉ˗�����
LRESULT CControlTray::DispatchEvent(
	HWND	hwnd,	// handle of window
	UINT	uMsg,	// message identifier
	WPARAM	wParam,	// first message parameter
	LPARAM	lParam 	// second message parameter
)
{
	int				nId;
	HWND			hwndWork;
	LPHELPINFO		lphi;

	int			nRowNum;
	EditNode*	pEditNodeArr;
	static HWND	hwndHtmlHelp;

	static WORD		wHotKeyMods;
	static WORD		wHotKeyCode;
	LPMEASUREITEMSTRUCT	lpmis;	/* ���ڃT�C�Y��� */
	LPDRAWITEMSTRUCT	lpdis;	/* ���ڕ`���� */
	int					nItemWidth;
	int					nItemHeight;
	static bool			bLDClick = false;	/* ���_�u���N���b�N�������� 03/02/20 ai */

	switch ( uMsg ){
	case WM_MENUCHAR:
		/* ���j���[�A�N�Z�X�L�[�������̏���(WM_MENUCHAR����) */
		return m_CMenuDrawer.OnMenuChar( hwnd, uMsg, wParam, lParam );
	case WM_DRAWITEM:
		lpdis = (DRAWITEMSTRUCT*) lParam;	/* ���ڕ`���� */
		switch( lpdis->CtlType ){
		case ODT_MENU:	/* �I�[�i�[�`�惁�j���[ */
			/* ���j���[�A�C�e���`�� */
			m_CMenuDrawer.DrawItem( lpdis );
			return TRUE;
		}
		return FALSE;
	case WM_MEASUREITEM:
		lpmis = (MEASUREITEMSTRUCT*) lParam;	// item-size information
		switch( lpmis->CtlType ){
		case ODT_MENU:	/* �I�[�i�[�`�惁�j���[ */
			/* ���j���[�A�C�e���̕`��T�C�Y���v�Z */
			nItemWidth = m_CMenuDrawer.MeasureItem( lpmis->itemID, &nItemHeight );
			if( -1 == nItemWidth ){
			}else{
				lpmis->itemWidth = nItemWidth;
				lpmis->itemHeight = nItemHeight;
			}
			return TRUE;
		}
		return FALSE;

	/* �^�X�N�g���C���N���b�N���j���[�ւ̃V���[�g�J�b�g�L�[�o�^ */
	case WM_HOTKEY:
		{
			int		idHotKey = (int) wParam;				// identifier of hot key
			UINT	fuModifiers = (UINT) LOWORD(lParam);	// key-modifier flags
			UINT	uVirtKey = (UINT) HIWORD(lParam);		// virtual-key code
			TCHAR	szClassName[100];
			TCHAR	szText[256];

			hwndWork = ::GetForegroundWindow();
			szClassName[0] = L'\0';
			::GetClassName( hwndWork, szClassName, _countof( szClassName ) - 1 );
			::GetWindowText( hwndWork, szText, _countof( szText ) - 1 );
			if( 0 == _tcscmp( szText, _T("���ʐݒ�") ) ){
				return -1;
			}

			if( ID_HOTKEY_TRAYMENU == idHotKey
			 &&	( wHotKeyMods )  == fuModifiers
			 && wHotKeyCode == uVirtKey
			){
				// Jan. 1, 2003 AROKA
				// �^�X�N�g���C���j���[�̕\���^�C�~���O��LBUTTONDOWN��LBUTTONUP�ɕύX�������Ƃɂ��
				::PostMessageAny( GetTrayHwnd(), MYWM_NOTIFYICON, 0, WM_LBUTTONUP );
			}
		}
		return 0;

	case MYWM_UIPI_CHECK:
		/* �G�f�B�^�|�g���C�Ԃł�UI���������̊m�F���b�Z�[�W */	// 2007.06.07 ryoji
		::SendMessage( (HWND)lParam, MYWM_UIPI_CHECK,  (WPARAM)0, (LPARAM)0 );	// �Ԏ���Ԃ�
		return 0L;

	case MYWM_HTMLHELP:
		{
			TCHAR* pWork = m_pShareData->m_sWorkBuffer.GetWorkBuffer<TCHAR>();

			//szHtmlFile�擾
			TCHAR	szHtmlHelpFile[1024];
			_tcscpy( szHtmlHelpFile, pWork );
			int		nLen = _tcslen( szHtmlHelpFile );

			//	Jul. 6, 2001 genta HtmlHelp�̌Ăяo�����@�ύX
			hwndHtmlHelp = OpenHtmlHelp(
				NULL,
				szHtmlHelpFile,
				HH_DISPLAY_TOPIC,
				(DWORD_PTR)0,
				true
			);

			HH_AKLINK	link;
			link.cbStruct		= sizeof_raw(link);
			link.fReserved		= FALSE;
			link.pszKeywords	= to_tchar(&pWork[nLen+1]);
			link.pszUrl			= NULL;
			link.pszMsgText		= NULL;
			link.pszMsgTitle	= NULL;
			link.pszWindow		= NULL;
			link.fIndexOnFail	= TRUE;

			//	Jul. 6, 2001 genta HtmlHelp�̌Ăяo�����@�ύX
			hwndHtmlHelp = OpenHtmlHelp(
				NULL,
				szHtmlHelpFile,
				HH_KEYWORD_LOOKUP,
				(DWORD_PTR)&link,
				false
			);
		}
		return (LRESULT)hwndHtmlHelp;;


	/* �ҏW�E�B���h�E�I�u�W�F�N�g����̃I�u�W�F�N�g�폜�v�� */
	case MYWM_DELETE_ME:
		// �^�X�N�g���C�̃A�C�R�����풓���Ȃ��A�܂��́A�g���C�ɃA�C�R��������Ă��Ȃ�
		if( !(m_pShareData->m_Common.m_sGeneral.m_bStayTaskTray && m_pShareData->m_Common.m_sGeneral.m_bUseTaskTray) || !m_bCreatedTrayIcon ){
			// ���݊J���Ă���ҏW���̃��X�g
			nRowNum = CAppNodeManager::Instance()->GetOpenedWindowArr( &pEditNodeArr, TRUE );
			if( 0 < nRowNum ){
				delete [] pEditNodeArr;
			}
			// �ҏW�E�B���h�E�̐���0�ɂȂ�����I��
			if( 0 == nRowNum ){
				::SendMessageAny( hwnd, WM_CLOSE, 0, 0 );
			}
		}
		return 0;

	case WM_CREATE:
		m_hWnd = hwnd;
		hwndHtmlHelp = NULL;
		// Modified by KEITA for WIN64 2003.9.6
		::SetWindowLongPtr( GetTrayHwnd(), GWLP_USERDATA, (LONG_PTR)this );

		/* �^�X�N�g���C���N���b�N���j���[�ւ̃V���[�g�J�b�g�L�[�o�^ */
		wHotKeyMods = 0;
		if( HOTKEYF_SHIFT & m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyMods ){
			wHotKeyMods |= MOD_SHIFT;
		}
		if( HOTKEYF_CONTROL & m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyMods ){
			wHotKeyMods |= MOD_CONTROL;
		}
		if( HOTKEYF_ALT & m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyMods ){
			wHotKeyMods |= MOD_ALT;
		}
		wHotKeyCode = m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyCode;
		::RegisterHotKey(
			GetTrayHwnd(),
			ID_HOTKEY_TRAYMENU,
			wHotKeyMods,
			wHotKeyCode
		);

		// 2006.07.09 ryoji �Ō�̕��ŃV���b�g�_�E������A�v���P�[�V�����ɂ���
		BOOL (WINAPI *pfnSetProcessShutdownParameters)( DWORD dwLevel, DWORD dwFlags );
		HINSTANCE hDll;
		hDll = ::GetModuleHandle(_T("KERNEL32"));
		if( NULL != hDll ){
			*(FARPROC*)&pfnSetProcessShutdownParameters = ::GetProcAddress( hDll, "SetProcessShutdownParameters" );
			if( NULL != pfnSetProcessShutdownParameters ){
				pfnSetProcessShutdownParameters( 0x180, 0 );
			}
		}
		return 0L;

//	case WM_QUERYENDSESSION:
	case WM_HELP:
		lphi = (LPHELPINFO) lParam;
		switch( lphi->iContextType ){
		case HELPINFO_MENUITEM:
			CEditApp::Instance()->ShowFuncHelp( hwnd, (EFunctionCode)lphi->iCtrlId );
			break;
		}
		return TRUE;
		case WM_COMMAND:
			OnCommand( HIWORD(wParam), LOWORD(wParam), (HWND) lParam );
			return 0L;

//		case MYWM_SETFILEINFO:
//			return 0L;
		case MYWM_CHANGESETTING:
			::UnregisterHotKey( GetTrayHwnd(), ID_HOTKEY_TRAYMENU );
			/* �^�X�N�g���C���N���b�N���j���[�ւ̃V���[�g�J�b�g�L�[�o�^ */
			wHotKeyMods = 0;
			if( HOTKEYF_SHIFT & m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyMods ){
				wHotKeyMods |= MOD_SHIFT;
			}
			if( HOTKEYF_CONTROL & m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyMods ){
				wHotKeyMods |= MOD_CONTROL;
			}
			if( HOTKEYF_ALT & m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyMods ){
				wHotKeyMods |= MOD_ALT;
			}
			wHotKeyCode = m_pShareData->m_Common.m_sGeneral.m_wTrayMenuHotKeyCode;
			::RegisterHotKey(
				GetTrayHwnd(),
				ID_HOTKEY_TRAYMENU,
				wHotKeyMods,
				wHotKeyCode
			);

//@@		/* ���L�f�[�^�̕ۑ� */
//@@		m_cShareData.SaveShareData();

			/* �A�N�Z�����[�^�e�[�u���̍č쐬 */
			if( m_pShareData->m_sHandles.m_hAccel != NULL ){
				::DestroyAcceleratorTable( m_pShareData->m_sHandles.m_hAccel );
				m_pShareData->m_sHandles.m_hAccel = NULL;
			}
			m_pShareData->m_sHandles.m_hAccel =
				CKeyBind::CreateAccerelator(
					m_pShareData->m_Common.m_sKeyBind.m_nKeyNameArrNum,
					m_pShareData->m_Common.m_sKeyBind.m_pKeyNameArr
				);
			if( NULL == m_pShareData->m_sHandles.m_hAccel ){
				ErrorMessage(
					NULL,
					_T("CControlTray::DispatchEvent()\n")
					_T("�A�N�Z�����[�^ �e�[�u�����쐬�ł��܂���B\n")
					_T("�V�X�e�����\�[�X���s�����Ă��܂��B")
				);
			}

			return 0L;

		case MYWM_NOTIFYICON:
//			MYTRACE_A( "MYWM_NOTIFYICON\n" );
			switch (lParam){
//�L�[���[�h�F�g���C�E�N���b�N���j���[�ݒ�
//	From Here Oct. 12, 2000 JEPRO ���E�Ƃ����ꏈ���ɂȂ��Ă����̂�ʁX�ɏ�������悤�ɕύX
			case WM_RBUTTONUP:	// Dec. 24, 2002 towest UP�ɕύX
				::SetActiveWindow( GetTrayHwnd() );
				::SetForegroundWindow( GetTrayHwnd() );
				/* �|�b�v�A�b�v���j���[(�g���C�E�{�^��) */
				nId = CreatePopUpMenu_R();
				switch( nId ){
				case F_HELP_CONTENTS:
					/* �w���v�ڎ� */
					{
						ShowWinHelpContents( GetTrayHwnd(), CEditApp::Instance()->GetHelpFilePath() );	//	�ڎ���\������
					}
					break;
				case F_HELP_SEARCH:
					/* �w���v�L�[���[�h���� */
					{
						MyWinHelp( GetTrayHwnd(), CEditApp::Instance()->GetHelpFilePath(), HELP_KEY, (ULONG_PTR)_T("") );	// 2006.10.10 ryoji MyWinHelp�ɕύX�ɕύX
					}
					break;
				case F_EXTHELP1:
					/* �O���w���v�P */
					do{
						if( CHelpManager().ExtWinHelpIsSet() ) {	//	���ʐݒ�̂݊m�F
							break;
						}
						else{
							ErrorBeep();
						}
					}while(IDYES == ::MYMESSAGEBOX( 
							NULL, MB_YESNOCANCEL | MB_ICONEXCLAMATION | MB_APPLMODAL | MB_TOPMOST,
							GSTR_APPNAME,
							_T("�O���w���v�P���ݒ肳��Ă��܂���B\n�������ݒ肵�܂���?"))
					);/*do-while*/

					break;
				case F_EXTHTMLHELP:
					/* �O��HTML�w���v */
					{
//						CEditView::Command_EXTHTMLHELP();
					}
					break;
				case F_ABOUT:
					/* �o�[�W������� */
					{
						CDlgAbout cDlgAbout;
						cDlgAbout.DoModal( m_hInstance, GetTrayHwnd() );
					}
					break;
//				case IDM_EXITALL:
				case F_EXITALL:	//Dec. 26, 2000 JEPRO F_�ɕύX
					/* �T�N���G�f�B�^�̑S�I�� */
					CControlTray::TerminateApplication( GetTrayHwnd() );	// 2006.12.25 ryoji �����ǉ�
					break;
				default:
					break;
				}
				return 0L;
//	To Here Oct. 12, 2000

			case WM_LBUTTONDOWN:
				//	Mar. 29, 2003 genta �O�̂��߃t���O�N���A
				bLDClick = false;
				return 0L;
			case WM_LBUTTONUP:	// Dec. 24, 2002 towest UP�ɕύX
//				MYTRACE_A( "WM_LBUTTONDOWN\n" );
				/* 03/02/20 ���_�u���N���b�N��̓��j���[��\�����Ȃ� ai Start */
				if( bLDClick ){
					bLDClick = false;
					return 0L;
				}
				/* 03/02/20 ai End */
				::SetActiveWindow( GetTrayHwnd() );
				::SetForegroundWindow( GetTrayHwnd() );
				/* �|�b�v�A�b�v���j���[(�g���C���{�^��) */
				nId = CreatePopUpMenu_L();
				switch( nId ){
				case F_FILENEW:	/* �V�K�쐬 */
					/* �V�K�ҏW�E�B���h�E�̒ǉ� */
					OnNewEditor();
					break;
				case F_FILEOPEN:	/* �J�� */
					{
						CDlgOpenFile	cDlgOpenFile;

						// MRU���X�g�̃t�@�C���̃��X�g
						CMRU cMRU;
						std::vector<LPCTSTR> vMRU = cMRU.GetPathList();

						// �t�@�C���I�[�v���_�C�A���O�̏�����
						SLoadInfo sLoadInfo;
						sLoadInfo.cFilePath = _T("");
						sLoadInfo.eCharCode = CODE_AUTODETECT;	// �����R�[�h��������
						sLoadInfo.bViewMode = false;
						cDlgOpenFile.Create(
							m_hInstance,
							NULL,
							_T("*.*"),
							vMRU.empty()? NULL: vMRU[0],//@@@ 2001.12.26 YAZAKI m_fiMRUArr�ɂ̓A�N�Z�X���Ȃ�
							vMRU,
							CMRUFolder().GetPathList()	// OPENFOLDER���X�g�̃t�@�C���̃��X�g
						);
						if( !cDlgOpenFile.DoModalOpenDlg( &sLoadInfo ) ){
							break;
						}
						if( NULL == GetTrayHwnd() ){
							break;
						}
						
						// �V���ȕҏW�E�B���h�E���N��
						CControlTray::OpenNewEditor( m_hInstance, GetTrayHwnd(), sLoadInfo );
					}
					break;
				case F_GREP_DIALOG:
					/* Grep */
					DoGrep();  //Stonee, 2001/03/21  Grep��ʊ֐���
					break;
				case F_FILESAVEALL:	// Jan. 24, 2005 genta �S�ď㏑���ۑ�
					CAppNodeGroupHandle(0).PostMessageToAllEditors(
						WM_COMMAND,
						MAKELONG( F_FILESAVE_QUIET, 0 ),
						(LPARAM)0,
						NULL
					);
					break;
				case F_EXITALLEDITORS:	//Oct. 17, 2000 JEPRO ���O��ύX(F_FILECLOSEALL��F_WIN_CLOSEALL)	// 2007.02.13 ryoji ��F_EXITALLEDITORS
					/* �ҏW�̑S�I�� */
					CControlTray::CloseAllEditor( TRUE, GetTrayHwnd(), TRUE, 0 );	// 2006.12.25, 2007.02.13 ryoji �����ǉ�
					break;
				case F_EXITALL:	//Dec. 26, 2000 JEPRO F_�ɕύX
					/* �T�N���G�f�B�^�̑S�I�� */
					CControlTray::TerminateApplication( GetTrayHwnd() );	// 2006.12.25 ryoji �����ǉ�
					break;
				default:
					if( nId - IDM_SELWINDOW  >= 0 && nId - IDM_SELWINDOW  < m_pShareData->m_sNodes.m_nEditArrNum ){
						hwndWork = m_pShareData->m_sNodes.m_pEditArr[nId - IDM_SELWINDOW].GetHwnd();

						/* �A�N�e�B�u�ɂ��� */
						ActivateFrameWindow( hwndWork );
					}
					else if( nId-IDM_SELMRU >= 0 && nId-IDM_SELMRU < 999 ){

						/* �V�����ҏW�E�B���h�E���J�� */
						//	From Here Oct. 27, 2000 genta	�J�[�\���ʒu�𕜌����Ȃ��@�\
						CMRU cMRU;
						EditInfo openEditInfo;
						cMRU.GetEditInfo(nId - IDM_SELMRU, &openEditInfo);

						if( m_pShareData->m_Common.m_sFile.GetRestoreCurPosition() ){
							CControlTray::OpenNewEditor2( m_hInstance, GetTrayHwnd(), &openEditInfo, FALSE );
						}
						else {
							SLoadInfo sLoadInfo;
							sLoadInfo.cFilePath = openEditInfo.m_szPath;
							sLoadInfo.eCharCode = openEditInfo.m_nCharCode;
							sLoadInfo.bViewMode = false;
							CControlTray::OpenNewEditor(
								m_hInstance,
								GetTrayHwnd(),
								sLoadInfo
							);

						}
						//	To Here Oct. 27, 2000 genta
					}
					else if( nId - IDM_SELOPENFOLDER  >= 0 && nId - IDM_SELOPENFOLDER  < 999 ){
						/* MRU���X�g�̃t�@�C���̃��X�g */
						CMRU cMRU;
						std::vector<LPCTSTR> vMRU = cMRU.GetPathList();

						/* OPENFOLDER���X�g�̃t�@�C���̃��X�g */
						CMRUFolder cMRUFolder;
						std::vector<LPCTSTR> vOPENFOLDER = cMRUFolder.GetPathList();

						//Stonee, 2001/12/21 UNC�ł���ΐڑ������݂�
						NetConnect( cMRUFolder.GetPath( nId - IDM_SELOPENFOLDER ) );

						/* �t�@�C���I�[�v���_�C�A���O�̏����� */
						CDlgOpenFile	cDlgOpenFile;
						cDlgOpenFile.Create(
							m_hInstance,
							NULL,
							_T("*.*"),
							vOPENFOLDER[ nId - IDM_SELOPENFOLDER ],
							vMRU,
							vOPENFOLDER
						);
						SLoadInfo sLoadInfo( _T(""), CODE_AUTODETECT, false);
						if( !cDlgOpenFile.DoModalOpenDlg( &sLoadInfo ) ){
							break;
						}
						if( NULL == GetTrayHwnd() ){
							break;
						}

						// �V���ȕҏW�E�B���h�E���N��
						CControlTray::OpenNewEditor( m_hInstance, GetTrayHwnd(), sLoadInfo );
					}
					break;
				}
				return 0L;
			case WM_LBUTTONDBLCLK:
				bLDClick = true;		/* 03/02/20 ai */
				/* �V�K�ҏW�E�B���h�E�̒ǉ� */
				OnNewEditor();
				// Apr. 1, 2003 genta ���̌�ŕ\�����ꂽ���j���[�͕���
				::PostMessageAny( GetTrayHwnd(), WM_CANCELMODE, 0, 0 );
				return 0L;
			case WM_RBUTTONDBLCLK:
				return 0L;
			}
			break;

		case WM_QUERYENDSESSION:
			/* ���ׂẴE�B���h�E����� */	//Oct. 7, 2000 jepro �u�ҏW�E�B���h�E�̑S�I���v�Ƃ������������L�̂悤�ɕύX
			if( CloseAllEditor( FALSE, GetTrayHwnd(), TRUE, 0 ) ){	// 2006.12.25, 2007.02.13 ryoji �����ǉ�
				//	Jan. 31, 2000 genta
				//	���̎��_�ł�Windows�̏I�����m�肵�Ă��Ȃ��̂ŏ풓�������ׂ��ł͂Ȃ��D
				//	DestroyWindow( hwnd );
				return TRUE;
			}else{
				return FALSE;
			}
		case WM_CLOSE:
			/* ���ׂẴE�B���h�E����� */	//Oct. 7, 2000 jepro �u�ҏW�E�B���h�E�̑S�I���v�Ƃ������������L�̂悤�ɕύX
			if( CloseAllEditor( FALSE, GetTrayHwnd(), TRUE, 0 ) ){	// 2006.12.25, 2007.02.13 ryoji �����ǉ�
				DestroyWindow( hwnd );
			}
			return 0L;

		//	From Here Jan. 31, 2000 genta	Windows�I�����̌㏈���D
		//	Windows�I������WM_CLOSE���Ă΂�Ȃ���CDestroyWindow��
		//	�Ăяo���K�v���Ȃ��D�܂��C���b�Z�[�W���[�v�ɖ߂�Ȃ��̂�
		//	���b�Z�[�W���[�v�̌��̏����������Ŋ���������K�v������D
		case WM_ENDSESSION:
			//	����Windows�̏I�������f���ꂽ�̂Ȃ牽�����Ȃ�
			if( wParam == TRUE )
				OnDestroy();	// 2006.07.09 ryoji WM_DESTROY �Ɠ�������������i�g���C�A�C�R���̔j���Ȃǂ�NT�n�ł͕K�v�j

			return 0;	//	�������̃v���Z�X�ɐ��䂪�߂邱�Ƃ͂Ȃ�
		//	To Here Jan. 31, 2000 genta
		case WM_DESTROY:
			OnDestroy();

			/* Windows �ɃX���b�h�̏I����v�����܂��B*/
			::PostQuitMessage( 0 );
			return 0L;
		default:
// << 20010412 by aroka
//	Apr. 24, 2001 genta RegisterWindowMessage���g���悤�ɏC��
			if( uMsg == m_uCreateTaskBarMsg ){
				/* TaskTray Icon�̍ēo�^��v�����郁�b�Z�[�W�D
					Explorer���ċN�������Ƃ��ɑ��o�����D*/
				CreateTrayIcon( GetTrayHwnd() ) ;
			}
			break;	/* default */
// >> by aroka
	}
	return DefWindowProc( hwnd, uMsg, wParam, lParam );
}




/* WM_COMMAND���b�Z�[�W���� */
void CControlTray::OnCommand( WORD wNotifyCode, WORD wID , HWND hwndCtl )
{
	switch( wNotifyCode ){
	/* ���j���[����̃��b�Z�[�W */
	case 0:
		break;
	}
	return;
}

/*!
	@brief �V�K�E�B���h�E���쐬����
	
	�^�X�N�g���C����̐V�K�쐬�̏ꍇ�ɂ̓J�����g�f�B���N�g����
	�ۑ����̃f�t�H���g�f�B���N�g�����Ō�Ɏg��ꂽ�f�B���N�g���Ƃ���D
	�������Ō�Ɏg��ꂽ�f�B���N�g�������݂��Ȃ��ꍇ�͎��Ɏg��ꂽ�f�B���N�g���Ƃ��C
	�������݂���f�B���N�g����������܂ŗ��������Ɏ����D
	
	�ǂ̗�����������Ȃ������ꍇ�ɂ͌��݂̃J�����g�f�B���N�g���ō쐬����D

	@author genta
	@date 2003.05.30 �V�K�쐬
*/
void CControlTray::OnNewEditor()
{

	const TCHAR* szCurDir = NULL;

	//	�ŋߎg�����t�H���_�����Ԃɂ��ǂ�
	CMRUFolder mrufolder;

	int nCount = mrufolder.Length();
	for( int i = 0; i < nCount ; i++ ){
		const TCHAR* recentdir = mrufolder.GetPath( i );
		DWORD attr = GetFileAttributes( recentdir );

		if( attr != -1 ){
			if(( attr & FILE_ATTRIBUTE_DIRECTORY ) != 0 ){
				szCurDir = recentdir;
				break;
			}
		}
	}


	SLoadInfo sLoadInfo;
	sLoadInfo.cFilePath = _T("");
	sLoadInfo.eCharCode = CODE_NONE;
	sLoadInfo.bViewMode = false;
	OpenNewEditor( m_hInstance, GetTrayHwnd(), sLoadInfo, NULL, false, szCurDir );
}

/*!
	�V�K�ҏW�E�B���h�E�̒ǉ� ver 0

	@date 2000.10.24 genta WinExec -> CreateProcess�D�����@�\��t��
	@date 2002.02.17 YAZAKI CShareData�̃C���X�^���X�́ACProcess�ɂЂƂ���̂݁B
	@date 2003.05.30 genta �O���v���Z�X�N�����̃J�����g�f�B���N�g���w����\�ɁD
	@date 2007.06.26 ryoji �V�K�ҏW�E�B���h�E�� hWndParent �Ɠ����O���[�v���w�肵�ċN������
	@date 2008.04.19 ryoji MYWM_FIRST_IDLE �҂���ǉ�
	@date 2008.05.05 novice GetModuleHandle(NULL)��NULL�ɕύX
*/
bool CControlTray::OpenNewEditor(
	HINSTANCE			hInstance,			//!< [in] �C���X�^���XID (���͖��g�p)
	HWND				hWndParent,			//!< [in] �e�E�B���h�E�n���h���D�G���[���b�Z�[�W�\���p
	const SLoadInfo&	sLoadInfo,			//!< [in]
	const TCHAR*		szCmdLineOption,	//!< [in] �ǉ��̃R�}���h���C���I�v�V����
	bool				sync,				//!< [in] true�Ȃ�V�K�G�f�B�^�̋N���܂őҋ@����
	const TCHAR*		szCurDir			//!< [in] �V�K�G�f�B�^�̃J�����g�f�B���N�g��
)
{
	/* ���L�f�[�^�\���̂̃A�h���X��Ԃ� */
	DLLSHAREDATA*	pShareData = CShareData::getInstance()->GetShareData();

	/* �ҏW�E�B���h�E�̏���`�F�b�N */
	if( pShareData->m_sNodes.m_nEditArrNum >= MAX_EDITWINDOWS ){	//�ő�l�C��	//@@@ 2003.05.31 MIK
		TCHAR szMsg[128];
		auto_sprintf( szMsg, _T("�ҏW�E�B���h�E���̏����%d�ł��B\n����ȏ�͓����ɊJ���܂���B"), MAX_EDITWINDOWS );
		::MessageBox( NULL, szMsg, GSTR_APPNAME, MB_OK );
		return false;
	}

	// -- -- -- -- �R�}���h���C��������𐶐� -- -- -- -- //
	CCommandLineString cCmdLineBuf;

	//�A�v���P�[�V�����p�X
	TCHAR szEXE[MAX_PATH + 1];
	::GetModuleFileName( NULL, szEXE, _countof( szEXE ) );
	cCmdLineBuf.AppendF( _T("\"%ts\""), szEXE );

	// �t�@�C����
	if( _tcslen(sLoadInfo.cFilePath.c_str()) )	cCmdLineBuf.AppendF( _T(" \"%ts\""), sLoadInfo.cFilePath.c_str() );

	// �ǉ��̃R�}���h���C���I�v�V����
	if(szCmdLineOption)cCmdLineBuf.AppendF(_T(" %ts"), szCmdLineOption);

	// �R�[�h�w��
	if( IsValidCodeType(sLoadInfo.eCharCode) )cCmdLineBuf.AppendF( _T(" -CODE=%d"), sLoadInfo.eCharCode );

	// �r���[���[�h�w��
	if( sLoadInfo.bViewMode )cCmdLineBuf.AppendF( _T(" -R") );

	// �O���[�vID (�e�E�B���h�E����擾)
	HWND hwndAncestor = MyGetAncestor( hWndParent, GA_ROOTOWNER2 );	// 2007.10.22 ryoji GA_ROOTOWNER -> GA_ROOTOWNER2
	int nGroup = CAppNodeManager::Instance()->GetEditNode( hwndAncestor )->GetGroup();
	if( nGroup > 0 ){
		cCmdLineBuf.AppendF( _T(" -GROUP=%d"), nGroup );
	}


	// -- -- -- -- �v���Z�X���� -- -- -- -- //

	//	�v���Z�X�̋N��
	PROCESS_INFORMATION p;
	STARTUPINFO s;

	s.cb = sizeof_raw( s );
	s.lpReserved = NULL;
	s.lpDesktop = NULL;
	s.lpTitle = NULL;
	/*
	s.dwX = CW_USEDEFAULT;
	s.dwY = CW_USEDEFAULT;
	s.dwXSize = CW_USEDEFAULT;
	s.dwYSize = CW_USEDEFAULT;
	*/

	s.dwFlags = STARTF_USESHOWWINDOW;
	s.wShowWindow = SW_SHOWDEFAULT;
	s.cbReserved2 = 0;
	s.lpReserved2 = NULL;

	//	May 30, 2003 genta �J�����g�f�B���N�g���w����\��
	//�G�f�B�^�v���Z�X���N��
	DWORD dwCreationFlag = CREATE_DEFAULT_ERROR_MODE;
#ifdef _DEBUG
//	dwCreationFlag |= DEBUG_PROCESS; //2007.09.22 kobake �f�o�b�O�p�t���O
#endif
	TCHAR szCmdLine[1024]; _tcscpy_s(szCmdLine, _countof(szCmdLine), cCmdLineBuf.c_str());
	BOOL bCreateResult = CreateProcess(
		szEXE,					// ���s�\���W���[���̖��O
		szCmdLine,				// �R�}���h���C���̕�����
		NULL,					// �Z�L�����e�B�L�q�q
		NULL,					// �Z�L�����e�B�L�q�q
		FALSE,					// �n���h���̌p���I�v�V����
		dwCreationFlag,			// �쐬�̃t���O
		NULL,					// �V�������u���b�N
		szCurDir,				// �J�����g�f�B���N�g���̖��O
		&s,						// �X�^�[�g�A�b�v���
		&p						// �v���Z�X���
	);
	if( !bCreateResult ){
		//	���s
		TCHAR* pMsg;
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
						FORMAT_MESSAGE_IGNORE_INSERTS |
						FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPTSTR)&pMsg,
						0,
						NULL
		);
		ErrorMessage(
			hWndParent,
			_T("\'%ts\'\n�v���Z�X�̋N���Ɏ��s���܂����B\n%ts"),
			szEXE,
			pMsg
		);
		::LocalFree( (HLOCAL)pMsg );	//	�G���[���b�Z�[�W�o�b�t�@�����
		return false;
	}

	bool bRet = true;
	if( sync ){
		//	�N�������v���Z�X�����S�ɗ����オ��܂ł�����Ƒ҂D
		int nResult = WaitForInputIdle( p.hProcess, 10000 );	//	�ő�10�b�ԑ҂�
		if( nResult != 0 ){
			ErrorMessage(
				hWndParent,
				_T("\'%ts\'\n�v���Z�X�̋N���Ɏ��s���܂����B"),
				szEXE
			);
			bRet = false;
		}
	}
	else{
		// �^�u�܂Ƃߎ��͋N�������v���Z�X�������オ��܂ł��΂炭�^�C�g���o�[���A�N�e�B�u�ɕۂ�	// 2007.02.03 ryoji
		if( pShareData->m_Common.m_sTabBar.m_bDispTabWnd && !pShareData->m_Common.m_sTabBar.m_bDispTabWndMultiWin ){
			WaitForInputIdle( p.hProcess, 3000 );
			sync = true;
		}
	}

	// MYWM_FIRST_IDLE ���͂��܂ł�����Ƃ����]���ɑ҂�	// 2008.04.19 ryoji
	// Note. �N����v���Z�X���������������� COM �֐��iSHGetFileInfo API �Ȃǂ��܂ށj�����s����ƁA
	//       ���̎��_�� COM �̓����@�\�������� WaitForInputIdle �͏I�����Ă��܂��\��������i�炵���j�B
	if( sync && bRet )
	{
		int i;
		for( i = 0; i < 200; i++ ){
			MSG msg;
			DWORD dwExitCode;
			if( ::PeekMessage( &msg, 0, MYWM_FIRST_IDLE, MYWM_FIRST_IDLE, PM_REMOVE ) ){
				if( msg.message == WM_QUIT ){	// �w��͈͊O�ł� WM_QUIT �͎��o�����
					::PostQuitMessage( msg.wParam );
					break;
				}
				// �Ď��Ώۃv���Z�X����̃��b�Z�[�W�Ȃ甲����
				// �����łȂ���Δj�����Ď������o��
				if( msg.wParam == p.dwProcessId ){
					break;
				}
			}
			if( ::GetExitCodeProcess( p.hProcess, &dwExitCode ) && dwExitCode != STILL_ACTIVE ){
				break;	// �Ď��Ώۃv���Z�X���I������
			}
			::Sleep(10);
		}
	}

	CloseHandle( p.hThread );
	CloseHandle( p.hProcess );

	return bRet;
}


/*!	�V�K�ҏW�E�B���h�E�̒ǉ� ver 2:

	@date Oct. 24, 2000 genta create.
*/
bool CControlTray::OpenNewEditor2(
	HINSTANCE		hInstance,
	HWND			hWndParent,
	const EditInfo*	pfi,
	bool			bViewMode,
	bool			sync
)
{
	DLLSHAREDATA*	pShareData;

	/* ���L�f�[�^�\���̂̃A�h���X��Ԃ� */
	pShareData = CShareData::getInstance()->GetShareData();

	/* �ҏW�E�B���h�E�̏���`�F�b�N */
	if( pShareData->m_sNodes.m_nEditArrNum >= MAX_EDITWINDOWS ){	//�ő�l�C��	//@@@ 2003.05.31 MIK
		TCHAR szMsg[128];
		auto_sprintf( szMsg, _T("�ҏW�E�B���h�E���̏����%d�ł��B\n����ȏ�͓����ɊJ���܂���B"), MAX_EDITWINDOWS );
		::MessageBox( NULL, szMsg, GSTR_APPNAME, MB_OK );
		return false;
	}

	// �ǉ��̃R�}���h���C���I�v�V����
	CCommandLineString cCmdLine;
	if( pfi != NULL ){
		if( pfi->m_ptCursor.x >= 0					)cCmdLine.AppendF( _T(" -X=%d"), pfi->m_ptCursor.x +1 );
		if( pfi->m_ptCursor.y >= 0					)cCmdLine.AppendF( _T(" -Y=%d"), pfi->m_ptCursor.y +1 );
		if( pfi->m_nViewLeftCol >= CLayoutInt(0)	)cCmdLine.AppendF( _T(" -VX=%d"), (Int)pfi->m_nViewLeftCol + 1 );
		if( pfi->m_nViewTopLine >= CLayoutInt(0)	)cCmdLine.AppendF( _T(" -VY=%d"), (Int)pfi->m_nViewTopLine + 1 );
		if( IsValidCodeType(pfi->m_nCharCode)		)cCmdLine.AppendF( _T(" -CODE=%d"), pfi->m_nCharCode );
		if( bViewMode							)cCmdLine.AppendF( _T(" -R") );
	}
	SLoadInfo sLoadInfo;
	sLoadInfo.cFilePath = pfi ? pfi->m_szPath : _T("");
	sLoadInfo.eCharCode = CODE_AUTODETECT;
	sLoadInfo.bViewMode = bViewMode;
	return OpenNewEditor( hInstance, hWndParent, sLoadInfo, cCmdLine.c_str(), sync );
}
//	To Here Oct. 24, 2000 genta



void CControlTray::ActiveNextWindow()
{
	/* ���݊J���Ă���ҏW���̃��X�g�𓾂� */
	EditNode*	pEditNodeArr;
	int			nRowNum = CAppNodeManager::Instance()->GetOpenedWindowArr( &pEditNodeArr, TRUE );
	if(  nRowNum > 0 ){
		/* �����̃E�B���h�E�𒲂ׂ� */
		int				nGroup = 0;
		int				i;
		for( i = 0; i < nRowNum; ++i ){
			if( CEditWnd::Instance()->GetHwnd() == pEditNodeArr[i].GetHwnd() )
			{
				nGroup = pEditNodeArr[i].m_nGroup;
				break;
			}
		}
		if( i < nRowNum ){
			// �O�̃E�B���h�E
			int		j;
			for( j = i - 1; j >= 0; --j ){
				if( nGroup == pEditNodeArr[j].m_nGroup )
					break;
			}
			if( j < 0 ){
				for( j = nRowNum - 1; j > i; --j ){
					if( nGroup == pEditNodeArr[j].m_nGroup )
						break;
				}
			}
			/* �O�̃E�B���h�E���A�N�e�B�u�ɂ��� */
			HWND	hwndWork = pEditNodeArr[j].GetHwnd();
			ActivateFrameWindow( hwndWork );
			/* �Ō�̃y�C�����A�N�e�B�u�ɂ��� */
			::PostMessage( hwndWork, MYWM_SETACTIVEPANE, (WPARAM)-1, 1 );
		}
		delete [] pEditNodeArr;
	}
}

void CControlTray::ActivePrevWindow()
{
	/* ���݊J���Ă���ҏW���̃��X�g�𓾂� */
	EditNode*	pEditNodeArr;
	int			nRowNum = CAppNodeManager::Instance()->GetOpenedWindowArr( &pEditNodeArr, TRUE );
	if(  nRowNum > 0 ){
		/* �����̃E�B���h�E�𒲂ׂ� */
		int				nGroup = 0;
		int				i;
		for( i = 0; i < nRowNum; ++i ){
			if( CEditWnd::Instance()->GetHwnd() == pEditNodeArr[i].GetHwnd() ){
				nGroup = pEditNodeArr[i].m_nGroup;
				break;
			}
		}
		if( i < nRowNum ){
			// ���̃E�B���h�E
			int		j;
			for( j = i + 1; j < nRowNum; ++j ){
				if( nGroup == pEditNodeArr[j].m_nGroup )
					break;
			}
			if( j >= nRowNum ){
				for( j = 0; j < i; ++j ){
					if( nGroup == pEditNodeArr[j].m_nGroup )
						break;
				}
			}
			/* ���̃E�B���h�E���A�N�e�B�u�ɂ��� */
			HWND	hwndWork = pEditNodeArr[j].GetHwnd();
			ActivateFrameWindow( hwndWork );
			/* �ŏ��̃y�C�����A�N�e�B�u�ɂ��� */
			::PostMessage( hwndWork, MYWM_SETACTIVEPANE, (WPARAM)-1, 0 );
		}
		delete [] pEditNodeArr;
	}
}



/*!	�T�N���G�f�B�^�̑S�I��

	@date 2002.2.17 YAZAKI CShareData�̃C���X�^���X�́ACProcess�ɂЂƂ���̂݁B
	@date 2006.12.25 ryoji �����̕ҏW�E�B���h�E�����Ƃ��̊m�F�i�����ǉ��j
*/
void CControlTray::TerminateApplication(
	HWND hWndFrom	//!< [in] �Ăяo�����̃E�B���h�E�n���h��
)
{
	DLLSHAREDATA* pShareData = CShareData::getInstance()->GetShareData();	/* ���L�f�[�^�\���̂̃A�h���X��Ԃ� */

	/* ���݂̕ҏW�E�B���h�E�̐��𒲂ׂ� */
	if( pShareData->m_Common.m_sGeneral.m_bExitConfirm ){	//�I�����̊m�F
		if( 0 < CAppNodeGroupHandle(0).GetEditorWindowsNum() ){
			if( IDYES != ::MYMESSAGEBOX(
				hWndFrom,
				MB_YESNO | MB_APPLMODAL | MB_ICONQUESTION,
				GSTR_APPNAME,
				_T("���݊J���Ă���ҏW�p�̃E�B���h�E�����ׂĕ��ďI�����܂���?")
			) ){
				return;
			}
		}
	}
	/* �u���ׂẴE�B���h�E�����v�v�� */	//Oct. 7, 2000 jepro �u�ҏW�E�B���h�E�̑S�I���v�Ƃ������������L�̂悤�ɕύX
	BOOL bCheckConfirm = (pShareData->m_Common.m_sGeneral.m_bExitConfirm)? FALSE: TRUE;	// 2006.12.25 ryoji �I���m�F�ς݂Ȃ炻��ȏ�͊m�F���Ȃ�
	if( CloseAllEditor( bCheckConfirm, hWndFrom, TRUE, 0 ) ){	// 2006.12.25, 2007.02.13 ryoji �����ǉ�
		::PostMessageAny( pShareData->m_sHandles.m_hwndTray, WM_CLOSE, 0, 0 );
	}
	return;
}




/*!	���ׂẴE�B���h�E�����

	@date Oct. 7, 2000 jepro �u�ҏW�E�B���h�E�̑S�I���v�Ƃ������������L�̂悤�ɕύX
	@date 2002.2.17 YAZAKI CShareData�̃C���X�^���X�́ACProcess�ɂЂƂ���̂݁B
	@date 2006.12.25 ryoji �����̕ҏW�E�B���h�E�����Ƃ��̊m�F�i�����ǉ��j
	@date 2007.02.13 ryoji �u�ҏW�̑S�I���v����������(bExit)��ǉ�
	@date 2007.06.20 ryoji nGroup������ǉ�
*/
BOOL CControlTray::CloseAllEditor(
	BOOL	bCheckConfirm,	//!< [in] [���ׂĕ���]�m�F�I�v�V�����ɏ]���Ė₢���킹�����邩�ǂ���
	HWND	hWndFrom,		//!< [in] �Ăяo�����̃E�B���h�E�n���h��
	BOOL	bExit,			//!< [in] TRUE: �ҏW�̑S�I�� / FALSE: ���ׂĕ���
	int		nGroup			//!< [in] �O���[�vID
)
{
	EditNode*	pWndArr;
	int		n;

	n = CAppNodeManager::Instance()->GetOpenedWindowArr( &pWndArr, FALSE );
	if( 0 == n ){
		return TRUE;
	}
	
	/* �S�ҏW�E�B���h�E�֏I���v�����o�� */
	if( !CAppNodeGroupHandle(nGroup).RequestCloseEditor( pWndArr, n, bExit, bCheckConfirm, hWndFrom ) ){	// 2007.02.13 ryoji bExit�������p��
		return FALSE;
	}else{
		return TRUE;
	}
}




/*! �|�b�v�A�b�v���j���[(�g���C���{�^��) */
int	CControlTray::CreatePopUpMenu_L( void )
{
	int			i;
	int			j;
	int			nId;
	HMENU		hMenuTop;
	HMENU		hMenu;
	HMENU		hMenuPopUp;
	TCHAR		szMemu[100 + MAX_PATH * 2];	//	Jan. 19, 2001 genta
	POINT		po;
	RECT		rc;
//	HWND		hwndDummy;
	int			nMenuNum;
	EditInfo*	pfi;

	//�{���̓Z�}�t�H�ɂ��Ȃ��Ƃ���
	if( m_bUseTrayMenu ) return -1;
	m_bUseTrayMenu = true;

	m_CMenuDrawer.ResetContents();
	CFileNameManager::Instance()->TransformFileName_MakeCache();

	hMenuTop = ::LoadMenu( m_hInstance, MAKEINTRESOURCE( IDR_TRAYMENU_L ) );
	hMenu = ::GetSubMenu( hMenuTop, 0 );
	nMenuNum = ::GetMenuItemCount( hMenu )/* - 1*/;
	for( i = nMenuNum - 1; i >= 0; i-- ){
		::DeleteMenu( hMenu, i, MF_BYPOSITION );
	}

	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_FILENEW, _T("�V�K�쐬(&N)"), FALSE );
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_FILEOPEN, _T("�J��(&O)..."), FALSE );

	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_GREP_DIALOG, _T("Grep(&G)..."), FALSE );
	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );

	/* MRU���X�g�̃t�@�C���̃��X�g�����j���[�ɂ��� */
//@@@ 2001.12.26 YAZAKI MRU���X�g�́ACMRU�Ɉ˗�����
	CMRU cMRU;
	hMenuPopUp = cMRU.CreateMenu( &m_CMenuDrawer );	//	�t�@�C�����j���[
	if ( cMRU.Length() > 0 ){
		//	�A�N�e�B�u
		m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT)hMenuPopUp , _T("�ŋߎg�����t�@�C��(&F)") );
	}
	else {
		//	��A�N�e�B�u
		m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_POPUP | MF_GRAYED, (UINT)hMenuPopUp , _T("�ŋߎg�����t�@�C��(&F)") );
	}

	/* �ŋߎg�����t�H���_�̃��j���[���쐬 */
//@@@ 2001.12.26 YAZAKI OPENFOLDER���X�g�́ACMRUFolder�ɂ��ׂĈ˗�����
	CMRUFolder cMRUFolder;
	hMenuPopUp = cMRUFolder.CreateMenu( &m_CMenuDrawer );
	if ( cMRUFolder.Length() > 0 ){
		//	�A�N�e�B�u
		m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_POPUP, (UINT)hMenuPopUp, _T("�ŋߎg�����t�H���_(&D)") );
	}
	else {
		//	��A�N�e�B�u
		m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_POPUP | MF_GRAYED, (UINT)hMenuPopUp, _T("�ŋߎg�����t�H���_(&D)") );
	}

	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_FILESAVEALL, _T("���ׂď㏑���ۑ�(&Z)"), FALSE );	// Jan. 24, 2005 genta

	/* ���݊J���Ă���ҏW���̃��X�g�����j���[�ɂ��� */
	j = 0;
	for( i = 0; i < m_pShareData->m_sNodes.m_nEditArrNum; ++i ){
		if( IsSakuraMainWindow( m_pShareData->m_sNodes.m_pEditArr[i].GetHwnd() ) ){
			++j;
		}
	}

	if( j > 0 ){
		m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );
		j = 0;
		for( i = 0; i < m_pShareData->m_sNodes.m_nEditArrNum; ++i ){
			if( IsSakuraMainWindow( m_pShareData->m_sNodes.m_pEditArr[i].GetHwnd() ) ){
				/* �g���C����G�f�B�^�ւ̕ҏW�t�@�C�����v���ʒm */
				::SendMessageAny( m_pShareData->m_sNodes.m_pEditArr[i].GetHwnd(), MYWM_GETFILEINFO, 0, 0 );
				pfi = (EditInfo*)&m_pShareData->m_sWorkBuffer.m_EditInfo_MYWM_GETFILEINFO;
					if( pfi->m_bIsGrep ){
						/* �f�[�^���w��o�C�g���ȓ��ɐ؂�l�߂� */

						//pfi->m_szGrepKey �� cmemDes
						CNativeW	cmemDes;
						LimitStringLengthW( pfi->m_szGrepKey, wcslen( pfi->m_szGrepKey ), 64, cmemDes );

						//cmmDes �� szMenu2
						//	Jan. 19, 2002 genta
						//	���j���[�������&���l��
						TCHAR szMenu2[MAX_PATH * 2];
						dupamp( cmemDes.GetStringT(), szMenu2 );
//	From Here Oct. 4, 2000 JEPRO commented out & modified
//		j >= 10 + 26 �̎��̍l�����Ȃ���(�ɋ߂�)���J���t�@�C������36���z���邱�Ƃ͂܂��Ȃ��̂Ŏ�����OK�ł��傤

						//szMenu�����
						//	Jan. 19, 2002 genta
						//	&�̏d��������ǉ��������ߌp��������኱�ύX
						auto_sprintf( szMemu, _T("&%tc �yGrep�z\"%ts%ts\""),
							((1 + i) <= 9)?(_T('1') + i):(_T('A') + i - 9),
							szMenu2,
							( (int)wcslen( pfi->m_szGrepKey ) > cmemDes.GetStringLength() ) ? _T("�c"):_T("")
						);
					}else{
						// 2003/01/27 Moca �t�@�C�����̊ȈՕ\��
						// pfi->m_szPath �� szFileName
						TCHAR szFileName[_MAX_PATH];
						CFileNameManager::Instance()->GetTransformFileNameFast( pfi->m_szPath, szFileName, MAX_PATH );

						// szFileName �� szMenu2
						//	Jan. 19, 2002 genta
						//	���j���[�������&���l��
						TCHAR szMenu2[MAX_PATH * 2];
						dupamp( szFileName, szMenu2 );
						auto_sprintf( szMemu, _T("&%tc %ts %ts"),
							((1 + i) <= 9)?(_T('1') + i):(_T('A') + i - 9),
							(0 < _tcslen( szMenu2 ))? szMenu2:_T("�i����j"),
							pfi->m_bIsModified ? _T("*"):_T(" ")
						);
//		To Here Oct. 4, 2000
						// gm_pszCodeNameArr_Bracket ����R�s�[����悤�ɕύX
						if(IsValidCodeTypeExceptSJIS(pfi->m_nCharCode)){
							_tcscat( szMemu, CCodeTypeName(pfi->m_nCharCode).Bracket() );
						}
					}

//				::InsertMenu( hMenu, IDM_EXITALL, MF_BYCOMMAND | MF_STRING, IDM_SELWINDOW + i, szMemu );
				m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, IDM_SELWINDOW + i, szMemu, FALSE );
				++j;
			}
		}
	}
	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_EXITALLEDITORS, _T("�ҏW�̑S�I��(&Q)"), FALSE );	//Oct. 17, 2000 JEPRO ���O��ύX(F_FILECLOSEALL��F_WIN_CLOSEALL)	//Feb. 18, 2001 JEPRO �A�N�Z�X�L�[�ύX(L��Q)	// 2006.10.21 ryoji �\��������ύX	// 2007.02.13 ryoji ��F_EXITALLEDITORS
	if( j == 0 ){
		::EnableMenuItem( hMenu, F_EXITALLEDITORS, MF_BYCOMMAND | MF_GRAYED );	//Oct. 17, 2000 JEPRO ���O��ύX(F_FILECLOSEALL��F_WIN_CLOSEALL)	// 2007.02.13 ryoji ��F_EXITALLEDITORS
		::EnableMenuItem( hMenu, F_FILESAVEALL, MF_BYCOMMAND | MF_GRAYED );	// Jan. 24, 2005 genta
	}

	//	Jun. 9, 2001 genta �\�t�g�E�F�A������
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_EXITALL, _T("�T�N���G�f�B�^�̑S�I��(&X)"), FALSE );	//Dec. 26, 2000 JEPRO F_�ɕύX

	po.x = 0;
	po.y = 0;
	::GetCursorPos( &po );
	po.y -= 4;

	rc.left = 0;
	rc.right = 0;
	rc.top = 0;
	rc.bottom = 0;

	::SetForegroundWindow( GetTrayHwnd() );
	nId = ::TrackPopupMenu(
		hMenu,
		TPM_BOTTOMALIGN
		| TPM_RIGHTALIGN
		| TPM_RETURNCMD
		| TPM_LEFTBUTTON
		/*| TPM_RIGHTBUTTON*/
		,
		po.x,
		po.y,
		0,
		GetTrayHwnd(),
		&rc
	);
	::PostMessageAny( GetTrayHwnd(), WM_USER + 1, 0, 0 );
	::DestroyMenu( hMenuTop );
//	MYTRACE_A( "nId=%d\n", nId );

	m_bUseTrayMenu = false;

	return nId;
}

//�L�[���[�h�F�g���C�E�N���b�N���j���[����
//	Oct. 12, 2000 JEPRO �|�b�v�A�b�v���j���[(�g���C���{�^��) ���Q�l�ɂ��ĐV���ɒǉ���������

/*! �|�b�v�A�b�v���j���[(�g���C�E�{�^��) */
int	CControlTray::CreatePopUpMenu_R( void )
{
	int		i;
	int		nId;
	HMENU	hMenuTop;
	HMENU	hMenu;
	POINT	po;
	RECT	rc;
	int		nMenuNum;

	//�{���̓Z�}�t�H�ɂ��Ȃ��Ƃ���
	if( m_bUseTrayMenu ) return -1;
	m_bUseTrayMenu = true;

	m_CMenuDrawer.ResetContents();

	hMenuTop = ::LoadMenu( m_hInstance, MAKEINTRESOURCE( IDR_TRAYMENU_L ) );
	hMenu = ::GetSubMenu( hMenuTop, 0 );
	nMenuNum = ::GetMenuItemCount( hMenu )/* - 1*/;
	for( i = nMenuNum - 1; i >= 0; i-- ){
		::DeleteMenu( hMenu, i, MF_BYPOSITION );
	}

#if 0
	2002/04/26 YAZAKI �g���Ȃ����͕̂\�����Ȃ�

	/* �g���C�E�N���b�N�́u�I�v�V�����v���j���[ */
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_GRAYED, F_TYPE_LIST, _T("�^�C�v�ʐݒ�ꗗ(&L)..."), FALSE );	//Jan. 12, 2001 JEPRO ���̃��j���[���ڂ𖳌�������
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_GRAYED, F_OPTION_TYPE, _T("�^�C�v�ʐݒ�(&Y)..."), FALSE );	//Jan. 12, 2001 JEPRO ���̃��j���[���ڂ𖳌�������
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_GRAYED, F_OPTION, _T("���ʐݒ�(&C)..."), FALSE );				//Jan. 12, 2001 JEPRO ���̃��j���[���ڂ𖳌�������
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_GRAYED, F_FONT, _T("�t�H���g�ݒ�(&F)..."), FALSE );			//Jan. 12, 2001 JEPRO ���̃��j���[���ڂ𖳌�������
	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );
#endif

	/* �g���C�E�N���b�N�́u�w���v�v���j���[ */
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_HELP_CONTENTS , _T("�w���v�ڎ�(&O)"), FALSE );
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_HELP_SEARCH , _T("�w���v�L�[���[�h����(&S)"), FALSE );	//Nov. 25, 2000 JEPRO �u�g�s�b�N�́v���u�L�[���[�h�v�ɕύX
//	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );
//	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_MENU_ALLFUNC , _T("�R�}���h�ꗗ(&M)"), FALSE );	//Jan. 12, 2001 JEPRO �܂��R�����g�A�E�g��ꍆ (T_T)
	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );

#if 0
	2002/04/26 YAZAKI �g���Ȃ����͕̂\�����Ȃ�

	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_GRAYED, F_EXTHELP1 , _T("�O���w���v�P(&E)"), FALSE );			//Jan. 12, 2001 JEPRO ���̃��j���[���ڂ𖳌�������
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING | MF_GRAYED, F_EXTHTMLHELP , _T("�O��HTML�w���v(&H)"), FALSE );	//Jan. 12, 2001 JEPRO ���̃��j���[���ڂ𖳌�������
	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );
#endif

//	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, IDM_ABOUT, _T("�o�[�W�������(&A)"), FALSE );
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_ABOUT, _T("�o�[�W�������(&A)"), FALSE );	//Dec. 25, 2000 JEPRO F_�ɕύX

	m_CMenuDrawer.MyAppendMenuSep( hMenu, MF_BYPOSITION | MF_SEPARATOR, 0, NULL, FALSE );
//	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, IDM_EXITALL, _T("�e�L�X�g�G�f�B�^�̑S�I��(&X)"), FALSE );
//	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_EXITALL, _T("�e�L�X�g�G�f�B�^�̑S�I��(&X)"), FALSE );	//Dec. 26, 2000 JEPRO F_�ɕύX
	//	Jun. 18, 2001 genta �\�t�g�E�F�A������
	m_CMenuDrawer.MyAppendMenu( hMenu, MF_BYPOSITION | MF_STRING, F_EXITALL, _T("�T�N���G�f�B�^�̑S�I��(&X)"), FALSE );	//De

	po.x = 0;
	po.y = 0;
	::GetCursorPos( &po );
	po.y -= 4;

	rc.left = 0;
	rc.right = 0;
	rc.top = 0;
	rc.bottom = 0;

	::SetForegroundWindow( GetTrayHwnd() );
	nId = ::TrackPopupMenu(
		hMenu,
		TPM_BOTTOMALIGN
		| TPM_RIGHTALIGN
		| TPM_RETURNCMD
		| TPM_LEFTBUTTON
		/*| TPM_RIGHTBUTTON*/
		,
		po.x,
		po.y,
		0,
		GetTrayHwnd(),
		&rc
	);
	::PostMessageAny( GetTrayHwnd(), WM_USER + 1, 0, 0 );
	::DestroyMenu( hMenuTop );
//	MYTRACE_A( "nId=%d\n", nId );

	m_bUseTrayMenu = false;

	return nId;
}

/*!
	@brief WM_DESTROY ����
	@date 2006.07.09 ryoji �V�K�쐬
*/
void CControlTray::OnDestroy()
{
	HWND hwndExitingDlg;

	if (GetTrayHwnd() == NULL)
		return;	// ���ɔj������Ă���

	// �z�b�g�L�[�̔j��
	::UnregisterHotKey( GetTrayHwnd(), ID_HOTKEY_TRAYMENU );

	// 2006.07.09 ryoji ���L�f�[�^�ۑ��� CControlProcess::Terminate() ����ړ�
	//
	// �u�^�X�N�g���C�ɏ풓���Ȃ��v�ݒ�ŃG�f�B�^��ʁiNormal Process�j�𗧂��グ���܂�
	// �Z�b�V�����I������悤�ȏꍇ�ł����L�f�[�^�ۑ����s���Ȃ������蒆�f����邱�Ƃ�
	// �����悤�A�����ŃE�B���h�E���j�������O�ɕۑ�����
	//

	/* �I���_�C�A���O��\������ */
	if( m_pShareData->m_Common.m_sGeneral.m_bDispExitingDialog ){
		/* �I�����_�C�A���O�̕\�� */
		hwndExitingDlg = ::CreateDialog(
			m_hInstance,
			MAKEINTRESOURCE( IDD_EXITING ),
			GetTrayHwnd()/*::GetDesktopWindow()*/,
			(DLGPROC)ExitingDlgProc
		);
		::ShowWindow( hwndExitingDlg, SW_SHOW );
	}

	/* ���L�f�[�^�̕ۑ� */
	CShareData_IO::SaveShareData();

	/* �I���_�C�A���O��\������ */
	if( m_pShareData->m_Common.m_sGeneral.m_bDispExitingDialog ){
		/* �I�����_�C�A���O�̔j�� */
		::DestroyWindow( hwndExitingDlg );
	}

	if( m_bCreatedTrayIcon ){	/* �g���C�ɃA�C�R��������� */
		TrayMessage( GetTrayHwnd(), NIM_DELETE, 0, NULL, NULL );
	}

	/* �A�N�Z�����[�^�e�[�u���̍폜 */
	if( m_pShareData->m_sHandles.m_hAccel != NULL ){
		::DestroyAcceleratorTable( m_pShareData->m_sHandles.m_hAccel );
		m_pShareData->m_sHandles.m_hAccel = NULL;
	}

	m_hWnd = NULL;
}

/*!
	@brief �I���_�C�A���O�p�v���V�[�W��
	@date 2006.07.02 ryoji CControlProcess ����ړ�
*/
INT_PTR CALLBACK CControlTray::ExitingDlgProc(
	HWND	hwndDlg,	// handle to dialog box
	UINT	uMsg,		// message
	WPARAM	wParam,		// first message parameter
	LPARAM	lParam		// second message parameter
)
{
	switch( uMsg ){
	case WM_INITDIALOG:
		return TRUE;
	}
	return FALSE;
}

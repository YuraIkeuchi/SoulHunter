#include "OpenBrowser.h"

#include <tchar.h>

void OpenBrowser::OpenCsvFile(CString filename)
{
	CString default = _T("C:\\K020G1233\\SoulHunterGit\\Resources\\");

	ShellExecute(nullptr, _T("open"), default + filename, nullptr, nullptr, SW_SHOW);
}

void OpenBrowser::OpenWebPage()
{
	ShellExecute(nullptr, _T("open"), _T("https://dixq.net/forum/viewtopic.php?t=12787"), nullptr, nullptr, SW_SHOW);
}

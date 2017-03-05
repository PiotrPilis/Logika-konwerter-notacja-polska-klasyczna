#include <windows.h>
#include <Commctrl.h>
#include <wchar.h>
#include <sstream>
#include <locale>
#include <iostream>
#include <string>
#include "main.h"

#define ID_TAB_ZW 1
#define ID_TAB_ST 0

LPSTR NazwaKlasy = "Klasa";
MSG Komunikat;

char LastChar = '\0';

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );

HWND b_a, b_b, b_c, b_d, b_e, b_f, b_g, b_h, b_i, b_j, b_k, b_l, b_m, b_n, b_o, b_p, b_r, b_s, b_t, b_w, b_z, b_neg, b_notw, b_nzam, b_licz, b_dysjunkcja, b_koniunkcja, b_alternatywa, b_implikacja, b_rownowaznosc, bb_neg, b_cofnij, b_usun, hText, hTextResult, Copyright;
HWND hTab;
BYTE id_tab = 0;
bool zakaz_wpisywania = false;
BYTE type_data = 0;
int nmb_con, nmb_var, nmb_naw = 0;

std::string* narrow( const std::wstring& str, std::string& incomingString )
{
std::ostringstream stm;
const std::ctype<char>& ctfacet =
std::use_facet< std::ctype<char> >( stm.getloc() );
for( size_t i=0; i<str.size(); ++i )
stm << ctfacet.narrow( str[i], 0 );
stm << "\n";
incomingString = stm.str();
return &incomingString;
}


wchar_t* add_var(wchar_t* buff, wchar_t* add_char)
{
	if(id_tab == 1)
	{
		if(nmb_con == 0 && type_data == 1)
		{
			MessageBox( NULL, "Nie podałeś spójnika!", "Błąd", MB_ICONEXCLAMATION | MB_OK );
			return buff;
		} else
		{
			if(nmb_con * 2 < nmb_var && type_data == 1)
			{
				MessageBox( NULL, "Podaj więcej spojników!", "Błąd", MB_ICONEXCLAMATION | MB_OK );
				return buff;
			} else
			{
				/*if(wcslen(buff) >= 40)
				{
					zakaz_wpisywania = true;
					MessageBox( NULL, "Nie można wpisać więcej znaków!", "Błąd", MB_ICONEXCLAMATION | MB_OK );
					return buff;
				} else
				{*/
					wchar_t* tmp_buff = new wchar_t[wcslen(buff) + 1 + wcslen(add_char)];
					tmp_buff[wcslen(buff) + wcslen(add_char)] = '\0';
					for(int gh = 0; gh < wcslen(buff); gh++)
					{
						tmp_buff[gh] = buff[gh];
					}
					for(int gf = 0; gf < wcslen(add_char); gf++)
					{
					tmp_buff[wcslen(buff) + gf] = add_char[gf];
					}
					if(type_data == 1)
						nmb_var++;
					else if(type_data == 2)
					nmb_con++;
					return tmp_buff;
				//}
			}
		}
	} else
	{
		/*if(wcslen(buff) >= 40)
		{
			zakaz_wpisywania = true;
			MessageBox( NULL, "Nie można wpisać więcej znaków!", "Błąd", MB_ICONEXCLAMATION | MB_OK );
			return buff;
		} else
		{*/
			wchar_t* tmp_buff = new wchar_t[wcslen(buff) + 1 + wcslen(add_char)];
			tmp_buff[wcslen(buff) + wcslen(add_char)] = '\0';
			for(int gh = 0; gh < wcslen(buff); gh++)
			{
				tmp_buff[gh] = buff[gh];
			}
			for(int gf = 0; gf < wcslen(add_char); gf++)
			{
				tmp_buff[wcslen(buff) + gf] = add_char[gf];
			}
			return tmp_buff;
		//}
	}
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    
    // WYPEŁNIANIE STRUKTURY
    WNDCLASSEX wc;
    
    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =( HBRUSH )( COLOR_WINDOW + 1 );
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon( NULL, IDI_APPLICATION );
    
    // REJESTROWANIE KLASY OKNA
    if( !RegisterClassEx( & wc ) )
    {
        MessageBox( NULL, "Błąd podczas rejestracji okna!", "Błąd",
        MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }
    
    // TWORZENIE OKNA
    HWND hwnd;
    
    hwnd = CreateWindowEx( WS_EX_CLIENTEDGE, NazwaKlasy, "Konwerter (notacja polska <-> logika klasyczna)", WS_SYSMENU,
    CW_USEDEFAULT, CW_USEDEFAULT, 300, 350, NULL, NULL, hInstance, NULL );
    
    if( hwnd == NULL )
    {
        MessageBox( NULL, "Błąd podczas tworzenia okna!", "Błąd", MB_ICONEXCLAMATION );
        return 1;
    }
    
    ShowWindow( hwnd, nCmdShow ); // Pokaż okienko...
    UpdateWindow( hwnd );

	hTab = CreateWindowEx( 0, WC_TABCONTROL, 0, WS_CHILD | WS_VISIBLE | TCS_FIXEDWIDTH, 0, 0, 544, 375, hwnd,( HMENU ) 10, hInstance, NULL );
	TabCtrl_SetItemSize( hTab, 150, 20 );
TCITEM tci1, tci2;
tci1.mask = TCIF_TEXT;
tci2.mask = TCIF_TEXT;
tci1.pszText = "Z not. klas.";
tci2.pszText = "Z not. pol.";
tci1.cchTextMax = sizeof( tci1.pszText );
tci2.cchTextMax = sizeof( tci2.pszText );
TabCtrl_InsertItem( hTab, ID_TAB_ZW, & tci1 );
TabCtrl_InsertItem( hTab, ID_TAB_ST, & tci2 );

	b_a = CreateWindowExW( 0, L"BUTTON", L"a", WS_CHILD | WS_VISIBLE, 5, 120, 35, 30, hwnd, (HMENU)500, hInstance, NULL );
	b_b = CreateWindowExW( 0, L"BUTTON", L"b", WS_CHILD | WS_VISIBLE, 40, 120, 35, 30, hwnd, (HMENU)501, hInstance, NULL );
	b_c = CreateWindowExW( 0, L"BUTTON", L"c", WS_CHILD | WS_VISIBLE, 75, 120, 35, 30, hwnd, (HMENU)502, hInstance, NULL );
	b_d = CreateWindowExW( 0, L"BUTTON", L"d", WS_CHILD | WS_VISIBLE, 110, 120, 35, 30, hwnd, (HMENU)503, hInstance, NULL );
	b_e = CreateWindowExW( 0, L"BUTTON", L"e", WS_CHILD | WS_VISIBLE, 145, 120, 35, 30, hwnd, (HMENU)504, hInstance, NULL );
	b_f = CreateWindowExW( 0, L"BUTTON", L"f", WS_CHILD | WS_VISIBLE, 180, 120, 35, 30, hwnd, (HMENU)505, hInstance, NULL );

	b_g = CreateWindowExW( 0, L"BUTTON", L"g", WS_CHILD | WS_VISIBLE, 5, 150, 35, 30, hwnd, (HMENU)506, hInstance, NULL );
	b_h = CreateWindowExW( 0, L"BUTTON", L"h", WS_CHILD | WS_VISIBLE, 40, 150, 35, 30, hwnd, (HMENU)507, hInstance, NULL );
	b_i = CreateWindowExW( 0, L"BUTTON", L"i", WS_CHILD | WS_VISIBLE, 75, 150, 35, 30, hwnd, (HMENU)508, hInstance, NULL );
	b_j = CreateWindowExW( 0, L"BUTTON", L"j", WS_CHILD | WS_VISIBLE, 110, 150, 35, 30, hwnd, (HMENU)509, hInstance, NULL );
	b_k = CreateWindowExW( 0, L"BUTTON", L"k", WS_CHILD | WS_VISIBLE, 145, 150, 35, 30, hwnd, (HMENU)510, hInstance, NULL );
	b_l = CreateWindowExW( 0, L"BUTTON", L"l", WS_CHILD | WS_VISIBLE, 180, 150, 35, 30, hwnd, (HMENU)511, hInstance, NULL );

	b_m = CreateWindowExW( 0, L"BUTTON", L"m", WS_CHILD | WS_VISIBLE, 5, 180, 35, 30, hwnd, (HMENU)512, hInstance, NULL );
	b_n = CreateWindowExW( 0, L"BUTTON", L"n", WS_CHILD | WS_VISIBLE, 40, 180, 35, 30, hwnd, (HMENU)513, hInstance, NULL );
	b_o = CreateWindowExW( 0, L"BUTTON", L"o", WS_CHILD | WS_VISIBLE, 75, 180, 35, 30, hwnd, (HMENU)514, hInstance, NULL );
	b_p = CreateWindowExW( 0, L"BUTTON", L"p", WS_CHILD | WS_VISIBLE, 110, 180, 35, 30, hwnd, (HMENU)515, hInstance, NULL );
	b_r = CreateWindowExW( 0, L"BUTTON", L"r", WS_CHILD | WS_VISIBLE, 145, 180, 35, 30, hwnd, (HMENU)516, hInstance, NULL );
	b_s = CreateWindowExW( 0, L"BUTTON", L"s", WS_CHILD | WS_VISIBLE, 180, 180, 35, 30, hwnd, (HMENU)517, hInstance, NULL );

	b_t = CreateWindowExW( 0, L"BUTTON", L"t", WS_CHILD | WS_VISIBLE, 5, 210, 35, 30, hwnd, (HMENU)518, hInstance, NULL );
	b_w = CreateWindowExW( 0, L"BUTTON", L"w", WS_CHILD | WS_VISIBLE, 40, 210, 35, 30, hwnd, (HMENU)519, hInstance, NULL );
	b_z = CreateWindowExW( 0, L"BUTTON", L"z", WS_CHILD | WS_VISIBLE, 75, 210, 35, 30, hwnd, (HMENU)520, hInstance, NULL );
	b_neg = CreateWindowExW( 0, L"BUTTON", L"¬", WS_CHILD | WS_VISIBLE, 110, 210, 35, 30, hwnd, (HMENU)521, hInstance, NULL );
	b_notw = CreateWindowExW( 0, L"BUTTON", L"(", WS_CHILD | WS_VISIBLE, 145, 210, 35, 30, hwnd, (HMENU)522, hInstance, NULL );
	b_nzam = CreateWindowExW( 0, L"BUTTON", L")", WS_CHILD | WS_VISIBLE, 180, 210, 35, 30, hwnd, (HMENU)523, hInstance, NULL );
	b_licz = CreateWindowExW( 0, L"BUTTON", L"konwertuj", WS_CHILD | WS_VISIBLE, 10, 245, 145, 40, hwnd, (HMENU)524, hInstance, NULL );
	b_dysjunkcja = CreateWindowExW( 0, L"BUTTON", L"/", WS_CHILD | WS_VISIBLE, 160, 245, 55, 40, hwnd, (HMENU)525, hInstance, NULL );
	b_koniunkcja = CreateWindowExW( 0, L"BUTTON", L"∧", WS_CHILD | WS_VISIBLE, 220, 245, 55, 40, hwnd, (HMENU)526, hInstance, NULL );
	b_alternatywa = CreateWindowExW( 0, L"BUTTON", L"∨", WS_CHILD | WS_VISIBLE, 220, 200, 55, 40, hwnd, (HMENU)527, hInstance, NULL );
	b_implikacja = CreateWindowExW( 0, L"BUTTON", L"=>", WS_CHILD | WS_VISIBLE, 220, 155, 55, 40, hwnd, (HMENU)528, hInstance, NULL );
	b_rownowaznosc = CreateWindowExW( 0, L"BUTTON", L"<=>", WS_CHILD | WS_VISIBLE, 220, 110, 55, 40, hwnd, (HMENU)529, hInstance, NULL );
	b_cofnij = CreateWindowExW( 0, L"BUTTON", L"←", WS_CHILD | WS_VISIBLE, 90, 85, 70, 30, hwnd, (HMENU)530, hInstance, NULL );
	b_usun = CreateWindowExW( 0, L"BUTTON", L"C", WS_CHILD | WS_VISIBLE, 15, 85, 70, 30, hwnd, (HMENU)531, hInstance, NULL );

	bb_neg = CreateWindowExW( 0, L"BUTTON", L"N", WS_CHILD | WS_VISIBLE, 160, 210, 55, 30, hwnd, (HMENU)532, hInstance, NULL );
	ShowWindow( bb_neg, SW_HIDE );

	HFONT F_SPOJNIK=CreateFont(0,0,0,0,FW_DEMIBOLD,0,0,0,0,0,0,0,0,"Arial");
	SendMessage(b_alternatywa,WM_SETFONT,(WPARAM)F_SPOJNIK,0);
	SendMessage(b_koniunkcja,WM_SETFONT,(WPARAM)F_SPOJNIK,0);
	SendMessage(b_implikacja,WM_SETFONT,(WPARAM)F_SPOJNIK,0);
	SendMessage(b_rownowaznosc,WM_SETFONT,(WPARAM)F_SPOJNIK,0);
	SendMessage(b_dysjunkcja,WM_SETFONT,(WPARAM)F_SPOJNIK,0);

	SendMessage(bb_neg,WM_SETFONT,(WPARAM)F_SPOJNIK,0);


	hText = CreateWindowExW( WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 15, 30, 260, 35, hwnd, (HMENU)50, hInstance, NULL ); //powiedzmy że zmienna będzie nazywa się a
	hTextResult = CreateWindowExW( WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 180, 70, 100, 35, hwnd, (HMENU)50, hInstance, NULL );
	SetWindowText( hText, "" );
	SetWindowText( hTextResult, "" );

	//Copyright = CreateWindowExW( 0, L"STATIC", L"Copyrights 2014 by Piotr Pilis", WS_CHILD | WS_VISIBLE, 15, 300, 300, 300, hwnd, 0, hInstance, NULL );

    // Pętla komunikatów
    while( GetMessage( & Komunikat, NULL, 0, 0 ) )
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

// OBSŁUGA ZDARZEŃ
LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	wchar_t* Bufor;
	DWORD dwdlugosc;
	wchar_t* wchar;
	wchar_t* wchart;
	char* t;
	wchar_t* tmps;
	wchar_t* tmps_char;

	wchar_t* tmpBuff;
    switch( msg )
    {
	case WM_COMMAND:
		if(zakaz_wpisywania == false)
		{
		switch( wParam )
		{
		case 500:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'a';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 501:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'b';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 502:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'c';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 503:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'd';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 504:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'e';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 505:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'f';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 506:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'g';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 507:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'h';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 508:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'i';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 509:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'j';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 510:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'k';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 511:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'l';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 512:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'm';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 513:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'n';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 514:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'o';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 515:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'p';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 516:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'r';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 517:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L's';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 518:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L't';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 519:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'w';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 520:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'z';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1] ;
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			wchart = add_var(Bufor, wchar);
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 521:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'~';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 522:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L'(';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 523:
			type_data = 1;
			wchar = new wchar_t[2];
			wchar[0] = L')';
			wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 529:
			type_data = 2;
			if(id_tab == 0)
			{
				wchar = new wchar_t[4];
				wchar[0] = L'<';
				wchar[1] = L'=';
				wchar[2] = L'>';
				wchar[3] = L'\0';
			} else
			{
				wchar = new wchar_t[2];
				wchar[0] = L'E';
				wchar[1] = L'\0';
			}
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar));
			delete[] Bufor;
			break;
		case 525:
			type_data = 2;
			if(id_tab == 0)
			{
				wchar = new wchar_t[2];
				wchar[0] = L'/';
				wchar[1] = L'\0';
			} else
			{
				wchar = new wchar_t[2];
				wchar[0] = L'D';
				wchar[1] = L'\0';
			}
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 526:
			type_data = 2;
			if(id_tab == 0)
			{
				wchar = new wchar_t[2];
				wchar[0] = L'∧';
				wchar[1] = L'\0';
			} else
			{
				wchar = new wchar_t[2];
				wchar[0] = L'K';
				wchar[1] = L'\0';
			}
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 527:
			type_data = 2;
			if(id_tab == 0)
			{
				wchar = new wchar_t[2];
				wchar[0] = L'∨';
				wchar[1] = L'\0';
			} else
			{
				wchar = new wchar_t[2];
				wchar[0] = L'A';
				wchar[1] = L'\0';
			}
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 528:
			type_data = 2;
			if(id_tab == 0)
			{
				wchar = new wchar_t[3];
				wchar[0] = L'=';
				wchar[1] = L'>';
				wchar[2] = L'\0';
			} else
			{
				wchar = new wchar_t[2];
				wchar[0] = L'C';
				wchar[1] = L'\0';
			}
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 532:
			type_data = 2;
				wchar = new wchar_t[2];
				wchar[0] = L'N';
				wchar[1] = L'\0';
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1 );
			SetWindowTextW( hText, add_var(Bufor, wchar)); 
			delete[] Bufor;
			break;
		case 530:
			dwdlugosc = GetWindowTextLength( hText );
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1);

			tmpBuff = new wchar_t[2];
			tmpBuff[0] = Bufor[dwdlugosc - 1];
			tmpBuff[1] = '\0';
			if(wcscmp(const_cast<const wchar_t*>(tmpBuff), L">") == 0)
			{
				tmpBuff[0] = Bufor[dwdlugosc - 3];
				if(wcscmp(const_cast<const wchar_t*>(tmpBuff), L"<") == 0)
				{
					GetWindowTextW( hText, Bufor, dwdlugosc - 2);
					SetWindowTextW( hText, Bufor);
				} else
				{
					GetWindowTextW( hText, Bufor, dwdlugosc - 1);
					SetWindowTextW( hText, Bufor);
				}
			} else {
				GetWindowTextW( hText, Bufor, dwdlugosc);
				SetWindowTextW( hText, Bufor);
			}
			delete[] tmpBuff;
			delete[] Bufor;
			break;
		case 531:
			SetWindowTextW( hText, L""); 
			SetWindowTextW( hTextResult, L""); 
			break;
		case 524:
			dwdlugosc = GetWindowTextLength( hText );
			t = new char[dwdlugosc + 1];
			GetWindowText( hText, t, dwdlugosc + 1);
			Bufor = new wchar_t[dwdlugosc + 1];
			GetWindowTextW( hText, Bufor, dwdlugosc + 1);
			ManagerFormula form;
			if(id_tab == 1)
			{
				strlen(const_cast<const char*>(t));
				form.FromNotationToClassic(t, 0, 0);

				int nmb_char = 0;
				for(int g = 0; g < ldatac.size(); g++)
				{
					nmb_char += strlen(ldatac[g]);
				}
				tmps_char = new wchar_t[nmb_char + 1];
				tmps_char[nmb_char] = '\0';
				int it = 0;
				for(int g = 0; g < ldatac.size(); g++)
				{
					for(int k = 0; k < strlen(ldatac[g]); k++)
					{
						if(strcmp(const_cast<const char*>(ldatac[g]), "5") == 0)
						{
							tmps_char[it] = L'∨';
						} else if(strcmp(const_cast<const char*>(ldatac[g]), "6") == 0)
						{
							tmps_char[it] = L'∧';
						} else
						{
							tmps_char[it] = ldatac[g][k];
						}
						it++;
					}
				}
				//MessageBoxW( NULL, tmps_char, L"Wynik działania", MB_OK );
				SetWindowTextW( hTextResult, tmps_char );
				ldatac.clear();
				delete[] Bufor;
				delete[] t;
				delete[] tmps_char;
			} else
			{
				for(int gh = 0; gh <= dwdlugosc; gh++)
				{
					if(Bufor[gh] == L'∨')
						t[gh] = '5';
					else if(Bufor[gh] == L'∧')
						t[gh] = '6';
				}
				form.FromClassicToNotation(t, true);
				tmps = new wchar_t[ldata.size() + 1];
				tmps[ldata.size()] = '\0';
				for(int g = 0; g < ldata.size(); g++)
				{
					tmps[g] = ldata[g];
				}
				SetWindowTextW( hTextResult, tmps );
				//MessageBoxW( NULL, tmps, L"Wynik działania", MB_OK );
				ldata.clear();
				delete[] Bufor;
				delete[] tmps;
				delete[] t;
			}
			/*	b_cofnij = CreateWindowExW( 0, L"BUTTON", L"←", WS_CHILD | WS_VISIBLE, 90, 85, 70, 30, hwnd, (HMENU)530, hInstance, NULL );
	b_usun = CreateWindowExW( 0, L"BUTTON", L"C", WS_CHILD | WS_VISIBLE, 15, 85, 70, 30, hwnd, (HMENU)531, hInstance, NULL );
	b_licz = CreateWindowExW( 0, L"BUTTON", L"konwertuj", WS_CHILD | WS_VISIBLE, 10, 245, 145, 40, hwnd, (HMENU)524, hInstance, NULL );*/
		}
		} else
		{
			MessageBox( NULL, "Nie można wpisać więcej znaków!", "Błąd", MB_ICONEXCLAMATION | MB_OK );
		}
		break;
	case WM_NOTIFY:
		LPNMHDR n;
		n =( LPNMHDR ) lParam;
		if( n->code == TCN_SELCHANGE && n->hwndFrom == hTab ) // Sprawdza, czy uchwyt pochodzi od hTab
		{
			int index = TabCtrl_GetCurSel( hTab );
			switch( index ) // indeks aktualnej kontrolki
			{
				case ID_TAB_ST:							// z notacji polskiej
					//ShowWindow( , SW_SHOW );
					ShowWindow( b_notw, SW_HIDE );
					ShowWindow( b_nzam, SW_HIDE );
					ShowWindow( b_neg, SW_HIDE );
					ShowWindow( bb_neg, SW_SHOW );
					SetWindowText( b_alternatywa, "A" );
					SetWindowText( b_koniunkcja, "K" );
					SetWindowText( b_dysjunkcja, "D" );
					SetWindowText( b_implikacja, "C" );
					SetWindowText( b_rownowaznosc, "E" );
					SetWindowText( hText, "" );
					id_tab = 1;
					break;
				case ID_TAB_ZW:
					ShowWindow( b_notw, SW_SHOW );
					ShowWindow( b_nzam, SW_SHOW );
					ShowWindow( b_neg, SW_SHOW );
					ShowWindow( bb_neg, SW_HIDE );
					SetWindowTextW( b_alternatywa, L"∨" );
					SetWindowTextW( b_koniunkcja, L"∧" );
					SetWindowText( b_dysjunkcja, "/" );
					SetWindowText( b_implikacja, "=>" );
					SetWindowText( b_rownowaznosc, "<=>" );
					SetWindowText( hText, "" );
					id_tab = 0;
					break;
			}
		}

		break;
	case WM_CREATE:

		break;
    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;
        
    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
        
        default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
    }
    
	return 0;
}
/*
void main(int argc, char *argv[])
{
	/*std::string str;
	printf("Wpisz formule\n");
	std::cin >> str;
	char * buff = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), buff);
	buff[str.size()] = '\0';

	ManagerFormula form;
	//form.FromClassicToNotation(buff, true);
	form.FromNotationToClassic(buff, 0, 0);
	for(int g = 0; g < ldatac.size(); g++)
	{
		printf("%s", ldatac[g]);
	}
	delete[] buff;

	wchar_t* k = new wchar_t[4];
	k[2] = '\0';
	k[1] = 'x';
	k[0] = '←';
		std::string myshorterstring;
			std::string* stringPointer = narrow(k, myshorterstring);
			
	if(k[1] == L'x')
		printf("%s", stringPointer);
	system("pause");
}*/

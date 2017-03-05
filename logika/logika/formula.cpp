#include "main.h"

std::vector<char> ldata;
std::vector<char*> ldatac;
ManagerFormula::ManagerFormula()
{
	ManagerFormula::con = 0;
	ManagerFormula::nmbl_con = 0;	
}
char* ManagerFormula::s_end_var(char* buff)
{
	int num_n = 1;
	int i = 1;
	while(strlen(buff) >= i)
	{
		if (buff[i] == '(' || buff[i] == '{' || buff[i] == '[')
		{
			num_n++;
		} else if (buff[i] == ')' || buff[i] == '}' || buff[i] == ']')
		{
			num_n--;
			if (num_n < 1)
			{
				char* tmp = new char[i + 1];
				for (int k = 0; k <= i; k++)
				{
					tmp[k] = buff[k];
				}
				tmp[i + 1] = '\0';
				return tmp;
			}
		}
		i++;
	}
	return "\0";
}
bool_char ManagerFormula::extract_con(char* buff)
{
	bool_char bool_char_v;
	bool_char_v.main = false;
	if (buff[0] == '6')
	{

		if (ManagerFormula::con < koniunkcja + 1)
		{
			ManagerFormula::con = koniunkcja + 1;
			bool_char_v.main = true; 
		}
		bool_char_v.char_v = "6";
		return bool_char_v;
	} else if (buff[0] == '5')
	{
		if (ManagerFormula::con < alternatywa + 1)
		{
			ManagerFormula::con = alternatywa + 1;
			bool_char_v.main = true; 
		}
		bool_char_v.char_v = "5";
		return bool_char_v;
	} else if (buff[0] == '/')
	{
		if (ManagerFormula::con < dysjunkcja + 1)
		{
			ManagerFormula::con = dysjunkcja + 1;
			bool_char_v.main = true; 
		}
		bool_char_v.char_v = "/";
		return bool_char_v;
	} else if (buff[0] == '=' && buff[1] == '>')
	{
		if (ManagerFormula::con < implikacja + 1)
		{
			ManagerFormula::con = implikacja + 1;
			bool_char_v.main = true; 
		}
		bool_char_v.char_v = "=>";
		return bool_char_v;
	} else if (buff[0] == '<' && buff[1] == '=' && buff[2] == '>')
	{
		if (ManagerFormula::con < rownowaznosc + 1)
		{
			ManagerFormula::con = rownowaznosc + 1;
			bool_char_v.main = true; 
		}
		bool_char_v.char_v = "<=>";
		return bool_char_v;
	}
	bool_char_v.char_v = "\0";
	return bool_char_v;
}
char* ManagerFormula::extract_variable(char* buff)
{		
	char* tmp;
	if (buff[0] == '~' || buff[0] == '¬')
	{
		tmp = new char[strlen(buff) - 1];
		for (int k = 0; k <= strlen(buff) - 2; k++)
		{
			tmp[k] = buff[k + 1];
		}
		tmp[strlen(buff) - 1] = '\0';
		char* tmm = ManagerFormula::extract_variable(tmp);
		//delete[] tmp;
		char* tmpm = new char[strlen(tmm) + 1];
		for (int k = 0; k <= strlen(tmm); k++)
		{
			tmpm[k + 1] = tmm[k];
		}
		tmpm[0] = '~';
		return tmpm;
	} else if (buff[0] == '(' || buff[0] == '{' || buff[0] == '[')
	{
		tmp = ManagerFormula::s_end_var(buff);
		return tmp;
	} else if (buff[0] >= static_cast<int>('a') && buff[0] <= static_cast<int>('z'))
	{
		tmp = new char[1];
		tmp[0] = buff[0];
		tmp[1] = '\0';
		return tmp;
	} else if (buff[0] >= static_cast<int>('A') && buff[0] <= static_cast<int>('Z'))
	{
		tmp = new char[1];
		tmp[0] = buff[0];
		tmp[1] = '\0';
		return tmp;
	}
	return "\0";
}
bool ManagerFormula::do_var_and_con(char* buff, int nmb)
{
	char* tmp;
	bool_char conjj = ManagerFormula::extract_con(buff);										
	if (conjj.main == true)
		ManagerFormula::nmbl_con = 1 + nmb;
	ManagerFormula::data.push_back(conjj.char_v);
	if (ManagerFormula::data[1] == "\0")
		return false;																	// ...
	tmp = new char[strlen(buff) - strlen(ManagerFormula::data[data.size() - 1]) + 1];			// 2. Nowy buffor danych (bez wyodrębnionej zmiennej)
	for(int i = strlen(ManagerFormula::data[data.size() - 1]); i <= strlen(buff) - 1; i++)
	{
		tmp[i - strlen(ManagerFormula::data[data.size() - 1])] = buff[i]; 
	}
	tmp[strlen(buff) - strlen(ManagerFormula::data[data.size() - 1])] = '\0';





	ManagerFormula::data.push_back(ManagerFormula::extract_variable(tmp));
	if (ManagerFormula::data[2] == "\0")
		return false;
	delete[] tmp;
	tmp = new char[strlen(buff) - (strlen(ManagerFormula::data[ManagerFormula::data.size() - 1]) + strlen(ManagerFormula::data[data.size() - 2])) + 1];
	for(int i = strlen(ManagerFormula::data[ManagerFormula::data.size() - 1]) + strlen(ManagerFormula::data[data.size() - 2]); i <= strlen(buff) - 1; i++)
	{
		tmp[i - (strlen(ManagerFormula::data[ManagerFormula::data.size() - 1]) + strlen(ManagerFormula::data[ManagerFormula::data.size() - 2]))] = buff[i]; 
	}
	tmp[strlen(buff) - (strlen(ManagerFormula::data[ManagerFormula::data.size() - 1]) + strlen(ManagerFormula::data[ManagerFormula::data.size() - 2]))] = '\0';


	return true;
}
bool ManagerFormula::do_vars_and_con(char* buff)
{
	char* tmp;
	ManagerFormula::data.push_back(ManagerFormula::extract_variable(buff));										// 1. Wyodrębnij pierwszą zmienną
	if (ManagerFormula::data[0] == "\0")
		return false;
	tmp = new char[strlen(buff) - strlen(ManagerFormula::data[0]) + 1];							// 2. Nowy buffor danych (bez wyodrębnionej zmiennej)
	for(int i = strlen(ManagerFormula::data[0]); i <= strlen(buff) - 1; i++)
	{
		tmp[i - strlen(ManagerFormula::data[0])] = buff[i]; 
	}
	tmp[strlen(buff) - strlen(ManagerFormula::data[0])] = '\0';



	bool_char conjj = ManagerFormula::extract_con(tmp);											// 3. Wyodrębnij pierwszy spójnik
	if (conjj.main == true)
		nmbl_con = 1;
	ManagerFormula::data.push_back(conjj.char_v);
	if (ManagerFormula::data[1] == "\0")
		return false;
	delete[] tmp;
	tmp = new char[strlen(buff) - (strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[0])) + 1];
	for(int i = strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[0]); i <= strlen(buff) - 1; i++)
	{
		tmp[i - (strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[0]))] = buff[i]; 
	}
	tmp[strlen(buff) - (strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[0]))] = '\0';



	ManagerFormula::data.push_back(ManagerFormula::extract_variable(tmp));										// 4. Wyodrębnij drugą zmienną
	if (ManagerFormula::data[2] == "\0")
		return false;
	delete[] tmp;
	tmp = new char[strlen(buff) - (strlen(ManagerFormula::data[0]) + strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[2])) + 1];
	for(int i = strlen(ManagerFormula::data[2]) + strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[0]); i <= strlen(buff) - 1; i++)
	{
		tmp[i - (strlen(ManagerFormula::data[2]) + strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[0]))] = buff[i]; 
	}
	tmp[strlen(buff) - (strlen(ManagerFormula::data[2]) + strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[0]))] = '\0';


	int j = 0;
	int bn = strlen(ManagerFormula::data[0]) + strlen(ManagerFormula::data[1]) + strlen(ManagerFormula::data[2]);
	while(!(strlen(tmp) == 0))
	{
		j++;
		if(ManagerFormula::do_var_and_con(tmp, j) == false)
			return false;
		delete[] tmp;
		bn += strlen(ManagerFormula::data[2 * j + 1]) + strlen(ManagerFormula::data[2 * j + 2]);		
		tmp = new char[strlen(buff) - bn + 1];
		for(int i = bn; i <= strlen(buff) - 1; i++)
		{
			tmp[i - bn] = buff[i]; 
		}
		tmp[strlen(buff) - bn] = '\0';
	}

	delete[] tmp;
	return true;
}
void ManagerFormula::get_main_con()
{
	int nmbl_main_con = 0;
	for(int m = 1; m <= ManagerFormula::data.size() - 2; m = m + 2)
	{
		if (strcmp(ManagerFormula::data[m], "6") == 0)
		{
			if (ManagerFormula::con < koniunkcja + 1)
			{
				ManagerFormula::con = koniunkcja + 1;
				nmbl_main_con = (m + 1) / 2;
			}
		} else if (strcmp(ManagerFormula::data[m], "5") == 0)
		{
			if (ManagerFormula::con < alternatywa + 1)
			{
				ManagerFormula::con = alternatywa + 1;
				nmbl_main_con = (m + 1) / 2;
			}
		} else if (strcmp(ManagerFormula::data[m], "/") == 0)
		{
			if (ManagerFormula::con < dysjunkcja + 1)
			{
				ManagerFormula::con = dysjunkcja + 1;
				nmbl_main_con = (m + 1) / 2;
			}
		} else if (strcmp(ManagerFormula::data[m], "=>") == 0)
		{
			if (ManagerFormula::con < implikacja + 1)
			{
				ManagerFormula::con = implikacja + 1;
				nmbl_main_con = (m + 1) / 2;
			}
		} else if (strcmp(ManagerFormula::data[m], "<=>") == 0)
		{
			if (ManagerFormula::con < rownowaznosc + 1)
			{
				ManagerFormula::con = rownowaznosc + 1;
				nmbl_main_con = (m + 1) / 2;
			}
		} 
	}
	ManagerFormula::nmbl_con = nmbl_main_con;
}

char ManagerFormula::GetCharFromClassicToNotation(char* buff)
{
	if (strcmp(buff, "6") == 0)
	{
		return c_koniunkcja;
	} else if (strcmp(buff, "5") == 0)
	{
		return c_alternatywa;
	} else if (strcmp(buff, "/") == 0)
	{
		return c_dysjunkcja;
	} else if (strcmp(buff, "=>") == 0)
	{
		return c_implikacja;
	} else if (strcmp(buff, "<=>") == 0)
	{
		return c_rownowaznosc;
	}
	return '\0';
}
bool ManagerFormula::GetLowerLevel(int froml, int tol)
{
	char* tmp;
	int sizedata = 0;
	for(int nb = froml; nb <= tol; nb++)
	{
		sizedata += strlen(ManagerFormula::data[nb]);
	}
	tmp = new char[sizedata + 1];
	tmp[sizedata] = '\0';
	int kj = 0;
	for(int nb = froml; nb <= tol; nb++)
	{
		for(int nv = 0; nv < strlen(ManagerFormula::data[nb]); nv++)
		{
			tmp[kj] = ManagerFormula::data[nb][nv];
			kj++;
		}
	}
	
	ManagerFormula form;
	form.FromClassicToNotation(tmp, false);
	return true;
}
void ManagerFormula::DelAllNaw(char* c, int froml, int tol)
{
	char* ntmpbuf = new char[strlen(c) - 1];
	ntmpbuf[strlen(c) - 2] = '\0';
	for(int gf = strlen(c) - 3; gf >=  0; gf--)
	{
		ntmpbuf[gf] = c[gf + 1];
	}
	ManagerFormula::CheckNeg(ntmpbuf);
}
bool ManagerFormula::CheckNeg(char* c)
{
	if(c[0] == '~')
	{
		int nmb_neg = 1;
		do
		{
			if(c[nmb_neg] == '~')
				nmb_neg++;
			else
				break;
		} while(strlen(c) > nmb_neg);
		if(c[nmb_neg] == '(' || c[nmb_neg] == '[' || c[nmb_neg] == '{')
		{
			for(int j = 1; j <= nmb_neg; j++)
			{
				ldata.push_back('N');
			}
			char* ntmpbuff = new char[strlen(c) - (nmb_neg - 1)];
			ntmpbuff[strlen(c) - 1 - (nmb_neg - 1)] = '\0';
			for(int gh = 0; gh <= strlen(c) - 2 - (nmb_neg - 1); gh++)
			{
				ntmpbuff[gh] = c[gh + nmb_neg];
			}
			ManagerFormula::CheckNeg(ntmpbuff);	
			delete[] ntmpbuff;
		} else
		{
			char* ntmpbuff = new char[strlen(c) - (nmb_neg - 1)];
			ntmpbuff[strlen(c) - 1 - (nmb_neg - 1)] = '\0';
			for(int gh = 0; gh <= strlen(c) - 1; gh++)
			{
				ntmpbuff[gh] = c[gh + nmb_neg];
			}
			if(strlen(ntmpbuff) > 1)
			{
				ManagerFormula* form = new ManagerFormula();
				form->FromClassicToNotation(c, false);
				delete form;
			} else
			{
				for(int j = 1; j <= nmb_neg; j++)
				{
					ldata.push_back('N');
				}
				ldata.push_back(c[nmb_neg]);						
			}
			delete[] ntmpbuff;
		}
	} else if(c[0] == '(' || c[0] == '[' || c[0] == '{')
	{
		ManagerFormula::DelAllNaw(c, 1, strlen(c) - 2);
	} else
	{
		if(strlen(c) > 1)
		{
			ManagerFormula* form = new ManagerFormula();				
			form->FromClassicToNotation(c, false);
			delete form;
		} else {
			ldata.push_back(c[0]);
		}
	}
	return true;
}
bool ManagerFormula::FromClassicToNotation(char* buff, bool checkNeg)
{
	if(buff[0] == '~' && checkNeg == true && (buff[strlen(buff) - 1] == ')' || buff[strlen(buff) - 1] == ']' || buff[strlen(buff) - 1] == '}'))
	{
		int nmb_neg = 1;
		do
		{
			if(buff[nmb_neg] == '{' || buff[nmb_neg] == '[' || buff[nmb_neg] == '(')
			{
				if(nmb_neg%2 == 1)
					ldata.push_back('N');
				int nmb_naw = 1;
				while(buff[nmb_neg + nmb_naw] == '(' || buff[nmb_neg + nmb_naw] == '[' || buff[nmb_neg + nmb_naw] == '{')
				{
					nmb_naw++;
				}
				char* tmp = new char[strlen(buff) + 1 - nmb_neg - (nmb_naw * 2)];
				tmp[strlen(buff) - nmb_neg - (nmb_naw * 2)] = '\0';

				// tu błąd - jeśli masz zdanie: ~(p=>s)<=>h    stworzy tmp: p=>s)<=> - done!

				for(int gh = 0; gh < strlen(buff) - nmb_neg - (nmb_naw * 2); gh++)
				{
					tmp[gh] = buff[gh + nmb_neg + nmb_naw];
				}

				//printf("\ntmp for ~ than (:%s\n\n", tmp);
				ManagerFormula::FromClassicToNotation(tmp, false);
				delete[] tmp;
				break;
			} else if(buff[nmb_neg] == '~')
			{
				nmb_neg++;
			} else
			{
				ManagerFormula::FromClassicToNotation(buff, false);
				break;
			}
		} while(strlen(buff) > nmb_neg);
		//ManagerFormula::CheckNeg(buff);
		// dorób usuwanie nawiasów np. (p=>r) - done!
	} else if((buff[0] == '(' || buff[0] == '[' || buff[0] == '{') && (buff[strlen(buff) - 1] == ')' || buff[strlen(buff) - 1] == ']' || buff[strlen(buff) - 1] == '}'))
	{
		char* tmp = new char[strlen(buff) - 1];
		tmp[strlen(buff) - 2] = '\0';
		for(int gh = 0; gh < strlen(buff) - 2; gh++)
		{
			tmp[gh] = buff[gh + 1];
		}
		ManagerFormula::FromClassicToNotation(tmp, true);
	} else 
	{
		ManagerFormula::do_vars_and_con(buff);
			char contmp = ManagerFormula::GetCharFromClassicToNotation(ManagerFormula::data[ManagerFormula::nmbl_con * 2 - 1]);
		if(contmp == '\0')
			return false;
		ldata.push_back(contmp);																// główny spójnik
		if(ManagerFormula::nmbl_con > 1)
		{
			ManagerFormula::GetLowerLevel(0, ManagerFormula::nmbl_con * 2 - 2);								// od lewej strony gł. spójnika
		}
		else
		{
			ManagerFormula::CheckNeg(ManagerFormula::data[0]);
		}
		if((ManagerFormula::data.size() - 1) / 2 - ManagerFormula::nmbl_con != 0)
		{
			ManagerFormula::GetLowerLevel(ManagerFormula::nmbl_con * 2, ManagerFormula::data.size() - 1);			// od prawej strony gł. spójnika
		}
		else
		{
			ManagerFormula::CheckNeg(ManagerFormula::data[ManagerFormula::nmbl_con * 2]);
		}
	}
	return true;
}


/* Błędy
1. (a=>(~b=>c))=>d - ~ przesuwa przed nawias - done
2. (~(a=>b))=>c - nie bada ~(a=>b), ponieważ ma pominąć ten krok i wywala błąd - done
3. (~a=>b)=>c - pomija negacje stojącą przy a (~a) - done
4. ~(~(~((a=>~(~~b/c)/~(d=>e)))))=>f - maszyna: CNNNCaDN N DNbcNCdef; ja: CNNNCaDND N NbcNCdef - oddzieliłem różnice
   a=>~(~~b/c)/~(d=>e) - zamienia "~(~~b" na "~~(~b"
   (~~a=>b)=>c - jeden ~wyrzucił przed nawias, drugi po nawiasie - done
*/
ManagerFormula::gc ManagerFormula::GetCharFromNotationToClassic(char c)
{
	ManagerFormula::gc tmp;
	if(c == 'C')
	{
		tmp.c = "=>";
		tmp.type = 1;
	} else if(c == 'E')
	{
		tmp.c = "<=>";
		tmp.type = 1;
	} else if(c == 'D')
	{
		tmp.c = "/";
		tmp.type = 1;
	} else if(c == 'K')
	{
		tmp.c = "6";
		tmp.type = 1;
	} else if(c == 'A')
	{
		tmp.c = "5";
		tmp.type = 1;
	} else if(c == 'N')
	{
		tmp.c = "~";
		tmp.type = 2;
	} else 
	{
		tmp.c = new char[2];
		tmp.c[1] = '\0';
		tmp.c[0] = c;
		tmp.type = 3;
	}
	return tmp;
}

bool ManagerFormula::extract_variable_fn(char* buff, int to_line, BYTE last_con)
{
	ManagerFormula::main_con = ManagerFormula::GetCharFromNotationToClassic(buff[0]);
	if(ManagerFormula::main_con.type == 3)
	{
		ldatac.insert(ldatac.begin() + to_line, ManagerFormula::main_con.c);
		return true;
	} else if(ManagerFormula::main_con.type == 2)								// negacja
	{
		int nmb_neg = 0;
		while(ManagerFormula::main_con.type == 2)
		{
			ldatac.insert(ldatac.begin() + to_line + nmb_neg, ManagerFormula::main_con.c);
			nmb_neg++;
			ManagerFormula::main_con = ManagerFormula::GetCharFromNotationToClassic(buff[nmb_neg]);
		}
		char* new_buff = new char[strlen(buff) - nmb_neg + 1];
		new_buff[strlen(buff) - nmb_neg] = '\0';
		for(int gh = 0; gh <= strlen(buff) - nmb_neg - 1; gh++)
		{
			new_buff[gh] = buff[gh + nmb_neg];
		}
		ManagerFormula new_form;
		new_form.extract_variable_fn(new_buff, to_line + nmb_neg, last_con);
	} else
	{
		ManagerFormula::FromNotationToClassic(buff, to_line, last_con);
	}
	return false;
}

bool ManagerFormula::FromNotationToClassic(char* buff, int to_line, BYTE last_con)		//buff -wiadome; do_ -ile jest znaków np. nawiasów zamykających, tak by umiejscowił nowy znak przed tym znakiem; last_con -ostatni najwyższy index spójnika, żeby wiedział kiedy otworzyć nawias...
{
	int bto_line = to_line;
	ManagerFormula::main_con = ManagerFormula::GetCharFromNotationToClassic(buff[0]);
	if(strlen(buff) < 3)
		return false;
	BYTE nmb_neg = 0;
	while(ManagerFormula::main_con.type == 2)
	{
		nmb_neg++;
		ldatac.insert(ldatac.begin() + bto_line, ManagerFormula::main_con.c);
		
		bto_line++;
		ManagerFormula::main_con = ManagerFormula::GetCharFromNotationToClassic(buff[nmb_neg]);
	}

	if(nmb_neg > 0)
	{
		char* tmp_c;
		tmp_c = "(";
		ldatac.insert(ldatac.begin() + bto_line, tmp_c);
		tmp_c = ")";
		ldatac.insert(ldatac.begin() + bto_line + 1, tmp_c);
		bto_line++;
	} else
	{
		if(ManagerFormula::main_con.type <= last_con)							// jeśli poprzedni spójnik był wyższej lub takiej samej rangi dodaj nawiasy...
		{
			char* tmp_c;
			tmp_c = "(";
			ldatac.insert(ldatac.begin() + bto_line, tmp_c);
			tmp_c = ")";
			ldatac.insert(ldatac.begin() + bto_line + 1, tmp_c);
			bto_line++;
		}
	}
	ldatac.insert(ldatac.begin() + bto_line, ManagerFormula::main_con.c);					// pamiętaj, że tu nie dodaliśmy bto_line, ponieważ jest prawa i lewa strona var
	int bbto_line = ldatac.size() - bto_line;
	char* new_buff_l = new char[strlen(buff) - nmb_neg];
	new_buff_l[strlen(buff) - nmb_neg - 1] = '\0';
	for(int gh = 0; gh < strlen(buff) - nmb_neg - 1; gh++)
	{
		new_buff_l[gh] = buff[gh + nmb_neg + 1];
	}
		// --> lewa strona głównego spójnika
	ManagerFormula* new_form_l = new ManagerFormula;
	new_form_l->extract_variable_fn(new_buff_l, bto_line, ManagerFormula::main_con.type);
		// <-- lewa strona głównego spójnika
	delete new_form_l;




	bto_line = ldatac.size() - bbto_line + 1;
	gc tmp_con;
	int nmbSpojnikow = 0;
	int nmbLineAdd = 0;
	int ObecnyZnak = 0;
		while(ObecnyZnak + 1 <= strlen(new_buff_l))
		{
			tmp_con = ManagerFormula::GetCharFromNotationToClassic(new_buff_l[ObecnyZnak]);

			if(tmp_con.type == 1)
			{
				nmbSpojnikow++;
				ObecnyZnak++;
			} else if(tmp_con.type == 3)
			{
				if(nmbSpojnikow > 0)
				{
					nmbSpojnikow--;
					ObecnyZnak++;
				} else
				{
					nmbLineAdd = ObecnyZnak + 1;
					break;
				}
			} else 
			{
				ObecnyZnak++;
			}
		}
	char* new_buff_r = new char[strlen(new_buff_l) - nmbLineAdd + 1];
	new_buff_r[strlen(new_buff_l) - nmbLineAdd] = '\0';
	for(int gh = nmbLineAdd; gh < strlen(new_buff_l); gh++)
	{
		new_buff_r[gh - nmbLineAdd] = new_buff_l[gh];
	}
		// --> prawa strona głównego spójnika
	ManagerFormula* new_form_r = new ManagerFormula;
	new_form_r->extract_variable_fn(new_buff_r, bto_line, ManagerFormula::main_con.type);
		// <-- prawa strona głównego spójnika
	delete new_form_r;
	delete[] new_buff_r;
	delete[] new_buff_l;

	return true;
}
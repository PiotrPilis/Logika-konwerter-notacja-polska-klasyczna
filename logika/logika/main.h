#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

	struct bool_char
	{
		char* char_v;
		bool main;
	};
	enum
	{
		koniunkcja,
		alternatywa,
		dysjunkcja,
		implikacja,
		rownowaznosc
	};
	enum
	{
		c_koniunkcja = 'K',
		c_alternatywa = 'A',
		c_dysjunkcja = 'D',
		c_implikacja = 'C',
		c_rownowaznosc = 'E'
	};
	extern std::vector<char> ldata;
	extern std::vector<char*> ldatac;
class ManagerFormula
{
private:
	BYTE con;										// indeks g³ównego spójnika (1-...-5)
	BYTE nmbl_con;									// pokazuje numer spójnika (1-...-x), gdzie x = x'ty numer g³ównego spójnika
	std::vector<char*> data;						// przechowuje roz³o¿one dane

	char* s_end_var(char* buff);
	bool_char extract_con(char* buff);
	char* extract_variable(char* buff);
	bool do_var_and_con(char* buff, int nmb);
	bool do_vars_and_con(char* buff);

	void get_main_con();

	bool GetLowerLevel(int froml, int tol);
	char GetCharFromClassicToNotation(char* buff);
	bool CheckNeg(char* c);
	void DelAllNaw(char* c, int froml, int tol);

	struct gc
	{
		char* c;
		BYTE type;
	};
	gc GetCharFromNotationToClassic(char c);
	gc main_con;
	bool extract_variable_fn(char* buff, int to_line, BYTE last_con);
public:
	ManagerFormula();
	bool FromClassicToNotation(char* buff, bool checkNeg);

	bool FromNotationToClassic(char* buff, int to_line, BYTE last_con);
};
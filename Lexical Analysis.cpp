#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <cstdlib> 
using namespace std;

struct listsize{
	char str[100] ;
	int table ;
	int num ;	
};

vector<listsize> list;
listsize listtemp;
char global_Table5[100][100];
char global_Table6[100][100];
char global_Table7[100][100];
void InputFile( string & name ) ;
void SkipWS ( char & num ) ;
void GetTokoen( string temp, char num,int & casenum ) ;
bool Table1 ( string temp, int & number );
bool Table2 ( string temp, int & number );
bool Table3 ( string temp, int & number );
bool Table4 ( string temp, int & number );
void FindToken( string temp, int total, bool isString );
int CalAsciiNum( string temp ) ;
// ----------------------------main-------------------------------------
int main() {
  char num = '\0' ;
  int casenum = 0;
  for (int i = 0; i < 100; i++ )  //initial global table5, 6, 7 
  {
  	strcpy(global_Table5[i], "0" ) ;
  	strcpy(global_Table6[i], "0" ) ;
  	strcpy(global_Table7[i], "0" ) ;
  }

  string fileName ;
  InputFile( fileName ) ;   
  cout << "Lexical Analysis:建檔完成" << endl ;
  cout << "請查看桌面output檔" << endl; 
} // main

// ------------------------InputFile-----------------------------------------  

void InputFile( string & name ) {
	ifstream fin; 
	string tempp;
	int total = 0;
	string sentence;
	string outputname = "10627149_output.txt" ;
	char temp[100] ;
	char num = '\0';
	char ck = '\0'; // check next char 
	int casenum = 0;
	bool isToken = false;
	int linetoken = 0; // record how many token in a line
	cout << "Input a file name: " ; // input file name
	cin >> name ;
	tempp = name + ".txt" ; 
	name = tempp ;
	tempp = ""; // initial temp
	fin.open( name.c_str() ); // open the file
    while ( !fin ) { // isnt exist
    	cout << "### " << name << " does not exist! ###" << endl;
    	cout << "Input a file name: " << endl;
		cin >> name;
		tempp = name + ".txt" ;
		name = tempp ;
		tempp = ""; // initial tempp
		fin.open( name.c_str() ); // open the file
	}
	ofstream fout( outputname.c_str() );
// ------------------------Start GetToken---------------------------------------------------
	//cout << "start" << endl ;
	while (fin.get(num) ) // if it is end, break the loop 
	{
		//cout << "---1---" << endl ;
		if ( num == ' ' ||  num == '\t' || num == '\n' ) // skip white space 
		{
			//cout << "skip white space" << endl; 
			ck = fin.peek();
			while ( ck == ' ' || num == '\t' || num == '\n')  
			{
				//cout << "skip" << endl; 
				fin.get(num);
				ck = fin.peek();							
			}	
			fin.get(num);
			//cout << "num :" << num << endl; 
		}	
		isToken = false;
		// ---------------------------------------a Line-------------------------------------------------
		while ( num != '\n' && !fin.eof() ) // if is '\n' mean a sentence is end 
		{
			//cout << "---2---" << endl ;
			for ( int i = 0; i < 100 ; i++ ) temp[i] = '\0'; // initial temp
			//------------------------------------------a Token---------------------------------------------
			if ( ( num >= '0' && num <= '9' ) || ( num >= 'A' && num <= 'Z') || ( num >= 'a' && num <= 'z' ) )
			{
				isToken = true;
				//cout << "---3---" << endl ;
				temp[total] = num;
				total++;
				//cout << "---" << temp << "---" << endl ;
				ck = fin.peek() ; // check the next char
				while (  ( ck >= '0' && ck <= '9' ) || ( ck >= 'A' && ck <= 'Z') || ( ck >= 'a' && ck <= 'z' ) ) // find a token
				{
					//cout << "---token---" << endl ;
					fin.get(num);
					temp[total] = num;
					total++;
					ck = fin.peek();
					//cout << "---" << temp << "---" << endl ;
				}				
			} //if
			else if ( num == '[' ||  num == ']' ||  num == ',' ||  num == '+' ||  num == '-' ||  
					  num == '*' ||  num == '/' ||  num == ':' ||  num == ';' ||  num == '?' ||  
					  num == '(' ||  num == ')' ||  num == '\'' )
			{
				isToken = true;
				//cout << "---delimeter---" << endl ;
				temp[total] = num;	
				//cout << "===" << temp << "===" << endl;			
				if ( num == ';')  // if ck is ; then scanf the whole sentence
				{
					ck = fin.peek();
					while (ck != '\n') 
					{
						fin.get(num);
						ck = fin.peek();							
					}
				}
				else if ( num == '\'') 
				{
					//cout << "IN THE ELSE IF " << endl;
					list.push_back(listtemp) ; // add a vector list 
					for( int i = 0; i < 100 ; i++ )  list[linetoken].str[i] = temp[i] ; // save the token '
					list[linetoken].table = 4 ;
					list[linetoken].num = 13 ;
					for ( int i = 0; i < 100 ; i++ ) temp[i] = '\0'; // initial temp
					total = 0;
					linetoken++;
					ck = fin.peek();
					while ( ck != '\'' )
					{
						fin.get(num);
						temp[total] = num;
						total++;
						ck = fin.peek();
					}
					list.push_back(listtemp) ; // add a vector list 
					for( int i = 0; i < 100 ; i++ )  list[linetoken].str[i] = temp[i] ; // save the token ' 
					FindToken( temp, linetoken, true ); 
					total++;
					linetoken++;
					for ( int i = 0; i < 100 ; i++ ) temp[i] = '\0'; // initial temp
					total = 0;
					fin.get(num);					
					temp[total] = num;			
				}
			} //else if

			//------------------------------------------a Token---------------------------------------------
			//cout << "---4---" << endl;
			if (isToken )
			{
				list.push_back(listtemp) ; // add a vector list
				for( int i = 0; i < 100 ; i++ )  list[linetoken].str[i] = temp[i] ; // save the token  
				FindToken( temp, linetoken, false ); 
				//cout << "---5---" << endl;
				linetoken++;
			}
			ck = fin.peek();
			while (ck == ' ' || ck == '\t' )  // skip white space 
			{
				fin.get(num);
				ck = fin.peek();							
			}			
			total = 0;
			//cout << "end" <<endl;
			fin.get(num);
    		//cout << "num:" <<num <<endl;
		} // while 
		
		for ( int i = 0; i < list.size(); i++ ) fout << list[i].str << " " ; // print a line 
		fout << endl;
		for ( int i = 0; i < list.size(); i++ ) fout << "(" << list[i].table << "," << list[i].num << ")" ; // print the token (table,number)
		fout << endl;
		// ---------------------------------------a Line-------------------------------------------------
		list.clear();
		total = 0;
		linetoken = 0;
		
		
		
	}

	

	
	
} // InputFile

// ----------------------------Calculate Ascii Number-------------------------------------
int CalAsciiNum( string temp ) {
	
	int total = 0;
	int size = 0;
	size = strlen( temp.c_str() ) ;
	for ( int i = 0; i < size ; i++ )
	{
		total = total + temp[i] ;
	}
	
	total = total % 100;
	//cout << "temp :" << temp << endl;
	//cout << "---" << total << "---" << endl;
	return total;
	
} // CalAsciiNum()

// ----------------------------FindToken-------------------------------------

void FindToken( string temp, int total, bool isString ) {
	int number = 0;
	int tablenum = 0;
	//cout << "---InFindToken---" << endl;
	if ( Table1( temp, number) )
	{
		//cout << "---Table1---" << endl;
		list[total].table = 1 ;
		list[total].num = number ;
	}
	else if ( Table2( temp, number) )
	{
		//cout << "---Table2---" << endl;
		list[total].table = 2 ;
		list[total].num = number ;
	}
	else if ( Table3( temp, number) )
	{
		//cout << "---Table3---" << endl;
		list[total].table = 3 ;
		list[total].num = number ;		
	}
	else if ( Table4( temp, number) )
	{
		//cout << "---Table4---" << endl;
		list[total].table = 4 ;
		list[total].num = number ;		
	} 
	else      // identify Symbol, Interger, String 
	{
		
		if ( isString ) // is string in table 7
		{
			//cout << "isstring" << endl ;
			//cout << "temp :" << temp << endl;
			list[total].table = 7 ;
			tablenum = CalAsciiNum( temp ) ; // calculate ascii number
			if ( strcmp( global_Table7[tablenum], "0" ) == 0 ) //never impact before
			{
				list[total].num = tablenum ;
				strcpy(global_Table7[tablenum], temp.c_str());
				//cout << "if" << endl;
			}
			else if( strcmp( global_Table7[tablenum], temp.c_str() ) == 0 ) // is the same string. save in the same table
			{
				list[total].num = tablenum ;
				strcpy(global_Table7[tablenum], temp.c_str());
			}
			else
			{
				//cout << "in else" << endl;
				
				while( strcmp( global_Table7[tablenum], "0" ) != 0 && strcmp( global_Table7[tablenum], temp.c_str() ) != 0 ) {
					//cout << "+" ; 
					if (tablenum == 99) 
					{
						//cout << "in 99" << endl;
						tablenum = 0;
					}
					else 
					{
						//cout << "in while else" << endl;
						tablenum++;
					}
					//cout << "tablenum :" << tablenum << endl;
				}
				list[total].num = tablenum ;
				strcpy(global_Table7[tablenum], temp.c_str());
			}
		}
		else 
		{
			if ( temp[0] >= '0' && temp[0] <= '9' ) // is interger in table 6
			{
				list[total].table = 6 ;
				tablenum = CalAsciiNum( temp ) ; // calculate ascii number 
				
				if ( strcmp( global_Table6[tablenum], "0" ) == 0 ) //never impact before
				{
					list[total].num = tablenum ; 
					strcpy(global_Table6[tablenum], temp.c_str());
				}
				else if( strcmp( global_Table6[tablenum], temp.c_str() ) == 0 ) // is the same string. save in the same table
				{
					list[total].num = tablenum ;
					strcpy(global_Table6[tablenum], temp.c_str());
				}
				else
				{
					while( strcmp( global_Table6[tablenum], "0" ) != 0 && strcmp( global_Table6[tablenum], temp.c_str() ) != 0 ) {
						if (tablenum == 99) tablenum = 0;
						tablenum++; 
					}
					list[total].num = tablenum ;
					strcpy(global_Table6[tablenum], temp.c_str());
				}
			}
			else
			{
				list[total].table = 5 ;  // is symbol in table 5
				tablenum = CalAsciiNum( temp ) ; // calculate ascii number
				if ( strcmp( global_Table5[tablenum], "0" ) == 0 ) //never impact before
				{
					list[total].num = tablenum ; 
					strcpy(global_Table5[tablenum], temp.c_str());
				}
				else if( strcmp( global_Table5[tablenum], temp.c_str() ) == 0 ) // is the same string. save in the same table
				{
					list[total].num = tablenum ;
					strcpy(global_Table5[tablenum], temp.c_str());
				}
				else
				{
					while( strcmp( global_Table5[tablenum], "0" ) != 0 && strcmp( global_Table5[tablenum], temp.c_str() ) != 0 ) {
						if (tablenum == 99) tablenum = 0;
						tablenum++; 
					}
					list[total].num = tablenum ;
					strcpy(global_Table5[tablenum], temp.c_str());
				}
			}
		}
		
	} 
	
	
	//cout << "---end---" << endl;
	
	
	
	
	
} // FindToken()

// ----------------------------Table1-------------------------------------
bool Table1 ( string temp, int & number  ) {
	
	if ( strcmp ( temp.c_str(), "AAD" )  == 0 ) {
		number = 1;
		return true ;
	} // if 
	else if ( strcmp ( temp.c_str(), "AAM" )  == 0 ) {
		number = 2;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "AAA" )  == 0 ) {
		number = 3;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "AAS" )  == 0 ) {
		number = 4;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CBW" )  == 0 ) {
		number = 5;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CLC" )  == 0 ) {
		number = 6;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CLD" )  == 0 ) {
		number = 7;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CLI" )  == 0 ) {
		number = 8;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CMC" )  == 0 ) {
		number = 9;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CMPSB" )  == 0 ) {
		number = 10;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CMPSW" )  == 0 ) {
		number = 11;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CWD" )  == 0 ) {
		number = 12;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "DAA" )  == 0 ) {
		number = 13;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "DAS" )  == 0 ) {
		number = 14;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "FWAIT" )  == 0 ) {
		number = 15;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "HLT" )  == 0 ) {
		number = 16;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "INTO" )  == 0 ) {
		number = 17;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "IRET" )  == 0 ) {
		number = 18;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LAHF" )  == 0 ) {
		number = 19;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LOCK" )  == 0 ) {
		number = 20;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LODSB" )  == 0 ) {
		number = 21;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LODSW" )  == 0 ) {
		number = 22;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "MOVSB" )  == 0 ) {
		number = 23;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "MOVSW" )  == 0 ) {
		number = 24;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "NOP" )  == 0 ) {
		number = 25;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "POPF" )  == 0 ) {
		number = 26;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "PUSHF" )  == 0 ) {
		number = 27;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "REP" )  == 0 ) {
		number = 28;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "REPE" )  == 0 ) {
		number = 29;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "REPNE" )  == 0 ) {
		number = 30;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "REPNZ" )  == 0 ) {
		number = 31;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "REPZ" )  == 0 ) {
		number = 32;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SAHF" )  == 0 ) {
		number = 33;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SCASB" )  == 0 ) {
		number = 34;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SCASW" )  == 0 ) {
		number = 35;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "STC" )  == 0 ) {
		number = 36;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "STD" )  == 0 ) {
		number = 37;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "STI" )  == 0 ) {
		number = 38;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "STOSB" )  == 0 ) {
		number = 39;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "STOSW" )  == 0 ) {
		number = 40;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "WAIT" )  == 0 ) {
		number = 41;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "XLAT" )  == 0 ) {
		number = 42;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "PUSH" )  == 0 ) {
		number = 43;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "POP" )  == 0 ) {
		number = 44;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "RET" )  == 0 ) {
		number = 45;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "RETF" )  == 0 ) {
		number = 46;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "INT" )  == 0 ) {
		number = 47;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "IN" )  == 0 ) {
		number = 48;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "OUT" )  == 0 ) {
		number = 49;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JMP" )  == 0 ) {
		number = 50;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CALL" )  == 0 ) {
		number = 51;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JA" )  == 0 ) {
		number = 52;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JAE" )  == 0 ) {
		number = 53;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JB" )  == 0 ) {
		number = 54;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JBE" )  == 0 ) {
		number = 55;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JC" )  == 0 ) {
		number = 56;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JCXZ" )  == 0 ) {
		number = 57;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JE" )  == 0 ) {
		number = 58;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JG" )  == 0 ) {
		number = 59;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JGE" )  == 0 ) {
		number = 60;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JL" )  == 0 ) {
		number = 61;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JLE" )  == 0 ) {
		number = 62;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNA" )  == 0 ) {
		number = 63;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNAE" )  == 0 ) {
		number = 64;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNB" )  == 0 ) {
		number = 65;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNBE" )  == 0 ) {
		number = 66;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNC" )  == 0 ) {
		number = 67;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNE" )  == 0 ) {
		number = 68;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNG" )  == 0 ) {
		number = 69;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNGE" )  == 0 ) {
		number = 70;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNL" )  == 0 ) {
		number = 71;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNLE" )  == 0 ) {
		number = 72;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNO" )  == 0 ) {
		number = 73;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNP" )  == 0 ) {
		number = 74;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNS" )  == 0 ) {
		number = 75;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JNZ" )  == 0 ) {
		number = 76;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JO" )  == 0 ) {
		number = 77;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JP" )  == 0 ) {
		number = 78;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JPE" )  == 0 ) {
		number = 79;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JPO" )  == 0 ) {
		number = 80;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JS" )  == 0 ) {
		number = 81;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "JZ" )  == 0 ) {
		number = 82;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LOOP" )  == 0 ) {
		number = 83;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LOOPE" )  == 0 ) {
		number = 84;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LOOPNE" )  == 0 ) {
		number = 85;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LOOPNZ" )  == 0 ) {
		number = 86;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LOOPZ" )  == 0 ) {
		number = 87;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LDS" )  == 0 ) {
		number = 88;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LEA" )  == 0 ) {
		number = 89;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "LES" )  == 0 ) {
		number = 90;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "DEC" )  == 0 ) {
		number = 91;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "INC" )  == 0 ) {
		number = 92;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "ESC" )  == 0 ) {
		number = 93;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "DIV" )  == 0 ) {
		number = 94;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "IDIV" )  == 0 ) {
		number = 95;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "IMUL" )  == 0 ) {
		number = 96;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "MUL" )  == 0 ) {
		number = 97;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "NEG" )  == 0 ) {
		number = 98;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "NOT" )  == 0 ) {
		number = 99;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "RCL" )  == 0 ) {
		number = 100;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "RCR" )  == 0 ) {
		number = 101;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "ROL" )  == 0 ) {
		number = 102;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "ROR" )  == 0 ) {
		number = 103;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SAR" )  == 0 ) {
		number = 104;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SHL" )  == 0 ) {
		number = 105;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SHR" )  == 0 ) {
		number = 106;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "XCHG" )  == 0 ) {
		number = 107;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "TEST" )  == 0 ) {
		number = 108;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "MOV" )  == 0 ) {
		number = 109;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "ADC" )  == 0 ) {
		number = 110;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "ADD" )  == 0 ) {
		number = 111;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "AND" )  == 0 ) {
		number = 112;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "CMP" )  == 0 ) {
		number = 113;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "OR" )  == 0 ) {
		number = 114;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SBB" )  == 0 ) {
		number = 115;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "SUB" )  == 0 ) {
		number = 116;
		return true ;
	} // else if 
	else if ( strcmp ( temp.c_str(), "XOR" )  == 0 ) {
		number = 117;
		return true ;
	} // else if 
	else {
		return false ;
	} // else

} // Table1()

// ----------------------------Table2-------------------------------------
bool Table2 ( string temp, int & number ) {
	if ( strcmp( temp.c_str() , "CODE" ) == 0 ) {
		number = 1;
		return true;
  	} // if 
	else if ( strcmp( temp.c_str() , "SEGMENT" ) == 0 ) {
		number = 2;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "PROC" ) == 0 ) {
		number = 3;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "NEAR" ) == 0 ) {
		number = 4;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "ASSUME" ) == 0 ) {
		number = 5;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "ORG" ) == 0 ) {
		number = 6;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "DB" ) == 0 ) {
		number = 7;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "DW" ) == 0 ) {
		number = 8;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "EQU" ) == 0 ) {
		number = 9;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "ENDP" ) == 0 ) {
		number = 10;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "ENDS" ) == 0 ) {
		number = 11;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "END" ) == 0 ) {
		number = 12;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "WORD" ) == 0 ) {
		number = 13;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "BYTE" ) == 0 ) {
		number = 14;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "PTR" ) == 0 ) {
		number = 15;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "DUP" ) == 0 ) {
		number = 16;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "OFFSET" ) == 0 ) {
		number = 17;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "PUBLIC" ) == 0 ) {
		number = 18;
		return true;
  	} // if 
 	else if ( strcmp( temp.c_str() , "FAR" ) == 0 ) {
		number = 19;
		return true;
  	} // if 
	else {
		return false;
	}
 
} // Table2

// ----------------------------Table3-------------------------------------
bool Table3 ( string temp, int & number ) {
	if ( strcmp( temp.c_str(),  "AH" ) == 0 ) {
		number = 1;
		return true;
	} // if 
	else if ( strcmp( temp.c_str(),  "AL" ) == 0 ) {
		number = 2;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "AX" ) == 0 ) {
		number = 3;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "BH" ) == 0 ) {
		number = 4;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "BL" ) == 0 ) {
		number = 5;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "BX" ) == 0 ) {
		number = 6;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "CH" ) == 0 ) {
		number = 7;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "CL" ) == 0 ) {
		number = 8;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "CX" ) == 0 ) {
		number = 9;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "DH" ) == 0 ) {
		number = 10;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "DL" ) == 0 ) {
		number = 11;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "DX" ) == 0 ) {
		number = 12;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "SP" ) == 0 ) {
		number = 13;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "BP" ) == 0 ) {
		number = 14;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "SI" ) == 0 ) {
		number = 15;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "DI" ) == 0 ) {
		number = 16;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "ES" ) == 0 ) {
		number = 17;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "CS" ) == 0 ) {
		number = 18;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "SS" ) == 0 ) {
		number = 19;
		return true;
	} // else if 
	else if ( strcmp( temp.c_str(),  "DS" ) == 0 ) {
		number = 20;
		return true;
	} // else if 
	else {
		return false;
	} // else

} // Table3()

// ----------------------------Table4-------------------------------------
bool Table4 ( string temp, int & number ) {
	if ( strcmp( temp.c_str(), "[" ) == 0 ) {
		number = 1;
		return true;
	} // if 
	else if ( strcmp( temp.c_str(), "]" ) == 0 ) {
		number = 2;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "," ) == 0 ) {
		number = 3;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "+" ) == 0 ) {
		number = 4;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "-" ) == 0 ) {
		number = 5;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "*" ) == 0 ) {
		number = 6;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "/" ) == 0 ) {
		number = 7;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), ":" ) == 0 ) {
		number = 8;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), ";" ) == 0 ) {
		number = 9;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "?" ) == 0 ) {
		number = 10;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "(" ) == 0 ) {
		number = 11;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), ")" ) == 0 ) {
		number = 12;
		return true;
	} // else if
	else if ( strcmp( temp.c_str(), "'" ) == 0 ) {
		number = 13;
		return true;
	} // else if
	else {
		return false;
	} // else


} // Table4()






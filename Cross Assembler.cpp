#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <cstdlib> 
using namespace std;

struct listsize{
	char str[100] ;
	int table ;
	int num ;	
};
struct line{
	string sentence;
	string inputline;
};
char global_address[4]; // machine address
vector<listsize> list;
vector<line> slist;
line linetemp; 
vector<string> codenum; // machine code
listsize listtemp;
int global_line;
char global_Table5[100][100];
char global_Table6[100][100];
char global_Table7[100][100];
void InputFile( string & name ) ;
void SkipWS ( char & num ) ;
void GetTokoen( string temp, char num,int & casenum ) ;
void ADDaddress( int number) ; 
void Add( char &num )  ;
void RecordMC( string temp ) ;
void MovCase( string & str, bool word, int & MacNum ) ;
void Compaddress( string & callstring, string str1, string str2) ;
bool Table1 ( string temp, int & number );
bool Table2 ( string temp, int & number );
bool Table3 ( string temp, int & number );
bool Table4 ( string temp, int & number );
void FindToken( string temp, int total, bool isString );
int CalAsciiNum( string temp ) ;
string TenTo16num( int num ) ;

// ----------------------------main-------------------------------------
int main() {
  char num = '\0' ;
  int casenum = 0;
  global_line = 0;
  for ( int i = 0; i < 4; i++) //initial global address
  {
  	global_address[i] = '0';
  }

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
	ifstream input; 
	string tempp;
	bool havemov = false;
	bool haveword = false;
	char callfrom[4];
	char callto[4];
	bool end = false ;
	bool callcase = false;
	bool callfinish = false;
	string callstr = "";
	string callstring = "" ;
	int total = 0;
	string sentence;
	int tempnum = 0;
	int x = 0;
	int callline = 0;
	int MacNum = 0;
	string inputline;
	string outputname = "10627149_output.txt" ;
	char temp[100] ;
	char num = '\0';
	char ck = '\0'; // check next char 
	int casenum = 0;
	bool isToken = false;
	int linetoken = 0; // record how many token in a line
	for ( int i = 0; i < 4; i++) callfrom[i] = '0' ; // initial call address
	for ( int i = 0; i < 4; i++) callto[i] = '0' ; // initial call address	
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
	input.open( name.c_str() );
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
			
			//----------------------------------deal special label-----------------------------------------
				
			if ( strcmp(temp, "INT") == 0 )
			{
					x = codenum.size();
					codenum.push_back(tempp) ; // add a vector codenum
					codenum[x] = "CD" ;
			}
			
			
			if ( strcmp(temp, "RET") == 0 )
			{
					x = codenum.size();
					codenum.push_back(tempp) ; // add a vector codenum
					codenum[x] = "C3" ;
			}
			if ( strcmp(temp, "CALL") == 0 )
			{
					callcase = true;
					x = codenum.size();
					codenum.push_back(tempp) ; // add a vector codenum
					codenum[x] = "E8" ;
					MacNum = 2;
			}			
			if ( strcmp(temp, "END") == 0 ) end = true; 
			
			//----------------------------------deal special label-----------------------------------------
						
			total = 0;
			//cout << "end" <<endl;
			fin.get(num);
    		//cout << "num:" <<num <<endl;
		} // while 
		
		
		/*
		for ( int i = 0; i < list.size(); i++ ) cout << list[i].str << " " ; // print a line 
		cout << endl;
		for ( int i = 0; i < list.size(); i++ ) cout << "(" << list[i].table << "," << list[i].num << ")" ; // print the token (table,number)
		cout << endl;
		*/
		for ( int i = 0; i < list.size(); i++ ) 
		{
			if ( list[i].str == callstr  ) 
			{
				for ( int j = 0; j < 4; j++ ) callto[j] = global_address[j] ;
				callfinish = true;
			}
		}
		sentence = "" ;
		if ( global_line != 2 && global_line != 3 && !end)   // machine address
			for ( int i = 0; i < 4; i++ ) sentence = sentence + global_address[i] ;
		else 
			sentence = sentence + "    " ;
		sentence = sentence + "   " ;
		for ( int i = 0; i < list.size(); i++ ) 
		{
			if (strcmp(list[i].str, "MOV") == 0 ) havemov = true;
			if (strcmp(list[i].str, "WORD") == 0 ) haveword = true;
		}

		if ( havemov && haveword ) 
		{	
			sentence = sentence + "2E: " ;
			x = codenum.size();
			codenum.push_back(tempp) ; // add a vector codenum
			codenum[x] = " R" ;
		}	


		if ( havemov ) // calculate the machine code with MOV case
		{
			if ( haveword )  MovCase( sentence, true, MacNum ) ;
			else MovCase( sentence, false, MacNum ) ;
		}
		
		
			
		for ( int i =0; i < codenum.size(); i++ ) sentence = sentence + codenum[i][0] + codenum[i][1] + " " ;
		getline(input,inputline);
		x = slist.size();
		slist.push_back(linetemp) ; // add a vector codenum
		slist[x].sentence = sentence;
		slist[x].inputline = inputline;
		
		//fout << left << setw(32) << sentence ;
		//fout << inputline << endl ; // print a line 
		//cout << codenum.size() << endl;
		ADDaddress( codenum.size() + MacNum );
		
		if ( callcase )
		{
			for ( int i = 0; i < 4; i++ ) callfrom[i] = global_address[i] ;
			callstr = list[1].str ;
			callline = global_line;
			callcase = false;
		}
		
		
		/*
		for ( int i = 0; i < list.size(); i++ ) fout << list[i].str << " " ; // print a line 
		fout << endl;
		for ( int i = 0; i < list.size(); i++ ) fout << "(" << list[i].table << "," << list[i].num << ")" ; // print the token (table,number)
		fout << endl;
		*/
		
		
		
		
		
		// ---------------------------------------a Line-------------------------------------------------
		
	    //callcase = false;
	    //callstr = "";		
	    
	    if ( callfinish )
	    {
	    	callstring = "" ;
	    	tempnum = 0;
	        Compaddress( callstring, callfrom, callto ) ;
	    	callfinish = false;
	    	callstr = "";
			slist[callline].sentence = slist[callline].sentence + "00" + callstring[0] + callstring[1];
			
			/*
	    	for ( int i = 0; i < 32; i++ )
	    	{
	    		if ( slist[callline].sentence[i] == 'E' )
	    			if ( slist[callline].sentence[i+1] == '8' )
						tempnum = i + 2;
			}
			cout << tempnum;
			slist[callline].sentence[tempnum] = ' ';
			slist[callline].sentence[tempnum+1] = '0';
			slist[callline].sentence[tempnum+2] = '0';
			slist[callline].sentence[tempnum+3] = callstring[0];
			slist[callline].sentence[tempnum+4]	= callstring[1];
	    	cout << slist[callline].sentence;
	    	*/
		}
	    
		sentence = "" ;
		havemov = false;
		haveword = false;
		list.clear();
		codenum.clear();
		total = 0;
		linetoken = 0;
		global_line++;
		MacNum = 0;
		
	}

	for ( int i = 0; i < slist.size();i++ ) 
	{
		fout << left << setw(32) << slist[i].sentence ;
		fout << slist[i].inputline << endl ;
	}

	
	
} // InputFile

// ----------------------------Compare Address-------------------------------------
void Compaddress( string & callstring, string str1, string str2) { // global_address[0] is the first number  
// number is the count how many is the address need to add
	int num = 0;
	char ch = '\0';
	char ch1 = '\0';
	int carrynum = 0 ;
	int number = 0 ;
	while ( str1 != str2 )
	{

		// str1 add 1
		if ( str1[3] == 'F' ) // if the address need to carry the number
		{
			Add( str1[3] );
			if ( str1[2] == 'F' )
			{
				Add( str1[2] );
				if (str1[1] == 'F' )
				{
					Add( str1[1] );
					if ( str1[0] == 'F')
						Add( str1[0] );
				}
				else
				{
					Add( str1[1] );
				} 
			}
			else
			{
				Add( str1[2] );
			} 
		}
		else
		{
			Add( str1[3] );
		}
		
		num++;
		

	} // while()
	
	carrynum = num / 16 ;
	number = num % 16 ;
	if ( number == 0 ) ch1 = '0'; 
	else if ( number == 1 ) ch1 = '1';
	else if ( number == 2 ) ch1 = '2';
	else if ( number == 3 ) ch1 = '3';	
	else if ( number == 4 ) ch1 = '4';
	else if ( number == 5 ) ch1 = '5';
	else if ( number == 6 ) ch1 = '6';
	else if ( number == 7 ) ch1 = '7';
	else if ( number == 8 ) ch1 = '8';
	else if ( number == 9 ) ch1 = '9';		
	else if ( number == 10 ) ch1 = 'A';
	else if ( number == 11 ) ch1 = 'B';
	else if ( number == 12 ) ch1 = 'C';
	else if ( number == 13 ) ch1 = 'D';
	else if ( number == 14 ) ch1 = 'E';
	else if ( number == 15 ) ch1 = 'F';	

	if ( carrynum == 0 ) ch = '0';
	else if ( carrynum == 1 ) ch = '1';
	else if ( carrynum == 2 ) ch = '2';
	else if ( carrynum == 3 ) ch = '3';	
	else if ( carrynum == 4 ) ch = '4';
	else if ( carrynum == 5 ) ch = '5';
	else if ( carrynum == 6 ) ch = '6';
	else if ( carrynum == 7 ) ch = '7';
	else if ( carrynum == 8 ) ch = '8';
	else if ( carrynum == 9 ) ch = '9';		
	else if ( carrynum == 10 ) ch = 'A';
	else if ( carrynum == 11 ) ch = 'B';
	else if ( carrynum == 12 ) ch = 'C';
	else if ( carrynum == 13 ) ch = 'D';
	else if ( carrynum == 14 ) ch = 'E';
	else if ( carrynum == 15 ) ch = 'F';		
	
	
	callstring[0] = ch ;
	callstring[1] = ch1 ;
	callstring[2] = '\0';
	
	
	
}



// ----------------------------Mov Case-------------------------------------
void MovCase( string & str, bool word, int & MacNum ) { // deal mov code case
	int type1 = 0;
	int type2 = 0;
	int segnum = 0;
	int regnum = 0;
	bool w = false ; 
	bool immediate = false ;
	bool segment = false;
	for ( int i = 0; i < list.size(); i++ ) if ( list[i].table == 6 ) immediate = true ;
	for ( int i = 0; i < list.size(); i++ ) 
	{
		if ( strcmp( list[i].str, "DS") == 0 || strcmp( list[i].str, "CS") == 0 || strcmp( list[i].str, "SS") == 0 || strcmp( list[i].str, "ES") == 0 ) 
		{ 
			segment = true;
			segnum = i; 
		} 
	} 

	if ( strcmp( list[1].str, "AX") == 0 || strcmp( list[1].str, "CX") == 0 || strcmp( list[1].str, "DX") == 0 || strcmp( list[1].str, "BX") == 0 || 
		 strcmp( list[1].str, "SP") == 0 || strcmp( list[1].str, "BP") == 0 || strcmp( list[1].str, "SI") == 0 || strcmp( list[1].str, "DI") == 0 ) // mean WORD PTR -> memory to register or memory to accumulator
		w = true;

	if ( segnum == 1 ) regnum = 3; 
	else  regnum = 1;
	if ( word ) // mean WORD PTR -> memory to register or memory to accumulator
	{
		if ( strcmp( list[1].str, "AX") == 0 ) // deal memory to accumulator Case, for example: MOV AX,WORD PTR XXX 
		{
			str = str + "A1 0000"; 
			MacNum = 3;	
		}
		// W = 1
		else if ( strcmp( list[1].str, "CX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8B 0E 0000"; 
			MacNum = 4;			
		}
		else if ( strcmp( list[1].str, "DX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8B 16 0000"; 
			MacNum = 4;			
		}		
		else if ( strcmp( list[1].str, "BX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8B 1E 0000"; 
			MacNum = 4;			
		}		
		else if ( strcmp( list[1].str, "SP") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8B 26 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "BP") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8B 2E 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "SI") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8B 36 0000"; 
			MacNum = 4;			
		}		
		else if ( strcmp( list[1].str, "DI") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8B 3E 0000"; 
			MacNum = 4;			
		}	
		// W = 0
		else if ( strcmp( list[1].str, "AL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 06 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "CL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 0E 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "DL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 16 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "BL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 1E 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "AH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 26 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "CH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 2E 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "DH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 36 0000"; 
			MacNum = 4;			
		}			
		else if ( strcmp( list[1].str, "BH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
		{
			str = str + "8A 3E 0000"; 
			MacNum = 4;			
		}				
		
	}
	else // mean without WORD PTR -> immediate to register or register to register
	{
		
		if( immediate ) // mean without WORD PTR -> immediate to register
		{
			// W = 1
			if ( strcmp( list[1].str, "AX") == 0 ) // deal memory to accumulator Case, for example: MOV AX,WORD PTR XXX 
			{
				str = str + "B8 "; 
				MacNum = 1;		
			}
			else if ( strcmp( list[1].str, "CX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B9 "; 
				MacNum = 1;			
			}
			else if ( strcmp( list[1].str, "DX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "BA "; 
				MacNum = 1;			
			}		
			else if ( strcmp( list[1].str, "BX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "BB "; 
				MacNum = 1;			
			}		
			else if ( strcmp( list[1].str, "SP") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "BC "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "BP") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "BD "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "SI") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "BE "; 
				MacNum = 1;			
			}		
			else if ( strcmp( list[1].str, "DI") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "BF "; 
				MacNum = 1;			
			}	
			// W = 0
			else if ( strcmp( list[1].str, "AL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B0 "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "CL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B1 "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "DL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B2 "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "BL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B3 "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "AH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B4 "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "CH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B5 "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "DH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B6 "; 
				MacNum = 1;			
			}			
			else if ( strcmp( list[1].str, "BH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "B7 "; 
				MacNum = 1;			
			}			
				
		}
		else if ( segment )
		{
			if ( segnum == 1 ) // mean MOV segment, register
				str = str + "8E "; 
			else // mean MOV register, segment
				str = str + "8C ";
			if ( strcmp( list[segnum].str, "ES") == 0 ) // deal memory to accumulator Case, for example: MOV AX,WORD PTR XXX 
			{
				str = str + "C"; 
				MacNum = 2;		
			}
			else if ( strcmp( list[segnum].str, "CS") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "C"; 
				MacNum = 2;			
			}
			else if ( strcmp( list[segnum].str, "SS") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "D"; 
				MacNum = 2;			
			}		
			else if ( strcmp( list[segnum].str, "DS") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				str = str + "D"; 
				MacNum = 2;			
			}				
			
			
			// W = 1
			if ( strcmp( list[regnum].str, "AX") == 0 ) // deal memory to accumulator Case, for example: MOV AX,WORD PTR XXX 
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "8 "; 
				else
					str = str + "0 ";
			}
			else if ( strcmp( list[regnum].str, "CX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "9 "; 
				else
					str = str + "1 ";		
			}
			else if ( strcmp( list[regnum].str, "DX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "A "; 
				else
					str = str + "2 ";	
			}		
			else if ( strcmp( list[regnum].str, "BX") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "B "; 
				else
					str = str + "3 ";		
			}		
			else if ( strcmp( list[regnum].str, "SP") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "C "; 
				else
					str = str + "4 ";		
			}			
			else if ( strcmp( list[regnum].str, "BP") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "D "; 
				else
					str = str + "5 ";		
			}			
			else if ( strcmp( list[regnum].str, "SI") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "E "; 
				else
					str = str + "6 ";		
			}		
			else if ( strcmp( list[regnum].str, "DI") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "F "; 
				else
					str = str + "7 ";		
			}	
			// W = 0
			else if ( strcmp( list[regnum].str, "AL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "8 "; 
				else
					str = str + "0 ";			
			}			
			else if ( strcmp( list[regnum].str, "CL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "9 "; 
				else
					str = str + "1 ";		
			}			
			else if ( strcmp( list[regnum].str, "DL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "A "; 
				else
					str = str + "2 ";		
			}			
			else if ( strcmp( list[regnum].str, "BL") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "B "; 
				else
					str = str + "3 ";		
			}			
			else if ( strcmp( list[regnum].str, "AH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "C "; 
				else
					str = str + "4 ";			
			}			
			else if ( strcmp( list[regnum].str, "CH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "D "; 
				else
					str = str + "5 ";		
			}			
			else if ( strcmp( list[regnum].str, "DH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "E "; 
				else
					str = str + "6 ";		
			}			
			else if ( strcmp( list[regnum].str, "BH") == 0 )// deal memory to register Case, for example: MOV DX,WORD PTR XXX
			{
				if ( strcmp( list[segnum].str, "DS") == 0 || strcmp( list[segnum].str, "CS") == 0 )
					str = str + "F "; 
				else
					str = str + "7 ";		
			}						
		
		}
		
		
		else // mean without WORD PTR -> register to register
		{
			if ( w ) str = str + "8B ";
			else str = str + "8A ";
			MacNum = 2;
			if ( strcmp( list[1].str, "AX") == 0 || strcmp( list[1].str, "CX") == 0 || strcmp( list[1].str, "AL") == 0 || strcmp( list[1].str, "CL") == 0 )
				str = str + "C";
			else if ( strcmp( list[1].str, "DX") == 0 || strcmp( list[1].str, "BX") == 0 || strcmp( list[1].str, "DL") == 0 || strcmp( list[1].str, "BL") == 0 )
				str = str + "D";
			else if ( strcmp( list[1].str, "SP") == 0 || strcmp( list[1].str, "BP") == 0 || strcmp( list[1].str, "AH") == 0 || strcmp( list[1].str, "CH") == 0 )
				str = str + "E";
			else if ( strcmp( list[1].str, "SI") == 0 || strcmp( list[1].str, "DI") == 0 || strcmp( list[1].str, "DH") == 0 || strcmp( list[1].str, "BH") == 0 )
				str = str + "F";			
			
			// if the first num = 0
			if ( strcmp( list[1].str, "AL") == 0 || strcmp( list[1].str, "CX") == 0 || strcmp( list[1].str, "DL") == 0 || strcmp( list[1].str, "DX") == 0 ||
			  	 strcmp( list[1].str, "AH") == 0 || strcmp( list[1].str, "SP") == 0 || strcmp( list[1].str, "DH") == 0 || strcmp( list[1].str, "SI") == 0 )
			{
				if ( strcmp( list[3].str, "AX") == 0 || strcmp( list[3].str, "AL") == 0 )
					str = str + "0 ";
				else if ( strcmp( list[3].str, "CL") == 0 || strcmp( list[3].str, "CX") == 0 )
					str = str + "1 ";
				else if ( strcmp( list[3].str, "DL") == 0 || strcmp( list[3].str, "DX") == 0 )
					str = str + "2 ";
				else if ( strcmp( list[3].str, "BL") == 0 || strcmp( list[3].str, "BX") == 0 )
					str = str + "3 ";
				else if ( strcmp( list[3].str, "AH") == 0 || strcmp( list[3].str, "SP") == 0 )
					str = str + "4 ";
				else if ( strcmp( list[3].str, "CH") == 0 || strcmp( list[3].str, "BP") == 0 )
					str = str + "5 ";
				else if ( strcmp( list[3].str, "DH") == 0 || strcmp( list[3].str, "SI") == 0 )
					str = str + "6 ";
				else if ( strcmp( list[3].str, "BH") == 0 || strcmp( list[3].str, "DI") == 0 )
					str = str + "7 ";				
					
			}
			//if the first num = 1
			else
			{
				if ( strcmp( list[3].str, "AX") == 0 || strcmp( list[3].str, "AL") == 0 )
					str = str + "8 ";
				else if ( strcmp( list[3].str, "CL") == 0 || strcmp( list[3].str, "CX") == 0 )
					str = str + "9 ";
				else if ( strcmp( list[3].str, "DL") == 0 || strcmp( list[3].str, "DX") == 0 )
					str = str + "A ";
				else if ( strcmp( list[3].str, "BL") == 0 || strcmp( list[3].str, "BX") == 0 )
					str = str + "B ";
				else if ( strcmp( list[3].str, "AH") == 0 || strcmp( list[3].str, "SP") == 0 )
					str = str + "C ";
				else if ( strcmp( list[3].str, "CH") == 0 || strcmp( list[3].str, "BP") == 0 )
					str = str + "D ";
				else if ( strcmp( list[3].str, "DH") == 0 || strcmp( list[3].str, "SI") == 0 )
					str = str + "E ";
				else if ( strcmp( list[3].str, "BH") == 0 || strcmp( list[3].str, "DI") == 0 )
					str = str + "F ";				
			}
			
		}
		
		
	}
//	list[i].table;
	
	
	
	
	
	
	
	
	
	
}




// ----------------------------ADD Machine Address-------------------------------------
void ADDaddress( int number) { // global_address[0] is the first number  
// number is the count how many is the address need to add
	while ( number > 0 )
	{
		if ( global_address[3] == 'F' ) // if the address need to carry the number
		{
			Add( global_address[3] );
			if ( global_address[2] == 'F' )
			{
				Add( global_address[2] );
				if (global_address[1] == 'F' )
				{
					Add( global_address[1] );
					if ( global_address[0] == 'F')
						Add( global_address[0] );
				}
				else
				{
					Add( global_address[1] );
				} 
			}
			else
			{
				Add( global_address[2] );
			} 
		}
		else
		{
			Add( global_address[3] );
		}
		
		
		
		number--;
	} // while()
	
	
	
}

// ---------------------------Record Machine Code-------------------------------------
void RecordMC( string temp ) {
	
	int size = 0;
	string stemp = "";
	size = strlen( temp.c_str() ) ;
	int num = 0;
	int codesize = codenum.size();
	for ( int i = 0; i < size ; i++)
	{
		codenum.push_back(stemp) ; // add a vector codenum
		num =  temp[i];
		//cout << "num : " << num << endl;
		codenum[codesize+i] = TenTo16num(num).c_str() ;

	}
}


string TenTo16num( int num ) {
	string ans = "" ;
	char ch = '\0';
	char ch1 = '\0';
	int carrynum = 0 ;
	int number = 0 ;
	carrynum = num / 16 ;
	//cout << "carry : " << carrynum << endl;
	number = num % 16 ;
	//cout << "number : " << number << endl;
	if ( number == 0 ) ch1 = '0'; 
	else if ( number == 1 ) ch1 = '1';
	else if ( number == 2 ) ch1 = '2';
	else if ( number == 3 ) ch1 = '3';	
	else if ( number == 4 ) ch1 = '4';
	else if ( number == 5 ) ch1 = '5';
	else if ( number == 6 ) ch1 = '6';
	else if ( number == 7 ) ch1 = '7';
	else if ( number == 8 ) ch1 = '8';
	else if ( number == 9 ) ch1 = '9';		
	else if ( number == 10 ) ch1 = 'A';
	else if ( number == 11 ) ch1 = 'B';
	else if ( number == 12 ) ch1 = 'C';
	else if ( number == 13 ) ch1 = 'D';
	else if ( number == 14 ) ch1 = 'E';
	else if ( number == 15 ) ch1 = 'F';	

	if ( carrynum == 0 ) ch = '0';
	else if ( carrynum == 1 ) ch = '1';
	else if ( carrynum == 2 ) ch = '2';
	else if ( carrynum == 3 ) ch = '3';	
	else if ( carrynum == 4 ) ch = '4';
	else if ( carrynum == 5 ) ch = '5';
	else if ( carrynum == 6 ) ch = '6';
	else if ( carrynum == 7 ) ch = '7';
	else if ( carrynum == 8 ) ch = '8';
	else if ( carrynum == 9 ) ch = '9';		
	else if ( carrynum == 10 ) ch = 'A';
	else if ( carrynum == 11 ) ch = 'B';
	else if ( carrynum == 12 ) ch = 'C';
	else if ( carrynum == 13 ) ch = 'D';
	else if ( carrynum == 14 ) ch = 'E';
	else if ( carrynum == 15 ) ch = 'F';	
	//cout << "ch = " << ch << "ch1 = " << ch1 << endl; 
	ans[0] = ch ;
	ans[1] = ch1;
	ans[2] = '\0' ;

	return ans; 
}

// ----------------------------ADD Address-------------------------------------
void Add( char & num )  {
	if ( num == '0' ) num = '1';
	else if ( num == '1' ) num = '2';	
	else if ( num == '2' ) num = '3';
	else if ( num == '3' ) num = '4';	
	else if ( num == '4' ) num = '5';	
	else if ( num == '5' ) num = '6';	
	else if ( num == '6' ) num = '7';	
	else if ( num == '7' ) num = '8';	
	else if ( num == '8' ) num = '9';	
	else if ( num == '9' ) num = 'A';	
	else if ( num == 'A' ) num = 'B';	
	else if ( num == 'B' ) num = 'C';	
	else if ( num == 'C' ) num = 'D';
	else if ( num == 'D' ) num = 'E';
	else if ( num == 'E' ) num = 'F';
	else if ( num == 'F' ) num = '0';

}
 

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
	string stemp = "";
	string inttemp = "";
	int j = 0;
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
			RecordMC(temp);
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
				if ( global_line > 3)
				{
					//for(int i = 0;i < strlen(temp.c_str())-1;i++ ) inttemp[i] = temp[i] ;  
					inttemp= temp;

					for ( int i = 0; i < strlen(inttemp.c_str()) ; i++ ) if ( inttemp[i] == 'H') inttemp[i] = '\0'  ;
					j = codenum.size();
					codenum.push_back(stemp) ; // add a vector codenum
					codenum[j] = inttemp ;
				}
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






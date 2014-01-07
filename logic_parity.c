/*  logic_parity
 *  Universita degli Studi di Urbino "Carlo Bo" Corso di Laurea in Informatica Applicat
 *
 *  Copyright (c) 2013 Julian Sparber <julian@sparber.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
#include <stdio.h>

#define true 1
#define false 0
#define LIMIT 15

typedef  struct{
	char name;
	int value;
	int not;
} fun;

int clearBuffer();
int getInput(fun[]);
int insertMem(fun [], char, int);
int validateInput(char, int);
int calcCase(fun[], int);
int profEquality(fun[]);
int printMem(fun[]);
int genValues(int, int);
int powerTwo(int);
int insertValues(fun[], int);
int profValues(fun[]);
int calcResult(fun[], int, int);
int boolCalc(int, int, int);

int main(){
	fun data[LIMIT+1]; 

	getInput(data);

	if ( profEquality(data) )
		printf("True\n");
	else
		printf("False\n");
	return 0;
}

int getInput(fun mem[]){
	int i = 0;
	int error = true;
	int second_formula = false;
	char cache = '1';
	while ( error || !second_formula ){
		/* Try, Clear all*/
		error = false;
		second_formula = false;
		i = 0;
		cache = '1';
		printf("Please type the logical formula\n" );
		while ( !error && i < LIMIT &&  cache != '\n' ){
			cache = getchar();
				error = validateInput(cache, i);
				if ( cache == '5' ){
					second_formula = true;
				}
				if ( cache == '\n' && i%2 == 0  ){
					error = true;
				}
				if ( !error ){
					if ( cache == '0' ){
						mem[i].not = true;
						cache = getchar();
					}
					else
						mem[i].not = false;
					
					error = insertMem(mem, cache, i);
					mem[LIMIT].value = ( i + 1 ) / 2;
					i++;
				}
		}
		if ( error || !second_formula || i >= LIMIT ){
			printf("Please type a corect formula\n");
			error = true;
			if ( cache != '\n' ){
					clearBuffer();
			}
		}

	}
	return error;
}

int clearBuffer(){
		if ( getchar() != '\n' )
				clearBuffer();
		return 0;
}

int validateInput(char cache, int i){
	int error = true;
	if ( i%2 == 0 ){
		if ( (cache >= 'A' && cache <= 'Z') || cache == '0' ){
			error = false;
		}
		else
			error = true;
	}
	else{
		if ( cache >= '1' && cache <= '5' ){
			error = false;
		}
		else
			error = true;
	}
	if ( cache == '\n' )
		error = false;
	return error;
}

int insertMem(fun mem[], char cache, int i){
	if ( i%2 == 0 ){
		mem[i].name = cache;
		mem[i].value = 0;
	}
	else{
		mem[i].name = cache;
		mem[i].value = (int)(cache - '0');
	}
	return 0;
}
int profEquality(fun mem[]){
	int  equal = true;
	int i = 0;
	while ( equal && i < mem[LIMIT+1].value  ){
		if ( calcCase(mem, i) ){
			equal = true;
			i++;
		}
		else
			equal = false;
	}
	return equal;
}
int calcCase(fun mem[], int line){
	int res = 0;
	insertValues(mem, line);
	profValues(mem);
	res = calcResult(mem, 0, LIMIT);
	return res;
}

int profValues(fun mem[]){
	int i = 0;
	int j = 2;
	while ( mem[i+1].name != '\n' ){
		while ( mem[j-1].name != '\n' ){
			if ( mem[i].name == mem[j].name ){
				mem[j].value = mem[i].value;
			}
			j += 2;
		}
		j = 0;
		i += 2;
	}

	i = 0;
	while ( mem[i-1].name != '\n' ){
		if ( mem[i].not == true ){
			mem[i].value = !mem[i].value;
		}
		i += 2;
	}
	return 0;
}
int calcResult(fun mem[], int start, int end){
	int ris;
	int pos = 0;
	int j = start;
	int level = 0;

	if ( mem[start+1].name == '\n' || end == 0 || end == start ){
		ris = mem[start].value;		
	}      
	else{
		while( j < end && mem[j+1].name != '\n' ){
			if ( level < mem[j+1].value ){
				level = mem[j+1].value;
				pos = j + 1;
			}
			j += 2;
		}
		ris = boolCalc(calcResult(mem, start, pos-1), mem[pos].value, calcResult(mem, pos+1, end));
	}
	return ris;
}
int boolCalc(int a, int op, int b){
	int res = 0;;
	switch (op){
		case 1:
			res = a && b;
			break;
		case 2:
			res = a || b;
			break;
		case 3:
			res = (!a) || b;
			break;
		case 4: 
			res = ( ( !a ) && ( !b ) ) || ( a && b );
			break;
		case 5:
			res = ( ( !a ) && ( !b ) ) || ( a && b );
			break;

	}	
	return res;
}
int insertValues(fun mem[], int line){
	int n = 0;
	while ( n < LIMIT && mem[n-1].name != '\n' && mem[n-1].name != '\n' ){
		mem[n].value = genValues(line, n/2);
		n +=2;
	}
	return 0;
}

int genValues(int line, int col){
	int i = 0;
	int j = 0;
	int ris = false;
	while ( i < line ){
		if ( j == (powerTwo(col) - 1) ){
			j = 0;
			ris = !ris;
		}
		else{
			j++;
		}
		i++;
	}
	return ris;
}

int powerTwo(int x){
	int ris;
	if ( x == 0 )
		ris = 1;
	else
		ris = powerTwo(x-1) * 2;
	return ris;
}
int printMem(fun mem[]){
	int i = 0;
	while ( i < LIMIT && mem[i].name != '\n' ) {
		printf("%d", mem[i].value);
		i++;
	}
	printf("\n");
	return 0;
}

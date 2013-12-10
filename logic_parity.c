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
#define LIMIT 10
typedef enum{
	not,
	or,
	and,
	ifthen,
	iff
} logic;
typedef  struct{
	char name;
	int value;
	int not;
	} fun;

int getInput(fun[]);
int insertMem(fun [], char, int);
int validateInput(char, int);
int main(){
	fun data[LIMIT]; 
	int i = 0;
	getInput(data);
	while ( i < LIMIT && data[i].value != (int)( '\n' - '0' )){
			printf("%c", data[i].name);
		i++;
	}
	printf("\n");	
	return 0;
}
int getInput(fun mem[]){
	int i = 0;
	int error = true;
	char cache;
	while ( error ){
		/* New Try, Clear Error*/
		error = false;
		printf("Please type the logical formel \n" );
		while ( !error && i < LIMIT &&  cache != '\n' ){
			scanf("%c", &cache);
				error = validateInput(cache, i);
				if ( cache == '\n' && validateInput(mem[i-1].name, i-1)){
					error = true;
				}
				if ( !error ){
					if ( cache == '0' ){
						mem[i].not = true;
						scanf("%c", &cache);
					}
					else
						mem[i].not = false;
					
					error = insertMem(mem, cache, i);
					i++;
				}
				if ( error ){
					printf("Please type a corect formel\n");
					i = 0;
				}
		}
	}
	return error;
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
		if ( cache >= '1' && cache <= '3' ){
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

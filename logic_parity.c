/*  logic_parity
 *  Universita degli Studi di Urbino "Carlo Bo" Corso di Laurea in Informatica Applicat
 *
 *  Copyright (c) 2013 Julian Sparber <julian@sparber.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
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
	char prop;
	int value;
	int not;
	} fun;

int getInput(fun[]);

int main(){
	fun data[LIMIT]; 
	int i = 0;
	getInput(data);
	while ( i < LIMIT && data[i].value != (int)( '\n' - '0' )){
		if ( i%2 == 0 )
			printf("%c", data[i].prop);
		else
			printf("%d", data[i].value);
		i++;
	}
	printf("\n");	
	return 0;
}
int getInput(fun input[]){
	int i = 0;
	fun tmp;
	int error = 0;
	char cache;
	printf("Please type the logical formel \n" );
	while ( !error && i < LIMIT &&  cache != '\n' ){
		scanf("%c", &cache);
			if ( i%2 == 0 ){
				if ( cache == '0' ){
					input[i].not = true;
				}
				else if ( cache >= 'A' && cache <= 'Z' ){
					input[i].value = true;
					input[i].prop = cache;
					if ( i > 2 && input[i-1].value < input[i-3].value ){
						tmp = input[i];
						input[i] = input[i-4];
						input[i-4] = tmp;
						tmp = input[i-1];
						input[i-1] = input[i-3];
						input[i-3] = tmp;
					}
					i++;
				}
				else{
					error += 1;
					i = 0;
					}
			}
			else if ( cache < 'A' || cache > 'Z' ){
				input[i].value = (int)(cache -'0');
				i++;
			
			}
			else{
				error += 1;
				i = 0;
			}
	}
	return error;
}

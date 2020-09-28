#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

int main(){
	int i = 4079;
	char cmd[15] = "kill ";
	while(i <= 4334){
		string k = to_string(i);
		cmd[5] = k;
		system(cmd);	
		i++;
	}
}

#include "Shell.h"

int main(){
    while(1){
        printf("\033[37;42m>>>\033[0m");
        running();
    }
    return 0;
}
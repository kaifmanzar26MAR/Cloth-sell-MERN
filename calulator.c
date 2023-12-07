#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void resizearr(char *arr[], int i, int ct) {
    for (int j = i; j < ct; j++) {
        arr[j] = arr[j + 1];
    }
}

char *solve(char *s) {
    int ct = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') ct++;
    }
    ct = 2 * ct;

    char *arr[ct + 1];
    int j = 0;
    int st = 0;
    int flag=0;
    for (int i = 0; i <= strlen(s); i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '\0') {
            if(s[i+1] == '+' || s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/' || s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/'){
                return "invalid";
            }
            char str[i - st + 2];
            strncpy(str, s + st-flag, i - st+flag);
            str[i - st+flag] = '\0';
            arr[j++] = strdup(str);
            // printf("%s ",arr[j-1]);

            if (s[i] != '\0') {
                if(s[i]=='-'){
                    flag=1;
                }else{
                    flag=0;
                }
                char opchar[2];
                if(flag==0)
                    opchar[0] = s[i];
                else opchar[0]='+';

                opchar[1] = '\0';
                arr[j++] = strdup(opchar);  
            }

            st = i + 1;
        }
    }

    char op[] = "/*+-";
    j = 0;
    for(int n=0;n<=ct;n++){
        printf("%s ",arr[n]);
    }printf("\n");
    while (j < 4) {
        char operator = op[j];
        for (int x = 0; x < ct + 1; x++) {
            
            char sss=arr[x][0];
            // printf("%c j",sss);
            if (sss==operator) {
                if (x == 0 || x == ct) {
                    return "not valid input 1  ";
                }

                char *s1 = arr[x - 1];
                if (s1[0] == '+' || s1[0] == '*' || s1[0] == '/') {
                    return "not valid input 2";
                }

                char *s2 = arr[x + 1];
                if (s2[0] == '+' || s2[0] == '*' || s2[0] == '/') {
                    return "not valid input 3";
                }

                int a = atoi(s1);
                int b = atoi(s2);
                int c = 0;

                switch (operator) {
                    case '/':
                        c = a / b;
                        break;
                    case '+':
                        c = a + b;
                        break;
                    case '-':
                        c = a - b;
                        break;
                    case '*':
                        c = a * b;
                        break;
                }

                char str[50];
                snprintf(str, sizeof(str), "%d", c);
                arr[x + 1] = strdup(str);

                free(s1);
                free(s2);

                resizearr(arr, x - 1, ct);
                ct--;
                resizearr(arr, x - 1, ct);
                ct--;
                for(int n=0;n<=ct;n++){
                    printf("%s ",arr[n]);
                }printf("\n");
                if(ct==0){
                    return arr[0];
                }

                x--;
            }
        }
        j++;
    }

    return arr[0];
}

int main() {
    char input[] = "10-40+20";
    char *result = solve(input);
    printf("Result: %s\n", result);

    return 0;
}

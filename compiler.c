#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "while", "for",
    "do", "return", "void", "switch", "case", "break", "continue",
    "default", "struct", "typedef", "static", "const"
};
int keywordCount = sizeof(keywords) / sizeof(keywords[0]);
int isKeyword(const char *str) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == '=' || ch == '<' || ch == '>' || ch == '!');
}
int isDelimiter(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n' || ch == ';' ||
            ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}');
}
void lexicalAnalysis(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file!\n");
        exit(1);
    }
    char token[100];
    int i = 0;
    char ch;
    printf("\n--- Lexical Analysis Output ---\n");
    while ((ch = fgetc(fp)) != EOF) {
        if (isDelimiter(ch)) {
            if (i != 0) {
                token[i] = '\0';
                if (isKeyword(token))
                    printf("<KEYWORD, %s>\n", token);
                else
                    printf("<IDENTIFIER, %s>\n", token);
                i = 0;
            }
        }
        else if (isOperator(ch)) {
            if (i != 0) {
                token[i] = '\0';
                if (isKeyword(token))
                    printf("<KEYWORD, %s>\n", token);
                else
                    printf("<IDENTIFIER, %s>\n", token);
                i = 0;
            }
            printf("<OPERATOR, %c>\n", ch);
        }
        else {
            token[i++] = ch;
        }
    }
    if (i != 0) {
        token[i] = '\0';
        if (isKeyword(token))
            printf("<KEYWORD, %s>\n", token);
        else
            printf("<IDENTIFIER, %s>\n", token);
    }

    fclose(fp);
}
int main() {
    char filename[100];
    printf("Enter input file name: ");
    scanf("%s", filename);
    lexicalAnalysis(filename);
    return 0;
}

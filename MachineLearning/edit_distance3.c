#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
 
int levenshtein(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++){
        matrix[x][0] = matrix[x-1][0] + 1;
        printf("x=%d\n",x);
    }
    for (y = 1; y <= s1len; y++){
        matrix[0][y] = matrix[0][y-1] + 1;
        printf("y=%d\n",y);
    }
    for (x = 1; x <= s2len; x++){
        for (y = 1; y <= s1len; y++){
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
            printf("return_min_of_three:matrix[%d][%d]:%d\n",x,y,matrix[x][y] );
            printf("return_min_of_three%d\n",matrix[x][y] );
        }
    }
    return(matrix[s2len][s1len]);
}
int main (int argc,char *argv[]){

    printf("%d\n",  levenshtein(argv[1], argv[2]));
        return 0;
}
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define k 1
#define FILENAME "hyakuninisshu.dat"
#define MAX_STRINGS 256


//3つの引数で一番小さいものを返す
long return_min_of_three(long a,long b,long c){
	long tmp_min=a;
	if(tmp_min>b) tmp_min=b;
	if(tmp_min>c) tmp_min=c;
	return tmp_min;
}

//二つの引数の文字が一致すれば１、一致しなければ０
long delta(char word1,char word2){
	if (word1==word2) {
		return 1;
	}else {
		return 0;
	}

}

//編集距離を返す関数
long get_edit_distance(char *word1, char *word2) {
	unsigned long word1_count, word2_count;
	long word1len = strlen(word1);
	long word2len = strlen(word2);
	unsigned long matrix[word2len+1][word1len+1];

    //matrixはレジュメでのT,word1_countはi,word2_countはj
	matrix[0][0] = 0;
	for (word1_count = 1; word1_count <= word2len; word1_count++){
		//printf("word1_count=%ld\n",word1_count );
		matrix[word1_count][0] = matrix[word1_count-1][0] + 1;
	}

	for (word2_count = 1; word2_count <= word1len; word2_count++){
		//printf("word2_count=%ld\n",word2_count );
		matrix[0][word2_count] = matrix[0][word2_count-1] + 1;
	}

	for (word1_count = 1; word1_count <=word2len; word1_count++){
		for (word2_count = 1; word2_count<=word1len; word2_count++){
			//printf("return_min_of_three:matrix[%ld][%ld]:%ld\n",word1_count,word2_count,matrix[word1_count][word2_count] );
			matrix[word1_count][word2_count] = return_min_of_three(matrix[word1_count-1][word2_count] + 1, matrix[word1_count][word2_count-1] + 1, matrix[word1_count-1][word2_count-1] +k*(+1 -delta(word1[word2_count-1],word2[word1_count-1])) );
			//printf("return_min_of_three%ld\n",matrix[word1_count][word2_count] );

		}
	}
	return(matrix[word2len][word1len]);
}


int main(int argc,char *argv[]){
	char *word1=argv[1];
	char *word2=argv[2];

    FILE *fp;
    char *hyakuninisshu[MAX_STRINGS][MAX_STRINGS];
    if ((fp = fopen(FILENAME, "r")) == NULL)
    {
        printf("ファイルのオープンに失敗しました。プログラムを終了します。\n");
        exit(1);
    }

    char buf[MAX_STRINGS];
    int i=0;
    while( fgets(buf,MAX_STRINGS,fp) != NULL ){
            sprintf(hyakuninisshu[i],"%s",buf );
            i++;
        }

       for(int j=0;j<i-1;j++){
    	printf("%d:%s",j,hyakuninisshu[j] );
    }

 
    fclose(fp);
    //hyakuninisshu[i]とhyakuninisshu[j]について10C2回編集距離を測る
    for(int i=0;i<10;i++){
    	
    	for(int j=i+1;j<10;j++){
    		//printf("i:%d->%sj:%d->%s\n",i,hyakuninisshu[i],j,hyakuninisshu[j] );
    		long edit_distance=get_edit_distance(hyakuninisshu[i],hyakuninisshu[j]);
    		printf("%ld,",edit_distance);
    	}
    	printf("\n");
    }
	return 0;


}

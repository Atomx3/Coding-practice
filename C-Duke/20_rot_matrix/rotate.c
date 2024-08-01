
void rotate(char matrix[10][10]){
    char matrixN[10][10];
   
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrixN[i][j] = matrix[9-j][i]; 
        }
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrix[i][j]= matrixN[i][j];
        }
    }
}
/*
// pointers for the same function purpose.
void rotate(char (*matrix)[10]) {
    char matrixN[10][10];

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrixN[i][j] = matrix[9 - j][i];
        }
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrix[i][j] = matrixN[i][j];
        }
    }
}*/

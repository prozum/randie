#include "matrix_test.h"
#include <stdlib.h>

double **ma1, **ma2, **ma3, vec1[3] = {1, 2, 1}, vecEmpty[];

void Setup(){
    double mat1[3][3] = { {9.1,6.0,2.8}, {7.4,1.0,3.0}, {4.5,0.0,8.0} };
    double mat2[3][3] = { {1.0,2.0,3.0}, {4.0,5.0,6.0}, {7.0,8.0,9.0} };
    double mat3[2][2] = { {32.1,8.3}, {0.72,43.7} };
    double mat4[3][2] = { {1, 2}, {3, 4}, {5, 6}};


    //double mat2[3][3];
    //double **ma1, **ma2, **ma3;
    int size = 3, row, col, i, j;
    double vec1[3] = {1, 2, 1};
    ma1 = (double **) malloc(size * sizeof(double*));
    ma2 = (double **) malloc(size * sizeof(double*));
    ma3 = (double **) malloc(size * sizeof(double*));
    ma4 = (double **) malloc(size * sizeof(double*));


    //Allocating space for second dimension
    for (row = 0; row < size; ++row) {
        ma1[row] = (double *) malloc(size * sizeof(double));
    }
    for (row = 0; row < size; ++row) {
        ma2[row] = (double *) malloc(size * sizeof(double));
    }
    for (row = 0; row < 2; ++row) {
        ma3[row] = (double *) malloc(2 * sizeof(double));
    }
    for (row = 0; row < 2; ++row) {
        ma4[row] = (double *) malloc(3 * sizeof(double));
    }

    //Setting values to test values from mat1 and 4
    for (row = 0; row<size; row++) {
        for (col = 0; col<size; col++) {
            ma1[row][col] = mat1[row][col];
        }
    }

    for (row = 0; row<size; row++) {
        for (col = 0; col<size; col++) {
            ma2[row][col] = mat2[row][col];
        }
    }
    for (row = 0; row < 2; ++row) {
        for (col = 0; col < 2; ++col) {
            ma3[row][col] = mat3[row][col];
        }
    }
    for (row = 0; row < 3; ++row) {
        for (col = 0; col < 2; ++col) {
            ma4[row][col] = mat4[row][col];
        }
    }
}

void MatrixTest::mult_mat_mat_ValidMatrix_ExpectCorrect() {
    Setup();
    double **resMat;
    //double **resMat = mult_mat_mat(ma1, ma2);
    double ResMulMat3x3[3][3] = { {52.7, 70.6, 88.5}, {32.4, 43.8, 55.2}, {60.5, 73.0, 85.5} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResMulMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::mult_mat_mat_InvalidMatrix_ExpectError() {
    Setup();
    double **resMat;
    //double **resMat = mult_mat_mat(ma1, ma3);
    double ResMulMat3x3[3][3] = { {52.7, 70.6, 88.5}, {32.4, 43.8, 55.2}, {60.5, 73.0, 85.5} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResMulMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::mult_mat_mat_DifferentSizes_ExpectCorrect() {
    Setup();
    double **resMat;
    //resMat = mult_mat_mat(ma1, ma4);
    double ResMulMat[3][2] = { {41.1, 59}, {25.4, 36.8}, {62.5, 81} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if(ResMulMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::trans_matrix_SquareMatrix_ExpectTransposed() {
    Setup();
    double ResTransMat[3][3] = { {1, 4, 7}, {2, 5, 8}, {3, 6, 9} };
    double **resMat;
    //double **resMat = trans_matrix(ma2);

    bool IsEqual = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResTransMat[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::trans_matrix_NotSquareMatrix_ExpectTransposed() {
    Setup();
    double ResTransMat[3][3] = { {1, 3, 5}, {2, 4, 6}};
    double **resMat;
    //double **resMat = trans_matrix(ma4);

    bool IsEqual = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if(ResTransMat[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_mat_mat_ValidMatrix_ExpectCorrect() {
    Setup();
    double **resMat;
    //double **resMat = add_mat_mat(ma1, ma2);
    double ResAddMat3x3[3][3] = { {10.1, 8, 5.8}, {11.4, 6, 9}, {11.5, 8, 17} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResAddMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::add_mat_mat_InvalidMatrix_ExpectError() {
    Setup();
    double **resMat;
    //double **resMat = add_mat_mat(ma1, ma3);
    double ResAddMat3x3[3][3] = { {10.1, 8, 5.8}, {11.4, 6, 9}, {11.5, 8, 17} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResAddMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_mat_mat_ValidMatrix_ExpectCorrect() {
    Setup();
    double **resMat;
    //double **resMat = sub_mat_mat(ma1, ma2);
    double ResSubMat3x3[3][3] = { {8.1, 4, -0.2}, {3.4, -4, -3}, {-2.5, -8, -1} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResSubMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_mat_mat_InvalidMatrix_ExpectError() {
    Setup();
    double **resMat;
    //double **resMat = sub_mat_mat(ma1, ma3);
    double ResSubMat3x3[3][3] = { {8.1, 4, -0.2}, {3.4, -4, -3}, {-2.5, -8, -1} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResSubMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::ident_mat_ExpectCorrect() {
    Setup();
    double **resMat;
    //double **resMat = ident_mat(3);
    double ResIdentMat3[3][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResIdentMat3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_vec_vec_ValidVectors_ExpectCorrect() {
    Setup();
    //double ResVec[] = add_vec_vec(vec1, vec1);

    double ResAddVec[] = {2, 4 ,2};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if(ResAddVec[i] != ResVec[i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_vec_vec_EmptyVector_ExpectError() {
    Setup();
    double ResAddVec[] = {2, 4 ,2};

    //double ResVec[] = add_vec_vec(vec1, vecEmpty);
    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if(ResAddVec[i] != ResVec[i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_vec_Vec_ValidVectors_ExpectCorrect() {
    Setup();
    double ResSubVec[] = {0, 0, 0};

    //double ResVec[] = sub_vec_vec(vec1, vec1);
    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if(ResSubVec[i] != ResVec[i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::sub_vec_vec_EmptyVectors_ExpectError() {
    Setup();
    double ResSubVec[] = {0, 0, 0};
    //double ResVec[] = sub_vec_vec(vec1, vecEmpty);

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if(ResSubVec[i] != ResVec[i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::inv_mat_ValidMatrix_ExpectCorrect() {
    Setup();
    double **resMat, InvMat[3][3] = { {1, 2, 3}, {0, 1, 4}, {5, 6, 0} }, **matToInv;

    matToInv = (double **) malloc(3 * sizeof(double*));
    for (int i = 0; i < 3; ++i) {
        matToInv[i] = (double *) malloc(3 * sizeof(double));
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matToInv[i][j] = InvMat[i][j];
        }
    }

    //resMat = inv_mat(matToInv);
    double ResMat[3][3] = { {-24, 18, 5}, {20, -15, -4}, {-5, 4, 1} };

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResMat[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::inv_mat_InvalidMatrix_ExpectError() {
    Setup();

    double **actualResMat, ResMat[3][3] = { {-24, 18, 5}, {20, -15, -4}, {-5, 4, 1} };

    //double **actualResMat = inv_mat(ma2);

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(ResMat[i][j] != actualResMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}
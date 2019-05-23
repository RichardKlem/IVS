//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     RICHARD KLEM <xklemr00@stud.fit.vutbr.cz>
// $Date:       $2019-03-04
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author RICHARD KLEM
 *
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech
//    matic.
//============================================================================//

//prazdna matice
class Maxtrix_Empty : public ::testing::Test
{
protected:
    Matrix *matrix_empty = new Matrix(101,42);
};

//matice 1x1
class Matrix_1x1 : public ::testing::Test
{
public:
    virtual void SetUp() {
      matrix_1x1->set(0, 0, 3);
    }

    Matrix *matrix_1x1 = new Matrix(1, 1);
};

//matice 2x2
class Matrix_2x2 : public ::testing::Test
{
public:
    virtual void SetUp() {

      matrix_2x2->set(std::vector<std::vector<double>> {{2,4},{8,16}});
    }

    Matrix *matrix_2x2 = new Matrix(2, 2);
};

//matice 2x2 urcena pro vypocet soustavy rovnic
class Matrix_2x2_EQ : public ::testing::Test
{
public:
    virtual void SetUp() {

      matrix_2x2_EQ->set(std::vector<std::vector<double>> {{2,4},{8,15}});
    }

    Matrix *matrix_2x2_EQ = new Matrix(2, 2);
};

//matice 1x3
class Matrix_1x3 : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    matrix_1x3->set(0,0,2);
    matrix_1x3->set(0,1,4);
    matrix_1x3->set(0,2,8);
  }
  Matrix *matrix_1x3 = new Matrix(1,3);
};

//matice 3x3
class Matrix_3x3 : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    matrix_3x3->set(0,0,2);
    matrix_3x3->set(0,1,3);
    matrix_3x3->set(0,2,5);
    matrix_3x3->set(1,0,7);
    matrix_3x3->set(1,1,11);
    matrix_3x3->set(1,2,13);
    matrix_3x3->set(2,0,17);
    matrix_3x3->set(2,1,19);
    matrix_3x3->set(2,2,23);
  }
  Matrix *matrix_3x3 = new Matrix(3, 3);
};

//matice 4x4 urcena pro vypocet soustavy rovnic
class Matrix_4x4_EQ : public ::testing::Test
{
public:
    virtual void SetUp() {

      matrix_4x4_EQ->set(std::vector<std::vector<double>> {{2,0,0,0},
        {0,1,0,0},{0,0,4,0,},{0,0,0,1}});
    }

    Matrix *matrix_4x4_EQ = new Matrix(4, 4);
};

TEST_F(Maxtrix_Empty, Inicialization)
{
  Matrix *matrix_0x0;
  //nelze vytvorit matici mensi nez 1x1
  EXPECT_ANY_THROW(matrix_0x0 = new Matrix(0, 0));

  //vytvoreni nulove matice 1x1 a test zda lze vlozit -> true
  Matrix *matrix_1x1 = new Matrix();
  EXPECT_TRUE(matrix_1x1->set(0,0,3.14));

  delete matrix_1x1;
  delete matrix_empty;
  delete matrix_0x0;
}

TEST_F(Matrix_2x2, Set)
{
  //prepsani hodnoty na pozici [0][1]
  EXPECT_TRUE(matrix_2x2->set(0,1,0));

  //prepsani na znak->ASCII
  EXPECT_TRUE(matrix_2x2->set(0,0,'A'));

  //vlozim za hranice matice->false
  EXPECT_FALSE(matrix_2x2->set(3,1,115));

  //vlozim pomoci vektoroveho set spravne
  EXPECT_TRUE(matrix_2x2->set(std::vector<std::vector<double>> {{1,0},{0,1}}));

  //vlozim pomoci vektoroveho set chybne, y = 4 je mimo rozsah matice
  EXPECT_FALSE(matrix_2x2->set(std::vector<std::vector<double>> {{1,0},{0,1},{0,0}}));

  delete matrix_2x2;
}

TEST_F(Matrix_2x2, Get)
{
  //zjistim hodnotu na pozici v matici
  EXPECT_EQ(matrix_2x2->get(0,0), 2);

  //zjistim hodnotu mimo matici -> vyjimka
  EXPECT_ANY_THROW(matrix_2x2->get(0,3));

  delete matrix_2x2;
}

TEST_F(Matrix_2x2, Operator_equal)
{
  //inicializace totozne matice, ale prazdne -> false
  Matrix *matrix_equal = new Matrix(2,2);
  EXPECT_FALSE(matrix_2x2->operator==(*matrix_equal));

  //nyni ji naplnim stejnymi hodnotami -> true
  matrix_equal->set(std::vector<std::vector<double>> {{2,4},{8,16}});
  EXPECT_TRUE(matrix_2x2->operator==(*matrix_equal));

  //inicializace matice s jinou velikosti -> vyjimka
  Matrix *matrix_nonEqual = new Matrix(3,3);
  EXPECT_ANY_THROW(matrix_2x2->operator==(*matrix_nonEqual));

  delete matrix_nonEqual;
  delete matrix_equal;
  delete matrix_2x2;
}

TEST_F(Matrix_3x3, Operator_add)
{
  Matrix *matrix_add_1 = new Matrix(3,3);
  EXPECT_EQ((matrix_3x3->operator+(*matrix_add_1)), (*matrix_3x3));

  matrix_add_1->set(0,0,5);
  double x = (matrix_3x3->operator+(*matrix_add_1)).get(0,0);
  double y = (matrix_3x3->get(0,0))+5;
  EXPECT_EQ(x,y);

  //inicializace matice s jinou velikosti -> vyjimka
  Matrix *matrix_nonEqual = new Matrix(7,3);
  EXPECT_ANY_THROW(matrix_3x3->operator+(*matrix_nonEqual));

  delete matrix_3x3;
  delete matrix_add_1;
  delete matrix_nonEqual;
}

TEST_F(Matrix_1x3, Operator_multiply)
{
  //nastaveni matice k operaci nasobeni
  Matrix *matrix_multiply = new Matrix();
  matrix_multiply->set(0,0,5);

  //test spravnosti nasobeni
  EXPECT_TRUE((matrix_multiply->operator*(*matrix_1x3).get(0,0)) == 10);

  //chybne poradi
  EXPECT_ANY_THROW(matrix_1x3->operator*(*matrix_multiply));

  //inicializace matice s jinou velikosti -> vyjimka
  Matrix *matrix_nonCompatible = new Matrix(2,4);
  EXPECT_ANY_THROW(matrix_1x3->operator*(*matrix_nonCompatible));

  //nasobeni matice skalarem
  EXPECT_EQ((matrix_1x3->operator*(1.1)).get(0,0), 2.2);

  delete matrix_multiply;
  delete matrix_nonCompatible;
  delete matrix_1x3;
}

TEST_F(Matrix_2x2_EQ, SolveEquation)
{
  //prava strana rovnic
  std::vector<double> b = {2,4};
  std::vector<double> res = matrix_2x2_EQ->solveEquation(b);

  //test, zda vysledky odpovidaji
  EXPECT_EQ(res[0], -7);
  EXPECT_EQ(res[1], 4);

  //test na vzhodnoceni vyjimky, determinant je 0
  Matrix *matrix_bad = new Matrix(2,2);
  matrix_bad->set(std::vector<std::vector<double>> {{2,4},{8,16}});
  EXPECT_ANY_THROW(matrix_bad->solveEquation(b));

  //test na NEctvercovou matici
  Matrix *matrix_worse = new Matrix(2,3);
  EXPECT_ANY_THROW(matrix_worse->solveEquation(b));

  delete matrix_2x2_EQ;
  delete matrix_bad;
  delete matrix_worse;
}

TEST_F(Matrix_3x3, SolveEquation)
{
  //prava strana rovnic
  std::vector<double> b = {13, 0, 0};
  std::vector<double> res = matrix_3x3->solveEquation(b);

  //test, zda vysledky odpovidaji
  EXPECT_EQ(res[0], -1);
  EXPECT_EQ(res[1], -10);
  EXPECT_EQ(res[2], 9);

  delete matrix_3x3;
}

TEST_F(Matrix_1x3, SolveEquation)
{
  //prava strana rovnic
  std::vector<double> b = {13};

  //ocekavana vyjimka, protoze matice neni ctvercova
  EXPECT_ANY_THROW(std::vector<double> res = matrix_1x3->solveEquation(b));

  delete matrix_1x3;
}

TEST_F(Matrix_4x4_EQ, SolveEquation)
{
  //prava strana rovnic
  std::vector<double> b = {2,3,4,7};
  std::vector<double> res = matrix_4x4_EQ->solveEquation(b);

  //test, zda vysledky odpovidaji
  EXPECT_EQ(res[0], 1);
  EXPECT_EQ(res[1], 3);
  EXPECT_EQ(res[2], 1);
  EXPECT_EQ(res[3], 7);

  delete matrix_4x4_EQ;
}

TEST_F(Matrix_1x1, SolveEquation)
{
  //prava strana rovnic
  std::vector<double> b = {1.5};
  std::vector<double> res = matrix_1x1->solveEquation(b);

  //test, zda vysledky odpovidaji
  EXPECT_EQ(res[0], 0.5);

  delete matrix_1x1;
}

/*** Konec souboru white_box_tests.cpp ***/

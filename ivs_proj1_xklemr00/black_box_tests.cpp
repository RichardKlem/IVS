//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     RICHARD KLEM <xklemr00@stud.fit.vutbr.cz>
// $Date:       $2019-03-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author RICHARD KLEM
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//
class NonEmptyTree : public ::testing::Test
{
protected:
  //vlozeni hodnot do stromu
    virtual void SetUp() {
        int values[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47};

        for(int i = 0; i < 14; ++i) {
            tree.InsertNode(values[i]);
        }
    }

    //konstruktor binarniho stromu
    BinaryTree tree;
};

class EmptyTree : public ::testing::Test
{
protected:

    //konstruktor binarniho stromu
    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
  //vlozeni hodnot do stromu
    virtual void SetUp() {
        int values[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47};

        for(int i = 0; i < 14; ++i) {
            tree.InsertNode(values[i]);
        }
    }

    //konstrukotor binarniho stromu
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode)
{
  //vlozi uzel s hodnotou 0
  EXPECT_TRUE(tree.InsertNode(0).first);

  //pokusi se znova vlozit uzel s hodnotou 0
  EXPECT_FALSE(tree.InsertNode(0).first);

  //vlozi uzel s hodnoutou 1, kontrola ukazatele
  EXPECT_TRUE(tree.InsertNode(1).second != NULL);

  //ziska ukazatel na uzel s hodnotou 1 a porovná ho se sekundarni
  //navratovou hodnotou ziskanou s InsertNode
  EXPECT_EQ(tree.FindNode(1), tree.InsertNode(1).second);

  //Vlozim znak, ktery se vlozi jako cislo podle ASCII hodnoty
  EXPECT_TRUE(tree.InsertNode('A').first);

  //Zjistim zda se opravdu znak vlozil
  EXPECT_TRUE((tree.FindNode(65)) != NULL);

}

TEST_F(EmptyTree, DeleteNode)
{
  tree.InsertNode(1);

  //smaze uzel s hodnotou 1
  EXPECT_TRUE(tree.DeleteNode(1));

  //pokusi se smazat uzel s hodnotou znova
  EXPECT_FALSE(tree.DeleteNode(1));

  //pokusim se smazat hodnotu pomoci ASCII znaku
  tree.InsertNode(65);
  EXPECT_TRUE(tree.DeleteNode('A'));
}

TEST_F(EmptyTree, FindNode)
{
  tree.InsertNode(0);

  //nalezne uzel s hodnotou 0
  EXPECT_TRUE((tree.FindNode(0)) != NULL);

  //pokusi se nalezt uzel s hodnotou 1
  EXPECT_TRUE((tree.FindNode(1)) == NULL);
}

TEST_F(NonEmptyTree, InsertNode)
{
  //vlozi uzel s hodnotou 0
  EXPECT_TRUE(tree.InsertNode(0).first);

  //pokusi se znova vlozit uzel s hodnotou 0
  EXPECT_FALSE(tree.InsertNode(0).first);

  //vlozi uzel s hodnoutou 1, kontrola ukazatele
  EXPECT_TRUE(tree.InsertNode(1).second != NULL);

  //ziska ukazatel na uzel s hodnotou 1 a porovná ho se sekundarni
  //navratovou hodnotou ziskanou s InsertNode
  EXPECT_EQ(tree.FindNode(1), tree.InsertNode(1).second);

  //Vlozim znak, ktery se vlozi jako cislo podle ASCII hodnoty
  EXPECT_TRUE(tree.InsertNode('A').first);

  //Zjistim zda se opravdu znak vlozil
  EXPECT_TRUE((tree.FindNode(65)) != NULL);
}

TEST_F(NonEmptyTree, DeleteNode)
{
  tree.InsertNode(1);

  //smaze uzel s hodnotou 1
  EXPECT_TRUE(tree.DeleteNode(1));

  //pokusi se smazat uzel s hodnotou znova
  EXPECT_FALSE(tree.DeleteNode(1));

  //pokusim se smazat hodnotu pomoci ASCII znaku
  tree.InsertNode(65);
  EXPECT_TRUE(tree.DeleteNode('A'));
}

TEST_F(NonEmptyTree, FindNode)
{
  tree.InsertNode(0);

  //nalezne uzel s hodnotou 0
  EXPECT_TRUE((tree.FindNode(0)) != NULL);

  //pokusi se nalezt uzel s hodnotou 1
  EXPECT_TRUE((tree.FindNode(1)) == NULL);
}

TEST_F(TreeAxioms, Axiom1)
{
  //vytvorim pole pro koncove uzly - listy
  std::vector<Node_t *> leafNodes;

  //naplnim pole koncovymi listy
  tree.GetLeafNodes(leafNodes);

  //prochazim kazdy list a kontroluji barvu
  for (Node_t *testNode: leafNodes) {
    EXPECT_TRUE((*testNode).color == BLACK);
  }
}

TEST_F(TreeAxioms, Axiom2)
{
  //vytvorim pole pro koncove uzly - listy
  std::vector<Node_t *> leafNodes;

  //naplnim pole všemi uzly
  tree.GetAllNodes(leafNodes);

  //prochazim pole a hledam cervene uzly, pokud najdu, tak zkontroluji,
  //ze jeho potomci existuji, jsou prave dva a jsou cerni
  for (Node_t *testNode: leafNodes)
  {
    if(testNode->color == RED)
    {
      ASSERT_TRUE(testNode->pLeft != NULL);
      ASSERT_TRUE(testNode->pRight != NULL);
      EXPECT_TRUE(testNode->pLeft->color == BLACK);
      EXPECT_TRUE(testNode->pRight->color == BLACK);
    }
  }
}

TEST_F(TreeAxioms, Axiom3)
{
  //vytvorim pole pro koncove uzly - listy
  std::vector<Node_t *> leafNodes;

  //naplnim pole koncovymi listy
  tree.GetLeafNodes(leafNodes);

  //ukazatel na "vyssi" uzel
  Node_t *nextNode;

  //promenne pro pocet cernych uzlu v ceste predchoziho a aktual. konc. uzlu
  int sumOfBlackNodes_prev = 0;
  int sumOfBlackNodes_actual = 0;

  //vezmu kazdy jeden listovy uzel a projdu postupne uzel po uzlu jeho cestu
  //az ke koreni, pokud po ceste narazim na cerny uzel, tak navysim pocitado
  for (Node_t *testNode: leafNodes) {
    nextNode = testNode->pParent;
    while (nextNode != NULL) {
      if (nextNode->color == BLACK) {
        sumOfBlackNodes_actual++;
      }
      nextNode = nextNode->pParent;
    }

    //inicializace prvotni hodnoty poctu cernych uzlu
    short int i = 0;
    if (i < 1) {
      sumOfBlackNodes_prev = sumOfBlackNodes_actual;
      i++;
    }

    //kontrola zda se pocet cernych uzlu rovna
    EXPECT_TRUE(sumOfBlackNodes_prev == sumOfBlackNodes_actual);
  }
}
  /*** Konec souboru black_box_tests.cpp ***/

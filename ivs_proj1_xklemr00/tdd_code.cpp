//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     RICHARD KLEM <xklemr00@stud.fit.vutbr.cz>
// $Date:       $2019-03-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author RICHARD KLEM
 *
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue:: Element_t *PriorityQueue::CreateElement(Element_t *pPrev, Element_t *pNext, int value)
{
  //novy objekt typu struktury Element_t
  Element_t *tmp = new Element_t();

  //predani ci zapsani ukazatelu a hodnoty
  tmp->pPrev = pPrev;
  tmp->pNext = pNext;
  tmp->value = value;

  //navrati dany objekt
  return tmp;
}

PriorityQueue::PriorityQueue()
{
  //neni treba zadne akce, head je implicitne nastaven na NULL, vse je OK
}

PriorityQueue::~PriorityQueue()
{
  //posuvny pointer
  Element_t *rider = GetHead();

  //prochazim vsechny prvky pomoci element
  //s pomoci element_toDelete odstranuji jednotlive prvky
  while (rider != NULL) {
    Element_t *element_toDelete = rider;
	rider = rider->pNext;
    delete element_toDelete;
  }
}

void PriorityQueue::Insert(int value)
{
  //prvky pomoci kterych se budeme posouvat seznamem a vkladat nove prvky
  Element_t *nextElement = NULL;
  Element_t *prevElement = NULL;
  Element_t *tmp = GetHead();

  //fronta je prazdna, koren(hlava) ukazuje na nove vytvoreny prvek
  if (head == NULL) {
    head = CreateElement(NULL, NULL, value);
    return;
  }

  //prvek ma byt vlozen na zacatek, je nejmensi
  else if (value < (tmp->value)) {
    Element_t *newElement = CreateElement(NULL, tmp, value);
    head = newElement;
    tmp->pPrev = newElement;
    return;
  }

  //prvek bude nekde uprostred nebo na konci, je vetsi nez nejmensi
  else {
    //nastaveni hodnot jezdce 'nextElement' a pomocneho ukazatele 'prevElement'
    prevElement = GetHead();
    nextElement = prevElement->pNext;

    //seznam se projizdi az do konce, nebo do hledaneho mista
    while(nextElement != NULL)
    {
      //posuv dal, kdyz je hodnota vetsi nez o prvek nasledujici
      if(value > nextElement->value){
        prevElement = nextElement;
        nextElement = nextElement->pNext;
      }

      //pokud nejsme na konci a hodnota value neni uz vetsi vlozi se prvek
      //mezi prevElement a nextElement
      else{
        Element_t *newElement = CreateElement(prevElement, nextElement, value);
        prevElement->pNext = newElement;
        nextElement->pPrev = newElement;
        return;
      }
    }//konec while

    //kdyz jsme dorazili na konec, tak hodnota je nejvetsi a vlozi se tedy
    //jako posledni polozka
    Element_t *newElement = CreateElement(prevElement, NULL, value);
    prevElement->pNext = newElement;
    return;
  }//konec postupu else pro hledani uprostred
}//konec Insert funkce

bool PriorityQueue::Remove(int value)
{
  Element_t *rider = GetHead();

  //prochazim seznam do konce
  while (rider != NULL) {
    
	  //hodnoty se shoduji
    if(rider->value == value){
      
		//a zaroven se nachazime uprostred seznamu
      if(rider->pNext != NULL && rider->pPrev != NULL){
        rider->pPrev->pNext = rider->pNext;
        rider->pNext->pPrev = rider->pPrev;
        delete rider;
        return true;
      }

      //nebo pokud se nachazime uplne na zacatku
      //vymaze se prvni prvek a z nasledujiciho se stava prvni
      else if(rider->pPrev == NULL && rider->pNext != NULL){
        head = rider->pNext;
        rider->pNext->pPrev = NULL;
        delete rider;
        return true;
      }

      //nebo pokud se nachazime na konci
      //vymaze se posledni prvek a z predchazejiciho se stava posledni
      else if(rider->pNext == NULL && rider->pPrev != NULL){
        rider->pPrev->pNext = NULL;
        delete rider;
        return true;
      }
      
	  //mazani jedinoeho posledniho prvku
      else{
        head = NULL;
        delete rider;
        return true;
      }
    }//konec podminky testovaci shodu hodnoty value

    //presun o dalsi prvek dal
    else{
      rider = rider->pNext;
    }
  }//konec cyklu

  return false;
}//konec funkce Remove

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
  //pomocny posuvny prvek
  Element_t *rider = GetHead();

  //dokud nedojdeme na konec, tak porovnavaji hodnoty
  //pokud se nekde budou shodovat vraci ukazatel na prvek, jinak NULL
  while (rider != NULL) {
    if(rider->value == value){
      return rider;
    }
    else{
      rider = rider->pNext;
    }
  }
  return NULL;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{	
	//jednoduse vraci ukazatel na prvni polozku
    return head;
}

/*** Konec souboru tdd_code.cpp ***/

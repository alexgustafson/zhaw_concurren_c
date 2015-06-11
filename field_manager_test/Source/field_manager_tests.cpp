/*
  ==============================================================================

    field_manager_tests.cpp
    Created: 10 Jun 2015 5:48:16pm
    Author:  Alexander Gustafson

  ==============================================================================
*/

#include "field_manager_tests.h"


void FieldManagerTests::FirstTest()
{
    
    beginTest("Testing The Tester");
    expect(true);
    expectEquals(true, !false);
}

void FieldManagerTests::TestField()
{
    beginTest("Create Field");

    set_size(1);
    take_cell(0, 0, 1);
    set_size(2);
    take_cell(1, 0, 2);
    take_cell(0, 1, 3);
    take_cell(1, 1, 4);
    
    set_size(3);
    
    take_cell(2, 0, 5);
    take_cell(0, 2, 6);
    take_cell(2, 1, 7);
    take_cell(1, 2, 8);
    take_cell(2, 2, 9);
    
    expectEquals(get_cell(0, 0)->player_id, 1);
    expectEquals(get_cell(1, 0)->player_id, 2);
    expectEquals(get_cell(0, 1)->player_id, 3);
    expectEquals(get_cell(1, 1)->player_id, 4);
    expectEquals(get_cell(2, 2)->player_id, 9);
    
}

void FieldManagerTests::runTest()
{
    FirstTest();
    TestField();
}
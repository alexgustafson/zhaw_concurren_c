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

void FieldManagerTests::CreateAndReleaseTests()
{
    beginTest("Create and Release Tests");
    initialize_field_manager(4);
    for (int i = 0; i < 50; i++) {
        set_size(i);
    }
    take_cell(0, 0, 212);
    for (int i = 50; i > 0; i--) {
        set_size(i);
    }
    expectEquals(get_cell_player(0, 0), 212);
    release_field_manager();
    Thread::sleep(100);
}

void FieldManagerTests::TestField()
{
    beginTest("Create Field");
    initialize_field_manager(4);

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
    
    set_size(4);
    
    take_cell(3, 3, 16);
    
    expectEquals(get_cell_player(3, 3), 16);
    
    set_size(3);
    
    expectEquals(get_cell_player(0, 0), 1);
    expectEquals(get_cell_player(1, 0), 2);
    expectEquals(get_cell_player(0, 1), 3);
    expectEquals(get_cell_player(1, 1), 4);
    expectEquals(get_cell_player(1, 2), 8);
    expectEquals(get_cell_player(2, 2), 9);
    
    //int should_be_error = take_cell(-1, 6, 12);

    release_field_manager();
    Thread::sleep(100);
}

void FieldManagerTests::concurrentJoin()
{
    beginTest("Concurrent Join");
    initialize_field_manager(6);
    
    ScopedPointer<Player> player1 = new Player();
    player1->setName("Player 1");
    add_instruction(player1, "join", 0);

    ScopedPointer<Player> player2 = new Player();
    player2->setName("Player 2");
    add_instruction(player2, "join", 0);
    
    ScopedPointer<Player> player3 = new Player();
    player3->setName("Player 3");
    add_instruction(player3, "join", 0);
    
    ScopedPointer<Player> player4 = new Player();
    player4->setName("Player 4");
    add_instruction(player4, "join", 0);
    
    pool->addJob(player1, false);
    pool->addJob(player2, false);
    pool->addJob(player3, false);
    pool->addJob(player4, false);

    while(pool->getNumJobs() > 0)
    {
        Thread::sleep(1);
    }
    
    expectEquals(get_size(), 36);
    
    release_field_manager();
    Thread::sleep(100);
}

void FieldManagerTests::atLeast8PlayersMustJoin()
{
    beginTest("Minumum 8 Players Needed");
    initialize_field_manager(16);
    set_delay(1);
    
    ScopedPointer<Player> player1 = new Player();
    player1->setName("Player 1");
    add_instruction(player1, "join", 0);
    
    ScopedPointer<Player> player2 = new Player();
    player2->setName("Player 2");
    add_instruction(player2, "join", 0);
    
    ScopedPointer<Player> player3 = new Player();
    player3->setName("Player 3");
    add_instruction(player3, "join", 0);
    
    ScopedPointer<Player> player4 = new Player();
    player4->setName("Player 4");
    add_instruction(player4, "join", 0);
    
    ScopedPointer<Player> player5 = new Player();
    player5->setName("Player 5");
    add_instruction(player5, "join", 0);
    
    ScopedPointer<Player> player6 = new Player();
    player6->setName("Player 6");
    add_instruction(player6, "join", 0);
    
    ScopedPointer<Player> player7 = new Player();
    player7->setName("Player 7");
    add_instruction(player7, "join", 0);
    
    ScopedPointer<Player> player8 = new Player();
    player8->setName("Player 8");
    add_instruction(player8, "sleep", 10);
    add_instruction(player8, "join", 0);
    
    pool->addJob(player1, false);
    pool->addJob(player2, false);
    pool->addJob(player3, false);
    pool->addJob(player4, false);
    pool->addJob(player5, false);
    pool->addJob(player6, false);
    pool->addJob(player7, false);
    pool->addJob(player8, false);
    
    while(pool->getNumJobs() > 0)
    {
        Thread::sleep(10);
    }
    
    expectEquals(get_size(), 256);
    expectEquals(is_there_a_winner(), -1);
    release_field_manager();
    Thread::sleep(100);

}

void FieldManagerTests::concurrentPlaying()
{
    beginTest("Concurrent Playing");

    initialize_field_manager(4);
    set_delay(1);
    
    ScopedPointer<Player> player1 = new Player();
    player1->setName("Player 1");
    add_instruction(player1, "join", 0);
    NamedValueSet* instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    
    ScopedPointer<Player> player2 = new Player();
    player2->setName("Player 2");
    player2->setId(2);
    add_instruction(player2, "join", 0);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    
    ScopedPointer<Player> player3 = new Player();
    player3->setName("Player 3");
    player3->setId(3);
    add_instruction(player3, "join", 0);
    instruction = add_instruction(player3, "sleep", 3);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    
    ScopedPointer<Player> player4 = new Player();
    player4->setName("Player 4");
    player4->setId(4);
    instruction = add_instruction(player4, "sleep", 5);
    instruction = add_instruction(player4, "join", 0);
    instruction = add_instruction(player4, "sleep", 15);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 3);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 3);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 3);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 3);
    
    pool->addJob(player1, false);
    pool->addJob(player2, false);
    pool->addJob(player3, false);
    pool->addJob(player4, false);
    
    expectEquals(is_there_a_winner(), -1);

    
    while(pool->getNumJobs() > 0)
    {
        Thread::sleep(1);
    }
    Logger::writeToLog("thread pool finished");
    expectEquals(get_size(), 16);
    expectEquals(is_there_a_winner(), 4);
    release_field_manager();
    Logger::writeToLog("field manager released");
    Thread::sleep(20);
}

void FieldManagerTests::concurrentPlayingAndLeaving()
{
    beginTest("Concurrent Playing");
    
    initialize_field_manager(4);
    set_delay(1);
    
    ScopedPointer<Player> player1 = new Player();
    player1->setName("Player 1");
    player1->setId(1);
    add_instruction(player1, "join", 0);
    NamedValueSet* instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    instruction = add_instruction(player1, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    instruction = add_instruction(player1, "leave", 0);

    
    ScopedPointer<Player> player2 = new Player();
    player2->setName("Player 2");
    player2->setId(2);
    add_instruction(player2, "join", 0);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player2, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    
    ScopedPointer<Player> player3 = new Player();
    player3->setName("Player 3");
    player3->setId(3);
    add_instruction(player3, "join", 0);
    instruction = add_instruction(player3, "sleep", 3);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player3, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    instruction = add_instruction(player3, "leave", 0);

    
    
    ScopedPointer<Player> player4 = new Player();
    player4->setName("Player 4");
    player4->setId(4);
    instruction = add_instruction(player4, "join", 0);
    instruction = add_instruction(player4, "sleep", 15);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 0);
    instruction->set("y", 3);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 1);
    instruction->set("y", 3);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 2);
    instruction->set("y", 3);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 0);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 1);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 2);
    instruction = add_instruction(player4, "take", 0);
    instruction->set("x", 3);
    instruction->set("y", 3);
    
    pool->addJob(player1, false);
    pool->addJob(player2, false);
    pool->addJob(player3, false);
    pool->addJob(player4, false);
    
    expectEquals(is_there_a_winner(), -1);
    
    
    while(pool->getNumJobs() > 0)
    {
        Thread::sleep(1);
    }
    
    expectEquals(get_size(), 16);
    expectEquals(is_there_a_winner(), 4);
    release_field_manager();
    Thread::sleep(100);
}

NamedValueSet* FieldManagerTests::add_instruction(FieldManagerTests::Player *player, const Identifier &inst, const var &parameter)
{
    NamedValueSet* instruction = new NamedValueSet();
    instruction->set(inst, parameter);
    player->instructions.add(instruction);
    return instruction;
}

void FieldManagerTests::runTest()
{
    FirstTest();
    CreateAndReleaseTests();
    TestField();
    concurrentJoin();
    atLeast8PlayersMustJoin();
    concurrentPlaying();
    concurrentPlayingAndLeaving();
}



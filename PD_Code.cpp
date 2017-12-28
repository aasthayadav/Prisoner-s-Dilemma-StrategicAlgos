#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

int first_move = 0;
int opponent_choice = 0;
int opponent_last_choice = 0;
int player_last_choice = 1;
double time_arr[8];
int time_index = 0;

typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

timestamp_t t0 = get_timestamp();
timestamp_t t1 = get_timestamp();
//first move is cooperation
void opponent_stategy()
{
    if(first_move == 0)
    {
        first_move = 1;
        opponent_choice = 1;
        opponent_last_choice = opponent_choice;
    }
    else if(opponent_last_choice == 1)
        opponent_choice = 2;
    else
        opponent_choice = (rand() % 2) + 1;

}

//first move is defection
void opponent_defect_stategy()
{
    if(first_move == 0)
    {
        first_move = 1;
        opponent_choice = 2;
        opponent_last_choice = opponent_choice;
    }
    else if(opponent_last_choice == 1)
        opponent_choice = 2;
    else
        opponent_choice = (rand() % 2) + 1;
}

//Tit for tat strategy
int TFT()
{
    if(first_move == 0)
    {
        first_move = 1;
        player_last_choice = 1;
        return 1;
    }
    else
        return opponent_last_choice;
    timestamp_t t1 = get_timestamp();
}

//Win-stay, Lose-switch strategy
int WSLS()
{
    if(first_move == 0)
    {
        first_move = 1;
        player_last_choice = 1;
        return 1;
    }
    //encountering a T or R payoff
    else if(opponent_last_choice == 1)
    {
        return player_last_choice;
    }
    //encountering a P or S payoff
    else
    {
        if(player_last_choice == 1)
        {
            player_last_choice = 2;
            return 2;
        }
        else
        {
            player_last_choice = 1;
            return 1;
        }
    }
}

//Generous Tit for Tat strategy
int GTFT()
{
    if(first_move == 0)
    {
        first_move = 1;
        player_last_choice = 1;
        return 1;
    }
    //on encountering S payoff, cooperate 30% of the time
    player_last_choice = opponent_last_choice;
    if(opponent_choice == 2 && player_last_choice == 1)
    {
        int choice_value = rand() % 10 + 1;
        if(choice_value <= 3)
        {
            player_last_choice = 1;
            return player_last_choice;
        }
        else
        {
            player_last_choice = 2;
            return player_last_choice;
        }
    }
    else
    {
        return player_last_choice;
    }
}

//Zero Determinant GTFT Strategy
int ZDGTFT()
{
    if(first_move == 0)
    {
        first_move = 1;
        player_last_choice = 1;
        return player_last_choice;
    }
    player_last_choice = opponent_last_choice;
    if(opponent_choice == 2 && player_last_choice == 1)
    {
        int choice_value = rand() % 10 + 1;
        if(choice_value <= 3)
        {
            player_last_choice = 1;
            return player_last_choice;
        }
        else
        {
            player_last_choice = 2;
            return player_last_choice;
        }
    }
    else if(opponent_choice == 1 && player_last_choice == 2)
    {
        int choice_value = rand() % 10 + 1;
        if(choice_value <= 3)
        {
            player_last_choice = 2;
            return player_last_choice;
        }
        else
        {
            player_last_choice = 1;
            return player_last_choice;
        }
    }
    else
    {
        return player_last_choice;
    }
}

//All Defection Strategy
int ALLD(int master_agent)
{
    if(master_agent == 1)
    {
        player_last_choice = 2;
        return player_last_choice;
    }
    else
    {
        player_last_choice = 1;
        return player_last_choice;
    }
}

//All Cooperation Strategy
int ALLC()
{
    player_last_choice = 1;
    return player_last_choice;
}

int main()
{

    int choice;
    int player2_strategy;
    double secs;

    back:
    cout<<" Please enter your choice from the options ";
    cout<<"\n 1. Model 1: Simulation between 2 agents";
    cout<<"\n 2. Exit";
    cout<<"\n Enter your choice here : ";
    cin>>choice;

    if(choice == 1)
    {
        cout<<"\n\n Creating Simulation";
        first_move = 0;
        //Strategy 1
        t0 = get_timestamp();
        // Process
        cout<<"\n Implementing Strategy 1: Tit For Tat(TFT) ";
        opponent_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = TFT();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        cout<"\n\n";
        system("PAUSE");

        //Strategy 2
        t0 = get_timestamp();
        cout<<"\n Implementing Strategy 2: Win-Stay, Lose-Switch(WSLS) ";
        opponent_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = WSLS();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        cout<"\n\n";
        system("PAUSE");

        //Strategy 3
        t0 = get_timestamp();
        cout<<"\n Implementing Strategy 3: Generous Tit-For-Tat(GTFT) ";
        opponent_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = GTFT();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        cout<"\n\n";
        system("PAUSE");

        //Strategy 4
        t0 = get_timestamp();
        cout<<"\n Implementing Strategy 4: Zero-Determinant GTFT ";
        opponent_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = ZDGTFT();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        cout<"\n\n";
        system("PAUSE");

        cout<<"\n\n Implementing same strategies with defection as first move";

        first_move = 0;
        //Strategy 1
        t0 = get_timestamp();
        cout<<"\n\n Implementing Strategy 1: Tit For Tat(TFT) ";
        opponent_defect_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = TFT();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        cout<"\n\n";
        system("PAUSE");

        //Strategy 2
        t0 = get_timestamp();
        cout<<"\n Implementing Strategy 2: Win-Stay, Lose-Switch(WSLS) ";
        opponent_defect_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = WSLS();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        cout<"\n\n";
        system("PAUSE");

        //Strategy 3
        t0 = get_timestamp();
        cout<<"\n Implementing Strategy 3: Generous Tit-For-Tat(GTFT) ";
        opponent_defect_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = GTFT();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        cout<"\n\n";
        system("PAUSE");

        //Strategy 4
        t0 = get_timestamp();
        cout<<"\n Implementing Strategy 4: Zero-Determinant GTFT ";
        opponent_defect_stategy();
        cout<<"\n Player 1 Strategy : "<<opponent_last_choice;
        player2_strategy = ZDGTFT();
        cout<<"\n Player 2 Strategy : "<<player2_strategy;
        if(opponent_last_choice == 1 && player2_strategy == 1)
        {
            cout<<"\n Both Players have chosen to Cooperate";
        }
        else if(opponent_last_choice == 1 && player2_strategy == 2)
        {
            cout<<"\n Player 1 receives Non-Beneficial Payoff and Player 2 receives Temptation Payoff";
        }
        else if(opponent_last_choice == 2 && player2_strategy == 1)
        {
            cout<<"\n Player 2 receives Non-Beneficial Payoff and Player 1 receives Temptation Payoff";
        }
        else
        {
            cout<<"\n Both Players receive a punishment payoff";
        }
        t1 = get_timestamp();
        secs = (t1 - t0) / 1000000.0L;
        cout<<"\n Execution Time : "<<secs<<"\n";
        goto back;
    }
    else if(choice == 2)
    {
        cout<<"\n\n";
        system("PAUSE");
        return 0;
    }
    else
    {
        cout<<"\n\n Invalid choice, please try again";
        goto back;
    }
}

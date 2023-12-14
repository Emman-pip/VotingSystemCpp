#include <iostream>
#include <string>
#include <map>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <cstdlib>
#include <stdlib.h> 
#include <typeinfo>

using namespace std;

// FLow of program
//     1. welcome user (prompt to continue)
//     2. choose option (vote, results, add candidates, exit)
//         if vote -> go to vote interface
//         if add -> add interface
//         if results -> result interface

//     vote:
//         display for presidents -> prompt to choose 1 or abstain
//         display for vice presidents -> prompt to choose 1 or abstain
//         display for secretary -> prompt to choose 1 or abstain
//         display for treasurer -> prompt to choose 1 or abstain
//         display for councilor -> prompt to choose 1 or abstain = 3x
//         prompt that voted casted specifically
//         prompt to exit or new vote
//     add:
//         display positions -> prompt to add name or back
//     results:
//         displat results per candidate

class ClearTerminal{
public:
    ClearTerminal(){
        try 
        {
            system("clear");
        } catch (exception e)
        {
            system("cls");
        }
    }
};

class Candidate{
public:
    string name;
    int votes;
};

class CandidatesData {
    public:
    
    map < int, Candidate > hashmap;
    // make array for parameters
    void defaultCandidates(string names[], int sizeNum)
    {
    const int sizeOf = sizeof(string);
    // cout << sizeof(names) << " " << sizeOf << endl;
        try 
        {
            for (int i = 0; i < sizeNum; i++)
            {
                map < string, int > insideHasmap;
                Candidate arr;
                arr.name = names[i];
                arr.votes = 0;
                hashmap.insert(make_pair(i, arr));
            }

        } catch (int num)
        {
            cout << "ERROR:" << endl;
        }
    }
};

class AllCandidatesData {
private:
    string presNames[4] = {"Abstain", "Noynoy Perez", "Jacques Medrana", "Morgana Militig"};
    string vPresNames[4] = {"Abstain", "Leni Platon", "Jack Roberts", "Cort Nilarman"};
    string secretariesNames[4] = {"Abstain", "Sta Anna Bernardo", "Joshua Padilla", "Leila De Pande"};
    string treasurerNames[4] = {"Abstain", "Janet Naples", "Friedrich Newton", "Friedmann Hughes"};
    string councilorNames[7] = {"Abstain", "Norman Footlocker", "Paul Accent", "Mark Comia", "Jacky Telet", "Joan Delos Santos", "Tilet Ramos"};
public:
    CandidatesData presidents;
    CandidatesData vice;
    CandidatesData secretaries;
    CandidatesData treasurers;
    CandidatesData councilors;

    AllCandidatesData(){
        presidents.defaultCandidates(presNames, sizeof(presNames)/sizeof(string));
        vice.defaultCandidates(vPresNames, sizeof(vPresNames)/sizeof(string));
        secretaries.defaultCandidates(secretariesNames, sizeof(secretariesNames)/sizeof(string));
        treasurers.defaultCandidates(treasurerNames, sizeof(treasurerNames)/sizeof(string));
        councilors.defaultCandidates(councilorNames, sizeof(councilorNames)/sizeof(string));
    }


};

class Interface 
{
public:
    int welcome(){
        ClearTerminal();
        cout << "\n========== WELCOME TO STUDENT VOTING SYSTEM ==========\n" << endl;
        cout << "Please choose an option:" << endl;
        cout << "       1. Vote\n       2. See results\n       3. Add candidates\n       4. Exit" << endl;
        int choice;
        cout << "\nCHOOSE OPTION: ";
        cin >> choice;
        cout << "\n" << endl;
        return choice;
    }
    void votingFullInterface(AllCandidatesData* data2){
        CandidatesData* pres = &data2->presidents; 
        CandidatesData* vp = &data2->vice; 
        CandidatesData* sec = &data2->secretaries; 
        CandidatesData* tres = &data2->treasurers; 
        CandidatesData* coun = &data2->councilors; 

        CandidatesData* candidatesMap[5] = {pres, vp, sec, tres, coun};

        string positions[5] = {"President", "Vice President", "Secretary", "Treasurer", "Councilors"};

        bool condition = true;
        for (int i = 0; i < sizeof(positions)/sizeof(string); i++)
        {
            ClearTerminal();

            try 
            {
                if (positions[i] == positions[4])
                {
                    for (int v = 3; v > 0; v--)
                    {   
                        ClearTerminal();
                        string text = positions[i] + "(" + to_string(v) + ")";
                        int vote = voteInterface(text , *candidatesMap[i]);
                        candidatesMap[i]->hashmap.at(vote).votes++;
                    }
                    break;
                }
                int vote = voteInterface(positions[i], *candidatesMap[i]);
                candidatesMap[i]->hashmap.at(vote).votes++;
                // cout << "TOTAL VOTE: " << candidatesMap[i]->hashmap.at(vote).name << candidatesMap[i]->hashmap.at(vote).votes;
                // sleep(5);
            } catch (std::out_of_range range)
            {
                cout << "You entered an invalid input. Please restart the voting process. \nPress any character and enter to continue."; 
                string err;
                cin >> err;

                return;
            }
        }

        cout << "\n========== THANK YOU FOR VOTING ==========\n" << endl;
        sleep(3);

    }
    void results(AllCandidatesData* data2){
        CandidatesData* pres = &data2->presidents;
        CandidatesData* vp = &data2->vice; 
        CandidatesData* sec = &data2->secretaries; 
        CandidatesData* tres = &data2->treasurers; 
        CandidatesData* coun = &data2->councilors; 

        CandidatesData* candidatesMap[5] = {pres, vp, sec, tres, coun};
        // candidatesMap[0] -> data.presidents;
        string positions[5] = {"President", "Vice President", "Secretary", "Treasurer", "Councilors"};
        ClearTerminal();
        for (int i = 0; i <  sizeof(positions)/sizeof(string); i++){
            cout << "\n========== " << positions[i] << " tally ==========\n" << endl;
            for (int v = 0; v < candidatesMap[i]->hashmap.size(); v++){
                cout << "  " << candidatesMap[i]->hashmap.at(v).name << " \n         vote got: " << candidatesMap[i]->hashmap.at(v).votes << "\n" << endl;
            }
        }

        while (true){
            cout << "enter 'OK' to exit: ";
            string ok;
            cin >> ok;
            if (ok == "OK"){
                break;
            }
        }
    }
    void addCandidate(AllCandidatesData* data){
        CandidatesData* pres = &data->presidents;
        CandidatesData* vp = &data->vice;
        CandidatesData* sec = &data->secretaries;
        CandidatesData* tres = &data->treasurers;
        CandidatesData* coun = &data->councilors;
        bool condition = true;

        CandidatesData* positions[5] = {pres, vp, sec, tres, coun};
        int choice;
        string name;

        while (condition){
            cout << "=======================================================================" << endl;
            cout << "Choose a position a run: \n  1. President\n  2. Vice President\n  3. Secretary\n  4. Treasurer\n  5. Councilor" << endl;
            cout << "\nENTER THE DESIRED POSITION: ";
            cin >> choice;
            
            if (choice > 5 || choice < 1){
                cout << "Invalid position" << endl;
                continue;
            }

            cout << endl << "\n ENTER YOUR NAME: ";
            cin >> name;

            condition = false;
        }
        Candidate newCandidate;
        newCandidate.name = name;
        int index = positions[choice-1]->hashmap.size();
        newCandidate.votes = 0;
        positions[choice-1]->hashmap.insert(make_pair(
            index,
            newCandidate
        )
        );

        cout << "CANDIDATE SUCCESSFULLY REGISTERED" << endl;
        sleep(2);
    }
private:
    int voteInterface(string position, CandidatesData data){
        const int size = data.hashmap.size();

        cout << "\n============================== Please Select Your " << position << " ==============================\n" << endl;
        
        for (int i = 0; i < size; i++){
            cout << "       " << i << ". " << data.hashmap.at(i).name << endl;
        }    
        cout << "\nCHOOSE CANDIDATE NUMBER: ";

        int choice;
        cin >> choice;
        cout << "\n" << endl ; 
        return choice;
    }
};

class System {
public:
    System(){
        AllCandidatesData data;
    
    bool condition = true;
    while (condition)
    {
        Interface UI;
        string pres = "pres";
        
        int choice = UI.welcome();
        
        switch (choice)
        {
        case 1:
            UI.votingFullInterface(&data);
            break;
        case 2:
            UI.results(&data);
            break;
        case 3:
            UI.addCandidate(&data);
            cout << 3 << endl;
            break;
        case 4:
            cout << "Thank you for using the Student Voting System\n" << endl;
            condition = false;
            break;
        }
    }
    }
};

int main()
{  
    System();   
    return 0;
}
/// STOEAN Andrei-Cosmin
/// 321AC
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

// the files you are working on in this project
#define USERS "users.txt"
#define PLAYERS "players.txt"
#define SUPERVISORS "supervisors.txt"
#define REFRESH "refresh.txt"

using namespace std;

// user class
class Users{
    protected:
        string lastname;
        string firstname;
        string city;
        unsigned debt;
        unsigned weight;
};

// subclass players
class Players : public Users{
    private:
        int number;
        int supervisor;
    public:
        // method for calculating the total amount of debts of all players
        // and the calculation of the players' debts on each supervisor
        long long int debtCalculation(long long int debtArray[]){
            long long int sum = 0;
            int i;
            ifstream inFile;
            inFile.open(PLAYERS);
            for(i = 0; i < 9; ++i){
                debtArray[i] = 0;
            }
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                // sum = the variable in which the sum is stored
                sum += this->debt;
                for(i = 1; i <= 9; ++i){
                    if(this->supervisor == i){
                        // the vector in which the debt of the players for each supervisor is retained
                        debtArray[i-1] += this->debt;
                    }
                }
            }
            inFile.close();
            return sum;
        }
        // the method for print players
        void printPlayers(){
            ifstream inFile;
            inFile.open(PLAYERS);
            cout << endl;
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                cout << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->supervisor << endl;
            }
            cout << endl;
            inFile.close();
        }
        // the method for setting each player in a randomly generated number, duty and weight system
        void setPlayers(){
            ifstream inFile;
            ofstream outFile;
            int index;
            int count = 0;
            inFile.open(PLAYERS);
            outFile.open(REFRESH);
            while(inFile >> index >> this->lastname >> this->firstname >> this->city){
                this->number = ++count;
                this->debt = rand() % 90001 + 10000;
                this->weight = rand() % 51 + 50;
                outFile << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << endl;
            }
            inFile.close();
            outFile.close();
            // modifying the file in which players are retained with an auxiliary file
            remove(PLAYERS);
            rename(REFRESH, PLAYERS);
        }
        // the method for allocating supervisors for each competitor
        void aloccSupervisors(){
            ifstream inFile;
            ofstream outFile;
            int index, random, ok;
            int xSupervisor[9];
            for(int i = 0; i < 9; ++i){
                xSupervisor[i] = 0;
            }
            inFile.open(PLAYERS);
            outFile.open(REFRESH);
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight){
                random = rand() % 9 + 0;
                // if the number of competitors for a supervisor has reached the appropriate value
                // avoids the generation of that supervisor for a competitor
                while(xSupervisor[random] > 10){
                    random = rand() % 9 + 0;
                }
                xSupervisor[random]++;
                this->supervisor = random+1;
                outFile << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->supervisor << endl;
            }
            inFile.close();
            outFile.close();
            remove(PLAYERS);
            rename(REFRESH, PLAYERS);
        }
        // method for the game 'Red Light Green Light'
        // with the elimination of the players who have the serial number even
        void RedLightGreenLight(){
            ifstream inFile;
            ofstream outFile;
            inFile.open(PLAYERS);
            outFile.open(REFRESH);
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                if(this->number % 2 != 0){
                    outFile << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->supervisor << endl;
                }
            }
            inFile.close();
            outFile.close();
            remove(PLAYERS);
            rename(REFRESH, PLAYERS);
        }
        // Tug Of War method
        void TugOfWar(){
            ifstream inFile;
            ofstream outFile;
            inFile.open(PLAYERS);
            outFile.open(REFRESH);
            int squads[4], numberPlayers = 50, members[50], weights[4], loser = 5, loserWeight = 999999999;
            int random, ok, num;
            for(int i = 0; i < 4; ++i){
                squads[i] = 0;
                weights[i] = 0;
            }
            // algorithm for dividing players into 4 equal teams
            for(int i = 0; i < numberPlayers; ++i){
                ok = 0;
                for(int j = 0; j < 4; ++j){
                    if(squads[j] < 12){
                        ok = 1;
                    }
                }
                if(ok == 0){
                    members[i] = -1;
                }
                else{
                    random = rand() % 4 + 0;
                    while(squads[random] > 11){
                        random = rand() % 4 + 0;
                    }
                    members[i] = random;
                    squads[random]++;
                }
            }
            // the algorithm for dueling teams on the weight of the players
            // weights [] = vector in which the weights of the players from each team are added together
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                num = this->number / 2;
                for(int i = 0; i < 4; ++i){
                    if(i == members[num]){
                        weights[i] += this->weight;
                    }
                }
            }
            inFile.close();
            for(int i = 0; i < 4; ++i){
                if(weights[i] < loserWeight){
                    loserWeight = weights[i];
                    loser = i;
                }
            }
            inFile.open(PLAYERS);
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                num = this->number / 2;
                if(members[num] != loser){
                    outFile << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->supervisor << endl;
                }
            }
            inFile.close();
            outFile.close();
            remove(PLAYERS);
            rename(REFRESH, PLAYERS);
        }
        // method for the game 'Marbles'
        void Marbles(){
            ifstream inFile;
            ofstream outFile;
            inFile.open(PLAYERS);
            outFile.open(REFRESH);
            int random[100], k, i, winners[100], j;
            k = 0;
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                // generating a random number for each player
                random[k] = rand() % 1000 + 10;
                k++;
            }
            inFile.close();
            inFile.open(PLAYERS);
            // in case of odd number of players, the last player will go directly to the final
            if(k%2 != 0){
                j = 0;
                for(i = 0; i < k; ++i){
                    // the numbers of each player are compared and each is chosen under the winner
                    if(random[i] > random[i+1]){
                        winners[j] = i+1;
                    }
                    else{
                        winners[j] = i;
                    }
                    j++;
                    i++;
                }
            }
            else{
                j = 0;
                for(i = 0; i < k-1; ++i){
                    if(random[i] > random[i+1]){
                        winners[j] = i+1;
                    }
                    else{
                        winners[j] = i;
                    }
                    j++;
                    i++;
                }
                winners[j] = k-1;
            }
            i = 0;
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                for(k = 0; k < j; ++k){
                    if(winners[k] == i){
                        outFile << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->supervisor << endl;
                    }
                }
                i++;
            }
            inFile.close();
            outFile.close();
            remove(PLAYERS);
            rename(REFRESH, PLAYERS);
        }
        // method for the game 'Genken'
        void Genken(){
            ifstream inFile;
            ofstream outFile;
            int i, winner;
            inFile.open(PLAYERS);
            outFile.open(REFRESH);
            int len = 0;
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                len++;
            }
            inFile.close();
            inFile.open(PLAYERS);
            int random1, random2;
            // two different random numbers are generated between the last two players
            winner = len-1;
            for(i = len-2; i >= 0; --i){
                random1 = rand() % 3 + 1;
                random2 = rand() % 3 + 1;
                while(random2 == random1){
                    random2 = rand() % 3 + 1;
                }
                // the winner is chosen
                // and the sequence is repeated until only one winner remains
                if((random1 == 1 && random2 == 2) || (random1 == 2 && random2 == 3) || (random1 == 3 && random2 == 1)){
                    winner = i;
                }
            }
            i = 0;
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor){
                if(i == winner){
                    outFile << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->supervisor << endl;
                }
                i++;
            }
            inFile.close();
            outFile.close();
            remove(PLAYERS);
            rename(REFRESH, PLAYERS);
        }
        // method for finding the winner's number
        // and it is transmitted to 'main ()' its debt
        int winner(int *no){
            ifstream inFile;
            inFile.open(PLAYERS);
            inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor;
            cout << endl << "The winner is " << this->lastname << ' ' << this->firstname << endl;
            *no = this->number;
            inFile.close();
            return this->debt;
        }
        // the method for finding the winner's supervisor
        int supervisorWinner(){
            int no;
            ifstream inFile;
            inFile.open(PLAYERS);
            inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->supervisor;
            inFile.close();
            no = this->supervisor;
            return no;
        }
};


// subclass supervisors
class Supervisors : public Users{
    private:
        int number;
        string form;
        long long int win;
    public:
        // the method for random generation of supervisors but also of players
        void setSupervisors(){
            ifstream inFile;
            ofstream outFile1, outFile2;
            int index;
            int xForm[9];
            int count = 0;
            int array[9];
            int ok, ok2;
            int count2 = 0;
            int count3[3];
            int random = rand() % 108 + 1;
            array[0] = random;
            // random generation of numbers for the choice of supervisors
            for(int i = 1; i < 9; ++i){
                ok2 = 0;
                while(ok2 == 0){
                    random = rand() % 108 + 1;
                    ok2 = 1;
                    for(int j = 0; j < i; ++j){
                        if(random == array[j]){
                            ok2 = 0;
                        }
                    }
                }
                array[i] = random;
            }
            inFile.open(USERS);
            // if the user file is missing, the program will end
            try{
                if(inFile){
                    cout << endl << "The file " << USERS << " exists!" << endl;
                }
                else{
                    throw 404;
                }
            }
            catch(int num){
                cout << endl << "The file " << USERS << " doesn't exist!" << endl;
                cout << "Make sure the " << USERS << " file is in the same folder as the application!" << endl;
                exit(0);
            }
            outFile1.open(PLAYERS);
            outFile2.open(SUPERVISORS);
            count3[0] = count3[1] = count3[2] = 0;
            for(int i = 0; i < 9; ++i){
                random = rand() % 3 + 0;
                while(count3[random] > 2){
                    random = rand() % 3 + 0;
                }
                xForm[i] = random;
                count3[random]++;
            }
            while(inFile >> index >> this->lastname >> this->firstname >> this->city){
                ok = 0;
                for(int i = 0; i < 9; ++i){
                    // if the serial number has been chosen, the user
                    // will be appointed supervisor
                    // otherwise, he will be named player
                    if(index == array[i]){
                        this->number = ++count;
                        this->debt = rand() % 90001 + 10000;
                        this->weight = rand() % 51 + 50;
                        switch(xForm[i]){
                            case 0:
                                this->form = "rectangle";
                                break;
                            case 1:
                                this->form = "triangle";
                                break;
                            case 2:
                                this->form = "circle";
                                break;
                        }
                        outFile2 << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->form << endl;
                        ok = 1;
                    }
                }
                if(ok == 0){
                    outFile1 << ++count2 << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << endl;
                }
            }
            inFile.close();
            outFile1.close();
            outFile2.close();
        }
        // the method for the winning supervisor
        // who transmits his debt to 'main ()'
        long long int winner(int swinner){
            long long int debtwinner;
            ifstream inFile;
            inFile.open(SUPERVISORS);
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->form){
                if(swinner == this->number){
                    debtwinner = this->debt;
                }
            }
            inFile.close();
            return debtwinner;
        }
        // the method for calculating the earnings of each supervisor
        // for eliminated players
        void setWin(long long int debtArray[], int debtWinner, int noWinner){
            ifstream inFile;
            ofstream outFile;
            inFile.open(SUPERVISORS);
            outFile.open(REFRESH);
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->form){
                for(int i = 0; i < 9; ++i){
                    if(i+1 == this->number){
                        this->win = debtArray[i];
                        if(this->number == noWinner){
                            this->win = debtWinner;
                        }
                        outFile << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << this->city << ' ' << this->debt << ' ' << this->weight << ' ' << this->form << ' ' << this->win << endl;
                    }
                }
            }
            inFile.close();
            outFile.close();
            remove(SUPERVISORS);
            rename(REFRESH, SUPERVISORS);
        }
        // the method for print the amount won in descending order
        // of supervisors
        void printSupervisors(){
            ifstream inFile;
            int arr[10], no[10], n, sum;
            int i, j, temp;
            inFile.open(SUPERVISORS);
            n = 0;
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->form >> this->win){
                arr[n] = this->win;
                no[n] = this->number;
                n++;
            }
            // implementing a 'bubble sort' to find the correct order
            for (i = 0; i < n-1; i++){
                for (j = 0; j < n-i-1; j++){
                    if (arr[j] < arr[j+1]){
                        temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;

                        temp = no[j];
                        no[j] = no[j+1];
                        no[j+1] = temp;
                    }
                }
            }
            for(i = 0; i < n; ++i){
                inFile.close();
                inFile.open(SUPERVISORS);
                while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->form >> this->win){
                    if(this->number == no[i]){
                        sum = this->win - this->debt;
                        cout << this->number << ' ' << this->lastname << ' ' << this->firstname << ' ' << sum << endl;
                    }
                }
            }
            inFile.close();
        }
        // the method for finding winning teams of supervisors
        string winSquadSupervisor(){
            string formWin;
            ifstream inFile;
            long long int wins[3];
            int i;
            for(i = 1; i <= 3; ++i){
                wins[i] = 0;
            }
            inFile.open(SUPERVISORS);
            while(inFile >> this->number >> this->lastname >> this->firstname >> this->city >> this->debt >> this->weight >> this->form >> this->win){
                if(this->form == "rectangle"){
                    wins[1] += this->win;
                    wins[1] -= this->debt;
                }
                if(this->form == "triangle"){
                    wins[2] += this->win;
                    wins[2] -= this->debt;
                }
                if(this->form == "circle"){
                    wins[3] += this->win;
                    wins[3] -= this->debt;
                }
            }
            inFile.close();
            long long int win = 0, j;
            for(i = 1; i <= 3; ++i){
                if(wins[i] > win){
                    win = wins[i];
                    j = i;
                }
            }
            switch(j){
                case 1:
                    formWin = "rectangle";
                break;
                case 2:
                    formWin = "triangle";
                    break;
                case 3:
                    formWin = "circle";
                break;
            }
            return formWin;
        }

};

// templates to see the end of each game
template <class game>
void gameEnded(game a){
    cout << a << " game completed successfully !!!" << endl;
}

// main function of the project
// basically, the main menu
int main(){
    long long int sumDebtPlayers, sumDebtSupervisors, debtWinnerSupervisor;
    int debtWinner, swinner, winner, age;
    long long int debtArray[9];
    string squadSupervisor;

    // for random generation for each program run
    srand(time(NULL));

    cout << endl << "***** Squid Game *****" << endl;
    cout << endl << "Because our game is not for children, please enter your age: ";
    cin >> age;
    try{
        if(age >= 18){
            cout << "Access granted! You are old enough" << endl;
        }
        else{
            throw(age);
        }
    }
    catch(int num){
        cout << "Access denied! You must be at least 18 years old" << endl;
        cout << "Your age is " << num << endl;
        exit(0);
    }

    cout << endl << "***** Hello and welcome in Squid Game! *****" << endl;
    cout << "\tby STOEAN ANDREI-COSMIN" << endl;

    cout << endl << "---> Random allocation for supervisors" << endl;

    Supervisors supervisors;
    supervisors.setSupervisors();

    cout << endl << "---> Random allocation for players" << endl;

    Players players;
    players.setPlayers();

    cout << endl << "---> Associating each player with the randomly selected supervisor" << endl;

    players.aloccSupervisors();

    sumDebtPlayers = players.debtCalculation(debtArray);

    cout << endl << "---> Red Light Green Light MiniGame <---" << endl;
    players.RedLightGreenLight();
    players.printPlayers();
    gameEnded<string>("Red Light Green Light");


    cout << endl << "---> Tug of War MiniGame <---" << endl;
    players.TugOfWar();
    players.printPlayers();
    gameEnded<string>("Tug of War");

    cout << endl << "---> Marbles MiniGame <---" << endl;
    players.Marbles();
    players.printPlayers();
    gameEnded<string>("Marbles");

    cout << endl << "---> Genken MiniGame <---" << endl;
    players.Genken();
    players.printPlayers();
    gameEnded<string>("Genken");

    cout << endl << "---> Winner <---" << endl;
    debtWinner = players.winner(&winner);
    cout << endl << "The winner won " << sumDebtPlayers - debtWinner << endl;

    cout << endl << "---> Supervisor winner <---" << endl;
    swinner = players.supervisorWinner();
    debtWinnerSupervisor = supervisors.winner(swinner);
    cout << endl << "The supervisor winner won " << debtWinner*10 - debtWinnerSupervisor << endl;

    supervisors.setWin(debtArray, debtWinner*10 - debtWinnerSupervisor, swinner);

    cout << endl << "---> Supervisors <---" << endl << endl;
    supervisors.printSupervisors();

    cout << endl << "---> The team of supervisors who won the most <---" << endl;
    squadSupervisor = supervisors.winSquadSupervisor();
    cout << endl << "This form is " << squadSupervisor << endl;

    remove(PLAYERS);
    remove(SUPERVISORS);

    return 0;
}

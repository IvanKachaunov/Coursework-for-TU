#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

// exitChoice function
void exitChoice();

// Масив който ще ни послужи за гласовете в inputPartyNameInfo и getInformation();
int votes[5] = {0, 0, 0, 0, 0}; //{ "BSP", "GERB", "DPS", "ITN", "VMRO" }

class ElectionArea {    // клас Избирателен район
public:

    ElectionArea(); //  конструктор

    ~ElectionArea();    // деструктор

    string* areaName;                             // 1) Име на района
    double numOfVotersForArea;                    // 2) брой гласоподаватели за район
    int numOfPartiesToVote;                       // 3) брой партии за които се гласува
    vector <int> numOfVotesPerParty;              // 4) динамичен масив с броя на гласувалите на всяка партия
    const string partiesNameArray[5] = { "BSP", "GERB", "DPS", "ITN", "VMRO" };  // 5) масив от символни низове съдържащ имената на партиите


    //makeChoice function
    int makeChoice() {   // Тази функция дава правото на потребителя да направи избор

        int choice;

        cout << "1 - Pick an area" << endl; // Избери район
        cout << "2 - Vote for party" << endl;   // Гласувай за партия
        cout << "3 - Get Information from Party Vote" << endl; // Взима информация от гласуването за партии
        cout << "4 - Exit" << endl; // Изход

        cin >> choice;
        return choice;
    }

    // Декларация на inputAreaNameInfo() функция за създаване на файл от обекти - райони
    int inputAreaNameInfo();

    // Декларация на inputPartyNameInfo() функция за райони и партии
    int inputPartyNameInfo();

    // Декларация за getInformation() за прочитане на информация от inputPartyNameInfo()
    void getInformation();
};


ElectionArea::ElectionArea() {
}

ElectionArea::~ElectionArea() {
}

int main() {

    string areaChoice;

    ElectionArea electionInfo;

    switch (electionInfo.makeChoice()) { // Влизаме в меню в което можем да направим избор какво да правим
    case 1:
        electionInfo.inputAreaNameInfo();   // inputAreaNameInfo()
        break;
    case 2:
        electionInfo.inputPartyNameInfo();  //  inputPartyNameInfo()
        break;
    case 3:
        electionInfo.getInformation();  //  getInformation()
        break;
    case 4:
        exitChoice();   //  exitChoice()
        break;
    default:    // Когато натиснем клавиш по-различен от тези в cases, излизаме от програмата и получаваме съобщение
        cout << "Wrong key, please try again later" << endl;
    }
}

// дефиниране на inputAreaNameInfo() функция извън класа ElectionArea
int ElectionArea::inputAreaNameInfo() {

    // Създаваме обект от файл като "ofstream" ни позволява да осъществим връзка с файла за запис
    ofstream areaNames;

    // "ios::app" представлява отваряне на файл за запис, добавяне в края на файла
    areaNames.open("areaNames.txt", ios::app);

    // Обект за вмъкване на данни във файла
    ElectionArea electionInfo;

    string str;
    cin.ignore();

    if (!areaNames.is_open()) {  // Ако файла съществува и има проблеми с отварянето е възможно да трябва да се изтрие в директорията му
        cout << "Cannot open file, please check directory" << endl;
        main();
    }

    while (areaNames.is_open()) { // докато файла е отворен (може да се отвори)
        // Запитваме за район
        cout << "Enter area name or press N/n to exit: " << endl;
        getline(cin, str);

        // Достъпваме Низа с указател от класа и го референсваме
        electionInfo.areaName = &str;

        // Проверка която позволява връщане в меню
        if (str == "N" || str == "n") {

            areaNames.close();  // затваряме файла, който е отворен

            break;

        }

        //Записване на район в файл!
        areaNames << *electionInfo.areaName << '\n';
    }

    // Запитваме потребителя за гласуване за район в същата функция
    string value;
    cout << "Do you want to vote again y/n: " << endl;
    getline(cin, value);

    if (value == "y" || value == "Y") {
        inputAreaNameInfo();
    }
    else if (value == "n" || value == "N") {
        main();
    }
    else {
        // При случаи в коrто потребителя не отговаря както трябва получава същите въпроси докато не отговори с y/n
        while (value != "y" || value != "Y" || value != "n" || value != "N") {
            cout << "Do you want to vote again y/n: " << endl;
            cin >> value;

            if (value == "n" || value == "N") {
                main();
                break;
            }

            if (value == "y" || value == "Y") {
                inputAreaNameInfo();
                break;
            }

        }

    }
    return 0;
}

// дефиниране на inputPartyNameInfo() функция извън класа ElectionArea
int ElectionArea::inputPartyNameInfo() {

    ElectionArea electionInfo;
    electionInfo.partiesNameArray;
    electionInfo.numOfPartiesToVote;

    // Създаваме нов обект от файл като "ofstream" ни позволява да осъществим връзка с файла за запис
    ofstream areaNpartyNames;

    // отваряме нов файл, като "ios::app" представлява отваряне на файл за запис, добавяне в края на файла
    areaNpartyNames.open("areaNamesNparties.txt", ios::app);

    // Случай при заета директория или неуспех правим проверка
    if (!areaNpartyNames.is_open()) {
        cout << "Cannot open file, please check directory" << endl;
        main();
    }

    // Потребителят получава съобщение за глас за партия
    cout << "How many parties will you vote: " << endl;

    // При въвеждането на броя за глас за партия, ако потребителя не отговори както трябва получава същото съобщение
    while (!(cin >> electionInfo.numOfPartiesToVote)) {

        cin >> electionInfo.numOfPartiesToVote;
        cin.clear();
        cin.ignore();
    }

    // Потребителят получава пралото да гласума само за 1 партия, като той може да гласува след това отново и отново
    if (electionInfo.numOfPartiesToVote > 1 || electionInfo.numOfPartiesToVote < 1) {
        cout << "You can vote for only one party!" << endl;
        main();
    }

    string str;
    cin.ignore();
    // Завъртаме for loop за 1 глас за партия
    for (int i = 0; i <= electionInfo.numOfPartiesToVote; i++) {


        //Запитваме user за район от който ще гласува за партия
        cout << "Enter area name or press N/n to exit: " << endl;
        getline(cin, str);

        // Достъпваме Низа с указател от класа и го референсваме
        electionInfo.areaName = &str;

        // Потребителя получава правото да се откаже от гласуването ако иска, като може да се върне когато реши
        if (str == "N" || str == "n") {

            areaNpartyNames.close();    // Затваряме файла

            main();

            break;

        }

        string partyChoice;
        // Партии за които потребителя може да гласува(само 1 избор от всички!)
        cout << "Available parties: " << endl;
        cout << "GERB" << endl;
        cout << "BSP" << endl;
        cout << "DPS" << endl;
        cout << "ITN" << endl;
        cout << "VMRO" << endl;
        // Запитваме въпрос за партията за която ще гласува
        cout << "Which party would you like to vote for: " << endl;
        getline(cin, partyChoice);

        //{ "BSP", "GERB", "DPS", "ITN", "VMRO" }
        if (partyChoice == electionInfo.partiesNameArray[0]) { votes[0]++; }
        if (partyChoice == electionInfo.partiesNameArray[1]) { votes[1]++; }
        if (partyChoice == electionInfo.partiesNameArray[2]) { votes[2]++; }
        if (partyChoice == electionInfo.partiesNameArray[3]) { votes[3]++; }
        if (partyChoice == electionInfo.partiesNameArray[4]) { votes[4]++; }

        // Ако потребителя гласува за една от дадените партии той получава глас, който се въвежда във файла заедно с областта и партията
        if (partyChoice == electionInfo.partiesNameArray[0] || partyChoice == electionInfo.partiesNameArray[1] || partyChoice == electionInfo.partiesNameArray[2] ||
            partyChoice == electionInfo.partiesNameArray[3] || partyChoice == electionInfo.partiesNameArray[4]) {

            electionInfo.numOfVotesPerParty;    // Достъпваме Вектор от класа

            // Записваме информацията във файла
            areaNpartyNames << *electionInfo.areaName << " ";
            areaNpartyNames << partyChoice << " ";
            // Серии от проверки за записване на глас
            if (partyChoice == electionInfo.partiesNameArray[0]) {

                numOfVotesPerParty.push_back(1);

                ostream_iterator<int> output_iterator(areaNpartyNames, "\n");
                copy(numOfVotesPerParty.begin(), numOfVotesPerParty.end(), output_iterator);

                numOfVotesPerParty.clear();

            }
            else if (partyChoice == electionInfo.partiesNameArray[1]) {

                numOfVotesPerParty.push_back(1);

                ostream_iterator<int> output_iterator(areaNpartyNames, "\n");
                copy(numOfVotesPerParty.begin(), numOfVotesPerParty.end(), output_iterator);

                numOfVotesPerParty.clear();
            }
            else if (partyChoice == electionInfo.partiesNameArray[2]) {

                numOfVotesPerParty.push_back(1);

                ostream_iterator<int> output_iterator(areaNpartyNames, "\n");
                copy(numOfVotesPerParty.begin(), numOfVotesPerParty.end(), output_iterator);

                numOfVotesPerParty.clear();
            }
            else if (partyChoice == electionInfo.partiesNameArray[3]) {

                numOfVotesPerParty.push_back(1);

                ostream_iterator<int> output_iterator(areaNpartyNames, "\n");
                copy(numOfVotesPerParty.begin(), numOfVotesPerParty.end(), output_iterator);

                numOfVotesPerParty.clear();
            }
            else if (partyChoice == electionInfo.partiesNameArray[4]) {

                numOfVotesPerParty.push_back(1);
                ostream_iterator<int> output_iterator(areaNpartyNames, "\n");
                copy(numOfVotesPerParty.begin(), numOfVotesPerParty.end(), output_iterator);

                numOfVotesPerParty.clear();
            }

            areaNpartyNames.close();    // Затваряме файла

        }
        else {  // Ако потребителя не напише една от дадените по-нагоре партии излиза от прозореца за гласуване за партия
            cout << "Party not included in the list, please try again later" << endl;
            main();
        }
        string decision;
        // Потребителя получава възможност за повторно гласуване което се записва във файл заедно със старият глас
        cout << "Do you wanna vote again y/n:" << endl;
        getline(cin, decision);
        if (decision == "y" || decision == "Y") {
            inputPartyNameInfo();
            break;
        }
        else if (decision == "n" || decision == "N") {
            main();
            break;
        }
        else {
            // При въвеждане, ако потребителя не отговори както трябва получава същото съобщение
            while (decision != "n" || decision != "N" || decision != "y" || decision != "Y") {
                cout << "Do you wanna vote again y/n:" << endl;
                cin >> decision;
                if (decision == "y" || decision == "Y") {
                    inputPartyNameInfo();
                    break;
                }if (decision == "n" || decision == "N") {
                    main();
                    break;
                }
            }

        }
    }
    return 0;
}

//Дефинираме getInformation() за да прочетем информацията от файла за гласуване за партии
void ElectionArea::getInformation() {

    ElectionArea electionInfo;
    //Създваме обект от файл който може да прочете информацията от файла за гласуване за партии намиращ се в inputPartyNameInfo()
    ifstream ReadInfo("areaNamesNparties.txt", ios::in);

    int numOfVotes;
    string party;
    string city;

    vector <string> cityAlphabeticalOrder;  // Създаваме вектор който взима стринг

    while (getline(ReadInfo, city)) // Създаваме цикъл, който може да чете информация от inputPartyNameInfo() вероятно създадения файл за партии

        cityAlphabeticalOrder.push_back(city);  // Използваме push за добавяне на нов елемент

    sort(cityAlphabeticalOrder.begin(), cityAlphabeticalOrder.end());   // сортираме вектора

        // Извеждаме информацията от написанато от user по ред по азбуката
    for (size_t i = 0; i < cityAlphabeticalOrder.size(); i++) {
        cout << cityAlphabeticalOrder[i] << '\n';
    }

    // проверка за взимане на областите от votes[5];
    int total = 0;
    for (int i = 0; i <= 4; i++) {
        total += votes[i];
    }

    cout << endl << endl << "Total votes:" << endl;

    // взимаме от масива информация(партиите) и правиме математически проверки за изчисляване на % гласове
    cout << "BSP - " << votes[0] << " (" << votes[0]*100 / total << "%)" << endl;
    cout << "GERB - " << votes[1] << " (" <<votes[1]*100 / total << "%)" << endl;
    cout << "DPS - " << votes[2] <<  " (" <<votes[2]*100 / total << "%)" << endl;
    cout << "ITN - " << votes[3] <<  " (" <<votes[3]*100 / total << "%)" << endl;
    cout << "VMRO - " << votes[4] << " (" <<votes[4]*100 / total << "%)" << endl;



    cin.ignore();
    // При случай в който свърши четенето на информация от файл или няма файл за четене потребителя получава опция за връщане
    cout << "Press y/Y to go back: " << endl;
    string goBack;
    getline(cin, goBack);
    if (goBack == "y" || goBack == "Y") {
        main();
    }
    else {
        // При въвеждане, ако потребителя не отговори както трябва получава същото съобщение
        while (goBack != "y" || goBack != "Y") {
            //cin.ignore();
            cout << "Press y/Y to go back: " << endl;
            cin >> goBack;

            if (goBack == "y" || goBack == "Y") {
                main();
                break;
            }

        }
    }
}

// exitChoice function
void exitChoice() {
    // Помага на потребителя да излезе когато реши
    exit(EXIT_SUCCESS);

}

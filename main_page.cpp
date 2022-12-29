#include <wx/wx.h>
#include "main_page.h"
#include "konto.h"

// Tablica kont zawierajaca imiê i nazwisko, numer konta, stan konta, pin, limit karty, limit dzienny.
Account account_tab[7] = {
    {"Jan Kowalski", "10124057747613305935262356", 9000, 1231,200,100},
    {"Marek Nowak", "6817", 1000000, 1234,300,250},
    {"Miros³aw ¯ak", "85848300017585442846273250", 30000, 4321,300,200},
    {"Agata Mi³a", "68175033332807111661682749", 1000000, 9832,100,100},
    {"Janina Z¹bek", "68175012372807111661682749", 10000, 7834,500,500},
    {"Zygmunt Nowy", "43325012372807111661682749", 230000, 5632,600,200},
    {"Marek Nowak", "88653012372807111661682749", 50000, 9320,20,80},
};

string tmp_input=""; // Zmienna wykorzystywana do tymczasowego przechowywania wejœcia wprowadzonego przez u¿ytkownika.
string account_number=""; // Zmienna do której po klikniêciu danej karty przypisujemy numer konta zgodny z tym który jest w tablicy kont.
string account_number_transfer=""; // Zmienna pomocnicza do przechowania numeru konta, na które ma byæ wykonany przelew (wykorzystywana w funkcjach Tranfer...).
int transfer_tmp = 0; // Zmienna tymczasowa pozwalaj¹ca najpierw wpisaæ numer konta, a nastêpnie przejœæ do wprowadzenia kwoty (wykorzystywana w funkcjach Tranfer...).
string tranfer_txt = "WprowadŸ dane do przelewu\nNumer konta: "; // Zmienna przechowuj¹ca tekst który po wpisaniu numeru konta wyœwietla okreœlony komunikat, natomiast po wykonaniu ca³ego procesu przelewu ustawiana jest na wartoœæ pocz¹tkow¹.

enum IDs {
    TEXT_ID = 2,
    BT_OPEN_ACCOUNT_ID = 3,
    BT_DEPOSIT_ID = 4,
    BT_WITHDRAW_ID = 5,
    BT_TRANSFER_ID = 6,
    BT_INFO_ACCOUNT_ID = 7,
    BT_CLOSE_ACCOUNT_ID = 8,
    BT_NUMBER_ONE_ID = 9,
    BT_NUMBER_TWO_ID = 10,
    BT_NUMBER_THREE_ID = 11,
    BT_NUMBER_FOUR_ID = 12,
    BT_NUMBER_FIVE_ID = 13,
    BT_NUMBER_SIX_ID = 14,
    BT_NUMBER_SEVEN_ID = 15,
    BT_NUMBER_EIGHT_ID = 16,
    BT_NUMBER_NINE_ID = 17,
    BT_NUMBER_ZERO_ID = 18,
    BT_NUMBER_TWO_ZERO_ID = 19,
    BT_NUMBER_THREE_ZERO_ID = 20,
    BT_ENTER_ID = 21,
    BT_CLEAR_ID = 22,
    BT_CARD_ONE = 23,
    BT_CARD_TWO = 24,
    BT_CARD_THREE = 25,
};

wxBEGIN_EVENT_TABLE(MainPage, wxFrame)
    EVT_BUTTON(BT_OPEN_ACCOUNT_ID, MainPage::OpenAccount)
    EVT_BUTTON(BT_DEPOSIT_ID, MainPage::Deposit)
    EVT_BUTTON(BT_WITHDRAW_ID, MainPage::Withdraw)
    EVT_BUTTON(BT_TRANSFER_ID, MainPage::Transfer)
    EVT_BUTTON(BT_INFO_ACCOUNT_ID, MainPage::InfoAccount)
    EVT_BUTTON(BT_CLOSE_ACCOUNT_ID, MainPage::CloseAccount)
    EVT_BUTTON(BT_NUMBER_ONE_ID, MainPage::NumberOne)
    EVT_BUTTON(BT_NUMBER_TWO_ID, MainPage::NumberTwo)
    EVT_BUTTON(BT_NUMBER_THREE_ID, MainPage::NumberThree)
    EVT_BUTTON(BT_NUMBER_FOUR_ID, MainPage::NumberFour)
    EVT_BUTTON(BT_NUMBER_FIVE_ID, MainPage::NumberFive)
    EVT_BUTTON(BT_NUMBER_SIX_ID, MainPage::NumberSix)
    EVT_BUTTON(BT_NUMBER_SEVEN_ID, MainPage::NumberSeven)
    EVT_BUTTON(BT_NUMBER_EIGHT_ID, MainPage::NumberEight)
    EVT_BUTTON(BT_NUMBER_NINE_ID, MainPage::NumberNine)
    EVT_BUTTON(BT_NUMBER_ZERO_ID, MainPage::NumberZero)
    EVT_BUTTON(BT_NUMBER_TWO_ZERO_ID, MainPage::NumberTwoZero)
    EVT_BUTTON(BT_NUMBER_THREE_ZERO_ID, MainPage::NumberThreeZero)
    EVT_BUTTON(BT_ENTER_ID, MainPage::Enter)
    EVT_BUTTON(BT_CLEAR_ID, MainPage::Clear)
    EVT_BUTTON(BT_CARD_ONE, MainPage::CardOne)
    EVT_BUTTON(BT_CARD_TWO, MainPage::CardTwo)
    EVT_BUTTON(BT_CARD_THREE, MainPage::CardThree)
wxEND_EVENT_TABLE()

//G³ówne okno bankomatu, brak mo¿liwoœci zmiany rozmiaru okna.
MainPage::MainPage(): wxFrame(NULL, wxID_ANY, "Bankomat", wxDefaultPosition, wxDefaultSize, (wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)))
{     
    sizer = new wxBoxSizer(wxVERTICAL);

    TopPanel(sizer);
    BottomPanel(sizer);
}

// Górny panel, na którym znajduj¹ siê przyciski funkcyjne oraz ekran tekstowy.
void MainPage::TopPanel(wxBoxSizer* sizer) 
{
   panel_top = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(960, 500));
   panel_top->SetBackgroundColour(wxColor(87, 86, 82));

   sizer->Add(panel_top, 0, wxLEFT | wxTOP | wxRIGHT, 5);
    
   screen = new wxTextCtrl(panel_top, TEXT_ID, "Witamy w bankomacie !", wxPoint(180, 50), wxSize(600, 400), wxTE_READONLY | wxTE_MULTILINE);
    
   open_account = new wxButton(panel_top, BT_OPEN_ACCOUNT_ID, "Otwórz konto", wxPoint(0, 50), wxSize(180, 100));
   info_account = new wxButton(panel_top, BT_INFO_ACCOUNT_ID, "Informacje o koncie", wxPoint(0, 200), wxSize(180, 100));
   close_account = new wxButton(panel_top, BT_CLOSE_ACCOUNT_ID, "Zamknij konto", wxPoint(0, 350), wxSize(180, 100));
   withdraw = new wxButton(panel_top, BT_WITHDRAW_ID, "Wyp³ata", wxPoint(780, 200), wxSize(180, 100));
   deposit = new wxButton(panel_top, BT_DEPOSIT_ID, "Wp³ata", wxPoint(780, 50), wxSize(180, 100));
   transfer = new wxButton(panel_top, BT_TRANSFER_ID, "Przelew", wxPoint(780, 350), wxSize(180, 100));
   
   this->SetSizerAndFit(sizer);
}

// Dolny panel zawieraj¹cy klawiaturê numeryczn¹ oraz trzy karty, które mo¿na za³¹czyæ, aby wykonaæ na nich operacje. Na pocz¹tku wy³¹czone s¹: klawiatura, karty, przyciski funkcyjne oprócz "Otwórz konto".
void MainPage::BottomPanel(wxBoxSizer* sizer)
{
    panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(960, 500));
    panel_bottom->SetBackgroundColour(wxColor(168, 169, 173));

    sizer->Add(panel_bottom, 0, wxLEFT, 5);
    
    this->SetSizerAndFit(sizer);
    
    number_one = new wxButton(panel_bottom, BT_NUMBER_ONE_ID, "1", wxPoint(220, 10), wxSize(100, 100));
    number_two = new wxButton(panel_bottom, BT_NUMBER_TWO_ID, "2", wxPoint(340, 10), wxSize(100, 100));
    number_three = new wxButton(panel_bottom, BT_NUMBER_THREE_ID, "3", wxPoint(460, 10), wxSize(100, 100));
    enter = new wxButton(panel_bottom, BT_ENTER_ID, "ENTER", wxPoint(580, 10), wxSize(150, 100));
    card_one = new wxButton(panel_bottom, BT_CARD_ONE, "4321", wxPoint(780, 10), wxSize(150, 100));
    number_four = new wxButton(panel_bottom, BT_NUMBER_FOUR_ID, "4", wxPoint(220, 130), wxSize(100, 100));
    number_five = new wxButton(panel_bottom, BT_NUMBER_FIVE_ID, "5", wxPoint(340, 130), wxSize(100, 100));
    number_six = new wxButton(panel_bottom, BT_NUMBER_SIX_ID, "6", wxPoint(460, 130), wxSize(100, 100));
    clear = new wxButton(panel_bottom, BT_CLEAR_ID, "CLEAR", wxPoint(580, 130), wxSize(150, 100));
    card_two = new wxButton(panel_bottom, BT_CARD_TWO, "1234", wxPoint(780, 130), wxSize(150, 100));
    number_seven = new wxButton(panel_bottom, BT_NUMBER_SEVEN_ID, "7", wxPoint(220, 250), wxSize(100, 100));
    number_eight = new wxButton(panel_bottom, BT_NUMBER_EIGHT_ID, "8", wxPoint(340, 250), wxSize(100, 100));
    number_nine = new wxButton(panel_bottom, BT_NUMBER_NINE_ID, "9", wxPoint(460, 250), wxSize(100, 100));
    number_three_zero = new wxButton(panel_bottom, BT_NUMBER_THREE_ZERO_ID, "000", wxPoint(220, 370), wxSize(100, 100));
    number_two_zero = new wxButton(panel_bottom, BT_NUMBER_TWO_ZERO_ID, "00", wxPoint(340, 370), wxSize(100, 100));
    number_zero = new wxButton(panel_bottom, BT_NUMBER_ZERO_ID, "0", wxPoint(460, 370), wxSize(100, 100));
    card_three = new wxButton(panel_bottom, BT_CARD_THREE, "9320", wxPoint(780, 250), wxSize(150, 100));
    DisablePinPad();
    DisableFunctionPad();
    DisableCards();
}

// Funkcja pozwalaj¹ca za³¹czyæ wybran¹ kartê.
void MainPage::OpenAccount(wxCommandEvent& evt)
{
    screen->SetValue("Aby otworzyæ konto wsuñ kartê");
    EnableCards();
    open_account->Disable();
}

// Funkcja otwieraj¹ca wybrane konto, znajduj¹ce siê w tablicy, które zgadzadza siê z za³¹czon¹ kart¹ (numer karty oraz PIN). Po trzykrotnym b³êdnym wpisaniu numeru PIN, nastêpuje blokada karty oraz zrestowanie treœci.
void MainPage::AccountOpenFun(wxCommandEvent& evt)
{
    for (int i = 0; i < 7; i++)
    {
        if (account_tab[i].getAccountNumber() == account_number && account_tab[i].getLock() == true)
        {
            screen->SetValue("BLOKADA KARTY");
            wxMessageBox(wxT("Karta zblokowana"));
            ResetContent();
            return;
        }
        else if (!close_account->IsEnabled() && account_tab[i].getAccountNumber() == account_number && tmp_input == to_string(account_tab[i].getPin()))
        {
            current_user_index = i;
            EnableFunctionPad();
            screen->SetValue("Witamy!\n");
            DisablePinPad();
            open_account->Disable();
            is_login = true;
            return;
        }
        else
        {
            screen->SetValue("Nie poprawny PIN\nWprowadz ponownie: ");
        }
    }

    if (counter == 2)
    {
        screen->SetValue("BLOKADA KARTY");
        for (int i = 0; i < 7; i++)
        {
            if (account_tab[i].getAccountNumber() == account_number)
            {
                account_tab[i].setLock();
            }
        }

        wxMessageBox(wxT("Nastêpuje blokada karty"));
        ResetContent();
        return;
    }

    counter++;
    tmp_input = "";
}

// Funkcja pozwalaj¹ca zacz¹æ operacjê wp³aty pieniêdzy na konto.
void MainPage::Deposit(wxCommandEvent& evt)
{
    EnablePinPad();
    function_switch = 1;
    screen->SetValue("WprowadŸ kwotê do wp³aty: ");
    tmp_input = "0";
}

// Funkcja dokonuj¹ca wp³aty okreœlonej kwoty na konto.
void MainPage::DepositFun(wxCommandEvent& evt)
{
    amount = stoi(tmp_input);
    if (amount != 0)
    {
        if (amount % 500 == 0 || amount % 200 == 0 || amount % 100 == 0 || amount % 50 == 0 || amount % 20 == 0 || amount % 10 == 0)
        {
            account_tab[current_user_index].AddMoney(amount);
            InfoAccount(evt);
        }
        else
        {
            DisablePinPad();
            screen->AppendText("\nBankomat przyjmuje wartoœci w nomina³ach 500, 200, 100, 50, 20, 10");
        }
    }
    else
    {
        DisablePinPad();
        screen->SetValue("Brak kwoty wyp³aty");
    }
    tmp_input = "";
}

// Funkcja pozwalaj¹ca zacz¹æ operacjê wyp³aty pieniêdzy z konta.
void MainPage::Withdraw(wxCommandEvent& evt)
{
    EnablePinPad();
    function_switch = 2;
    screen->SetValue("WprowadŸ kwotê do wyp³aty: ");
    tmp_input = "0";
}

// Funkcja dokonuj¹ca wyp³aty okreœlonej kwoty z konta.
void MainPage::WithdrawFun(wxCommandEvent& evt)
{
    bool good_amount = false; // czy podana kwota bêdzie mo¿liwa do wyp³aty w okreœlonych nomina³ach
    bool atm_empty = false; // czy podana kwota bêdzie mo¿liwa do wyp³aty, je¿eli mamy w zasobniku wystarczaj¹ca iloœæ banknotów
    bool can_withdraw = false; // czy podana kwota bêdzie mo¿liwa do wyp³aty, je¿eli mamy w zasobniku wystarczaj¹ca iloœæ banknotów i bêdziemy w stanie dan¹ pe³n¹ kwotê wyp³aciæ
    bool while_flag = true; // flaga przerywaj¹ca pêtlê while, gdy podana kwota bêdzie mo¿liwa do wyp³aty oraz mamy banknoty w bankomacie
    int tab_tmp[6] = {}; // tymczasowa tablica do przechowania liczby banknotów
    int amount_copy = 0; // kopia kwoty
    amount = stoi(tmp_input);
    amount_copy = amount;
    if (amount != 0)
    {
        if (amount % 500 == 0 || amount % 200 == 0 || amount % 100 == 0 || amount % 50 == 0 || amount % 20 == 0 || amount % 10 == 0)
        {
            good_amount = true;
        }
        else
        {
            DisablePinPad();
            screen->AppendText("\nBankomat przyjmuje wartoœci w nomina³ach 500, 200, 100, 50, 20, 10");
        }
        if (can_withdraw == false && good_amount == true)
        {
            for (int i = 0; i < 6; i++)
            {
                tab_tmp[i] = atm_bil_tab[i];
            }
            while (while_flag)
            {
                for (int i = 0; i < 6; i++)
                {
                    if (tab_tmp[0] == 0 && tab_tmp[1] == 0 && tab_tmp[2] == 0 && tab_tmp[3] == 0 && tab_tmp[4] == 0 && tab_tmp[5] == 0)
                    {
                        atm_empty = true;
                        while_flag = false;
                        can_withdraw = false;
                        break;
                    }
                    if (amount_copy % atm_bank_note_tab[i] == 0 && tab_tmp[i] > 0 && atm_empty == false)
                    {
                        tab_tmp[i] = tab_tmp[i] - 1;
                        amount_copy = amount_copy - atm_bank_note_tab[i];
                        if (amount_copy == 0)
                        {
                            while_flag = false;
                            can_withdraw = true;
                            break;
                        }
                    }
                }
            }
        }
        if (atm_empty == true && can_withdraw == false)
        {
            DisablePinPad();
            screen->SetValue("Brak banknotów w bankomacie :(");
        }
        if (good_amount == true && can_withdraw == true && atm_empty == false)
        {
            if (account_tab[current_user_index].getLimitCard() >= amount)
            {
                account_tab[current_user_index].RemoveMoney(amount);
                account_tab[current_user_index].setLimitCard(account_tab[current_user_index].getLimitCard() - amount);
                for (int i = 0; i < 6; i++)
                {
                    atm_bil_tab[i] = tab_tmp[i];
                }
                InfoAccount(evt);
            }
            else
            {
                DisablePinPad();
                screen->SetValue("Wprowadzona kwota ");
                screen->AppendText(to_string(amount));
                screen->AppendText(" przekracza limit karty\nAktualny limit: ");
                screen->AppendText(to_string(account_tab[current_user_index].getLimitCard()));
            }
        }
    }
    else
    {
        DisablePinPad();
        screen->SetValue("Brak kwoty wyp³aty");
    }
    tmp_input = "";
}

// Funkcja pozwalaj¹ca zacz¹æ operacjê przelewu pieniêdzy (najpierw nale¿y wpisaæ numer konta, a póŸniej kwotê).
void MainPage::Transfer(wxCommandEvent& evt)
{
    EnablePinPad();
    function_switch = 3;
    screen->SetValue(tranfer_txt);
    tmp_input = "";
    if (transfer_tmp == 1)
    {
        function_switch = 4;
        tmp_input = "0";
    }
}

// Funkcja umo¿liwiaj¹ca pobraæ i sprawdziæ wpisany numer konta, na które ma byæ wykonany przelew.
void MainPage::TransferFunNumber(wxCommandEvent& evt)
{
    account_number_transfer = tmp_input;
    for (int i = 0; i < 7; i++)
    {
        if (account_tab[i].getAccountNumber() == account_number_transfer)
        {
            good_account_transfer_number = true;
            index_transfer = i;
            break;
        }
    }
    if (good_account_transfer_number == false)
    {
        DisablePinPad();
        screen->SetValue("Nie poprawny numer konta !\nNie wykonano przelewu.");
        return;
    }
    transfer_tmp++;
    tranfer_txt = "Wprowadz kwotê: ";
    Transfer(evt);
}

// Funkcja umo¿liwiaj¹ca pobraæ i sprawdziæ wspian¹ kwotê ( czy zgodna jest z dziennym limitem przelewów ). 
void MainPage::TransferFunAmount(wxCommandEvent& evt)
{
    amount = stoi(tmp_input);
    if (amount != 0)
    {
        if (account_tab[current_user_index].getLimitDayTransfer() >= amount)
        {
            account_tab[index_transfer].AddMoney(amount);
            account_tab[current_user_index].RemoveMoney(amount);
            account_tab[current_user_index].setLimitDayTransfer(account_tab[current_user_index].getLimitDayTransfer() - amount);
            InfoAccount(evt);
        }
        else
        {
            DisablePinPad();
            screen->AppendText("\nPrzekroczono dzienny limit !");
        }
    }
    else
    {
        DisablePinPad();
        screen->SetValue("Brak kwoty przelewu");
    }
    tmp_input = "";
    transfer_tmp = 0;
    function_switch = 3;
    good_account_transfer_number = false;
    tranfer_txt = "WprowadŸ dane do przelewu\nNumer konta: ";
}

// Funkcja wykonuj¹ca inne funkcjê, po wyborze odpowiedniej funkcji bankomatu.
void MainPage::Enter(wxCommandEvent& evt)
{
    if (is_login == false)
    {
        AccountOpenFun(evt);
    }
    else {
        switch (function_switch) {
        case 1: DepositFun(evt);
            break;
        case 2: WithdrawFun(evt);
            break;
        case 3: TransferFunNumber(evt);
            break;
        case 4: TransferFunAmount(evt);
            break;
        }
    }
}

// Funkcja wypisuj¹ca informacje o aktualnie zalogowanym koncie.
void MainPage::InfoAccount(wxCommandEvent& evt)
{
    screen->SetValue(account_tab[current_user_index].getAccountInfo());
    DisablePinPad();
}

// Funkcja resetuj¹ca treœæ.
void MainPage::ResetContent()
{
    DisablePinPad();
    DisableFunctionPad();
    DisableCards();
    open_account->Enable();
    tmp_input = "";
    counter = 0;
    current_user_index = 0;
    screen->SetValue("Witamy w bankomacie !");
}

// Funkcja wylogowuj¹ca aktualnie zalogowanego u¿ytkownika.
void MainPage::CloseAccount(wxCommandEvent& evt)
{
    ResetContent();
    is_login = false;
}

// Funkcja wy³¹czaj¹ca wszystkie przyciski klawiatury.
void MainPage::DisablePinPad()
{
    number_one->Disable();
    number_two->Disable();
    number_three->Disable();
    number_four->Disable();
    number_five->Disable();
    number_six->Disable();
    number_seven->Disable();
    number_eight->Disable();
    number_nine->Disable();
    number_zero->Disable();
    number_two_zero->Disable();
    number_three_zero->Disable();
    enter->Disable();
    clear->Disable();
}

// FUnkcja wy³¹czaj¹ca wszystkie przyciski funkcyjne górnego panelu oprócz "Otwórz konto".
void MainPage::DisableFunctionPad()
{
    info_account->Disable();
    close_account->Disable();
    withdraw->Disable();
    transfer->Disable();
    deposit->Disable();
}

// Funkcja wy³¹czaj¹ca karty.
void MainPage::DisableCards()
{
    card_one->Disable();
    card_two->Disable();
    card_three->Disable();
}

// Funkcja w³¹czaj¹ca wszystkie przyciski klawiatury.
void MainPage::EnablePinPad()
{
    number_one->Enable();
    number_two->Enable();
    number_three->Enable();
    number_four->Enable();
    number_five->Enable();
    number_six->Enable();
    number_seven->Enable();
    number_eight->Enable();
    number_nine->Enable();
    number_zero->Enable();
    number_two_zero->Enable();
    number_three_zero->Enable();
    enter->Enable();
    clear->Enable();
}

// Funkcja w³¹czaj¹ca wszystkie przyciski funkcyjne górnego panelu oprócz "Otwórz konto".
void MainPage::EnableFunctionPad()
{
    info_account->Enable();
    close_account->Enable();
    withdraw->Enable();
    transfer->Enable();
    deposit->Enable();

}

//// Funkcja w³¹czaj¹ca karty.
void MainPage::EnableCards()
{
    card_one->Enable();
    card_two->Enable();
    card_three->Enable();
}

// Funkcje pozwal¹ce obs³u¿yæ klawiaturê poprzez do³¹czenie odpowiedniej cyfry do tymczasowego wejœcia i wyœwietlenie na ekranie.
void MainPage::NumberOne(wxCommandEvent& evt)
{
    tmp_input += "1";
    screen->AppendText("1");
}

void MainPage::NumberTwo(wxCommandEvent& evt)
{
    tmp_input += "2";
    screen->AppendText("2");
}

void MainPage::NumberThree(wxCommandEvent& evt)
{
    tmp_input += "3";
    screen->AppendText("3");
}

void MainPage::NumberFour(wxCommandEvent& evt)
{
    tmp_input += "4";
    screen->AppendText("4");
}

void MainPage::NumberFive(wxCommandEvent& evt)
{
    tmp_input += "5";
    screen->AppendText("5");
}

void MainPage::NumberSix(wxCommandEvent& evt)
{
    tmp_input += "6";
    screen->AppendText("6");
}

void MainPage::NumberSeven(wxCommandEvent& evt)
{
    tmp_input += "7";
    screen->AppendText("7");
}

void MainPage::NumberEight(wxCommandEvent& evt)
{
    tmp_input += "8";
    screen->AppendText("8");
}
void MainPage::NumberNine(wxCommandEvent& evt)
{
    tmp_input += "9";
    screen->AppendText("9");
}

void MainPage::NumberZero(wxCommandEvent& evt)
{
    tmp_input += "0";
    screen->AppendText("0");
}

void MainPage::NumberTwoZero(wxCommandEvent& evt)
{
    tmp_input += "00";
    screen->AppendText("00");
}

void MainPage::NumberThreeZero(wxCommandEvent& evt)
{
    tmp_input += "000";
    screen->AppendText("000");
}

void MainPage::Clear(wxCommandEvent& evt)
{
    tmp_input = ""; 
    screen->SetValue(": ");
}

//Funckje obs³uguj¹ce dan¹ kartê poprzez zapisanie do zmiennej trzymczasowej numeru konta i wyœwietlenie komunikatu
void MainPage::CardOne(wxCommandEvent& evt)
{
    account_number = account_tab[2].getAccountNumber();
    screen->SetValue("Wpisz numer PIN aby otworzyæ konto: ");
    EnablePinPad();
    DisableCards();
}

void MainPage::CardTwo(wxCommandEvent& evt)
{
    account_number = account_tab[1].getAccountNumber();
    screen->SetValue("Wpisz numer PIN aby otworzyæ konto: ");
    EnablePinPad();
    DisableCards();
}

void MainPage::CardThree(wxCommandEvent& evt)
{
    account_number = account_tab[6].getAccountNumber();
    screen->SetValue("Wpisz numer PIN aby otworzyæ konto: ");
    EnablePinPad();
    DisableCards();
}

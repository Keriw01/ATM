#pragma once
class MainPage : public wxFrame
{
public:
    MainPage();
    
    bool is_login = false; // flaga okre�laj�ca, czy u�ytkownik jest zalogowany
    bool good_account_transfer_number = false; // flaga okre�laj�ca czy numer konta na kt�re ma by� wykonany przelew znajduje si� w tablicy
    int current_user_index; // index aktualnie zalogowanego u�ytkownika
    int counter = 0; // licznik pr�b wprowadzenia PIN
    int function_switch; // wykorzystywana do prze��czania funkcji po wci�ni�ciu Enter()
    int amount = 0; // wprowadzona kwota
    int index_transfer; // index konta w tablicy na kt�re ma by� wykonany przelew
    int atm_bil_tab[6] = { 0,0,0,0,1,1 }; // tablica zawieraj�ca ilo�� banknot�w w nast�puj�cyh nomina�ach: 500, 200, 100, 50, 20, 10
    int atm_bank_note_tab[6] = { 500,200,100,50,20,10 }; // tablica okre�laj�ca nomina�y banknot�w

    wxBoxSizer* sizer = nullptr;
    wxPanel* panel_top = nullptr;
    wxTextCtrl* screen = nullptr;
    wxButton* open_account = nullptr;
    wxButton* deposit = nullptr;
    wxButton* withdraw = nullptr;
    wxButton* transfer = nullptr;
    wxButton* info_account = nullptr;
    wxButton* close_account = nullptr;
    wxPanel* panel_bottom = nullptr;
    wxButton* number_one = nullptr;
    wxButton* number_two = nullptr;
    wxButton* number_three = nullptr;
    wxButton* number_four = nullptr;
    wxButton* number_five = nullptr;
    wxButton* number_six = nullptr;
    wxButton* number_seven = nullptr;
    wxButton* number_eight = nullptr;
    wxButton* number_nine = nullptr;
    wxButton* number_zero = nullptr;
    wxButton* number_two_zero = nullptr;
    wxButton* number_three_zero = nullptr;
    wxButton* enter = nullptr;
    wxButton* clear = nullptr;
    wxButton* card_one = nullptr;
    wxButton* card_two = nullptr;
    wxButton* card_three = nullptr;

    void TopPanel(wxBoxSizer* sizer);
    void BottomPanel(wxBoxSizer* sizer);
    void OpenAccount(wxCommandEvent& evt);
    void AccountOpenFun(wxCommandEvent& evt);
    void Deposit(wxCommandEvent& evt);
    void DepositFun(wxCommandEvent& evt);
    void Withdraw(wxCommandEvent& evt);
    void WithdrawFun(wxCommandEvent& evt);
    void Transfer(wxCommandEvent& evt);
    void TransferFunNumber(wxCommandEvent& evt);
    void TransferFunAmount(wxCommandEvent& evt);
    void InfoAccount(wxCommandEvent& evt);
    void CloseAccount(wxCommandEvent& evt);
    void NumberOne(wxCommandEvent& evt);
    void NumberTwo(wxCommandEvent& evt);
    void NumberThree(wxCommandEvent& evt);
    void NumberFour(wxCommandEvent& evt);
    void NumberFive(wxCommandEvent& evt);
    void NumberSix(wxCommandEvent& evt);
    void NumberSeven(wxCommandEvent& evt);
    void NumberEight(wxCommandEvent& evt);
    void NumberNine(wxCommandEvent& evt);
    void NumberZero(wxCommandEvent& evt);
    void NumberTwoZero(wxCommandEvent& evt);
    void NumberThreeZero(wxCommandEvent& evt);
    void Enter(wxCommandEvent& evt);
    void Clear(wxCommandEvent& evt);
    void CardOne(wxCommandEvent& evt);
    void CardTwo(wxCommandEvent& evt);
    void CardThree(wxCommandEvent& evt);
    void DisablePinPad();
    void DisableFunctionPad();
    void DisableCards();
    void EnablePinPad();
    void EnableFunctionPad();
    void EnableCards();
    void ResetContent();

    wxDECLARE_EVENT_TABLE();
};
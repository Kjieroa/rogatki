
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

enum Stan {
    OTWARTY,
    ZAMYKANIE,
    ZAMKNIETY,
    OTWIERANIE,
    ALARM
};

class Przejazd {
private:
    Stan stan = OTWARTY;

    bool pociag = false;
    bool samochod = false;
    bool alarm = false;

    int mandaty = 0;

    int licznikOtwierania = 0;
    int licznikZamykania = 0;

public:

    string nazwaStanu() {
        switch (stan) {
            case OTWARTY: return "OTWARTY";
            case ZAMYKANIE: return "ZAMYKANIE";
            case ZAMKNIETY: return "ZAMKNIETY";
            case OTWIERANIE: return "OTWIERANIE";
            case ALARM: return "ALARM";
        }

        return "NIEZNANY";
    }

    void ekran() {
        system("cls");

        cout << "====================================\n";
        cout << "         PRZEJAZD KOLEJOWY\n";
        cout << "====================================\n\n";

        cout << "Stan szlabanu: " << nazwaStanu() << endl;

        cout << "Pociag: "
             << (pociag ? "WYKRYTY" : "BRAK") << endl;

        cout << "Samochod: "
             << (samochod ? "NA PRZEJEZDZIE" : "BRAK") << endl;

        cout << "Alarm: "
             << (alarm ? "AKTYWNY" : "WYLACZONY") << endl;

        cout << "Liczba mandatow: " << mandaty << endl;

        cout << "\nOtwieranie: "
             << licznikOtwierania << "/5";

        cout << "\nZamykanie: "
             << licznikZamykania << "/5\n";

        cout << "\n====================================\n";
        cout << "1 - Wykrycie pociagu\n";
        cout << "2 - Otwieranie szlabanu (5 klikniec)\n";
        cout << "3 - Zamykanie szlabanu (5 klikniec)\n";
        cout << "4 - Wjazd samochodu\n";
        cout << "5 - Usuniecie samochodu / reset alarmu\n";
        cout << "6 - Pociag opuszcza przejazd\n";
        cout << "7 - Wyjscie\n";
        cout << "====================================\n";
    }

    void wlaczAlarm() {
        if (alarm) return;

        alarm = true;
        stan = ALARM;

        mandaty++;

        licznikOtwierania = 0;
        licznikZamykania = 0;

        cout << "\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "            ALARM!          \n";
        cout << "   NIEBEZPIECZNY WJAZD!     \n";
        cout << "     WYSTAWIONO MANDAT!     \n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

        cout << "Liczba mandatow: " << mandaty << endl;
    }

    void wykryjPociag() {
        if (pociag) {
            cout << "Pociag jest juz wykryty!\n";
            return;
        }

        if (stan != OTWARTY) {
            cout << "Nie mozna wykryc pociagu w tym stanie!\n";
            return;
        }

        pociag = true;

        cout << "WYKRYTO NADJEZDZAJACY POCIAG!\n";
        cout << "Nalezy zamknac szlaban!\n";
    }

    void zamykanie() {
        if (alarm || stan == ZAMKNIETY ||
            stan == OTWIERANIE || samochod || !pociag) {

            cout << "Nie mozna zamknac szlabanu!\n";

            if (samochod) {
                cout << "Samochod znajduje sie na przejezdzie!\n";
            }

            return;
        }

        if (stan == OTWARTY) {
            stan = ZAMYKANIE;
        }

        if (stan != ZAMYKANIE) return;

        licznikZamykania++;

        cout << "Klikniecie zamykania: "
             << licznikZamykania << "/5\n";

        if (licznikZamykania >= 5) {
            licznikZamykania = 0;
            licznikOtwierania = 0;

            stan = ZAMKNIETY;

            cout << "\nSZLABAN ZAMKNIETY!\n";
        }
    }

    void otwieranie() {
        if (alarm || stan == OTWARTY ||
            stan == ZAMYKANIE || pociag) {

            cout << "Nie mozna otworzyc szlabanu!\n";
            return;
        }

        if (stan == ZAMKNIETY) {
            stan = OTWIERANIE;
        }

        if (stan != OTWIERANIE) return;

        licznikOtwierania++;

        cout << "Klikniecie otwierania: "
             << licznikOtwierania << "/5\n";

        if (licznikOtwierania >= 5) {
            licznikOtwierania = 0;
            licznikZamykania = 0;

            stan = OTWARTY;

            cout << "\nSZLABAN OTWARTY!\n";
        }
    }

    void wjazdSamochodu() {
        if (samochod) {
            cout << "Samochod juz znajduje sie na przejezdzie!\n";
            return;
        }

        samochod = true;

        cout << "WYKRYTO SAMOCHOD!\n";

        if (stan == ZAMYKANIE ||
            stan == ZAMKNIETY ||
            stan == OTWIERANIE) {

            wlaczAlarm();
        }
        else {
            cout << "Samochod na otwartym przejezdzie.\n";
        }
    }

    void usunSamochod() {
        if (!samochod) {
            cout << "Nie ma samochodu na przejezdzie.\n";
            return;
        }

        samochod = false;

        cout << "Samochod opuscil przejazd.\n";

        if (alarm) {
            alarm = false;

            // Przywracamy bezpieczny stan.
            if (pociag) {
                stan = ZAMKNIETY;
            }
            else {
                stan = OTWARTY;
            }

            cout << "ALARM ZOSTAL WYLACZONY!\n";
        }
    }

    void przejazdPociagu() {
        if (!pociag) {
            cout << "Nie wykryto pociagu!\n";
            return;
        }

        if (stan != ZAMKNIETY && stan != ALARM) {
            cout << "Szlaban musi byc zamkniety!\n";
            return;
        }

        pociag = false;

        cout << "POCIAG OPUSCIL PRZEJAZD!\n";
        cout << "Mozna teraz otworzyc szlaban.\n";
    }

    void obsluz(char wybor) {

        if (alarm && wybor != '5' &&
            wybor != '6' && wybor != '7') {

            cout << "ALARM AKTYWNY!\n";
            cout << "Usun samochod przyciskiem 5.\n";
            return;
        }

        switch (wybor) {

            case '1':
                wykryjPociag();
                break;

            case '2':
                otwieranie();
                break;

            case '3':
                zamykanie();
                break;

            case '4':
                wjazdSamochodu();
                break;

            case '5':
                usunSamochod();
                break;

            case '6':
                przejazdPociagu();
                break;

            case '7':
                cout << "Koniec programu.\n";
                exit(0);

            default:
                cout << "Nieznany przycisk!\n";
        }
    }
};

int main() {

    Przejazd przejazd;

    przejazd.ekran();

    while (true) {

        if (_kbhit()) {

            char wybor = _getch();

            przejazd.obsluz(wybor);

            przejazd.ekran();
        }

        Sleep(50);
    }

    return 0;
}

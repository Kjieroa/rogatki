# Symulator przejazdu kolejowego

## Opis
Program napisany w języku C++, symulujący działanie przejazdu kolejowego. Umożliwia sterowanie szlabanem, wykrywanie pociągu i samochodu oraz obsługę alarmów.

## Funkcje
- Wykrywanie pociągu.
- Otwieranie i zamykanie szlabanu (5 kliknięć).
- Wykrywanie samochodu na przejeździe.
- Uruchamianie alarmu przy niebezpiecznym wjeździe.
- Wystawianie mandatów.
- Resetowanie alarmu po usunięciu samochodu.
- Wyświetlanie aktualnego stanu przejazdu.

## Stany szlabanu
- OTWARTY
- ZAMYKANIE
- ZAMKNIETY
- OTWIERANIE
- ALARM

## Sterowanie

| Klawisz | Funkcja |
|---|---|
| 1 | Wykrycie pociągu |
| 2 | Otwieranie szlabanu |
| 3 | Zamykanie szlabanu |
| 4 | Wjazd samochodu |
| 5 | Usunięcie samochodu / reset alarmu |
| 6 | Pociąg opuszcza przejazd |
| 7 | Wyjście z programu |

## Wymagania
- System Windows
- Kompilator C++
- Biblioteki: iostream, conio.h, windows.h, cstdlib

## Uruchomienie

Kompilacja:
```bash
g++ main.cpp -o przejazd.exe

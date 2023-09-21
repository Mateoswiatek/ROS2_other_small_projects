Spis projektów:
#battery_with_leds
##Krótki opis
Symulacjia kontroli baterii. Jeden Node "udaje" fizyczną baterię oraz podstawowe oprogramowanie ("battery") 
Drugi Node ("led_panel") jest modułem panelu informacyjnego na temat stanu baterii.

##Wykorzystane Technologie

Wykorzystane zagadnienia:
- Packages,
- Nodes,
- Custom Topics
  - Publisher and Subscriber,
- Callbacks
- Custom Services,
- Custom Interfaces
- Threads,
- Parameters
  "Custom" oznacza samemu zrobione / zaprojektowane.
##Pełniejszy Opis
Node "battery" symuluje rozładowywanie i ładowanie się baterii. Gdy poziom baterii osiągnie krytyczne wartości, wysyłane są zapytania do servera w celu zmiany kontrolnych diod led. Zapytania są wysyłane tylko gdy następuje przejscie przez poziom krytyczny. każde zapytanie wysyłane jest w oddzielnym wątku.
Node "led_panel" zmienia stan diod led w momencie gdy otrzymuje zapytanie od klienta ("battery") dodatkowo "led_panel" publikuje aktualny stan diod led na topic "led_panel_state". Node ma rónież dostępny jeden parametr: tablica stanów początkowych diod led.

##Możliwośći rozwoju
- dodanie parametru w "battery" odpowiedzialnego za tempo rozładowywania oraz ładowania się baterii.


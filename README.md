https://www.youtube.com/watch?v=vHP-zq23uvE&ab_channel=NickElectronics
https://www.youtube.com/watch?v=d-E12DlzGGc&ab_channel=Schematix

COil sichbar
https://www.amazon.de/Gatuida-Elektromagnetischer-Physikexperimente-Elektromagnetische-Induktionsspule/dp/B0DTFQ2F8J

Kupferlackdraht

# Digital Tzpewriter

Chip: https://www.alldatasheet.com/datasheet-pdf/view/66074/INTEL/P8052AH.html

- Tastatur mit 17 Lines und Erdung
- 56 Tasten (mit 6 Bits möglich = 64)

- TODO Tastatur auslesen
- Mainboard ausbauen

- https://www.dairequinlan.com/2020/12/the-keyboard-part-2-the-matrix/

Nachdem ich mir diesen Artikel durchgelesen habe, konnte ich die Matrix der Tastatur einfach durch das Kurzschließen der Pins herausfinden. Dafür habe ich jeweils ein Ground mit einem Voltage verbunden und notiert, welche Funktion der Schreibmaschine losging.

- Keyboard matrix

```
          1       2       3       4       5       6       7 (V)

  1       k       l       ö       ä       m       ,       .
  2       u       i       o       p       ü       ↵       j
  3       7       8       9       0       ß       `       Rück
  4       1       2       3       4       5       6       Tab F
  5       Tab     q       w       e       r       t       z
  6       Um Fe   a       s       d       f       g       h
  7       y       x       c       v       b       n       Umsch
  (G)
```

Somit habe ich das Signal zwischen Tastatur und Logicboard über das Flachband ausgelsen. Im nächsten Schritt möchte ich die Tastatur durch einen Arduino emulieren.

TODO Arduino Stromversorung
TODO Spannung auslesen
TODO Arduino Flachband verbindung
TODO Programmierung der Matrix in C

# Triennale — Radar Data Acquisition System

Progetto di tesi di Laurea Triennale in Ingegneria Elettronica.

Sistema embedded per acquisizione dati radar con trasmissione wireless via modulo RF CC1101, basato su microcontrollore PIC18F4620.

## Struttura del progetto

```
.
├── Datasheets/         # Datasheet dei componenti (PIC18F4620, CC1101, MAX3232, LP38690, Samtec TFM)
├── Design/             # Progettazione hardware (OrCAD)
│   ├── cc1101/         #   Modulo RF
│   ├── pic/            #   Microcontrollore
│   ├── radar/          #   Front-end radar
│   ├── rs232/          #   Interfaccia seriale
│   └── emc/            #   Compatibilità elettromagnetica
├── Docs/               # Documentazione tecnica di riferimento
│   ├── pic/            #   Programmazione PIC, tutorial CCS C
│   ├── radar/          #   Paper e documenti su sistemi radar
│   ├── rs232/          #   Specifiche RS-232, null modem
│   └── emc/            #   Normative EMC, ETSI, R&TTE
├── Firmware/
│   ├── ModemRF/        # Firmware di comunicazione RF (CC1101 + PIC18F4620)
│   └── Radar/          # Firmware acquisizione e visualizzazione
│       ├── acquisitore/ # Acquisizione dati radar I/Q
│       ├── Acquisitore_Firmware/
│       └── lcd/         # Driver display LCD (Epson S1D13700)
├── Foto/               # Foto dell'hardware e dei prototipi
└── Tesi/               # Documenti di tesi (DOC, PDF)
```

## Hardware

- **Microcontrollore**: Microchip PIC18F4620
- **Ricetrasmettitore RF**: Texas Instruments CC1101 (banda ISM sub-1 GHz)
- **Interfaccia PC**: RS-232 via MAX3232
- **Display**: LCD grafico con controller Epson S1D13700
- **Alimentazione**: Regolatore LP38690

## Firmware

Il firmware è scritto in C con compilatore CCS C per microcontrollori PIC.

### ModemRF
Modulo di comunicazione wireless punto-punto basato su CC1101 con interfaccia SPI. Gestisce trasmissione e ricezione di pacchetti con CRC, routine di calibrazione e controllo di flusso via RS-232.

### Radar — Acquisitore
Firmware per l'acquisizione dei segnali radar I/Q, controllo del guadagno tramite potenziometro digitale, cancellazione del clutter e trasmissione dati verso PC via RS-232.

### Radar — LCD
Driver per display grafico LCD con controller Epson S1D13700, utilizzato per la visualizzazione in tempo reale dei dati acquisiti.

## Toolchain

- **Compilatore**: CCS C Compiler per PIC (file `.PJT`)
- **PCB Design**: OrCAD (`.DSN`, `.DBK`, `.OPJ`, `.MNL`)
- **Microcontrollore**: PIC18F4620

## Documenti principali

- `Tesi/Tesi.pdf` — Testo completo della tesi
- `Tesi/Presentazione/` — Slide di presentazione
- `Design/Schema.pdf` — Schema elettrico
- `Design/TESI.DSN` — Progetto OrCAD

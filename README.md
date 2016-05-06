# SEP2016

Zusammenfassung
- [x] ShowMore nicht als eigener Command notwendig ([Jakob](https://github.com/jguertl))
- [x] OutOfMemoryException nicht notwendig ([Jakob](https://github.com/jguertl))

Dokumentation und Programmierstil
- [ ] Wiederkehrende Hardcoded Values

OOP Konzepte
- [ ] Unnötig komplizierte Konstrukte
- [x] Other: try catch in startGame, BaseException Sinn? ([Jakob](https://github.com/jguertl))

Struktur & Korrektheit
- [ ] Fehlermeldungen von Valgrind
- [ ] Drohende Segmentation Violations
- [ ] Speicherlöcher
- [ ] Abfangen von bad_alloc
- [ ] Speicherlöcher: alle new in unique_pointer oder saubereres Speichermanagement

Nicht bestandene Testcases
- [x] Save
- [x] Fehler bei Save: File cannot be written
- [x] Fastmove
- [x] Feld: Eis
- [x] Feld: Teleport
- [x] Feld: Einbahn
- [x] Feld: Bonus/Treibsand
- [ ] "No more steps" Behandlung
- [ ] Other: WrongParameterException nicht aufgefangen ([Jakob](https://github.com/jguertl))

Allgemeine Fehler in Testcases
- [ ] Tippfehler in Fehlermeldung ([Jakob](https://github.com/jguertl))
- [ ] Falsche Reihenfolge der Fehlermeldungen ([Jakob](https://github.com/jguertl))

Features
- [x] Command Line Argumente ([Jakob](https://github.com/jguertl))
- [x] Error Handling ([Jakob](https://github.com/jguertl))
- [x] Input/Befehle parsen ([Jakob](https://github.com/jguertl))
- [x] Filename Validierung ([Jakob](https://github.com/jguertl))
- [x] 'Fastmove' Befehl ([Peter](https://github.com/petbuer))
- [x] Fastmove bei Load ausführen ([Peter](https://github.com/petbuer))
- [x] 'Reset' Befehl ([Peter](https://github.com/petbuer))
- [x] Load -> Backup speichern für Reset ([Peter](https://github.com/petbuer))
- [x] Bei Reset wird Load ohne Fastmove aufgerufen ([Peter](https://github.com/petbuer))
- [x] 'Load' Befehl + Validierung ([Peter](https://github.com/petbuer))
- [x] Teleport prüfen ([Peter](https://github.com/petbuer))
- [x] 'Show' Befehl ([Peter](https://github.com/petbuer))
- [x] 'Move' Befehl ([Peter](https://github.com/petbuer))
- [x] Spiellogik aller Felder ([Peter](https://github.com/petbuer))
- [x] 'Save' Befehl ([Peter](https://github.com/petbuer))

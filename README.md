# SEP2016

Zusammenfassung
- [ ] ShowMore nicht als eigener Command notwendig
- [ ] OutOfMemoryException nicht notwendig

Dokumentation und Programmierstil
- [ ] Wiederkehrende Hardcoded Values

OOP Konzepte
- [ ] Unnötig komplizierte Konstrukte
- [ ] Other: try catch in startGame, BaseException Sinn?

Struktur & Korrektheit
- [ ] Fehlermeldungen von Valgrind
- [ ] Drohende Segmentation Violations
- [ ] Speicherlöcher
- [ ] Abfangen von bad_alloc
- [ ] Speicherlöcher: alle new in unique_pointer oder saubereres Speichermanagement

Nicht bestandene Testcases
- [ ] Save
- [ ] Fehler bei Save: File cannot be written
- [ ] Fastmove
- [ ] Feld: Eis
- [ ] Feld: Teleport
- [ ] Feld: Einbahn
- [ ] Feld: Bonus/Treibsand
- [ ] "No more steps" Behandlung
- [ ] Other: WrongParameterException nicht aufgefangen

Allgemeine Fehler in Testcases
- [ ] Tippfehler in Fehlermeldung
- [ ] Falsche Reihenfolge der Fehlermeldungen

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

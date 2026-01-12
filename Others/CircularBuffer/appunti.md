Prima prova del circular buffer, implementato nella sua forma scema, per ora può scriverci sopra, leggere in avanti ed indietro



rendere buffer di dimensione apparentemente variabile in funzione dei bpm e del numero di battute desiderate V
Problemi: Implementazione effettiva con MIDI, devo gestire il Midiclock, start, stop e continue.

Capire se esiste una classe già fatta x gestire il midi, in particolare la creazione di questi segnali. e
es: MIDI clock è un status byte (0xF8) che viene mandato 24 volte ogni 4 step( 6 volte x step), in base a quello calcolo il clock che POI passo alla mia funzione.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! coportamenti diversi tra master e slave

Slave Stop : smetto di scrivere
Master Stop : fermo la testina : Non scrivo e non leggo
Slave continue (in base alla modalità) leggo ciò che c'è nel buffer senza scrtivere niente di nuovo
Master continue : riprendo a scrivere e forzo ad andare in avanti
Slave start : xxxx
Master Start : riporto la testina a 0 e forzo ad andare in avanti







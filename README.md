# RS037-battle-tanks
battle tanks


Battle tanks je igrica za dva igraca, koji medjusobno pucaju jedan na drugog. Pogotkom suprotnog igraca smanjuje mu se helt, i prvi igrac koji potrosi sam helt je izgubio. 

Igrica se pokrece pritiskom na taster 'g'.
Sto se i ispisuje pri pokretanju igrice sa komandom ./tank,  "Start game -g".Tada se aktivira kretanje zida i meraca brzine metka i mogucnost kretanja tenkova levo desno kako bi izbegavali metkove.

Igraci se krecu pritiskom na testere:

-crveni igrac: 6->desno, 4->levo
-zeleni igrac: a->levo, d->desno.

Nisan iz koga tenkovi pucaju se pomera za 90 stepeni na gore i vraca u pocetni polozaj pritiskom na tastere:

-crveni igrac: 8-> na gore, 2->na dole
-plavi igrac: w-> na gore, s->na dole.

Pucanje igraca se izvrsava pritiskom na tastere:

-crveni igrac: 5->puca tj ispaljuje metak ka plavom igracu
-plavi igrac: q->puca tj ispaljuje metak ka crvenom igracu.

Kada se sad helt potrosi na ekran se ispisuje tekst "Game over, winner is _____(RED/BLUE)" i onda se iz igrice izlazi pritiskom na taster esc.
OMPSS-Service
==============

Internetinio matematinio programavimo ir projektavimo serverine paslauga skirta Ubuntu operacinei sistemai. 

Diegimas:
--------------
Parsisiuskite projekta pasinaudoja zemiau pateikta komanda:

    git clone https://github.com/nereliz/OMPSS-Server.git $dir

Tada sukurkite nuoroda i vydkomaji aplanka:

    sudo ln $dir/ompss /etc/ompss

Sekantis zingsnis sukurti nuoroda i *init.d* aplanka

    sudo ln /etc/ompss/init.d/opss /etc/init.d/ompss

**$dir** jusu pasiriktas aplankas


Konfiguravimas:
--------------

Konfiguracijoms naudojama */etc/ompss/config.ini* rinkmena.

Pastaba:
-------

Projekto serverines paslaugos kodo branduolys buvo sukurtas kiek anksciau ir skirtas *Microsoft Windows*. Sio projekto ribose 
jis buvo kiek pakoreguotas, kad ji butu galima naudoti *Ubuntu* aplinkoje bei prideti papildomi skriptai leidziantis serverine
programa naudoti kaip paslauga.

Projektas realizuotas kaip dalis baigimojo magistraturos darbo Siauliu Universitete.

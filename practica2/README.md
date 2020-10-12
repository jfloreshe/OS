# PRACTICA 2
## Participantes
```
Flores Herrera, Jefferson Miguel
Macedo Huamán, Vanessa Mayra
```
## PADRE - HIJO - NIETO
Este programa nos permite crear un proceso llamado padre, este proceso crea un nuevo proceso llamado hijo, el proceso hijo crea a su vez otro proceso llamado nieto.

Padre no puede terminar hasta que hijo se halla terminado de ejecutar, para que esto suceda hijo tiene que enviar 14 señales al proceso nieto, el proceso nieto recibira las señales enviadas por hijo y mostrará un mensaje respectivo por cada señal, si a nieto se le envía una señal que lo asesine, hijo tendrá que crear un nuevo nieto y así terminar de enviar todas las señales para que pueda terminar su ejecución.

## Comportamiento extraños
Cuando se envía la señal SIGSEGV no ocasiona el error de undefined behaviour.
Cuando se envía la señal SIGCHLD no se imprime el mensaje predeterminado para cada señal.

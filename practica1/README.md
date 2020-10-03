Primero se ha creado la estructura tiempo para guardar la hora de creación de cada nuevo proceso.
Se ha creado una estructura item para guardar lo relacionado a un proceso en este caso su pid y su hora de creacion
Se ha creado la estructura region para crear el buffer de pids que usaremos, usamos srand para el tiempo random que haremos dormir luego de terminar de crear o elminiar un proceso.
para la memoria compartida estamos usando el tamaño de la estructura region asi mismo un puntero a region para los datos compartidos.
En producer para poder enviar la información a la memoria estamos esperando que retorne un 0 en fork, de esta forma se espera que termine el hijo para que el padre pueda seguir ejecutandose.
Para poder manejar las horas estamos haciendo uso de time.h y sys/time.h el segundo nos permite crear tiempo en sistemas POSIX
En consumer se ha creado una funcion diff que nos retorna la diferencia entre un tiempo final y un inicial de esta manera calculamos el tiempo que vive un proceso
Por ultimo tanto el consumer y el producer tienen permiso de escritura y lectura cuando acceden a la memoria de esta forma podemos modificar los datos desde consumer.c

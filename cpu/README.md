# Modulo CPU

Modulo que muestra la informacion de los procesos corriendo en el sistema.


Compilar archivo
```
make all
```

Insertar modulo al kernel
```
sudo insmod cpu_201313898.ko
```

Verificar mensaje de entrada y salida del modulo
```
dmesg
```

Verificar informacion de los procesos en el directorio proc/
```
cd /proc/
```

Para saber todos los procesos que existen deberìa de aparecer en el primer lugar
```
lsmod
```

Para poder ver el archivo escrito por el modulo
```
cat cpu_practica1
```

Para eliminar el modulo 
```
sudo rmmod cpu_201313898

Se deberia abrir el archivo con la informacion del PID, Nombre y Estado de los procesos que estan corriendo en el sistema.


## Descripcion del Codigo

Obtenemos los datos de los procesos que se contaron a la estructura tasks structs, tiene una lista de metadata de los procesos que contiene.
 

## License

Bajo licencia GLP.

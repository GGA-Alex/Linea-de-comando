# Linea-de-comando

Diseñar una programa que permita simular una terminal de comandos.

## Funcionamiento

Los comandos que se implementaron son los siguientes:

- **copiar [NombreFichero] [Estado]** : Este comando copia al final del mismo fichero todos los registros que coincidan con [Estado].
- **eliminar [NombreFichero] [CodigoPostal]** : Este comando elimina del fichero todos los registros que coincidan con el [CodigoPostal] ingresado.
- **renombrar [NombreFichero] [NuevoNombreFichero]** : Este comando cambia el nombre del fichero.
- **combinar [NombreFichero1] [ NombreFichero2]** : Este comando toma los dos ficheros especificados y genera uno nuevo combinando su contenido alternando los registros uno y uno, nombrar el nuevo archivo como [NombreFichero1_NombreFichero2].
- **agrupar [NombreFichero1] [ NombreFichero2]** ... [NombreFichero5] : Este comando agrupa hasta 5 ficheros cualquiera dentro de una carpeta con el nombre [Agrupacion], verifiar si ya existe una carpeta, de ser así el nombre de las nuevas carpetas será [Agrupación2], [Agrupación3], etc...

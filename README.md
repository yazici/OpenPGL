# OpenPGL
Open Procedural Generation Library — программное обеспечение для автоматического создания игрового контента автономно, или совместно с дизайнером.
## Сборка
1. Для сборки приложения скачайте или клонируйте репозиторий с исходным кодом.
2. Скачайте архив с дополнительными библиотеками. [Download](https://github.com/Max1880/OpenPGL/releases/tag/lib)
3. Извлеките папку **library** из архива и скопируйте её в папку с исходным кодом.
```
__ OpenPGL
   |— library
   |— source
   |— CMakeLists.txt
   |— README.md
   |— .gitignore
   |— LICENSE
```
4. Создайте папку куда будет помещен собираемый проект.
```shell
mkdir Build
cd Build
cmake ../OpenPGL
```

```
__ Build
   | (Собранный проект)
__ OpenPGL
   |— library
   |— source
   |— CMakeLists.txt
   |— README.md
   |— .gitignore
   |— LICENSE
```
5. Откройте папку **Build** и запустите собранный проект.

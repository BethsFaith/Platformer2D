# Platformer2D

Developed with Unreal Engine 5.4.1

# Сборка

Чтобы запустить из исходников, необходимо наличие Unreal Engine 5.4. Запуск Platformer2D.uproject. Если появляется окно с просьбой пересборки проекта на другую версию движка, нажимаем "Принять". При ошибках автоматической сборки - открыть .sln (Должна быть установлена Visual Studio), нажать правой кнопкой мыши на решение, далее - выбрать "пересобрать проект".

# Дополнительно

Ассеты, используемые в этом проекте, находятся по ссылке: https://pixelfrog-assets.itch.io/treasure-hunters

.exe файл (debug сборка) лежит на диске: https://drive.google.com/file/d/1niVBgnHSVIBXVZmMmOaT2UFTN7q4enRP/view?usp=drive_link
Запуск: Binaries/Win64/Platformer2.exe

Код в блюпринтах и на с++ содержит комментарии на русском языке. (Если комментарии на с++ отображаются некорректно, убедитесь что включена кодировка Windows1251).

# Управление

* x - атака;
* a - передвижение влево;
* d - передвижение вправо;
* spacebar - прыжок;

# Игра 

* В игре присутствует вражеское нпс, которое при приближении игрока включает агр режим (ускоряется и движется по направлению к игроку).
* Шипы наносят урон игровому персонажу при контакте. Морская раковина срабатывает как ловушка, имеет перезарядку (3 сек по умолчанию)
* Черепа и зелья являются собираемыми предметами, счетчик по первым отображается слева в верхем углу, зелья - пополняют здоровья, которое так же отображается в левом верхнем углу экрана.
* При приближении к сундуку или после смерти игрового персонажа открывается ui с возможностью перезапуска уровня.

# Решение

1. Персонажи:

* ABasePaperCharacter - наследник от APaperCharacter, содержит показатели здоровья, урона, работу с анимациями (переходы), является базовым классом для персонажа игрока и врагов.
* AMainCharacter - содержит камеру и сбор предметов.
* AEnemyCharacter - содержит функционал реагирования нпс на приближение/отдаление персонажа игрока.

* BP_Enemy - класс, написанный на блюпринтах, содержит основую логику вражеского нпс. Предполагается как основа (родитель) для всех врагов. Например, для создания нового врага достаточно наследоваться от этого класса и заполнить переменные в категории "анимации" и "показатели".
* BP_MainCharacter - класс на блюпринтах, содержит основной функционал для игрового персонажа.

* AIC_Enemy - контроллер, содержит базовое поведение (движение) для вражеских нпс.

2. Предметы: 

* BP_Item - базовый класс, содержит box с коллизией, который при столкновении с игроком вызывает определенный event.
* BP_Heal - предмет для восстановления хп игрока
* BP_Treasure - предмет для сбора.

3. UI:

* BP_UserUi - отображение здоровья и количества предметов у игрока (внутри используются классы BP_UserHPBar и BP_TreasureCounter)
* BP_GameOver - для перезапуска игры. Срабатывает после смерти персонажа игрока или когда уровень "пройден".

Подробности можно увидеть в комментариях. 


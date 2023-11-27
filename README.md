# pc_club

Решенеи ТЗ представленно в виде файла с исходным кодом на С++. 

#### Инструкция по компиляции и выполнению работы программы программы:
Компиляция компилируется компилятором g++ в Ubuntu 20.04.1 .  Для компиляции кода нужно написать в терминале, открытом в папке с файлом pc_club.cpp 
``` 
g++ pc_club.cpp -o pc_club
```
После этого в папке появится исполняемый файл pc_club, для запуска исполняемого файла в терминале нужно ввести команду вида - ./pc_club "имя_входного файла.txt". Например:
```
./pc_club in.txt
```
#### Пример рабты программы
Пример 1 (файл in.txt):
<table>
    <tr>
        <th>Входной файл</th>
        <th>Вывод в консоли</th>
    </tr>
    <tr>
        <td><p> 3<br>
                09:00 19:00<br>
                10<br>
                08:48 1 client1<br>
                09:41 1 client1<br>
                09:48 1 client2<br>
                09:52 3 client1<br>
                09:54 2 client1 1<br>
                10:25 2 client2 2<br>
                10:58 1 client3<br>
                10:59 2 client3 3<br>
                11:30 1 client4<br>
                11:35 2 client4 2<br>
                11:45 3 client4<br>
                12:33 4 client1<br>
                12:43 4 client2<br>
                15:52 4 client4<br>
        </p></td>
        <td>
                09:00<br>
                08:48 1 client1<br>
                08:48 13 NotOpenYet<br>
                09:41 1 client1<br>
                09:48 1 client2<br>
                09:52 3 client1<br>
                09:52 13 ICanWaitNoLonger!<br>
                09:54 2 client1 1<br>
                10:25 2 client2 2<br>
                10:58 1 client3 <br>
                10:59 2 client3 3<br>
                11:30 1 client4<br>
                11:35 2 client4 2<br>
                11:35 13 PlaceIsBusy<br>
                11:45 3 client4<br>
                12:33 4 client1<br>
                12:33 12 client4 1<br>
                12:43 4 client2<br>
                15:52 4 client4<br>
                19:00 11 client3<br>
                19:00<br>
                1 70 05:58<br> 
                2 30 02:18<br>
                3 90 08:01 </td>
    </tr>
</table>
Пример 2 (файл in2.txt):
<table>
    <tr>
        <th>Входной файл</th>
        <th>Вывод в консоли</th>
    </tr>
    <tr>
        <td><p> 3<br>
                08:00 19:00<br>
                10<br>
                01:58 1 client1<br>
                06:48 1 client1<br>
                08:48 1 client1<br>
                08:48 1 client1<br>
                09:41 1 client1<br>
                09:47 1 client1<br>
                09:48 1 client2<br>
                09:48 4 client2<br>
                09:49 1 client2<br>
                09:52 3 client1<br>
                09:54 2 client1 1<br>
                10:00 2 client1 3<br>
                10:01 2 client1 1<br>
                10:25 2 client2 2<br>
                10:58 1 client3<br>
                10:59 2 client3 3<br>
                11:30 1 client4<br>
                11:35 2 client4 2<br>
                11:45 3 client4<br>
                12:33 4 client1<br>
                12:43 4 client2<br>
                15:52 4 client4<br>
                16:52 4 client5<br>
                17:00 1 aaaa<br>
                18:00 1 bbbb<br>
                19:00 1 aaa<br>
                20:58 1 client1<br>
        </p></td>
        <td>
                08:00<br>
                01:58 1 client1<br>
                01:58 13 NotOpenYet<br>
                06:48 1 client1<br>
                06:48 13 NotOpenYet<br>
                08:48 1 client1<br>
                08:48 1 client1<br>
                08:48 13 YouShallNotPass<br>
                09:41 1 client1<br>
                09:41 13 YouShallNotPass<br>
                09:47 1 client1<br>
                09:47 13 YouShallNotPass<br>
                09:48 1 client2<br>
                09:48 4 client2<br>
                09:49 1 client2<br>
                09:52 3 client1<br>
                09:52 13 ICanWaitNoLonger<br>
                09:54 2 client1 1<br>
                10:00 2 client1 3<br>
                10:01 2 client1 1<br>
                10:25 2 client2 2<br>
                10:58 1 client3<br>
                10:59 2 client3 3<br>
                11:30 1 client4<br>
                11:35 2 client4 2<br>
                11:35 13 PlaceIsBusy<br>
                11:45 3 client4<br>
                12:33 4 client1<br>
                12:33 12 client4 1<br>
                12:43 4 client2<br>
                15:52 4 client4<br>
                16:52 4 client5<br>
                16:52 13 ClientUnknown<br>
                17:00 1 aaaa<br>
                18:00 1 bbbb<br>
                19:00 1 aaa<br>
                20:58 1 client1<br>
                20:58 13 NotOpenYet<br>
                19:00 11 aaa<br>
                19:00 11 aaaa<br>
                19:00 11 bbbb<br>
                19:00 11 client3<br>
                19:00<br>
                1 80 05:57<br>
                2 30 02:18<br>
                3 100 08:02</td>
    </tr>
</table>

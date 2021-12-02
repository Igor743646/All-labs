#/bin/bash

proxod()
{
for i in `ls .` #пока есть файлы и дериктории проходим
do
if test -d $i #если дериктория
then

cd $i #Заходим в дерикторию
proxod #Рекурсия
cd .. #Выходим из дериктории
elif test -f $i #Если файл
then
    #echo " $i"
    if test "$i" != "zach.sh" && test "$i" != "zach.sh~" #Если не исполняемый файл с утилитой
    then
	if test `file "$i" | cut -d' ' -f2` = "ASCII" || test `file "$i" | cut -d' ' -f2` = "UTF-8" #Если текстовый файл
	then #Перекодируем с помощью команды tr
	    echo "Файл `pwd`/$i был перекодирован";
	    echo `cat $i | tr [a-z] [defghijklmnopqrstuvwxyzabc]` > $i
	    echo `cat $i | tr [A-Z] [DEFGHIJKLMNOPQRSTUVWXYZABC]` > $i
	fi
    fi
fi
done
}
proxod #Вызов функции рекурсии


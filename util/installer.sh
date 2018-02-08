for util in $@
do
    if [ -e $util ] 
    then
        echo install $util ${PREFIX}/bin
        install $util ${PREFIX}/bin
    fi
done

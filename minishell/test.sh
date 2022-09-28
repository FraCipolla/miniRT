rm youpi; rm "wesh alors"; rm "ha  ha"; rm hey; rm '"'; rm file;  rm test_output;
# echo hello $USER
# echo hello | cat -e
# echo hello | cat -e | cat -e | cat -e
# echo hello | cat -e | cat -e | cat -e | cat > SIRIUS
# cat <<ye | cat -e | cat >SIRIUS
cat <SIRIUS > RON
cat <SIRIUS | cat -e | cat > RON

single cmd: simple, redir, heredoc, built in, execve
multiple cmd: simple pipe, redir, heredoc, built in, execve

# echo hello hihi haha <infile >outfile <<delim >> append bouh ha | yeah; // attention
echo arg"hello" "$USER"'$USER' blabla "" '';
echo arg"hello" "$USER"'$USER' blabla "" '' | cat -e >SIROUS
# redirection in parameter
FILE=test_output;
OUTFILE=>youpi; # this
echo 00 ; echo $OUTFILE | cat -e;

# Special cases
echo 1; ""echo minishell
echo 2; "" "" echo minishell # nope
echo 3;""echo minishell
echo 4;"ec''ho" bonjour  # nope
echo 5;"ec'''ho" bonjour  # nope
echo 6;echo    | cat -e #this
echo 7;echo ""  | cat -e #this
echo 7-0;echo "" "" | cat -e #this
echo 7-1;echo "" coucou | cat -e #this
echo 8;echo bon""jour
echo 9;echo """""mdrr"
echo 10;echo ''"" | cat -e
echo 11;echo ''""'' | cat -e
echo 12;echo """"bonjour"" "" | cat -e 
echo 13;"echo bonjou"""r | cat -e
echo 14;"echo""" ''bonjour | cat -e
echo 15;echo "$wfjwefielwhfhlwefkhwefwe" a | cat -e
echo 16;ls "-lR""-a" #this
echo 19;echo "" mdr "" | cat -e
echo 29;"$'PATH'"
echo 37;echo "mdrrr >coucou >> ceci n'est pas une redirection"
echo 39;echo a;

VAR=coucou;
echo 40; echo "echo>>file"hello  | wc - w ;# this
echo 41-1; echo """  hey   """ | cat -e;
echo 41-1-1; echo """"  hey   """" | cat -e; #this
echo 41-2; echo '''  hey   ''' | cat -e;
echo 41-2-1; echo ''''  hey   '''' | cat -e;
echo 42; echo "'$PATH'"| cat -e;
echo 43; echo '"$PATH"'| cat -e;
echo 44; echo ''''| cat -e;
echo 45; echo '""'| cat -e;
echo 46; echo '"'| cat -e;
echo 47; echo "''"| cat -e;
echo 48; echo "'"| cat -e;
echo 49; echo """"| cat -e;
echo 49-b; echo """" """" """"| cat -e; #this
echo 49-b; echo a a a| cat -e;
echo 50; echo  'word '  | cat -e;

#this
LS="ls -la"; #export
echo 51; $LS; # this should do a ls -la
echo 52; "$LS";
echo 52-b; echo $LS | cat -e;
echo 52-c; echo "$LS" | cat -e;
# to be checked
echo 53; cat < $HOME;


echo 54;
t="ha  ha"; #export
echo baguette > $t; # should print error message if empty ????
ls;
cat < $t;


//tcarciofi
>>>>>>>>>>>>>>> im a big arrow;
>> >> >> >> >> > > > > > im a big arrow;
<<<<<<<<<<<<<<< im a big arrow;
echo << "";
dasdas| asdasda| sdadasd| dasdsa;
i'm a big pipeline | prova;
!!!!!!!!!!!!!!! im a big randomstuff;
echo "$USER" > "$USER" | cat "$USER" && echo "$USER" > "$USER" | cat "$USER" && echo '$USER' > '$USER' | cat '$USER' && echo '"$USER"' > '"$USER"' | cat '"$USER"';
export prova=$USER;
export prova=$USER && echo "'$prova'" > "'$prova'" | cat "'$prova'" && echo "$prova" > "$prova" | cat "$prova" && echo '$prova' > '$prova' | cat '$prova' && echo '"$prova"' > '"$prova"'| cat '"$prova"';
export prova='$USER';
echo "'$prova'" > "'$prova'" | cat "'$prova'" && echo "$prova" > "$prova" | cat "$prova" && echo '$prova' > '$prova' | cat '$prova' && echo '"$prova"' > '"$prova"'| cat '"$prova"';


# when signals implememted check Leaks
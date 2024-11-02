env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

/bin/echo abc

/bin/ls 

/bin/ls

/bin/ls /

/bin/ls -a -h / /home

/bin/echo hello word

/bin/echo

# find / -name file_name -type f

/bin/pwd

/bin/printf 'abcdef\n'

"                          "

'                          '

echo

echo hello

echo hello world

echo "hello word"

echo 'hello word'

echo ''

echo ""

echo $.

echo $.%

exit

exit 1

exit 300

exit 1234556

exit 123 3435

exit abc def

exit abc 123

exit 123 abc

exit -123

/bin/ls

/bin/ls1

$? + $?

echo $??

echo $? + $?

echo $?+$?

echo "$? + $?"


echo "$?+$?"

echo '$?+$?'

echo '$? + $?'

fsdfdfsdfd

/bin/ls -ah /
echo $?

/bin/ls -ae1

<$var123 cat

<$var123 cat

<$var123 <$var123 cat

<>

echo "Hello World"

echo ""

echo "            "

echo "$??.$?.."

echo "Hello$HOME"

echo "Hello$HOME."

echo "Hello$HOME??"

echo 'Hello$HOME'

echo 'Hello$HOME.'

echo 'Hello$HOME??'

echo Hello$HOME

echo Hello$HOME.

echo Hello$HOME?

echo Hello$HOME??

echo "cat lo.c | cat > lol.c"

l""s""""

""ls""""

""l""s""

ls "-la" "/"

/bin/ls "-a" "-h" "/" "/home"

"/bin/echo" hello word

/bin/"echo"

#"find" "/" "-name" "file_name" "-type" "f"

l''s''''

''ls''''

''l''s''

ls '-la' '/'

/bin/ls '-a' '-h' '/' '/home'

'/bin/echo' hello word

/bin/'echo'

#'find' '/' '-name' 'file_name' '-type' 'f'

echo "''"

echo '""'

echo '"   "'

echo "'    '"

echo '$??.$?..'

echo 'Hello$HOME""'

echo 'Hello$HOME.'

echo 'Hello$HOME??'

export var="abc"
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var1="abc def"
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var2=""
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var3
env | sort -n | grep -v _= | grep -v SHLVL
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var4=123
export var4
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var5="abc"
export var6=$var5
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var7="abc def ghi"
export var8="qwe rty opi"
export $var7=$var8
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var8="echo Hello world"
$var8

export var9="echo 'Hello world'"
$var9

export var10='echo "Hello world"'
$var10

export var11="abc"
$var11
echo $?

export var = " abc def"
echo $?
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var1="abc def"
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export 123var="fdsdfd"
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export +var=123
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var.="123"
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var""=12343
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export vrs.adsa=123
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var12="123"
unset var12
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var13="123" var14="dss" var15="dasds"
unset var13 var14 var15
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

export var16 var16 var17 var18
unset var16 var17 var18
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

unset $varss109
env | sort -n | grep -vE ^_= | grep -vE ^SHLVL

unset 

unset vars777

cd /home
/bin/ls
pwd
echo $OLDPWD $PWD

cd ../
/bin/ls
pwd
echo $OLDPWD $PWD

cd ./
/bin/ls
pwd
echo $OLDPWD $PWD

unset PWD OLDPWD
cd /
/bin/ls
pwd
echo $OLDPWD $PWD

unset PWD OLDPWD
cd /
/bin/ls
pwd
echo $OLDPWD $PWD
cd
/bin/ls
pwd
echo $OLDPWD $PWD

cd ./notdir
/bin/ls
pwd

cd /
pwd

cd /home
pwd

cd /home/../home/../home/../home/../home/../home
pwd
/bin/ls

cd .
pwd

cd ..
pwd

ls
echo $?

unset PATH
ls
echo $?

unset PATH
clear
echo $?

unset PATH
<$main cat
echo $?

unset PATH
cat dir1
echo $?

export PATH="/bin/"
ls /
echo $?
cat fileName
echo $?
<$dsfd cat
echo $?
< $sfd cat

export PATH="$PWD"
ls /
echo $?
cat fileName
echo $?
<$dsfd cat
echo $?
< $sfd cat

export PATH="/bin/:$PWD"
ls /
echo $?
cat fileName
echo $?
<$dsfd cat
echo $?
< $sfd cat

export PATH="/bin/:$PWD:tsisy/"
ls /
echo $?
cat fileName
echo $?
<$dsfd cat
echo $?
< $sfd cat

< tcr.sh cat > out
echo $?

<tcr.sh cat >out
echo $?
<out cat

< tcr.sh <tcr.sh cat > out >out1
echo $?
<out cat

< tcr.sh cat > out
< tcr.sh cat >> out
echo $?
cat out

<$vars <$vars1 cat > out
echo $?

export var="abc def"
<$var cat >$var
echo $?

export var="abc def"
< $var cat > $var
echo $?

export var=""
< $var cat > $var < $var
echo var

<tcr.sh > out < tcr.sh>>out cat >out1 >>out < tcr.sh
echo $?

cp tcr.sh file
<file cat < file > file >file
echo $?

<< eof cat
abc
def
eof

<<eof cat
'abc'
"abc"
'def'"abc"
$HOME
$??
"$???"
$HOME$PWD
$PWD $HOME
"$PWD $HOME"
'$PWD' '$HOME'
'$PWD " '$HOME"
eof

<<eof'' cat
'abc'
"abc"
'def'"abc"
$HOME
$??
"$???"
$HOME$PWD
$PWD $HOME
"$PWD $HOME"
'$PWD' '$HOME'
'$PWD " '$HOME"
eof

<<eof'' cat
'abc'
"abc"
'def'"abc"
$HOME
$??
"$???"
$HOME$PWD
$PWD $HOME
eof

<<eof"" cat
'abc'
"abc"
'def'"abc"
$HOME
$??
"$???"
$HOME$PWD
$PWD $HOME
echo $"USER"
eof

cat tcr.sh | grep $ | wc

cat tcr.sh|grep -v $ | wc

ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls

ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ |ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ |ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ |ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/ | ls -lah /home/

ls |lsadsa| dfsdkl | dfsd  | ls

ls | sdfsd | ls | sfd

< tcr.sh cat | wc -l | tr -d '\n' | awk '{print $0}'

< tcr.sh cat > out | wc -l | tr -d '\n' | awk '{print $0}'

< tcr.sh cat | wc -l tcr.sh | tr -d '\n' | awk '{print $0}'

#< tcr.sh cat > out |<tcr.sh wc -l | < $adsfdsd tr -d k| awk '{print $0}'

<tcr.sh grep -v $ | wc -l >> $abc123

echo $HOME

echo $.

echo $<

echo $PATH'pwd'

echo $PATH.$HOME

echo $HOMES

echo $HOME$HOME

echo "$?+$?"

echo "$HOME"

echo "$PATH"


echo "$PATH'pwd'"

echo "$PATH.$HOME"

echo "$HOMES"

echo "$HOME$HOME"

echo "$PWD $HOME"

echo "$.$%"

export USER="me"
echo $USER

export USER="me"
echo "$USER"

export USER="me"
echo "$.USER"

export USER="me"
echo $"USER"


unset PWD
cd 
echo $PWD $OLDPWD

unset OLDPWD
cd
echo $PWD $OLDPWD

unset PWD OLDPWD
cd
cd ..
echo $PWD $OLDPWD
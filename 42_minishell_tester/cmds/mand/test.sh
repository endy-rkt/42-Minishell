echo $.$.

echo $??

echo "$.$."

echo '"$.$."'

echo "'$.$.'"

echo $?+$?

echo $? + $?

echo "$?+$?"

echo "$? + $?"

echo '$?+$?'

echo '$? + $?'

# echo $$

# echo "$$"

echo '$$'

# echo $$?

# echo "$$?"

echo '$$?'

# echo $$??

# echo "$$??"

echo '$$??'

echo $123abc

echo $abc123abc

echo $a1bc

echo $PWD?

echo $PWD??

echo ?$PWD??

echo "$PWD?"

echo "$PWD??"

echo "?$PWD??"

echo "??$PWD."

echo $PWD.

echo .$PWD.

echo "$PWD."

echo ".$PWD."

echo "..$PWD.."

echo $PWD$.

echo "$PWD$."

echo "$..$PWD$.."

echo $PWD . $PWD

# echo "$PWD . $PWD"

# echo ".$PWD		.		$PWD."

<<eof cat
$?
$??
$.$<$PWD
"$?"
"$??"
"$<$."
"$."
".$%$PWD"
"$???.$'PWD'"'$HOME'$EMPTY
'EOF'$PWD'$HOME'$?.$?'
eof

<<eof'end' cat
$?
$??
$.$<$PWD
"$?"
"$??"
"$<$."
"$."
".$%$PWD"
"$???.$'PWD'"'$HOME'$EMPTY
eofend
# '										'


# ambiguous redirect

< $TSISY cat

<$TSISY cat

export var="abc def"

<$var cat > out

<$var. cat > out

< $var cat > out

< minishell.h cat > $var

< minishell.h cat >$var.

< minishell.h cat -e > $PATH

< minishell.h cat -e > $TSISY

<minishell.h cat -e >$TSISY

<minishell.h <$TSISY cat -e > $TSISY

< minishell.h <$ETO cat -e > $TSISY

# syntax error
<< >

<<>

><

# misc

cat minishell | awk '{sum += $2; count++} END {print "Average:", sum/count}' | awk '{print $1, $2, " (calculated from", $3, "entries)"}'

<< eof awk '{sum += $2; count++} END {print "Average:", sum/count}' | awk '{print $1, $2, " (calculated from", $3, "entries)"}'
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
eof

export =value

export var name=value

export var$pecial="value"

export var="test"
export var=$var
echo "$var"

export var="value with spaces and special chars: $?"
echo "$var"

export var="first value"
export var="second value"
echo "$var"

export delim="END"
cat <<$delim
This uses a variable as the delimiter.
$delim

export var="World"
cat <<EOF
Hello, $var! This is a test of 'single quotes' and "double quotes".
EOF

cat <<EOF
Special characters: !@#$%^&*()_+[]{};':",.<>?/
EOF



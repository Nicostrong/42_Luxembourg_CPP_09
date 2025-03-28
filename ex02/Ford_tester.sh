# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Ford_tester.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42.luxembourg.lu>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 11:31:45 by nfordoxc          #+#    #+#              #
#    Updated: 2025/03/28 08:55:05 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

OS=$(uname)

bad_params=(
	""
	"toto"
	"4 3 2.1 0"
	"5 3 -2"
	"2147483648 0"
	"2 7,3 5"
	"8 6 2a 0"
	"6 2 jlkshdfg jklshfg sjdlkgh dsjkgh sdjkgh sdf 0"
)

good_params=(
	"9 8 7 6 5 4 3 2 1 0"
	"9 9 8 8 7 7 6 6 5 5 4 4 3 3 2 2 1 1 0 0"
	"2136474847 500 2 0"
	"5 6 2 0"
	"42 42 42 42 42 42 42 42 42 42 42 42"
)

big_params_mac=(
	"jot -r 500 0 10000 | tr '\n' ' '"
	"jot -r 500 0 10000 | sort -nr | tr '\n' ' '"
	"jot -r 1000 0 10000 | tr '\n' ' '"
	"jot -r 1000 0 10000 | sort -nr | tr '\n' ' '"
	"jot -r 5000 0 10000 | tr '\n' ' '"
	"jot -r 5000 0 10000 | sort -nr | tr '\n' ' '"
	"jot -r 10000 0 100000 | tr '\n' ' '"
	"jot -r 10000 0 100000 | sort -nr | tr '\n' ' '"
	"jot -r 50000 0 100000 | tr '\n' ' '"
	"jot -r 50000 0 100000 | sort -nr | tr '\n' ' '"
)

big_params_linux=(
	"shuf -i 0-10000 -n  500 | tr '\n' ' '"
	"shuf -i 0-10000 -n  500 | sort -nr | tr '\n' ' '"
	"shuf -i 0-10000 -n  1000 | tr '\n' ' '"
	"shuf -i 0-10000 -n  1000 | sort -nr | tr '\n' ' '"
	"shuf -i 0-10000 -n  5000| tr '\n' ' '"
	"shuf -i 0-10000 -n  5000| sort -nr | tr '\n' ' '"
	"shuf -i 0-100000 -n 10000 | tr '\n' ' '"
	"shuf -i 0-100000 -n 10000 | sort -nr | tr '\n' ' '"
	"shuf -i 0-100000 -n 50000 | tr '\n' ' '"
	"shuf -i 0-100000 -n 50000 | sort -nr | tr '\n' ' '"
)

if [[ "$OS" == "Linux" ]]; then
	big_params=("${big_params_linux[@]}")
else
	big_params=("${big_params_mac[@]}")
fi

error_count=0

make

NAME=PmergeMe

clear

echo -e "\033[0m"
echo -e "\033[1;94m _______   ______   _______    _______       _____\033[0m"
echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|     /     |\033[0m"
echo -e "\033[1;94m   | |    | |___   |  |____      | |       /  /|  |\033[0m"
echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |      /__/ |  |\033[0m"
echo -e "\033[1;94m   | |    | |____   _____| |     | |           |  |\033[0m"
echo -e "\033[1;94m   |_|    |______| |_______|     |_|           |__|\033[0m"
echo ""
echo -e "\t\t\033[1;93mBAD VALUES.\033[0m"
echo ""

for i in "${!bad_params[@]}"
do
	TEMPFILE=$(mktemp)
	echo -e "\033[1;94mTEST $((i + 1)): ./$NAME ${bad_params[i]}\033[1;93m"
	./$NAME ${bad_params[i]} > $TEMPFILE 2>&1

	if grep -q "Error" $TEMPFILE || grep -q "Usage" $TEMPFILE; then
		echo -e "\033[1;92m✅ OK => Bad argument catching.\033[0m"
	else
		echo -e "\033[1;91m❌ KO => Bad argument not catching.\033[0m"
		((error_count++))
	fi

	rm $TEMPFILE
done

echo -e "\033[1;94m _______   ______   _______    _______      ______\033[0m"
echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|    /  __   \\ \033[0m"
echo -e "\033[1;94m   | |    | |___   |  |____      | |      /__/  /  /\033[0m"
echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |          /  /\033[0m"
echo -e "\033[1;94m   | |    | |____   _____| |     | |        /  /___\033[0m"
echo -e "\033[1;94m   |_|    |______| |_______|     |_|       (_______)\033[0m"
echo ""
echo -e "\t\t\033[1;93mGOOD VALUES.\033[0m"
echo ""

for i in "${!good_params[@]}"
do
	TEMPFILE=$(mktemp)
	echo -e "\033[1;94mTEST $((i + 1)): ./$NAME ${good_params[i]}\033[1;93m"
	./$NAME ${good_params[i]} &> $TEMPFILE

	if [[ "$OS" == "Linux" ]]; then
		sed -i -E 's/\x1b\[[0-9;]*m//g' $TEMPFILE
	else
		sed -i 'bak' -E 's/\x1b\[[0-9;]*m//g' $TEMPFILE
	fi
	#sed -i 'bak' -E 's/\x1b\[[0-9;]*m//g' $TEMPFILE
	
	container_1=$(awk -F': ' 'NR == 3 { print $2 }' "$TEMPFILE" | xargs)
	container_2=$(awk -F': ' 'NR == 4 { print $2 }' "$TEMPFILE" | xargs)

	echo "Time to sort container 1 : $container_1";
	echo "Time to sort container 2 : $container_2";

	< $TEMPFILE awk -F': ' '
	NR == 1 { split($2, input, " "); n = length(input); }
	NR == 2 { split($2, expected, " "); }
	END {
		for (i = 1; i <= n; i++)
		{
			for (j = i + 1; j <= n; j++)
			{
				if (input[i] > input[j])
				{
					tmp = input[i];
					input[i] = input[j];
					input[j] = tmp;
				}
			}
		}
		correct = 1;
		for (i = 1; i <= n; i++)
		{
			if (input[i] != expected[i])
			{
				correct = 0;
				break;
			}
		}
		if (correct)
		{
			print "✅ Sort => OK !";
		}
		else
		{
			print "❌ Sort => KO";
			exit_code = 1;
		}
		exit exit_code;
	}'
	if [ $? -ne 0 ]; then
		((error_count++))
	fi
	rm $TEMPFILE
done

echo -e "\033[1;94m _______   ______   _______    _______      _______\033[0m"
echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|    |____   |\033[0m"
echo -e "\033[1;94m   | |    | |___   |  |____      | |          __|  |\033[0m"
echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |         |__   |\033[0m"
echo -e "\033[1;94m   | |    | |____   _____| |     | |        ____|  |\033[0m"
echo -e "\033[1;94m   |_|    |______| |_______|     |_|       |_______|\033[0m"
echo ""
echo -e "\t\t\033[1;93mBIG VALUES\033[0m"
echo ""

for i in "${!big_params[@]}"
do
	TEMPFILE=$(mktemp)
	echo -e "\033[1;94mTEST $((i + 1)): ./$NAME ${big_params[i]}\033[1;93m"
	eval ${big_params[i]} > params
	./$NAME $(cat params) &> $TEMPFILE
	
	if [[ "$OS" == "Linux" ]]; then
		sed -i -E 's/\x1b\[[0-9;]*m//g' $TEMPFILE
	else
		sed -i 'bak' -E 's/\x1b\[[0-9;]*m//g' $TEMPFILE
	fi
	#sed -i 'bak' -E 's/\x1b\[[0-9;]*m//g' $TEMPFILE

	container_1=$(awk -F': ' 'NR == 3 { print $2 }' "$TEMPFILE" | xargs)
	container_2=$(awk -F': ' 'NR == 4 { print $2 }' "$TEMPFILE" | xargs)

	echo "Time to sort container 1 : $container_1";
	echo "Time to sort container 2 : $container_2";
	
	< $TEMPFILE awk -F': ' '
	NR == 1 { split($2, input, " "); n = length(input); }
	NR == 2 { split($2, expected, " "); }
	END {
		for (i = 1; i <= n; i++)
		{
			for (j = i + 1; j <= n; j++)
			{
				if (input[i] > input[j])
				{
					tmp = input[i];
					input[i] = input[j];
					input[j] = tmp;
				}
			}
		}
		correct = 1;
		for (i = 1; i <= n; i++)
		{
			if (input[i] != expected[i])
			{
				correct = 0;
				break;
			}
		}
		if (correct)
		{
			print "✅ Sort => OK !";
		}
		else
		{
			print "❌ Sort => KO";
			exit_code = 1;
		}
		exit exit_code;
	}'
	if [ $? -ne 0 ]; then
		((error_count++))
	fi
	rm $TEMPFILE
	rm params
done

if [[ "$OS" == "Linux" ]]; then
	echo -e "\033[1;94m _______   ______   _______    _______      __\033[0m"
	echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|    |  |   __\033[0m"
	echo -e "\033[1;94m   | |    | |___   |  |____      | |       |  |__|  |\033[0m"
	echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |       |_____   |\033[0m"
	echo -e "\033[1;94m   | |    | |____   _____| |     | |             |  |\033[0m"
	echo -e "\033[1;94m   |_|    |______| |_______|     |_|             |__|\033[0m"
	echo ""
	echo -e "\t\t\033[1;93mBAD ARGUMENTS VALGRIND.\033[0m"
	echo ""

	for i in "${!bad_params[@]}"
	do
		TEMPFILE=$(mktemp)
		echo -e "\033[1;94mTEST VALGRIND $((i + 1)): ./$NAME ${bad_params[i]}\033[1;93m"
		valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./$NAME ${bad_params[i]} &> $TEMPFILE

		def_lost_bytes=$(grep "definitely lost:" $TEMPFILE | awk '{print $4}')
		ind_lost_bytes=$(grep "indirectly lost:" $TEMPFILE | awk '{print $4}')
		pos_lost_bytes=$(grep "possibly lost:" $TEMPFILE | awk '{print $4}')
		still_reach_bytes=$(grep "still reachable:" $TEMPFILE | awk '{print $4}')
		suppressed_bytes=$(grep "suppressed:" $TEMPFILE | awk '{print $4}')

		if [[ $def_lost_bytes -gt 0 || $ind_lost_bytes -gt 0 || $pos_lost_bytes -gt 0 || $still_reach_bytes -gt 0 || $suppressed_bytes -gt 0 ]]; then
			echo -e "\033[1;91m❌ Memory leaks detected :\033[0m"
			grep -E "definitely lost:|indirectly lost:|possibly lost:|still reachable:|suppressed:" $TEMPFILE
			((error_count++))
		else
			echo -e "\033[1;92m✅ No memory leaks detected.\033[0m"
		fi

		HEAP_USAGE=$(grep -E "total heap usage:|in use at exit:" $TEMPFILE)
		if [ -n "$HEAP_USAGE" ]; then
			echo -e "\033[1;94 Total heap usage :\033[0m"
			echo "$HEAP_USAGE"
		fi

		ERROR_SUMMARY=$(grep -E "ERROR SUMMARY:" $TEMPFILE)
		if [ -n "$ERROR_SUMMARY" ]; then
			echo -e "\033[1;94mERROR SUMMARY:\033[0m"
			echo "$ERROR_SUMMARY"
		fi

		rm $TEMPFILE
	done

	echo ""
	echo -e "\033[1;94m _______   ______   _______    _______       __        __\033[0m"
	echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|      \\ \\      / /\033[0m"
	echo -e "\033[1;94m   | |    | |___   |  |____      | |          \\ \\    / /\033[0m"
	echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |           \\ \\  / /\033[0m"
	echo -e "\033[1;94m   | |    | |____   _____| |     | |            \\ \\/ /\033[0m"
	echo -e "\033[1;94m   |_|    |______| |_______|     |_|             \\\__/\033[0m"
	echo ""
	echo -e "\t\t\033[1;93mGOOD ARGUMENTS VALGRIND.\033[0m"
	echo ""

	for i in "${!good_params[@]}"
	do
		TEMPFILE=$(mktemp)
		echo -e "\033[1;94mTEST VALGRIND $((i + 1)): ./$NAME ${good_params[i]}\033[1;93m"
		valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./$NAME ${good_params[i]} &> $TEMPFILE

		def_lost_bytes=$(grep "definitely lost:" $TEMPFILE | awk '{print $4}')
		ind_lost_bytes=$(grep "indirectly lost:" $TEMPFILE | awk '{print $4}')
		pos_lost_bytes=$(grep "possibly lost:" $TEMPFILE | awk '{print $4}')
		still_reach_bytes=$(grep "still reachable:" $TEMPFILE | awk '{print $4}')
		suppressed_bytes=$(grep "suppressed:" $TEMPFILE | awk '{print $4}')

		if [[ $def_lost_bytes -gt 0 || $ind_lost_bytes -gt 0 || $pos_lost_bytes -gt 0 || $still_reach_bytes -gt 0 || $suppressed_bytes -gt 0 ]]; then
			echo -e "\033[1;91m❌ Memory leaks detected :\033[0m"
			grep -E "definitely lost:|indirectly lost:|possibly lost:|still reachable:|suppressed:" $TEMPFILE
			((error_count++))
		else
			echo -e "\033[1;92m✅ No memory leaks detected.\033[0m"
		fi

		HEAP_USAGE=$(grep -E "total heap usage:|in use at exit:" $TEMPFILE)
		if [ -n "$HEAP_USAGE" ]; then
			echo -e "\033[1;9 Total heap usage :\033[0m"
			echo "$HEAP_USAGE"
		fi

		ERROR_SUMMARY=$(grep -E "ERROR SUMMARY:" $TEMPFILE)
		if [ -n "$ERROR_SUMMARY" ]; then
			echo -e "\033[1;94mERROR SUMMARY:\033[0m"
			echo "$ERROR_SUMMARY"
		fi

		rm $TEMPFILE
	done

	echo ""
	echo -e "\033[1;94m _______   ______   _______    _______       __        __  _\033[0m"
	echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|      \\ \\      / / | |\033[0m"
	echo -e "\033[1;94m   | |    | |___   |  |____      | |          \\ \\    / /  | |\033[0m"
	echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |           \\ \\  / /   | |\033[0m"
	echo -e "\033[1;94m   | |    | |____   _____| |     | |            \\ \\/ /    | |\033[0m"
	echo -e "\033[1;94m   |_|    |______| |_______|     |_|             \\__/     |_|\033[0m"
	echo ""
	echo -e "\t\t\033[1;93mBIG ARGUMENTS VALGRIND.\033[0m"
	echo ""

	for i in "${!big_params[@]}"
	do
		TEMPFILE=$(mktemp)
		echo -e "\033[1;94mTEST VALGRIND $((i + 1)): ./$NAME ${big_params[i]}\033[1;93m"
		valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes ./$NAME ${big_params[i]} &> $TEMPFILE

		def_lost_bytes=$(grep "definitely lost:" $TEMPFILE | awk '{print $4}')
		ind_lost_bytes=$(grep "indirectly lost:" $TEMPFILE | awk '{print $4}')
		pos_lost_bytes=$(grep "possibly lost:" $TEMPFILE | awk '{print $4}')
		still_reach_bytes=$(grep "still reachable:" $TEMPFILE | awk '{print $4}')
		suppressed_bytes=$(grep "suppressed:" $TEMPFILE | awk '{print $4}')

		if [[ $def_lost_bytes -gt 0 || $ind_lost_bytes -gt 0 || $pos_lost_bytes -gt 0 || $still_reach_bytes -gt 0 || $suppressed_bytes -gt 0 ]]; then
			echo -e "\033[1;91m❌ Memory leaks detected :\033[0m"
			grep -E "definitely lost:|indirectly lost:|possibly lost:|still reachable:|suppressed:" $TEMPFILE
			((error_count++))
		else
			echo -e "\033[1;92m✅ No memory leaks detected.\033[0m"
		fi

		HEAP_USAGE=$(grep -E "total heap usage:|in use at exit:" $TEMPFILE)
		if [ -n "$HEAP_USAGE" ]; then
			echo -e "\033[1;94 Total heap usage :\033[0m"
			echo "$HEAP_USAGE"
		fi

		ERROR_SUMMARY=$(grep -E "ERROR SUMMARY:" $TEMPFILE)
		if [ -n "$ERROR_SUMMARY" ]; then
			echo -e "\033[1;94mERROR SUMMARY:\033[0m"
			echo "$ERROR_SUMMARY"
		fi

		rm $TEMPFILE
	done
fi

echo -e "\033[1;94m _______  _   ___    _\033[0m"
echo -e "\033[1;94m|  ____| |_| |   \  | |\033[0m"
echo -e "\033[1;94m| |__     _  | |\ \ | |\033[0m"
echo -e "\033[1;94m|  __|   | | | | \ \| |\033[0m"
echo -e "\033[1;94m| |      | | | |  \ | |\033[0m"
echo -e "\033[1;94m|_|      |_| |_|   \__|\033[0m"
echo ""

if ((error_count == 0)); then
	echo -e "\033[1;92m✅  No error detected.\033[0m"
else
	echo -e "\n\033[1;91m❌ Total number of errors detected : $error_count\033[0m"
fi

echo -e "\033[1;94mTo complete the test run the program with this arguments\033[0m"
echo -e "\033[1;94m./$NAME 6 2 '5' 0\033[0m"
echo -e "\033[1;94m./$NAME 6 2 \"5\" 0\033[0m"

make fclean > /dev/null 2>&1

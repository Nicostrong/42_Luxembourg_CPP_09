# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_tester.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/20 14:38:53 by nfordoxc          #+#    #+#              #
#    Updated: 2025/03/20 16:02:41 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

paramsBad=(
	""
	" "					# Expression vide avec un espace
	"2 2 2 2"
	"tot + tata"		# Mots non valides
	"2 6 + 3a *"		# Caractère invalide dans un nombre
	"6 +"				# Pas assez d'opérandes
	"6 0 /"				# Division par zéro
	"4 4 4 +"			# Trop de nombres sans opérateurs suffisants
	"8 g 5 * 2 +"		# Lettre invalide dans l'expression
	"4 4 4 + +"			# Trop d'opérateurs
	"+ 3 4"				# Opérateur en premier
	"3 4 +"				# Devrait être valide (ajouté pour voir si le programme le bloque)
	"3.5 2 +"			# Nombre flottant invalide
	"2,3,+"				# Séparateur incorrect (virgule)
	"2147483647 1 +"	# Dépassement d'entier
	"10 0 +"			# nombre non valide
)

paramsGood=(
	"3 5 + 7 * 2 - 1 + 6 /"
	"7 8 * 7 * 4 - 1 + 9 / 5 +"
	"8 5 * 2 +"
	"3 4 +"
	"2 3 + 4 *"
	"8 5 - 3 /"
	"5 3 * 2 1 + /"
	"0 9 -"
	"6 2 / 3 * 5 +"
	"1 2 + 3 4 + *"
	"9 3 / 2 * 5 -"
	"2 2 2 2 2 2 + + + + +"
	"4 2 6 7 4 9 3 + * - / + *"
	"2 4 6 8 1 3 5 7 9 * - + - / * + -"
	"6 7 *"
	"8 5 * 2 / 3 + 6 2 * *"
	"2 9 6 * 2 / * 2 6 * -"
	"2 5 1 7 + * +"
	"1 6 5 4 3 + * + +"
)

answers=(
	"9"
	"48"
	"42"
	"7"
	"20"
	"1"
	"5"
	"-9"
	"14"
	"21"
	"1"
	"12"
	"8"
	"-2"
	"42"
	"276"
	"42"
	"42"
	"42"
)

error_count=0

make || { echo "Compilation failed"; exit 1;}

NAME="./RPN"

clear

echo -e "\033[1;94m _______   ______   _______    _______       _____\033[0m"
echo -e "\033[1;94m|__   __| |  ____| |   ____|  |__   __|     /     |\033[0m"
echo -e "\033[1;94m   | |    | |___   |  |____      | |       /  /|  |\033[0m"
echo -e "\033[1;94m   | |    |  ___|  |_____  |     | |      /__/ |  |\033[0m"
echo -e "\033[1;94m   | |    | |____   _____| |     | |           |  |\033[0m"
echo -e "\033[1;94m   |_|    |______| |_______|     |_|           |__|\033[0m"
echo ""
echo -e "\t\t\033[1;93mBAD ARGUMENT.\033[0m"
echo ""

for i in "${!paramsBad[@]}"
do
	TEMPFILE=$(mktemp)
	echo -e "\033[1;94mTEST $((i + 1)): $NAME ${paramsBad[i]}\033[1;93m"
	$NAME ${paramsBad[i]} &> $TEMPFILE

	if grep -q "Error" $TEMPFILE || grep -q "Usage" $TEMPFILE; then
		echo -e "\033[1;92m[✅] OK => Bad argument catching.\033[0m"
	else
		echo -e "\033[1;91m[❌] KO => Bad argument not catching.\033[0m"
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
echo -e "\t\t\033[1;93mGOOD ARGUMENT.\033[0m"
echo ""

for i in "${!paramsGood[@]}"
do
	expected="${answers[$i]}"

	echo -e "\033[1;94mTEST $((i + 1)): $NAME \"${paramsGood[i]}\“\033[1;93m"
	output=$($NAME "${paramsGood[i]}")

	if [[ "$output" == "$expected" ]]; then
		echo -e "[✅] Test passed: \"${paramsGood[i]}\" => $output"
	else
		echo -e "[❌] Test failed: \"${paramsGood[i]}\" (expected: '$expected', got: '$output')"
		((error_count++))
	fi

done

echo -e "\033[1;94m _______  _   ___    _\033[0m"
echo -e "\033[1;94m|  ____| |_| |   \  | |\033[0m"
echo -e "\033[1;94m| |__     _  | |\ \ | |\033[0m"
echo -e "\033[1;94m|  __|   | | | | \ \| |\033[0m"
echo -e "\033[1;94m| |      | | | |  \ | |\033[0m"
echo -e "\033[1;94m|_|      |_| |_|   \__|\033[0m"
echo ""

if ((error_count == 0)); then
	echo -e "\033[1;92m[✅] Aucune erreur détectée.\033[0m"
else
	echo -e "\n\033[1;91m[❌] Nombre total d'erreurs détectées : $error_count\033[0m"
fi

make fclean > /dev/null 2>&1
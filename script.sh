#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <command> <trie_type> [additional arguments]"
    exit 1
fi

command=$1
trie_type=$2
echo "in the script"

case $command in
    inserer)
        echo "in the good case"
        ./main2 "inserer" "$trie_type" "$3" 
        echo "call finish"
        ;;
    fusion)
        ./main2 fusion "$trie_type" "$3" "$4"
        ;;
    suppression)
        ./main2 suppression "$trie_type" "$3"
        ;;
    listeMots)
        ./main2 listeMots "$trie_type" "$3"
        ;;
    profondeurMoyenne)
        ./main2 profondeurMoyenne "$trie_type" "$3"
        ;;
    prefixe)
        ./main2 prefixe "$trie_type" "$3" "$4"
        ;;
    *)
        echo "Unknown command: $command"
        exit 1
        ;;
esac
